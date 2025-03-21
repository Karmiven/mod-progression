UPDATE `npc_trainer` SET `MoneyCost` = 6000000 WHERE `SpellID` = 33391;
DELETE FROM `npc_trainer` WHERE `ID` = 200002 AND `SpellID` IN (25286, 25288, 25289);
DELETE FROM `npc_trainer` WHERE `ID` = 200004 AND `SpellID` IN (25290, 25291, 25292, 31789);
DELETE FROM `npc_trainer` WHERE `ID` = 200006 AND `SpellID` IN (21849, 21850, 25297, 25298, 25299, 31018, 31709);
DELETE FROM `npc_trainer` WHERE `ID` = 200008 AND `SpellID` IN (23028, 25304, 25306, 25345, 27090, 27127, 28609, 28612);
DELETE FROM `npc_trainer` WHERE `ID` = 200010 AND `SpellID` IN (25307, 25309, 25311, 28610);
DELETE FROM `npc_trainer` WHERE `ID` = 200012 AND `SpellID` IN (21562, 21564, 25314, 25315, 25316, 27683);
DELETE FROM `npc_trainer` WHERE `ID` = 200014 AND `SpellID` IN (25294, 25295, 25296);
DELETE FROM `npc_trainer` WHERE `ID` = 200016 AND `SpellID` IN (25300, 25302, 31016);
DELETE FROM `npc_trainer` WHERE `ID` = 200018 AND `SpellID` IN (25357, 25361, 29228, 36936);
INSERT INTO `npc_trainer` (`ID`, `SpellID`, `MoneyCost`, `ReqSkillLine`, `ReqSkillRank`, `ReqLevel`, `ReqSpell`) VALUES
(200002, 25286, 60000, 0, 0, 60, 0),
(200002, 25288, 60000, 0, 0, 60, 0),
(200002, 25289, 65000, 0, 0, 60, 0),
(200004, 25290, 50000, 0, 0, 60, 0),
(200004, 25291, 50000, 0, 0, 60, 0),
(200004, 25292, 46000, 0, 0, 60, 0),
(200004, 31789, 4000, 0, 0, 14, 0),
(200006, 21849, 23000, 0, 0, 50, 0),
(200006, 21850, 34000, 0, 0, 60, 0),
(200006, 25297, 34000, 0, 0, 60, 0),
(200006, 25298, 34000, 0, 0, 60, 0),
(200006, 25299, 34000, 0, 0, 60, 0),
(200006, 31018, 30000, 0, 0, 60, 0),
(200006, 31709, 34000, 0, 0, 60, 0),
(200008, 23028, 38000, 0, 0, 56, 0),
(200008, 25304, 42000, 0, 0, 60, 0),
(200008, 25306, 42000, 0, 0, 62, 0),
(200008, 25345, 42000, 0, 0, 60, 0),
(200008, 27090, 150000, 0, 0, 70, 0),
(200008, 27127, 100000, 0, 0, 70, 0),
(200008, 28609, 42000, 0, 0, 60, 0),
(200008, 28612, 42000, 0, 0, 60, 0),
(200010, 25307, 26000, 0, 0, 62, 0),
(200010, 25309, 26000, 0, 0, 60, 0),
(200010, 25311, 26000, 0, 0, 60, 0),
(200010, 28610, 34000, 0, 0, 60, 0),
(200012, 21562, 28000, 0, 0, 48, 0),
(200012, 21564, 46000, 0, 0, 60, 0),
(200012, 25314, 65000, 0, 0, 60, 0),
(200012, 25315, 6500, 0, 0, 60, 0),
(200012, 25316, 6500, 0, 0, 60, 0),
(200012, 27683, 42000, 0, 0, 56, 0),
(200014, 25294, 50000, 0, 0, 60, 0),
(200014, 25295, 50000, 0, 0, 60, 0),
(200014, 25296, 50000, 0, 0, 60, 0),
(200016, 25300, 72000, 0, 0, 60, 0),
(200016, 25302, 50000, 0, 0, 60, 0),
(200016, 31016, 65000, 0, 0, 60, 0),
(200018, 25357, 6500, 0, 0, 60, 0),
(200018, 25361, 34000, 0, 0, 60, 0),
(200018, 29228, 65000, 0, 0, 60, 0),
(200018, 36936, 7000, 0, 0, 30, 0);
