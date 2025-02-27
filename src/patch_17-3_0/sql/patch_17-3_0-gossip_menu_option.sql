DELETE FROM `gossip_menu_option` WHERE `MenuID` = 421 AND `OptionID` = 8;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 435 AND `OptionID` = 12;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 751 AND `OptionID` = 7;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 1942 AND `OptionID` = 8;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 1951 AND `OptionID` IN (11, 14);
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 2121 AND `OptionID` = 10;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 2168 AND `OptionID` = 8;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 2351 AND `OptionID` = 6;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 2352 AND `OptionID` = 11;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 3284 AND `OptionID` = 8;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 3330 AND `OptionID` = 7;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 3355 AND `OptionID` = 8;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 3532 AND `OptionID` = 8;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 3558 AND `OptionID` = 8;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 3572 AND `OptionID` = 6;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 7667 AND `OptionID` = 8;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 7788 AND `OptionID` = 7;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 8138 AND `OptionID` = 8;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 8205 AND `OptionID` = 8;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 10056 AND `OptionID` = 11;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 10078 AND `OptionID` = 8;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 10265 AND `OptionID` = 11;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 10767 AND `OptionID` = 8;
DELETE FROM `gossip_menu_option` WHERE `MenuID` = 10769 AND `OptionID` = 2;
INSERT INTO `gossip_menu_option` (`MenuID`, `OptionID`, `OptionIcon`, `OptionText`, `OptionBroadcastTextID`, `OptionType`, `OptionNpcFlag`, `ActionMenuID`, `ActionPoiID`, `BoxCoded`, `BoxMoney`, `BoxText`, `BoxBroadcastTextID`, `VerifiedBuild`) VALUES
(421, 8, 0, 'Inscription', 48811, 1, 1, 10010, 13, 0, 0, '', 0, 0),
(435, 12, 0, 'Barber', 45376, 1, 1, 10011, 30, 0, 0, '', 0, 0),
(751, 7, 0, 'Inscription', 48811, 1, 1, 10021, 296, 0, 0, '', 0, 0),
(1942, 8, 0, 'Inscription', 48811, 1, 1, 10017, 189, 0, 0, '', 0, 0),
(1951, 11, 0, 'Barber', 45376, 1, 1, 10018, 188, 0, 0, '', 0, 0),
(1951, 14, 0, 'Lexicon of Power', 32998, 1, 1, 10205, 189, 0, 0, '', 0, 0),
(2121, 10, 0, 'Barber', 45376, 1, 1, 10014, 60, 0, 0, '', 0, 0),
(2168, 8, 0, 'Inscription', 48811, 1, 1, 10013, 72, 0, 0, '', 0, 0),
(2351, 6, 0, 'Inscription', 48811, 1, 1, 10015, 107, 0, 0, '', 0, 0),
(2352, 11, 0, 'Lexicon of Power', 32998, 1, 1, 10205, 107, 0, 0, '', 0, 0),
(3284, 8, 0, 'Inscription', 48811, 1, 1, 10017, 189, 0, 0, '', 0, 0),
(3330, 7, 0, 'Inscription', 48811, 1, 1, 10021, 296, 0, 0, '', 0, 0),
(3355, 8, 0, 'Inscription', 48811, 1, 1, 10822, 344, 0, 0, '', 0, 0),
(3532, 8, 0, 'Inscription', 48811, 1, 1, 10010, 13, 0, 0, '', 0, 0),
(3558, 8, 0, 'Inscription', 48811, 1, 1, 10013, 72, 0, 0, '', 0, 0),
(3572, 6, 0, 'Inscription', 48811, 1, 1, 10015, 107, 0, 0, '', 0, 0),
(7667, 8, 0, 'Inscription', 48811, 1, 1, 10022, 376, 0, 0, '', 0, 0),
(7788, 7, 0, 'Inscription', 48811, 1, 1, 10016, 212, 0, 0, '', 0, 0),
(8138, 8, 0, 'Inscription', 48811, 1, 1, 10016, 212, 0, 0, '', 0, 0),
(8205, 8, 0, 'Inscription', 48811, 1, 1, 10022, 376, 0, 0, '', 0, 0),
(10056, 11, 0, 'Lexicon of Power', 32998, 1, 1, 10205, 148, 0, 0, '', 0, 0),
(10078, 8, 0, 'Inscription', 48811, 1, 1, 10067, 148, 0, 0, '', 0, 0),
(10265, 11, 0, 'Lexicon of Power', 32998, 1, 1, 10205, 107, 0, 0, '', 0, 0),
(10767, 8, 0, 'Inscription', 48811, 1, 1, 10751, 344, 0, 0, '', 0, 0),
(10769, 2, 0, 'Barber', 45376, 1, 1, 10739, 320, 0, 0, '', 0, 0);
