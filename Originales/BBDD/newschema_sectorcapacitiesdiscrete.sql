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
INSERT INTO `sectorcapacitiesdiscrete` VALUES ('0.00',67,0,360),('1.00',67,0,360),('10.00',67,0,360),('11.00',67,0,360),('12.00',67,0,360),('13.00',67,0,360),('14.00',67,0,360),('15.00',64,0,360),('16.00',64,0,360),('17.00',64,0,360),('18.00',64,0,360),('19.00',64,0,360),('2.00',67,0,360),('20.00',64,0,360),('21.00',64,0,360),('22.00',64,0,360),('23.00',64,0,360),('24.00',64,0,360),('25.00',67,0,360),('26.00',67,0,360),('27.00',67,0,360),('28.00',67,0,360),('29.00',67,0,360),('3.00',67,0,360),('30.00',67,0,360),('31.00',67,0,360),('32.00',67,0,360),('33.00',67,0,360),('34.00',67,0,360),('35.00',67,0,360),('36.00',67,0,360),('37.00',64,0,360),('38.00',64,0,360),('39.00',64,0,360),('4.00',67,0,360),('5.00',67,0,360),('6.00',67,0,360),('7.00',67,0,360),('8.00',67,0,360),('9.00',67,0,360),('S41',67,0,360),('S42',67,0,360),('S43',67,0,360),('S44',67,0,360);
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

-- Dump completed on 2016-03-05 12:55:06
