DELETE FROM `creature_addon` WHERE `guid` IN (5200000, 5300000, 5300001, 5300002, 5300003);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `visibilityDistanceType`, `auras`) VALUES
(5200000, 520000000, 0, 0, 1, 0, 0, NULL), -- Lord Kazzak
-- Argent Guard <The Argent Dawn>
(5300000, 0, 0, 0, 1, 0, 0, NULL),
(5300001, 0, 0, 0, 1, 0, 0, NULL),
(5300002, 530000200, 0, 0, 1, 0, 0, NULL),
(5300003, 0, 0, 0, 1, 0, 0, NULL);

-- Alterac Valley
DELETE FROM `creature_addon` WHERE `guid` IN (5800003, 5800011, 5800013, 5800015, 5800017, 5800023, 5800024, 5800033, 5800035, 5800038, 5800045, 5800046, 5800059, 5800061, 5800064, 5800065, 5800067, 5800068, 5800074, 5800075, 5800100, 5800103, 5800109, 5800118, 5800121, 5800124, 5800126, 5800128, 5800130, 5800132, 5800135, 5800138, 5800147, 5800148, 5800151, 5800152, 5800155, 5800158, 5800160, 5800162, 5800164, 5800166);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `visibilityDistanceType`, `auras`) VALUES
-- Stormpike Guardsman
(5800003, 580000300, 0, 0, 1, 0, 0, ''),
(5800011, 580001100, 0, 0, 1, 0, 0, ''),
(5800013, 580001300, 0, 0, 1, 0, 0, ''),
(5800015, 580001500, 0, 0, 1, 0, 0, ''),
(5800017, 580001700, 0, 0, 1, 0, 0, ''),
(5800033, 580003300, 0, 0, 1, 0, 0, ''),
(5800035, 580003500, 0, 0, 1, 0, 0, ''),
(5800038, 580003800, 0, 0, 1, 0, 0, ''),
(5800046, 580004600, 0, 0, 1, 0, 0, ''),
(5800074, 580007400, 0, 0, 1, 0, 0, ''),
-- Stormpike Battleguard
(5800023, 580002300, 0, 0, 1, 0, 0, ''),
-- Stormpike Battleguard
(5800024, 580002400, 0, 0, 1, 0, 0, ''),
-- Stormpike Mine Layer
(5800045, 580004500, 0, 0, 1, 0, 0, ''),
-- Stormpike Mountaineer
(5800059, 580005900, 0, 0, 1, 0, 0, ''),
(5800065, 580006500, 0, 0, 1, 0, 0, ''),
(5800068, 580006800, 0, 0, 1, 0, 0, ''),
-- Alliance Sentinel
(5800061, 580006100, 0, 0, 1, 0, 0, ''),
(5800064, 580006400, 0, 0, 1, 0, 0, ''),
(5800067, 580006700, 0, 0, 1, 0, 0, ''),
(5800075, 580007500, 0, 0, 1, 0, 0, ''),
-- Frostwolf Battleguard
(5800100, 580010000, 0, 0, 1, 0, 0, ''),
(5800103, 580010300, 0, 0, 1, 0, 0, ''),
-- Frostwolf Legionnaire
(5800109, 580010900, 0, 0, 1, 0, 0, ''),
(5800118, 580011800, 0, 0, 1, 0, 0, ''),
(5800121, 580012100, 0, 0, 1, 0, 0, ''),
(5800124, 580012400, 0, 0, 1, 0, 0, ''),
(5800126, 580012600, 0, 0, 1, 0, 0, ''),
(5800128, 580012800, 0, 0, 1, 0, 0, ''),
(5800130, 580013000, 0, 0, 1, 0, 0, ''),
(5800132, 580013200, 0, 0, 1, 0, 0, ''),
(5800135, 580013500, 0, 0, 1, 0, 0, ''),
(5800148, 580014800, 0, 0, 1, 0, 0, ''),
(5800152, 580015200, 0, 0, 1, 0, 0, ''),
-- Frostwolf Mine Layer
(5800138, 580013800, 0, 0, 1, 0, 0, ''),
-- Lieutenant Murp
(5800147, 580014700, 0, 0, 1, 0, 0, ''),
-- Lieutenant Grummus
(5800151, 580015100, 0, 0, 1, 0, 0, ''),
-- Frostwolf Warrior
(5800155, 580015500, 0, 0, 1, 0, 0, ''),
(5800158, 580015800, 0, 0, 1, 0, 0, ''),
(5800160, 580016000, 0, 0, 1, 0, 0, ''),
(5800162, 580016200, 0, 0, 1, 0, 0, ''),
(5800164, 580016400, 0, 0, 1, 0, 0, ''),
(5800166, 580016600, 0, 0, 1, 0, 0, '');
