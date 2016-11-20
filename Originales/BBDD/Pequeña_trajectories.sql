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
-- Table structure for table `trajectories`
--

DROP TABLE IF EXISTS `trajectories`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trajectories` (
  `Flight_Id` int(10) unsigned NOT NULL,
  `Route_Id` int(10) unsigned NOT NULL,
  `SeqNum` int(10) unsigned NOT NULL,
  `Point` varchar(20) NOT NULL,
  `Time` int(10) NOT NULL,
  `MinUseTime` int(10) NOT NULL,
  `MaxUseTime` int(10) NOT NULL,
  PRIMARY KEY (`Flight_Id`,`Route_Id`,`SeqNum`),
  CONSTRAINT `trajectories_ibfk_1` FOREIGN KEY (`Flight_Id`) REFERENCES `flights` (`Flight_Id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trajectories`
--

LOCK TABLES `trajectories` WRITE;
/*!40000 ALTER TABLE `trajectories` DISABLE KEYS */;
INSERT INTO `trajectories` VALUES (1,1,1,'A2',0,0,0),(1,1,2,'P3',1,1,2),(1,1,3,'P2',1,1,2),(1,1,4,'P1',1,1,2),(1,1,5,'A1',1,1,2),(1,2,1,'P3',0,0,0),(1,2,2,'P20',2,2,3),(1,2,3,'P2',2,2,3),(2,1,1,'A2',0,0,0),(2,1,2,'P7',2,2,3),(2,1,3,'P15',2,2,3),(2,1,4,'P19',2,2,2),(2,1,5,'A4',1,1,2),(3,1,1,'A1',0,0,0),(3,1,2,'P4',2,2,3),(3,1,3,'P11',2,2,4),(3,1,4,'P12',1,1,2),(3,1,5,'P16',2,2,3),(3,1,6,'A3',1,1,2),(4,1,1,'A4',0,0,0),(4,1,2,'P19',1,1,2),(4,1,3,'P15',1,1,2),(4,1,4,'P10',1,1,2),(4,1,5,'P7',1,1,2),(4,1,6,'A2',1,1,2),(5,1,1,'A2',0,0,0),(5,1,2,'P3',1,1,1),(5,1,3,'P6',1,1,1),(5,1,4,'P9',1,1,2),(5,1,5,'P13',1,1,2),(5,1,6,'P32',1,1,2),(5,1,7,'P16',1,1,1),(5,1,8,'A3',1,1,1),(6,1,1,'A3',0,0,0),(6,1,2,'P16',2,2,3),(6,1,3,'P12',2,2,2),(6,1,4,'P8',1,1,2),(6,1,5,'P4',2,2,3),(6,1,6,'A1',1,1,2);
/*!40000 ALTER TABLE `trajectories` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-03-05 12:55:05
