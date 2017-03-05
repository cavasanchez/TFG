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
-- Table structure for table `sectorcapacitiesdiscrete`
--

DROP TABLE IF EXISTS `sectorcapacitiesdiscrete`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sectorcapacitiesdiscrete` (
  `Sector_Id` varchar(20) NOT NULL,
  `Capacity` int(11) NOT NULL,
  `InitialTimeStep` int(11) NOT NULL,
  `FinalTimeStep` int(11) NOT NULL,
  PRIMARY KEY (`Sector_Id`,`InitialTimeStep`,`FinalTimeStep`),
  CONSTRAINT `sectorcapacitiesdiscrete_ibfk_1` FOREIGN KEY (`Sector_Id`) REFERENCES `sectors` (`Sector_Id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sectorcapacitiesdiscrete`
--

LOCK TABLES `sectorcapacitiesdiscrete` WRITE;
/*!40000 ALTER TABLE `sectorcapacitiesdiscrete` DISABLE KEYS */;
INSERT INTO `sectorcapacitiesdiscrete` VALUES ('S01',1,0,63),('S02',1,0,63),('S03',1,0,63),('S04',1,0,63),('S05',1,0,63),('S06',1,0,63),('S07',1,0,63),('S08',1,0,63),('S09',1,0,63),('S10',1,0,63),('S11',1,0,63),('S12',1,0,63),('S13',1,0,63),('S14',1,0,63),('S15',1,0,63),('S16',1,0,63);
/*!40000 ALTER TABLE `sectorcapacitiesdiscrete` ENABLE KEYS */;
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
