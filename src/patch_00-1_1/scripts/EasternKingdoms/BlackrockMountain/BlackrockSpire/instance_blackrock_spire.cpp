/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "AreaTriggerScript.h"
#include "InstanceMapScript.h"
#include "InstanceScript.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "blackrock_spire.h"

uint32 const DragonspireMobs[3] = { NPC_BLACKHAND_DREADWEAVER, NPC_BLACKHAND_SUMMONER, NPC_BLACKHAND_VETERAN };

enum EventIds
{
    EVENT_DRAGONSPIRE_ROOM_STORE           = 1,
    EVENT_DRAGONSPIRE_ROOM_CHECK           = 2,

    EVENT_SOLAKAR_WAVE                     = 3,

    EVENT_DRAGONSPINE_DOOR_STAGE_1         = 4,
    EVENT_DRAGONSPINE_DOOR_STAGE_2         = 5,
    EVENT_DRAGONSPINE_DOOR_STAGE_3         = 6,
    EVENT_DRAGONSPINE_DOOR_STAGE_4         = 7
};

enum Timers
{
    TIMER_SOLAKAR_WAVE = 30000
};

enum SolakarWaves
{
    MAX_WAVE_COUNT = 5
};

Position SolakarPosLeftProgression  = Position(78.0f, -280.0f, 93.0f, 3.0f * M_PI / 2.0);
Position SolakarPosRightProgression = Position(84.0f, -280.0f, 93.0f, 3.0f * M_PI / 2.0);
Position SolakarPosBossProgression  = Position(80.0f, -280.0f, 93.0f, 3.0f * M_PI / 2.0);

enum Texts
{
    SAY_NEFARIUS_REND_WIPE      = 11,
    SAY_SOLAKAR_FIRST_HATCHER   = 0,
    SAY_SCARSHIELD_INF_WHISPER  = 0
};

MinionData const minionData[] =
{
    { NPC_CHROMATIC_ELITE_GUARD, DATA_GENERAL_DRAKKISATH },
    { 0,                         0,                      }
};

DoorData const doorData[] =
{
    { GO_GYTH_EXIT_DOOR,    DATA_WARCHIEF_REND_BLACKHAND,  DOOR_TYPE_PASSAGE },
    { GO_DRAKKISATH_DOOR_1, DATA_GENERAL_DRAKKISATH,       DOOR_TYPE_PASSAGE },
    { GO_DRAKKISATH_DOOR_2, DATA_GENERAL_DRAKKISATH,       DOOR_TYPE_PASSAGE },
    { 0,                 0,          DOOR_TYPE_ROOM,                         } // END
};

class instance_blackrock_spire : public InstanceMapScript
{
public:
    instance_blackrock_spire() : InstanceMapScript(BRSScriptName, 229) { }

    struct instance_blackrock_spireMapScript : public InstanceScript
    {
        uint32 CurrentSolakarWave = 0;
        uint32 SolakarState       = NOT_STARTED; // there should be a global instance encounter state, where is it?
        GuidVector SolakarSummons;
        uint32 VaelastraszState   = NOT_STARTED;
        uint32 UbrsDoorState      = NOT_STARTED;

        instance_blackrock_spireMapScript(InstanceMap* map) : InstanceScript(map)
        {
            SetHeaders(DataHeader);
            SetBossNumber(EncounterCount);
            LoadMinionData(minionData);
            LoadDoorData(doorData);
            CurrentSolakarWave = 0;
            SolakarState       = NOT_STARTED;
            SolakarSummons.clear();
            VaelastraszState   = NOT_STARTED;
        }

        void CreatureLooted(Creature* creature, LootType loot) override
        {
            switch (creature->GetEntry())
            {
                case NPC_THE_BEAST:
                    if (loot == LOOT_SKINNING)
                    {
                        creature->CastSpell(creature, SPELL_FINKLE_IS_EINHORN, true);
                    }
                    break;
            }
        }

