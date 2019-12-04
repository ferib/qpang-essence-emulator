-- --------------------------------------------------------
-- Host:                         137.74.87.216
-- Server version:               5.7.26-0ubuntu0.18.04.1 - (Ubuntu)
-- Server OS:                    Linux
-- HeidiSQL Version:             9.5.0.5196
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- Dumping database structure for qpang
CREATE DATABASE IF NOT EXISTS `qpang` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `qpang`;

-- Dumping structure for table qpang.game_item_spawns
CREATE TABLE IF NOT EXISTS `game_item_spawns` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `position_id` bigint(20) unsigned NOT NULL,
  `map_id` bigint(20) unsigned NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `game_item_spawns_position_id_foreign` (`position_id`),
  KEY `game_item_spawns_map_id_foreign` (`map_id`),
  CONSTRAINT `game_item_spawns_map_id_foreign` FOREIGN KEY (`map_id`) REFERENCES `maps` (`id`),
  CONSTRAINT `game_item_spawns_position_id_foreign` FOREIGN KEY (`position_id`) REFERENCES `positions` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Dumping data for table qpang.game_item_spawns: ~0 rows (approximately)
DELETE FROM `game_item_spawns`;
/*!40000 ALTER TABLE `game_item_spawns` DISABLE KEYS */;
INSERT INTO `game_item_spawns` (`id`, `position_id`, `map_id`, `created_at`, `updated_at`) VALUES
	(2, 28, 5, NULL, NULL),
	(3, 26, 5, NULL, NULL),
	(4, 27, 5, NULL, NULL),
	(5, 29, 5, NULL, NULL),
	(6, 42, 1, NULL, NULL),
	(7, 43, 1, NULL, NULL),
	(8, 44, 1, NULL, NULL),
	(9, 45, 1, NULL, NULL);
/*!40000 ALTER TABLE `game_item_spawns` ENABLE KEYS */;

-- Dumping structure for table qpang.map_spawns
CREATE TABLE IF NOT EXISTS `map_spawns` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `map_id` bigint(20) unsigned NOT NULL,
  `game_mode_id` bigint(20) unsigned NOT NULL,
  `position_id` bigint(20) unsigned NOT NULL,
  `team` int(10) unsigned DEFAULT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `map_spawns_map_id_foreign` (`map_id`),
  KEY `map_spawns_game_mode_id_foreign` (`game_mode_id`),
  KEY `map_spawns_position_id_foreign` (`position_id`),
  CONSTRAINT `map_spawns_game_mode_id_foreign` FOREIGN KEY (`game_mode_id`) REFERENCES `game_modes` (`id`),
  CONSTRAINT `map_spawns_map_id_foreign` FOREIGN KEY (`map_id`) REFERENCES `maps` (`id`),
  CONSTRAINT `map_spawns_position_id_foreign` FOREIGN KEY (`position_id`) REFERENCES `positions` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=52 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Dumping data for table qpang.map_spawns: ~18 rows (approximately)
