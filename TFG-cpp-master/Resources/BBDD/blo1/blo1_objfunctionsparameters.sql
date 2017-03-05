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
-- Table structure for table `objfunctionsparameters`
--

DROP TABLE IF EXISTS `objfunctionsparameters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `objfunctionsparameters` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `pesoObj1` double DEFAULT NULL,
  `pesoObj2` double DEFAULT NULL,
  `pesoObj3` double DEFAULT NULL,
  `pesoObj4` double DEFAULT NULL,
  `pesoObj5` double DEFAULT NULL,
  `tipoObj1` int(11) DEFAULT NULL,
  `tipoObj2` int(11) DEFAULT NULL,
  `tipoObj3` int(11) DEFAULT NULL,
  `tipoObj4` int(11) DEFAULT NULL,
  `tipoObj5` int(11) DEFAULT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `objfunctionsparameters`
--

LOCK TABLES `objfunctionsparameters` WRITE;
/*!40000 ALTER TABLE `objfunctionsparameters` DISABLE KEYS */;
INSERT INTO `objfunctionsparameters` VALUES (0,1,1,1,1,1,1,1,3,1,1),(1,1,0,1,0,0,1,1,2,1,1),(2,1,0,1,0,0,1,1,4,1,1),(3,1,0,1,0,0,1,1,5,1,1);
/*!40000 ALTER TABLE `objfunctionsparameters` ENABLE KEYS */;
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
