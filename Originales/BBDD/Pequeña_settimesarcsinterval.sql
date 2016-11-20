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
-- Table structure for table `settimesarcsinterval`
--

DROP TABLE IF EXISTS `settimesarcsinterval`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `settimesarcsinterval` (
  `Flight_Id` int(11) NOT NULL,
  `Arc_Id` varchar(40) NOT NULL,
  `BeginInterval` int(11) NOT NULL,
  `EndInterval` int(11) NOT NULL,
  PRIMARY KEY (`Flight_Id`,`Arc_Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `settimesarcsinterval`
--

LOCK TABLES `settimesarcsinterval` WRITE;
/*!40000 ALTER TABLE `settimesarcsinterval` DISABLE KEYS */;
INSERT INTO `settimesarcsinterval` VALUES (1,'A1\'A1',4,9),(1,'A2\'P3',1,5),(1,'A2A2\'',0,3),(1,'P1A1\'',4,9),(1,'P20P2',5,7),(1,'P2P1',3,8),(1,'P3P2',2,7),(1,'P3P20',3,5),(2,'A2\'P7',3,4),(2,'A2A2\'',1,1),(2,'A4\'A4',8,9),(2,'P15P19',7,8),(2,'P19A4\'',8,9),(2,'P7P15',5,6),(3,'A1\'P4',22,25),(3,'A1A1\'',20,22),(3,'A3\'A3',28,31),(3,'P11P12',25,28),(3,'P12P16',27,30),(3,'P16A3\'',28,31),(3,'P4P11',24,27),(4,'A2\'A2',5,7),(4,'A4\'P19',1,3),(4,'A4A4\'',0,1),(4,'P10P7',4,6),(4,'P15P10',3,5),(4,'P19P15',2,4),(4,'P7A2\'',5,7),(5,'A2\'P3',23,24),(5,'A2A2\'',22,23),(5,'A3\'A3',29,31),(5,'P13P32',27,29),(5,'P16A3\'',29,31),(5,'P32P16',28,30),(5,'P3P6',24,25),(5,'P6P9',25,27),(5,'P9P13',26,28),(6,'A1\'A1',48,50),(6,'A3\'P16',42,44),(6,'A3A3\'',40,41),(6,'P12P8',45,47),(6,'P16P12',44,46),(6,'P4A1\'',48,50),(6,'P8P4',47,49);
/*!40000 ALTER TABLE `settimesarcsinterval` ENABLE KEYS */;
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
