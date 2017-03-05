CREATE DATABASE  IF NOT EXISTS `newschema` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `newschema`;
-- MySQL dump 10.13  Distrib 5.5.47, for debian-linux-gnu (x86_64)
--
-- Host: 127.0.0.1    Database: newschema
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
-- Table structure for table `sectorcapacitiestree`
--

DROP TABLE IF EXISTS `sectorcapacitiestree`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sectorcapacitiestree` (
  `Sector_Id` varchar(20) NOT NULL,
  `Capacity` int(11) NOT NULL,
  `InitialTimeStep` int(11) NOT NULL,
  `FinalTimeStep` int(11) NOT NULL,
  `Node` int(11) NOT NULL,
  KEY `Sector_Id` (`Sector_Id`),
  CONSTRAINT `sectorcapacitiestree_ibfk_1` FOREIGN KEY (`Sector_Id`) REFERENCES `sectors` (`Sector_Id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sectorcapacitiestree`
--

LOCK TABLES `sectorcapacitiestree` WRITE;
/*!40000 ALTER TABLE `sectorcapacitiestree` DISABLE KEYS */;
INSERT INTO `sectorcapacitiestree` VALUES ('15.00',-55,3,7,0),('16.00',-55,8,12,0),('17.00',-55,13,17,0),('18.00',-55,18,22,0),('19.00',-55,23,27,0),('20.00',-55,3,7,0),('21.00',-55,8,12,0),('22.00',-55,13,17,0),('23.00',-55,18,22,0),('24.00',-55,23,27,0),('37.00',-55,3,7,0),('38.00',-55,8,12,0),('39.00',-55,13,17,0);
/*!40000 ALTER TABLE `sectorcapacitiestree` ENABLE KEYS */;
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