DELETE FROM `map_spawns`;
/*!40000 ALTER TABLE `map_spawns` DISABLE KEYS */;
INSERT INTO `map_spawns` (`id`, `map_id`, `game_mode_id`, `position_id`, `team`, `created_at`, `updated_at`) VALUES
	(1, 5, 2, 2, 1, NULL, NULL),
	(2, 5, 2, 3, 2, NULL, NULL),
	(3, 8, 2, 4, 1, NULL, NULL),
	(4, 8, 2, 5, 1, NULL, NULL),
	(5, 8, 2, 6, 2, NULL, NULL),
	(6, 8, 2, 7, 2, NULL, NULL),
	(7, 2, 2, 8, 1, NULL, NULL),
	(8, 2, 2, 9, 2, NULL, NULL),
	(9, 7, 2, 10, 1, NULL, NULL),
	(10, 7, 2, 11, 2, NULL, NULL),
	(11, 9, 2, 12, 1, NULL, NULL),
	(12, 9, 2, 13, 1, NULL, NULL),
	(13, 9, 2, 14, 2, NULL, NULL),
	(14, 9, 2, 15, 2, NULL, NULL),
	(15, 11, 2, 16, 1, NULL, NULL),
	(16, 11, 2, 17, 1, NULL, NULL),
	(17, 11, 2, 18, 2, NULL, NULL),
	(18, 11, 2, 19, 2, NULL, NULL),
	(19, 5, 2, 23, 2, NULL, NULL),
	(20, 5, 2, 25, 2, NULL, NULL),
	(21, 5, 2, 24, 2, NULL, NULL),
	(22, 5, 2, 21, 1, NULL, NULL),
	(23, 5, 2, 20, 1, NULL, NULL),
	(24, 5, 2, 22, 1, NULL, NULL),
	(25, 5, 1, 2, 0, NULL, NULL),
	(26, 5, 1, 20, 0, NULL, NULL),
	(27, 5, 1, 30, 0, NULL, NULL),
	(28, 5, 1, 31, 0, NULL, NULL),
	(29, 5, 1, 35, 0, NULL, NULL),
	(31, 5, 1, 33, 0, NULL, NULL),
	(32, 5, 1, 32, 0, NULL, NULL),
	(33, 5, 1, 24, 0, NULL, NULL),
	(34, 5, 1, 3, 0, NULL, NULL),
	(35, 5, 1, 34, 0, NULL, NULL),
	(36, 1, 1, 54, 0, NULL, NULL),
	(37, 1, 1, 48, 0, NULL, NULL),
	(38, 1, 1, 49, 0, NULL, NULL),
	(39, 1, 1, 46, 0, NULL, NULL),
	(40, 1, 1, 47, 0, NULL, NULL),
	(41, 1, 1, 52, 0, NULL, NULL),
	(42, 1, 1, 53, 0, NULL, NULL),
	(43, 1, 1, 50, 0, NULL, NULL),
	(44, 1, 1, 51, 0, NULL, NULL),
	(46, 1, 2, 36, 1, NULL, NULL),
	(47, 1, 2, 37, 1, NULL, NULL),
	(48, 1, 2, 38, 1, NULL, NULL),
	(49, 1, 2, 39, 2, NULL, NULL),
	(50, 1, 2, 40, 2, NULL, NULL),
	(51, 1, 2, 41, 2, NULL, NULL);
/*!40000 ALTER TABLE `map_spawns` ENABLE KEYS */;

-- Dumping structure for table qpang.positions
CREATE TABLE IF NOT EXISTS `positions` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `x` double(8,2) NOT NULL,
  `y` double(8,2) NOT NULL,
  `z` double(8,2) NOT NULL,
  `name` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=55 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- Dumping data for table qpang.positions: ~19 rows (approximately)
