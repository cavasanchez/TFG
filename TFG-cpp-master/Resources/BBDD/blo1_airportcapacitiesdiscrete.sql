CREATE DATABASE  IF NOT EXISTS `blo1` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `blo1`;
-- MySQL dump 10.13  Distrib 5.5.47, for debian-linux-gnu (x86_64)
--
-- Host: 127.0.0.1    Database: blo1
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
-- Table structure for table `airportcapacitiesdiscrete`
--

DROP TABLE IF EXISTS `airportcapacitiesdiscrete`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `airportcapacitiesdiscrete` (
  `Airport_Id` varchar(20) NOT NULL,
  `DepartureCapacity` int(10) NOT NULL,
  `ArrivalCapacity` int(10) NOT NULL,
  `InitialTimeStep` int(10) NOT NULL,
  `FinalTimeStep` int(10) NOT NULL,
  PRIMARY KEY (`Airport_Id`,`InitialTimeStep`,`FinalTimeStep`),
  CONSTRAINT `airportcapacitiesdiscrete_ibfk_1` FOREIGN KEY (`Airport_Id`) REFERENCES `airports` (`Airport_Id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `airportcapacitiesdiscrete`
--

LOCK TABLES `airportcapacitiesdiscrete` WRITE;
/*!40000 ALTER TABLE `airportcapacitiesdiscrete` DISABLE KEYS */;
INSERT INTO `airportcapacitiesdiscrete` VALUES ('A41',38,35,0,360),('A42',38,35,0,360),('A43',38,35,0,360),('A44',38,35,0,360);
/*!40000 ALTER TABLE `airportcapacitiesdiscrete` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-03-05 12:55:03