        void OnCreatureCreate(Creature* creature) override
        {
            switch (creature->GetEntry())
            {
                case NPC_UROK_MAGUS:
                    [[fallthrough]];
                case NPC_UROK_ENFORCER:
                    UrokMobs.push_back(creature->GetGUID());
                    break;
                case NPC_HIGHLORD_OMOKK:
                    HighlordOmokk = creature->GetGUID();
                    break;
                case NPC_SHADOW_HUNTER_VOSHGAJIN:
                    ShadowHunterVoshgajin = creature->GetGUID();
                    break;
                case NPC_WARMASTER_VOONE:
                    WarMasterVoone = creature->GetGUID();
                    break;
                case NPC_MOTHER_SMOLDERWEB:
                    MotherSmolderweb = creature->GetGUID();
                    break;
                case NPC_UROK_DOOMHOWL:
                    UrokDoomhowl = creature->GetGUID();
                    break;
                case NPC_QUARTERMASTER_ZIGRIS:
                    QuartermasterZigris = creature->GetGUID();
                    break;
                case NPC_GIZRUL_THE_SLAVENER:
                    GizrultheSlavener = creature->GetGUID();
                    break;
                case NPC_HALYCON:
                    Halycon = creature->GetGUID();
                    break;
                case NPC_OVERLORD_WYRMTHALAK:
                    OverlordWyrmthalak = creature->GetGUID();
                    break;
                case NPC_PYROGAURD_EMBERSEER:
                    PyroguardEmberseer = creature->GetGUID();
                    if (GetBossState(DATA_PYROGAURD_EMBERSEER) == DONE)
                        creature->DisappearAndDie();
                    break;
                case NPC_WARCHIEF_REND_BLACKHAND:
                    if (GetBossState(DATA_GYTH) != IN_PROGRESS)
                    {
                        WarchiefRendBlackhand = creature->GetGUID();
                    }

                    if (GetBossState(DATA_GYTH) == DONE)
                        creature->DisappearAndDie();
                    break;
                case NPC_GYTH:
                    Gyth = creature->GetGUID();
                    break;
                case NPC_THE_BEAST:
                    TheBeast = creature->GetGUID();
                    break;
                case NPC_GENERAL_DRAKKISATH:
                    GeneralDrakkisath = creature->GetGUID();
                    break;
                case NPC_LORD_VICTOR_NEFARIUS:
                    LordVictorNefarius = creature->GetGUID();
                    if (GetBossState(DATA_GYTH) == DONE)
                        creature->DisappearAndDie();
                    break;
                case NPC_FINKLE_EINHORN:
                    creature->AI()->Talk(SAY_FINKLE_GANG);
                    break;
                case NPC_CHROMATIC_ELITE_GUARD:
                    AddMinion(creature);
                    break;
            }
        }

