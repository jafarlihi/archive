-- phpMyAdmin SQL Dump
-- version 4.5.2
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Dec 10, 2016 at 08:51 AM
-- Server version: 10.1.19-MariaDB
-- PHP Version: 7.0.9

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `gallery_module`
--

-- --------------------------------------------------------

--
-- Table structure for table `albums`
--

CREATE TABLE `albums` (
  `id` int(11) NOT NULL,
  `title` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `albums`
--

INSERT INTO `albums` (`id`, `title`) VALUES
(1, 'Qafqaz Uni'),
(2, 'Test Album #2'),
(3, 'Empty test album 3'),
(4, 'Test album'),
(5, 'yeni albom 21'),
(6, 'Wallpapers'),
(7, 'Yeni albom 66'),
(8, 'New album foreign key ttest'),
(9, 'asdsad'),
(10, 'test albom');

-- --------------------------------------------------------

--
-- Table structure for table `album_images`
--

CREATE TABLE `album_images` (
  `album_id` int(11) NOT NULL,
  `image_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `album_images`
--

INSERT INTO `album_images` (`album_id`, `image_id`) VALUES
(1, 2),
(1, 5),
(5, 3),
(5, 12),
(5, 16),
(8, 4),
(8, 5),
(8, 6),
(8, 3),
(8, 2),
(9, 1),
(9, 2),
(9, 4),
(10, 1),
(10, 7),
(10, 8),
(10, 22);

-- --------------------------------------------------------

--
-- Table structure for table `images`
--

CREATE TABLE `images` (
  `id` int(11) NOT NULL,
  `tags` varchar(16384) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `images`
--

INSERT INTO `images` (`id`, `tags`) VALUES
(1, '["azerbaijan","map"]'),
(2, '["azerbaijan","baku","city"]'),
(3, '["azerbaijan","baku","city","streets","street"]'),
(4, '["azerbaijan","baku","city"]'),
(5, '["azerbaijan","baku","city","streets"]'),
(6, '["bird","orange"]'),
(7, '["bird","parrot","colorful"]'),
(8, '["bird","white","animal"]'),
(9, '["bird","animal","green","blue","peacock"]'),
(10, '["bridge","city"]'),
(11, '["earth","blue"]'),
(12, '["earth","night"]'),
(13, '["earth"]'),
(14, '["landscape"]'),
(15, '["php","logo","blue"]'),
(16, '["php","programming"]'),
(17, '["qafqaz","university","building"]'),
(18, '["qafqaz","university","building"]'),
(19, '["qafqaz","university","buildings","campus"]'),
(20, '["qafqaz","university","campus","gate"]'),
(21, '["qafqaz","university","map"]'),
(22, '["phone","android","samsung"]'),
(23, '["wallpaper","black"]'),
(24, '["wallpaper","black"]'),
(25, '["wallpaper","black"]'),
(26, '["wallpaper","black","background"]');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `albums`
--
ALTER TABLE `albums`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `album_images`
--
ALTER TABLE `album_images`
  ADD KEY `album_index` (`album_id`),
  ADD KEY `image_index` (`image_id`) USING BTREE;

--
-- Indexes for table `images`
--
ALTER TABLE `images`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `albums`
--
ALTER TABLE `albums`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;
--
-- AUTO_INCREMENT for table `images`
--
ALTER TABLE `images`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=27;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `album_images`
--
ALTER TABLE `album_images`
  ADD CONSTRAINT `album_constraint` FOREIGN KEY (`album_id`) REFERENCES `albums` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `image_constraint` FOREIGN KEY (`image_id`) REFERENCES `images` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
