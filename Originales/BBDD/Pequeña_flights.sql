CREATE DATABASE  IF NOT EXISTS `Pequeña` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `Pequeña`;
-- MySQL dump 10.13  Distrib 5.5.47, for debian-linux-gnu (x86_64)
--
-- Host: 127.0.0.1    Database: Pequeña
-- ------------------------------------------------------
-- Server version	5.5.47-0ubuntu0.14.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `flights`
--

DROP TABLE IF EXISTS `flights`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `flights` (
  `Flight_Id` int(11) unsigned NOT NULL,
  `Airline_Id` varchar(20) NOT NULL,
  `GroundDelayCost` int(11) NOT NULL,
  `AirborneDelayCost` int(11) NOT NULL,
  `ArrivalDelayCost` int(11) NOT NULL,
  `CancellationCost` int(11) NOT NULL,
  `AirborneDelayFuelPenalty` int(10) NOT NULL,
  `CostNodeDesviation` int(11) NOT NULL DEFAULT '-1',
  `Aircraft_Id` varchar(20) NOT NULL,
  `MaxAirDelay` int(11) NOT NULL,
  `Turnaround` int(11) NOT NULL,
  `MaxGroundDelay` int(11) NOT NULL,
  `AirportDeparture` varchar(20) NOT NULL,
  `AirportArrival` varchar(20) NOT NULL,
  `TimeDeparture` int(11) NOT NULL,
  PRIMARY KEY (`Flight_Id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `flights`
--

LOCK TABLES `flights` WRITE;
/*!40000 ALTER TABLE `flights` DISABLE KEYS */;
INSERT INTO `flights` VALUES (1,'Comp01',11,21,31,501,1,41,'EC666',2,1,3,'A2','A1',0),(2,'Comp02',12,22,32,502,2,42,'KH161',1,1,0,'A2','A4',1),(3,'Comp01',13,23,33,503,3,43,'EC666',1,1,2,'A1','A3',20),(4,'Comp03',14,24,34,504,4,44,'BG689',1,0,1,'A4','A2',0),(5,'Comp03',15,25,35,505,5,45,'BG689',1,0,1,'A2','A3',22),(6,'Comp03',16,26,36,506,6,46,'BG689',1,0,1,'A3','A1',40);
/*!40000 ALTER TABLE `flights` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-03-05 12:55:06