        void OnGameObjectCreate(GameObject* go) override
        {
            switch (go->GetEntry())
            {
                case GO_EMBERSEER_IN:
                    go_emberseerin = go->GetGUID();
                    HandleGameObject(ObjectGuid::Empty, GetBossState(DATA_DRAGONSPIRE_ROOM) == DONE, go);
                    break;
                case GO_DOORS:
                    go_doors = go->GetGUID();
                    if (GetBossState(DATA_DRAGONSPIRE_ROOM) == DONE)
                        HandleGameObject(ObjectGuid::Empty, true, go);
                    break;
                case GO_EMBERSEER_OUT:
                    go_emberseerout = go->GetGUID();
                    if (GetBossState(DATA_PYROGAURD_EMBERSEER) == DONE)
                        HandleGameObject(ObjectGuid::Empty, true, go);
                    break;
                case GO_HALL_RUNE_1:
                    go_roomrunes[0] = go->GetGUID();
                    if (GetBossState(DATA_HALL_RUNE_1) == DONE)
                        HandleGameObject(ObjectGuid::Empty, false, go);
                    break;
                case GO_HALL_RUNE_2:
                    go_roomrunes[1] = go->GetGUID();
                    if (GetBossState(DATA_HALL_RUNE_2) == DONE)
                        HandleGameObject(ObjectGuid::Empty, false, go);
                    break;
                case GO_HALL_RUNE_3:
                    go_roomrunes[2] = go->GetGUID();
                    if (GetBossState(DATA_HALL_RUNE_3) == DONE)
                        HandleGameObject(ObjectGuid::Empty, false, go);
                    break;
                case GO_HALL_RUNE_4:
                    go_roomrunes[3] = go->GetGUID();
                    if (GetBossState(DATA_HALL_RUNE_4) == DONE)
                        HandleGameObject(ObjectGuid::Empty, false, go);
                    break;
                case GO_HALL_RUNE_5:
                    go_roomrunes[4] = go->GetGUID();
                    if (GetBossState(DATA_HALL_RUNE_5) == DONE)
                        HandleGameObject(ObjectGuid::Empty, false, go);
                    break;
                case GO_HALL_RUNE_6:
                    go_roomrunes[5] = go->GetGUID();
                    if (GetBossState(DATA_HALL_RUNE_6) == DONE)
                        HandleGameObject(ObjectGuid::Empty, false, go);
                    break;
                case GO_HALL_RUNE_7:
                    go_roomrunes[6] = go->GetGUID();
                    if (GetBossState(DATA_HALL_RUNE_7) == DONE)
                        HandleGameObject(ObjectGuid::Empty, false, go);
                    break;
                case GO_EMBERSEER_RUNE_1:
                    go_emberseerrunes[0] = go->GetGUID();
                    if (GetBossState(DATA_PYROGAURD_EMBERSEER) == DONE)
                        HandleGameObject(ObjectGuid::Empty, false, go);
                    break;
                case GO_EMBERSEER_RUNE_2:
                    go_emberseerrunes[1] = go->GetGUID();
                    if (GetBossState(DATA_PYROGAURD_EMBERSEER) == DONE)
                        HandleGameObject(ObjectGuid::Empty, false, go);
                    break;
                case GO_EMBERSEER_RUNE_3:
                    go_emberseerrunes[2] = go->GetGUID();
                    if (GetBossState(DATA_PYROGAURD_EMBERSEER) == DONE)
                        HandleGameObject(ObjectGuid::Empty, false, go);
                    break;
                case GO_EMBERSEER_RUNE_4:
                    go_emberseerrunes[3] = go->GetGUID();
                    if (GetBossState(DATA_PYROGAURD_EMBERSEER) == DONE)
                        HandleGameObject(ObjectGuid::Empty, false, go);
                    break;
                case GO_EMBERSEER_RUNE_5:
                    go_emberseerrunes[4] = go->GetGUID();
                    if (GetBossState(DATA_PYROGAURD_EMBERSEER) == DONE)
                        HandleGameObject(ObjectGuid::Empty, false, go);
                    break;
                case GO_EMBERSEER_RUNE_6:
                    go_emberseerrunes[5] = go->GetGUID();
                    if (GetBossState(DATA_PYROGAURD_EMBERSEER) == DONE)
                        HandleGameObject(ObjectGuid::Empty, false, go);
                    break;
                case GO_EMBERSEER_RUNE_7:
                    go_emberseerrunes[6] = go->GetGUID();
                    if (GetBossState(DATA_PYROGAURD_EMBERSEER) == DONE)
                        HandleGameObject(ObjectGuid::Empty, false, go);
                    break;
                case GO_PORTCULLIS_ACTIVE:
                    go_portcullis_active = go->GetGUID();
                    if (GetBossState(DATA_GYTH) == DONE)
                        HandleGameObject(ObjectGuid::Empty, true, go);
                    break;
                case GO_UROK_PILE:
                    go_urokPile = go->GetGUID();
                    break;
                case GO_UROK_CIRCLE:
                    go_urokOgreCirles.push_back(go->GetGUID());
                    break;
                case GO_UROK_CHALLENGE:
                    go_urokChallenge = go->GetGUID();
                    break;
                case GO_DRAGONSPINE_DOOR:
                    go_dragonspineDoor = go->GetGUID();
                    if (UbrsDoorState == DONE)
                    {
                        HandleGameObject(ObjectGuid::Empty, true, go);
                    }
                    break;
                case GO_DARK_IRON_BRAZIER_1:
                    go_darkIronBraziers[0] = go->GetGUID();
                    if (UbrsDoorState == DONE)
                    {
                        HandleGameObject(ObjectGuid::Empty, true, go);
                    }
                    break;
                case GO_DARK_IRON_BRAZIER_2:
                    go_darkIronBraziers[1] = go->GetGUID();
                    if (UbrsDoorState == DONE)
                    {
                        HandleGameObject(ObjectGuid::Empty, true, go);
                    }
                    break;
                case GO_DARK_IRON_BRAZIER_3:
                    go_darkIronBraziers[2] = go->GetGUID();
                    if (UbrsDoorState == DONE)
                    {
                        HandleGameObject(ObjectGuid::Empty, true, go);
                    }
                    break;
                case GO_DARK_IRON_BRAZIER_4:
                    go_darkIronBraziers[3] = go->GetGUID();
                    if (UbrsDoorState == DONE)
                    {
                        HandleGameObject(ObjectGuid::Empty, true, go);
                    }
                    break;
                case GO_DARK_IRON_BRAZIER_5:
                    go_darkIronBraziers[4] = go->GetGUID();
                    if (UbrsDoorState == DONE)
                    {
                        HandleGameObject(ObjectGuid::Empty, true, go);
                    }
                    break;
                case GO_DARK_IRON_BRAZIER_6:
                    go_darkIronBraziers[5] = go->GetGUID();
                    if (UbrsDoorState == DONE)
                    {
                        HandleGameObject(ObjectGuid::Empty, true, go);
                    }
                    break;
                default:
                    break;
            }

            InstanceScript::OnGameObjectCreate(go);
        }

