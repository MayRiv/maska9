-- phpMyAdmin SQL Dump
-- version 4.4.3
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Sep 24, 2015 at 11:55 
-- Server version: 5.6.24
-- PHP Version: 5.5.24

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `maska9`
--

-- --------------------------------------------------------

--
-- Table structure for table `Games`
--

CREATE TABLE IF NOT EXISTS `Games` (
  `GameId` int(11) NOT NULL,
  `RoomId` int(11) NOT NULL,
  `Status` int(11) NOT NULL,
  `MasterId` int(11) NOT NULL,
  `RoundNumber` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Games`
--

INSERT INTO `Games` (`GameId`, `RoomId`, `Status`, `MasterId`, `RoundNumber`) VALUES
(1, 1, 0, 1, 1),
(2, 1, 0, 1, 1);

-- --------------------------------------------------------

--
-- Table structure for table `Masters`
--

CREATE TABLE IF NOT EXISTS `Masters` (
  `MasterId` int(11) NOT NULL,
  `MasterName` varchar(256) NOT NULL,
  `Rating` double DEFAULT NULL,
  `MasterPass` varchar(256) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Masters`
--

INSERT INTO `Masters` (`MasterId`, `MasterName`, `Rating`, `MasterPass`) VALUES
(1, 'Locky', 0, 'c4ca4238a0b923820dcc509a6f75849b');

-- --------------------------------------------------------

--
-- Table structure for table `PlayerGame`
--

CREATE TABLE IF NOT EXISTS `PlayerGame` (
  `Id` int(11) NOT NULL,
  `Player` varchar(256) NOT NULL,
  `GameId` int(11) NOT NULL,
  `Role` varchar(256) NOT NULL,
  `BestVotes` int(11) NOT NULL,
  `DressCode` int(11) NOT NULL,
  `Surprise` tinyint(1) NOT NULL,
  `Penalty` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `PlayerGame`
--

INSERT INTO `PlayerGame` (`Id`, `Player`, `GameId`, `Role`, `BestVotes`, `DressCode`, `Surprise`, `Penalty`) VALUES
(7, 'Fetish', 1, 'Citizen', 3, 0, 0, 0),
(8, 'May', 1, 'Sherif', 4, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `Players`
--

CREATE TABLE IF NOT EXISTS `Players` (
  `Name` varchar(256) NOT NULL,
  `TeamId` int(11) NOT NULL,
  `PersonalRating` double DEFAULT NULL,
  `DressCodeRating` double DEFAULT NULL,
  `SurpriseRating` double DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Players`
--

INSERT INTO `Players` (`Name`, `TeamId`, `PersonalRating`, `DressCodeRating`, `SurpriseRating`) VALUES
('Fetish', 1, NULL, NULL, NULL),
('May', 1, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `Roles`
--

CREATE TABLE IF NOT EXISTS `Roles` (
  `RoleId` int(11) NOT NULL,
  `Role` varchar(256) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Roles`
--

INSERT INTO `Roles` (`RoleId`, `Role`) VALUES
(1, 'Don'),
(2, 'Mafia'),
(3, 'Sherif'),
(4, 'Citizen');

-- --------------------------------------------------------

--
-- Table structure for table `Statuses`
--

CREATE TABLE IF NOT EXISTS `Statuses` (
  `StatusId` int(11) NOT NULL,
  `Status` varchar(256) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Statuses`
--

INSERT INTO `Statuses` (`StatusId`, `Status`) VALUES
(0, 'City'),
(1, 'Mafia'),
(2, 'Draw');

-- --------------------------------------------------------

--
-- Table structure for table `Teams`
--

CREATE TABLE IF NOT EXISTS `Teams` (
  `TeamId` int(11) NOT NULL,
  `Name` varchar(256) NOT NULL,
  `Rating` double DEFAULT NULL,
  `password` varchar(256) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Teams`
--

INSERT INTO `Teams` (`TeamId`, `Name`, `Rating`, `password`) VALUES
(1, 'qwerty', 0, 'c4ca4238a0b923820dcc509a6f75849b');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Games`
--
ALTER TABLE `Games`
  ADD PRIMARY KEY (`GameId`),
  ADD KEY `Status` (`Status`),
  ADD KEY `MasterId` (`MasterId`);

--
-- Indexes for table `Masters`
--
ALTER TABLE `Masters`
  ADD PRIMARY KEY (`MasterId`);

--
-- Indexes for table `PlayerGame`
--
ALTER TABLE `PlayerGame`
  ADD PRIMARY KEY (`Id`),
  ADD KEY `PlayerId` (`Player`),
  ADD KEY `GameId` (`GameId`),
  ADD KEY `RoleId` (`Role`);

--
-- Indexes for table `Players`
--
ALTER TABLE `Players`
  ADD PRIMARY KEY (`Name`),
  ADD KEY `TeamId` (`TeamId`),
  ADD KEY `TeamId_2` (`TeamId`);

--
-- Indexes for table `Roles`
--
ALTER TABLE `Roles`
  ADD PRIMARY KEY (`RoleId`);

--
-- Indexes for table `Statuses`
--
ALTER TABLE `Statuses`
  ADD PRIMARY KEY (`StatusId`);

--
-- Indexes for table `Teams`
--
ALTER TABLE `Teams`
  ADD PRIMARY KEY (`TeamId`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Games`
--
ALTER TABLE `Games`
  MODIFY `GameId` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=29;
--
-- AUTO_INCREMENT for table `Masters`
--
ALTER TABLE `Masters`
  MODIFY `MasterId` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `PlayerGame`
--
ALTER TABLE `PlayerGame`
  MODIFY `Id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=10;
--
-- AUTO_INCREMENT for table `Roles`
--
ALTER TABLE `Roles`
  MODIFY `RoleId` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=5;
--
-- AUTO_INCREMENT for table `Teams`
--
ALTER TABLE `Teams`
  MODIFY `TeamId` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=2;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
