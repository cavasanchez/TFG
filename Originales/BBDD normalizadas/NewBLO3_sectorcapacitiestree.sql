-- MySQL dump 10.13  Distrib 5.7.18, for Linux (x86_64)
--
-- Host: 127.0.0.1    Database: NewBLO3
-- ------------------------------------------------------
-- Server version	5.7.18-0ubuntu0.16.04.1

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
INSERT INTO `sectorcapacitiestree` VALUES ('45.00',0,3,7,0),('46.00',0,8,12,0),('47.00',0,13,17,0),('48.00',0,18,22,0),('49.00',0,23,27,0),('50.00',0,28,32,0),('51.00',0,33,37,0),('52.00',0,38,42,0),('53.00',0,43,47,0),('54.00',0,3,7,0),('55.00',0,8,12,0),('56.00',0,13,17,0),('57.00',0,18,22,0),('58.00',0,23,27,0),('59.00',0,28,32,0),('60.00',0,33,37,0),('61.00',0,38,42,0),('62.00',0,43,47,0),('121.00',0,3,7,0),('122.00',0,8,12,0),('123.00',0,13,17,0),('124.00',0,18,22,0),('125.00',0,23,27,0),('126.00',0,28,32,0),('127.00',0,33,37,0),('128.00',0,38,42,0);
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

-- Dump completed on 2017-06-25 13:22:06
