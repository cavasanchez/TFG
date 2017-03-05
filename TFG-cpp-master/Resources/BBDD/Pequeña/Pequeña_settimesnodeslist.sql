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
-- Table structure for table `settimesnodeslist`
--

DROP TABLE IF EXISTS `settimesnodeslist`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `settimesnodeslist` (
  `Flight_Id` int(11) NOT NULL,
  `Node_Id` varchar(30) NOT NULL,
  `Time` int(11) NOT NULL,
  PRIMARY KEY (`Flight_Id`,`Node_Id`,`Time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `settimesnodeslist`
--

LOCK TABLES `settimesnodeslist` WRITE;
/*!40000 ALTER TABLE `settimesnodeslist` DISABLE KEYS */;
INSERT INTO `settimesnodeslist` VALUES (1,'A1',4),(1,'A1',5),(1,'A1',6),(1,'A1',7),(1,'A1',8),(1,'A1',9),(1,'A1\'',4),(1,'A1\'',5),(1,'A1\'',6),(1,'A1\'',7),(1,'A1\'',8),(1,'A1\'',9),(1,'A2\'',0),(1,'A2\'',1),(1,'A2\'',2),(1,'A2\'',3),(1,'P1',3),(1,'P1',4),(1,'P1',5),(1,'P1',6),(1,'P1',7),(1,'P1',8),(1,'P2',2),(1,'P2',3),(1,'P2',4),(1,'P2',5),(1,'P2',6),(1,'P2',7),(1,'P20',3),(1,'P20',4),(1,'P20',5),(1,'P3',1),(1,'P3',2),(1,'P3',3),(1,'P3',4),(1,'P3',5),(2,'A2\'',1),(2,'A4',8),(2,'A4',9),(2,'A4\'',8),(2,'A4\'',9),(2,'P15',5),(2,'P15',6),(2,'P19',7),(2,'P19',8),(2,'P7',3),(2,'P7',4),(3,'A1\'',20),(3,'A1\'',21),(3,'A1\'',22),(3,'A3',28),(3,'A3',29),(3,'A3',30),(3,'A3',31),(3,'A3\'',28),(3,'A3\'',29),(3,'A3\'',30),(3,'A3\'',31),(3,'P11',24),(3,'P11',25),(3,'P11',26),(3,'P11',27),(3,'P12',25),(3,'P12',26),(3,'P12',27),(3,'P12',28),(3,'P16',27),(3,'P16',28),(3,'P16',29),(3,'P16',30),(3,'P4',22),(3,'P4',23),(3,'P4',24),(3,'P4',25),(4,'A2',5),(4,'A2',6),(4,'A2',7),(4,'A2\'',5),(4,'A2\'',6),(4,'A2\'',7),(4,'A4\'',0),(4,'A4\'',1),(4,'P10',3),(4,'P10',4),(4,'P10',5),(4,'P15',2),(4,'P15',3),(4,'P15',4),(4,'P19',1),(4,'P19',2),(4,'P19',3),(4,'P7',4),(4,'P7',5),(4,'P7',6),(5,'A2\'',22),(5,'A2\'',23),(5,'A3',29),(5,'A3',30),(5,'A3',31),(5,'A3\'',29),(5,'A3\'',30),(5,'A3\'',31),(5,'P13',26),(5,'P13',27),(5,'P13',28),(5,'P16',28),(5,'P16',29),(5,'P16',30),(5,'P3',23),(5,'P3',24),(5,'P32',27),(5,'P32',28),(5,'P32',29),(5,'P6',24),(5,'P6',25),(5,'P9',25),(5,'P9',26),(5,'P9',27),(6,'A1',48),(6,'A1',49),(6,'A1',50),(6,'A1\'',48),(6,'A1\'',49),(6,'A1\'',50),(6,'A3\'',40),(6,'A3\'',41),(6,'P12',44),(6,'P12',45),(6,'P12',46),(6,'P16',42),(6,'P16',43),(6,'P16',44),(6,'P4',47),(6,'P4',48),(6,'P4',49),(6,'P8',45),(6,'P8',46),(6,'P8',47);
/*!40000 ALTER TABLE `settimesnodeslist` ENABLE KEYS */;
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
