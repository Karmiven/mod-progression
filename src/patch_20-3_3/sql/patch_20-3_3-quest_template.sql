UPDATE `quest_template` SET `RewardItem1`=49426 WHERE `ID` IN (
    24788 -- Daily Heroic Random (1st)
);

UPDATE `quest_template` SET `RewardItem1`=47241 WHERE `ID` IN (
    24789, -- Daily Heroic Random (Nth)
    24790 -- Daily Normal Random (1st)
);

UPDATE `quest_template` SET `RewardItem1`=47241 WHERE `ID` IN (
    13240, -- Timear Foresees Centrifuge Constructs in your Future!
    13241, -- Timear Foresees Ymirjar Berserkers in your Future!
    13243, -- Timear Foresees Infinite Agents in your Future!
    13244, -- Timear Foresees Titanium Vanguards in your Future!
    13245, -- Proof of Demise: Ingvar the Plunderer
    13246, -- Proof of Demise: Keristrasza
    13247, -- Proof of Demise: Ley-Guardian Eregos
    13248, -- Proof of Demise: King Ymiron
    13249, -- Proof of Demise: The Prophet Tharon'ja
    13250, -- Proof of Demise: Gal'darah
    13251, -- Proof of Demise: Mal'Ganis
    13252, -- Proof of Demise: Sjonnir The Ironshaper
    13253, -- Proof of Demise: Loken
    13254, -- Proof of Demise: Anub'arak
    13255, -- Proof of Demise: Herald Volazj
    13256, -- Proof of Demise: Cyanigosa
    14199 -- Proof of Demise: The Black Knight
);

UPDATE `quest_template` SET `Flags`=`Flags`|16384 WHERE `ID` IN (
    13240, -- Timear Foresees Centrifuge Constructs in your Future!
    13241, -- Timear Foresees Ymirjar Berserkers in your Future!
    13243, -- Timear Foresees Infinite Agents in your Future!
    13244, -- Timear Foresees Titanium Vanguards in your Future!
    13245, -- Proof of Demise: Ingvar the Plunderer
    13246, -- Proof of Demise: Keristrasza
    13247, -- Proof of Demise: Ley-Guardian Eregos
    13248, -- Proof of Demise: King Ymiron
    13249, -- Proof of Demise: The Prophet Tharon'ja
    13250, -- Proof of Demise: Gal'darah
    13251, -- Proof of Demise: Mal'Ganis
    13252, -- Proof of Demise: Sjonnir The Ironshaper
    13253, -- Proof of Demise: Loken
    13254, -- Proof of Demise: Anub'arak
    13255, -- Proof of Demise: Herald Volazj
    13256, -- Proof of Demise: Cyanigosa
    13256
);

UPDATE `quest_template` SET `QuestCompletionLog`='Return to Archmage Timear in Crystalsong Forest.' WHERE `ID` IN (
    13240, -- Timear Foresees Centrifuge Constructs in your Future!
    13241, -- Timear Foresees Ymirjar Berserkers in your Future!
    13243, -- Timear Foresees Infinite Agents in your Future!
    13244 -- Timear Foresees Titanium Vanguards in your Future!
);

UPDATE `quest_template` SET `QuestCompletionLog`='Return to Archmage Lan\'dalock at Forlorn Woods in Crystalsong Forest.' WHERE `ID` IN (
    13245, -- Proof of Demise: Ingvar the Plunderer
    13246, -- Proof of Demise: Keristrasza
    13247, -- Proof of Demise: Ley-Guardian Eregos
    13248, -- Proof of Demise: King Ymiron
    13249, -- Proof of Demise: The Prophet Tharon'ja
    13250, -- Proof of Demise: Gal'darah
    13251, -- Proof of Demise: Mal'Ganis
    13252, -- Proof of Demise: Sjonnir The Ironshaper
    13253, -- Proof of Demise: Loken
    13254, -- Proof of Demise: Anub'arak
    13255, -- Proof of Demise: Herald Volazj
    13256 -- Proof of Demise: Cyanigosa
);
