DELETE FROM `pool_template` WHERE `entry` IN (5678, 87000);
INSERT INTO `pool_template` (`entry`, `max_limit`, `description`) VALUES
(5678, 1, 'Heroic Dungeon Dailies'),
(87000, 1, 'Dungeon Dailies');