        bool SetBossState(uint32 type, EncounterState state) override
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            switch (type)
            {
                case DATA_WARCHIEF_REND_BLACKHAND:
                    if (state == FAIL)
                    {
                        if (Creature* rend = instance->GetCreature(WarchiefRendBlackhand))
                        {
                            rend->Respawn(true);
                        }

                        if (Creature* nefarius = instance->GetCreature(LordVictorNefarius))
                        {
                            nefarius->AI()->Talk(SAY_NEFARIUS_REND_WIPE);
                        }
                    }
                    break;
                default:
                    break;
            }

            return true;
        }

        void ProcessEvent(WorldObject* /*obj*/, uint32 eventId) override
        {
            switch (eventId)
            {
                case EVENT_PYROGUARD_EMBERSEER:
                    if (GetBossState(DATA_PYROGAURD_EMBERSEER) == NOT_STARTED)
                    {
                        if (Creature* Emberseer = instance->GetCreature(PyroguardEmberseer))
                            Emberseer->AI()->SetData(1, 1);
                    }
                    break;
                case EVENT_UROK_DOOMHOWL:
                    if (GetBossState(DATA_UROK_DOOMHOWL) == NOT_STARTED)
                    {
                        SetBossState(DATA_UROK_DOOMHOWL, IN_PROGRESS);
                        if (GameObject* pile = instance->GetGameObject(go_urokPile))
                        {
                            pile->SetLootState(GO_JUST_DEACTIVATED);
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
                case AREATRIGGER:
                    if (data == AREATRIGGER_DRAGONSPIRE_HALL)
                    {
                        if (GetBossState(DATA_DRAGONSPIRE_ROOM) != DONE)
                            Events.ScheduleEvent(EVENT_DRAGONSPIRE_ROOM_STORE, 1s);
                    }

                    if (data == DATA_DRAGONSPINE_DOOR)
                    {
                        if (UbrsDoorState == NOT_STARTED)
                        {
                            Events.ScheduleEvent(EVENT_DRAGONSPINE_DOOR_STAGE_1, 3s);
                        }
                    }
                    break;
                case DATA_SOLAKAR_FLAMEWREATH:
                    switch (data)
                    {
                        case IN_PROGRESS:
                            if (SolakarState == NOT_STARTED)
                            {
                                Events.ScheduleEvent(EVENT_SOLAKAR_WAVE, 500ms);
                            }
                            break;
                        case FAIL:
                            for (ObjectGuid const& guid : SolakarSummons)
                            {
                                if (Creature* creature = instance->GetCreature(guid))
                                {
                                    creature->DespawnOrUnsummon();
                                }
                            }
                            SolakarSummons.clear();
                            CurrentSolakarWave = 0;
                            SetData(DATA_SOLAKAR_FLAMEWREATH, NOT_STARTED);
                            break;
                        case DONE:
                            break;
                    }
                    SolakarState = data;
                    break;
                case DATA_VAELASTRASZ:
                    VaelastraszState = data;
                    break;
                case DATA_UROK_DOOMHOWL:
                    if (data == FAIL)
                    {
                        if (GetBossState(DATA_UROK_DOOMHOWL) != NOT_STARTED)
                        {
                            SetBossState(DATA_UROK_DOOMHOWL, NOT_STARTED);
                            if (GameObject* challenge = instance->GetGameObject(go_urokChallenge))
                            {
                                challenge->Delete();
                            }
                            if (GameObject* pile = instance->GetGameObject(go_urokPile))
                            {
                                pile->SetLootState(GO_READY);
                                pile->Respawn();
                            }
                            for (auto const& circleGUID : go_urokOgreCirles)
                            {
                                if (GameObject* circle = instance->GetGameObject(circleGUID))
                                {
                                    circle->Delete();
                                }
                            }
                            for (auto const& mobGUID : UrokMobs)
                            {
                                if (Creature* mob = instance->GetCreature(mobGUID))
                                {
                                    mob->DespawnOrUnsummon();
                                }
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        uint32 GetData(uint32 type) const override
        {
            if (type == DATA_SOLAKAR_FLAMEWREATH)
            {
                return SolakarState;
            }
            else if (type == DATA_VAELASTRASZ)
            {
                return VaelastraszState;
            }
            else
            {
                return InstanceScript::GetData(type);
            }
        }

        void SummonSolakarWave(uint8 number)
        {
            if (number < MAX_WAVE_COUNT)
            {
                if (Creature* summon = instance->SummonCreature(NPC_ROOKERY_GUARDIAN, SolakarPosLeftProgression))
                {
                    SolakarSummons.push_back(summon->GetGUID());
                }

                if (Creature* summon = instance->SummonCreature(NPC_ROOKERY_HATCHER, SolakarPosRightProgression))
                {
                    SolakarSummons.push_back(summon->GetGUID());
                }

                if (number == 0)
                {
                    if (Creature* FirstHatcher = instance->GetCreature(SolakarSummons.back())) // works because we spawned a hatcher second
                    {
                        FirstHatcher->AI()->Talk(SAY_SOLAKAR_FIRST_HATCHER);
                    }
                }
            }
            else if (number == MAX_WAVE_COUNT)
            {
                if (Creature* summon = instance->SummonCreature(NPC_SOLAKAR, SolakarPosBossProgression))
                {
                    SolakarSummons.push_back(summon->GetGUID());
                }
            }
        }

        ObjectGuid GetGuidData(uint32 type) const override
        {
            switch (type)
            {
                case DATA_HIGHLORD_OMOKK:
                    return HighlordOmokk;
                case DATA_SHADOW_HUNTER_VOSHGAJIN:
                    return ShadowHunterVoshgajin;
                case DATA_WARMASTER_VOONE:
                    return WarMasterVoone;
                case DATA_MOTHER_SMOLDERWEB:
                    return MotherSmolderweb;
                case DATA_UROK_DOOMHOWL:
                    return UrokDoomhowl;
                case DATA_QUARTERMASTER_ZIGRIS:
                    return QuartermasterZigris;
                case DATA_GIZRUL_THE_SLAVENER:
                    return GizrultheSlavener;
                case DATA_HALYCON:
                    return Halycon;
                case DATA_OVERLORD_WYRMTHALAK:
                    return OverlordWyrmthalak;
                case DATA_PYROGAURD_EMBERSEER:
                    return PyroguardEmberseer;
                case DATA_WARCHIEF_REND_BLACKHAND:
                    return WarchiefRendBlackhand;
                case DATA_GYTH:
                    return Gyth;
                case DATA_THE_BEAST:
                    return TheBeast;
                case DATA_GENERAL_DRAKKISATH:
                    return GeneralDrakkisath;
                case GO_EMBERSEER_IN:
                    return go_emberseerin;
                case GO_DOORS:
                    return go_doors;
                case GO_EMBERSEER_OUT:
                    return go_emberseerout;
                case GO_HALL_RUNE_1:
                    return go_roomrunes[0];
                case GO_HALL_RUNE_2:
                    return go_roomrunes[1];
                case GO_HALL_RUNE_3:
                    return go_roomrunes[2];
                case GO_HALL_RUNE_4:
                    return go_roomrunes[3];
                case GO_HALL_RUNE_5:
                    return go_roomrunes[4];
                case GO_HALL_RUNE_6:
                    return go_roomrunes[5];
                case GO_HALL_RUNE_7:
                    return go_roomrunes[6];
                case GO_EMBERSEER_RUNE_1:
                    return go_emberseerrunes[0];
                case GO_EMBERSEER_RUNE_2:
                    return go_emberseerrunes[1];
                case GO_EMBERSEER_RUNE_3:
                    return go_emberseerrunes[2];
                case GO_EMBERSEER_RUNE_4:
                    return go_emberseerrunes[3];
                case GO_EMBERSEER_RUNE_5:
                    return go_emberseerrunes[4];
                case GO_EMBERSEER_RUNE_6:
                    return go_emberseerrunes[5];
                case GO_EMBERSEER_RUNE_7:
                    return go_emberseerrunes[6];
                case GO_PORTCULLIS_ACTIVE:
                    return go_portcullis_active;
                case GO_UROK_PILE:
                    return go_urokPile;
                case GO_UROK_CHALLENGE:
                    return go_urokChallenge;
                case GO_DRAGONSPINE_DOOR:
                    return go_dragonspineDoor;
                case GO_DARK_IRON_BRAZIER_1:
                    return go_darkIronBraziers[0];
                case GO_DARK_IRON_BRAZIER_2:
                    return go_darkIronBraziers[1];
                case GO_DARK_IRON_BRAZIER_3:
                    return go_darkIronBraziers[2];
                case GO_DARK_IRON_BRAZIER_4:
                    return go_darkIronBraziers[3];
                case GO_DARK_IRON_BRAZIER_5:
                    return go_darkIronBraziers[4];
                case GO_DARK_IRON_BRAZIER_6:
                    return go_darkIronBraziers[5];
                default:
                    break;
            }

            return ObjectGuid::Empty;
        }

        void Update(uint32 diff) override
        {
            Events.Update(diff);

            while (uint32 eventId = Events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DRAGONSPIRE_ROOM_STORE:
                        Dragonspireroomstore();
                        Events.ScheduleEvent(EVENT_DRAGONSPIRE_ROOM_CHECK, 3s);
                        break;
                    case EVENT_DRAGONSPIRE_ROOM_CHECK:
                        Dragonspireroomcheck();
                        if ((GetBossState(DATA_DRAGONSPIRE_ROOM) != DONE))
                            Events.ScheduleEvent(EVENT_DRAGONSPIRE_ROOM_CHECK, 3s);
                        break;
                    case EVENT_SOLAKAR_WAVE:
                        SummonSolakarWave(CurrentSolakarWave);
                        if (CurrentSolakarWave < MAX_WAVE_COUNT)
                        {
                            Events.ScheduleEvent(EVENT_SOLAKAR_WAVE, TIMER_SOLAKAR_WAVE);
                            CurrentSolakarWave++;
                        }
                        break;
                    case EVENT_DRAGONSPINE_DOOR_STAGE_1:
                        UbrsDoorState = IN_PROGRESS;
                        if (GameObject* go = instance->GetGameObject(go_darkIronBraziers[0]))
                        {
                            go->SetGoState(GO_STATE_ACTIVE);
                        }
                        if (GameObject* go = instance->GetGameObject(go_darkIronBraziers[1]))
                        {
                            go->SetGoState(GO_STATE_ACTIVE);
                        }

                        Events.ScheduleEvent(EVENT_DRAGONSPINE_DOOR_STAGE_2, 3s);
                        break;
                    case EVENT_DRAGONSPINE_DOOR_STAGE_2:
                        if (GameObject* go = instance->GetGameObject(go_darkIronBraziers[2]))
                        {
                            go->SetGoState(GO_STATE_ACTIVE);
                        }
                        if (GameObject* go = instance->GetGameObject(go_darkIronBraziers[3]))
                        {
                            go->SetGoState(GO_STATE_ACTIVE);
                        }

                        Events.ScheduleEvent(EVENT_DRAGONSPINE_DOOR_STAGE_3, 3s);
                        break;
                    case EVENT_DRAGONSPINE_DOOR_STAGE_3:
                        if (GameObject* go = instance->GetGameObject(go_darkIronBraziers[4]))
                        {
                            go->SetGoState(GO_STATE_ACTIVE);
                        }
                        if (GameObject* go = instance->GetGameObject(go_darkIronBraziers[5]))
                        {
                            go->SetGoState(GO_STATE_ACTIVE);
                        }

                        Events.ScheduleEvent(EVENT_DRAGONSPINE_DOOR_STAGE_4, 3s);
                        break;
                    case EVENT_DRAGONSPINE_DOOR_STAGE_4:
                        if (GameObject* go = instance->GetGameObject(go_dragonspineDoor))
                        {
                            go->SetGoState(GO_STATE_ACTIVE);
                        }

                        UbrsDoorState = DONE;
                        break;
                    default:
                        break;
                }
            }
        }

        void Dragonspireroomstore()
        {

            for (uint8 i = 0; i < 7; ++i)
            {
                // Refresh the creature list
                runecreaturelist[i].clear();

                if (GameObject* rune = instance->GetGameObject(go_roomrunes[i]))
                {
                    for (uint8 j = 0; j < 3; ++j)
                    {
                        std::list<Creature*> creatureList;
                        GetCreatureListWithEntryInGrid(creatureList, rune, DragonspireMobs[j], 15.0f);
                        for (std::list<Creature*>::iterator itr = creatureList.begin(); itr != creatureList.end(); ++itr)
                        {
                            if (Creature* creature = *itr)
                            {
                                runecreaturelist[i].push_back(creature->GetGUID());
                            }
                        }
                    }
                }
            }
        }

        void Dragonspireroomcheck()
        {
            Creature* mob = nullptr;
            GameObject* rune = nullptr;

            for (uint8 i = 0; i < 7; ++i)
            {
                bool _mobAlive = false;
                rune = instance->GetGameObject(go_roomrunes[i]);
                if (!rune)
                    continue;

                if (rune->GetGoState() == GO_STATE_ACTIVE)
                {
                    for (ObjectGuid const& guid : runecreaturelist[i])
                    {
                        mob = instance->GetCreature(guid);
                        if (mob && mob->IsAlive())
                            _mobAlive = true;
                    }
                }

                if (!_mobAlive && rune->GetGoState() == GO_STATE_ACTIVE)
                {
                    HandleGameObject(ObjectGuid::Empty, false, rune);

                    switch (rune->GetEntry())
                    {
                        case GO_HALL_RUNE_1:
                            SetBossState(DATA_HALL_RUNE_1, DONE);
                            break;
                        case GO_HALL_RUNE_2:
                            SetBossState(DATA_HALL_RUNE_2, DONE);
                            break;
                        case GO_HALL_RUNE_3:
                            SetBossState(DATA_HALL_RUNE_3, DONE);
                            break;
                        case GO_HALL_RUNE_4:
                            SetBossState(DATA_HALL_RUNE_4, DONE);
                            break;
                        case GO_HALL_RUNE_5:
                            SetBossState(DATA_HALL_RUNE_5, DONE);
                            break;
                        case GO_HALL_RUNE_6:
                            SetBossState(DATA_HALL_RUNE_6, DONE);
                            break;
                        case GO_HALL_RUNE_7:
                            SetBossState(DATA_HALL_RUNE_7, DONE);
                            break;
                        default:
                            break;
                    }
                }
            }

            if (GetBossState(DATA_HALL_RUNE_1) == DONE && GetBossState(DATA_HALL_RUNE_2) == DONE && GetBossState(DATA_HALL_RUNE_3) == DONE &&
                    GetBossState(DATA_HALL_RUNE_4) == DONE && GetBossState(DATA_HALL_RUNE_5) == DONE && GetBossState(DATA_HALL_RUNE_6) == DONE &&
                    GetBossState(DATA_HALL_RUNE_7) == DONE)
            {
                SetBossState(DATA_DRAGONSPIRE_ROOM, DONE);
                if (GameObject* door1 = instance->GetGameObject(go_emberseerin))
                    HandleGameObject(ObjectGuid::Empty, true, door1);
                if (GameObject* door2 = instance->GetGameObject(go_doors))
                    HandleGameObject(ObjectGuid::Empty, true, door2);
                if (GameObject* door3 = instance->GetGameObject(go_emberseerin))
                    HandleGameObject(ObjectGuid::Empty, true, door3);
            }
        }

    protected:
        EventMap Events;
        ObjectGuid HighlordOmokk;
        ObjectGuid ShadowHunterVoshgajin;
        ObjectGuid WarMasterVoone;
        ObjectGuid MotherSmolderweb;
        ObjectGuid UrokDoomhowl;
        ObjectGuid QuartermasterZigris;
        ObjectGuid GizrultheSlavener;
        ObjectGuid Halycon;
        ObjectGuid OverlordWyrmthalak;
        ObjectGuid PyroguardEmberseer;
        ObjectGuid WarchiefRendBlackhand;
        ObjectGuid Gyth;
        ObjectGuid LordVictorNefarius;
        ObjectGuid TheBeast;
        ObjectGuid GeneralDrakkisath;
        ObjectGuid go_emberseerin;
        ObjectGuid go_doors;
        ObjectGuid go_emberseerout;
        ObjectGuid go_blackrockaltar;
        ObjectGuid go_roomrunes[7];
        ObjectGuid go_emberseerrunes[7];
        GuidVector runecreaturelist[7];
        ObjectGuid go_portcullis_active;
        ObjectGuid go_urokPile;
        ObjectGuid go_urokChallenge;
        ObjectGuid go_dragonspineDoor;
        ObjectGuid go_darkIronBraziers[6];
        std::vector<ObjectGuid> go_urokOgreCirles;
        std::vector<ObjectGuid> UrokMobs;
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_blackrock_spireMapScript(map);
    }
};

/*#####
# at_dragonspire_hall
#####*/

class at_dragonspire_hall : public AreaTriggerScript
{
public:
    at_dragonspire_hall() : AreaTriggerScript("at_dragonspire_hall") { }

    bool OnTrigger(Player* player, const AreaTrigger* /*at*/) override
    {
        if (player && player->IsAlive())
        {
            if (InstanceScript* instance = player->GetInstanceScript())
            {
                instance->SetData(AREATRIGGER, AREATRIGGER_DRAGONSPIRE_HALL);

                if (player->HasItemCount(ITEM_SEAL_OF_ASCENSION, 1))
                {
                    instance->SetData(AREATRIGGER, DATA_DRAGONSPINE_DOOR);
                }

                return true;
            }
        }

        return false;
    }
};

void AddSC_instance_blackrock_spire_progression()
{
    new instance_blackrock_spire();
    new at_dragonspire_hall();
}