DELETE FROM `positions`;
/*!40000 ALTER TABLE `positions` DISABLE KEYS */;
INSERT INTO `positions` (`id`, `x`, `y`, `z`, `name`, `created_at`, `updated_at`) VALUES
	(1, 2.00, 0.00, 3.00, 'mid spawn', NULL, NULL),
	(2, -23.16, 0.16, -20.00, 'Dollhouse bathroom bath', NULL, NULL),
	(3, 30.00, 0.17, 7.13, 'Dollhouse workplace shelfs', NULL, NULL),
	(4, -5.65, 3.34, 28.00, 'Bunker Team 1 Room', NULL, NULL),
	(5, 27.60, -0.90, -0.13, 'Bunker Team 1 Tent', NULL, NULL),
	(6, 5.65, 3.35, -28.00, 'Bunekr Team 2 Room', NULL, NULL),
	(7, -28.00, -0.90, 0.00, 'Bunker Team 2 Tent', NULL, NULL),
	(8, 20.00, 0.00, -16.00, 'Diorama TDM Blue', NULL, NULL),
	(9, -20.00, 0.00, 16.00, 'Diorama TDM Yellow', NULL, NULL),
	(10, -26.70, 0.00, 16.80, 'Stad TDM Blue', NULL, NULL),
	(11, 26.70, 0.00, -16.80, 'Stad TDM Yellow', NULL, NULL),
	(12, -23.78, 0.00, 28.00, 'Temple TDM Blue 1', NULL, NULL),
	(13, 28.00, 0.00, 23.78, 'Temple TDM Blue 2', NULL, NULL),
	(14, 23.78, 0.00, -28.00, 'Temple TDM Yellow 1', NULL, NULL),
	(15, -28.00, 0.00, -23.78, 'Temple TDM Yellow 2', NULL, NULL),
	(16, -8.00, 0.00, -43.00, 'Bridge TDM Blue 1', NULL, NULL),
	(17, 8.00, 0.00, -43.00, 'Bridge TDM Blue 2', NULL, NULL),
	(18, -8.00, 0.00, 43.00, 'Bridge TDM Yellow 1', NULL, NULL),
	(19, 8.00, 0.00, 43.00, 'Bridge TDM Yellow 2', NULL, NULL),
	(20, -23.30, 0.07, -12.09, 'Dollhouse bathroom shower', NULL, NULL),
	(21, -17.02, 0.09, -20.50, 'Dollhouse bathroom center', NULL, NULL),
	(22, -19.95, -3.40, -14.10, 'Dollhouse bathroom stairs', NULL, NULL),
	(23, 27.31, 0.06, -4.95, 'Dollhouse workplace locker', NULL, NULL),
	(24, 39.46, 0.06, -3.80, 'Dollhouse workplace boxes', NULL, NULL),
	(25, 36.07, 0.06, 7.29, 'Dollhouse workplace last shelf', NULL, NULL),
	(26, 14.89, 0.06, -1.90, 'Dollhouse kitchen center', NULL, NULL),
	(27, 18.53, 0.06, -5.58, 'Dollhouse kitchen bar', NULL, NULL),
	(28, -17.31, 0.09, -16.76, 'Dollhouse bathroom wall', NULL, NULL),
	(29, 15.66, -3.39, -5.00, 'Dollhouse downstairs center', '2019-07-07 14:28:48', NULL),
	(30, -22.84, 0.09, -7.17, 'Dollhouse bedroom bed', NULL, NULL),
	(31, -15.60, 0.05, 7.37, 'Dollhouse bedroom closet', NULL, NULL),
	(32, 3.40, 0.06, 5.93, 'Dollhouse livingroom sofa', NULL, NULL),
	(33, 18.84, 0.05, 7.06, 'Dollhouse kitchen table', NULL, NULL),
	(34, 39.27, -3.39, 1.13, 'Dollhouse workplace under stairs', NULL, NULL),
	(35, 0.95, -3.39, -7.04, 'Dollhouse center under stairs', NULL, NULL),
	(36, 23.52, 0.01, -17.37, 'Garden Team 1 - 1', NULL, NULL),
	(37, 21.30, 0.02, -21.53, 'Garden Team 1 - 2', NULL, NULL),
	(38, 14.36, 0.02, -23.54, 'Garden Team 1 - 3', NULL, NULL),
	(39, -23.52, 0.01, 17.37, 'Garden Team 2 - 1', NULL, NULL),
	(40, -21.30, 0.02, 21.53, 'Garden Team 2 - 2', NULL, NULL),
	(41, -14.36, 0.02, 23.54, 'Garden Team 2 - 3', NULL, NULL),
	(42, -9.68, 2.02, -0.03, 'Garden Powerup center 2', NULL, NULL),
	(43, -9.87, 2.02, 0.09, 'Garden Powerup center 1', NULL, NULL),
	(44, -6.91, 0.02, -23.20, 'Garden Powerup Side 1', NULL, NULL),
	(45, 6.74, 0.01, 23.55, 'Garden Powerup Side 2', NULL, NULL),
	(46, -5.52, -0.07, 5.15, 'Garden Center Water 1', NULL, NULL),
	(47, 5.30, -0.04, -5.37, 'Garden Center Water 2', NULL, NULL),
	(48, 13.73, 0.02, -13.72, 'Garden Center Fountain 1', NULL, NULL),
	(49, -13.73, 0.02, 13.72, 'Garden Center Fountain 2', NULL, NULL),
	(50, -17.39, 0.02, -6.39, 'Garden Side Center 1', NULL, NULL),
	(51, 17.39, 0.02, 6.39, 'Garden Side Center 2', NULL, NULL),
	(52, -22.77, 0.02, -23.33, 'Garden Corner 1', NULL, NULL),
	(53, 22.77, 0.02, 23.33, 'Garden Corner 2', NULL, NULL),
	(54, 0.04, 1.74, 0.03, 'Garden Center', NULL, NULL);
/*!40000 ALTER TABLE `positions` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
