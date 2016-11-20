-- MySQL dump 10.13  Distrib 5.5.15, for Win64 (x86)
--
-- Host: localhost    Database: EjemploNet
-- ------------------------------------------------------
-- Server version	5.5.15

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
INSERT INTO `airportcapacitiesdiscrete` VALUES ('A1',1,1,0,63),('A2',1,1,0,63),('A3',1,1,0,63),('A4',1,1,0,63);
/*!40000 ALTER TABLE `airportcapacitiesdiscrete` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `airportcapacitiestree`
--

DROP TABLE IF EXISTS `airportcapacitiestree`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `airportcapacitiestree` (
  `Airport_Id` varchar(20) NOT NULL,
  `DepartureCapacity` int(10) NOT NULL,
  `ArrivalCapacity` int(10) NOT NULL,
  `InitialTimeStep` int(10) NOT NULL,
  `FinalTimeStep` int(10) NOT NULL,
  `Node` int(10) NOT NULL,
  PRIMARY KEY (`Airport_Id`,`InitialTimeStep`,`FinalTimeStep`),
  CONSTRAINT `airportcapacitiestree_ibfk_1` FOREIGN KEY (`Airport_Id`) REFERENCES `airports` (`Airport_Id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `airportcapacitiestree`
--

LOCK TABLES `airportcapacitiestree` WRITE;
/*!40000 ALTER TABLE `airportcapacitiestree` DISABLE KEYS */;
INSERT INTO `airportcapacitiestree` VALUES ('A1',1,0,11,30,0),('A3',1,0,37,49,0);
/*!40000 ALTER TABLE `airportcapacitiestree` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `airports`
--

DROP TABLE IF EXISTS `airports`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `airports` (
  `Airport_Id` varchar(20) NOT NULL,
  `AirportSector` varchar(20) NOT NULL DEFAULT '',
  PRIMARY KEY (`Airport_Id`,`AirportSector`),
  KEY `AirportSector` (`AirportSector`),
  CONSTRAINT `airports_ibfk_1` FOREIGN KEY (`AirportSector`) REFERENCES `sectors` (`Sector_Id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `airports`
--

LOCK TABLES `airports` WRITE;
/*!40000 ALTER TABLE `airports` DISABLE KEYS */;
INSERT INTO `airports` VALUES ('A1','S01'),('A3','S04'),('A2','S13'),('A4','S16');
/*!40000 ALTER TABLE `airports` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cancelflight`
--

DROP TABLE IF EXISTS `cancelflight`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cancelflight` (
  `Flight_Id` varchar(20) NOT NULL,
  `Scenario` int(10) unsigned NOT NULL,
  PRIMARY KEY (`Flight_Id`,`Scenario`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cancelflight`
--

LOCK TABLES `cancelflight` WRITE;
/*!40000 ALTER TABLE `cancelflight` DISABLE KEYS */;
/*!40000 ALTER TABLE `cancelflight` ENABLE KEYS */;
UNLOCK TABLES;

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
INSERT INTO `flights` VALUES (1,'Comp01',101,102,103,104,105,106,'EC666',2,1,3,'A2','A1',0),(2,'Comp02',201,202,203,204,205,206,'KH161',1,1,0,'A2','A4',1),(3,'Comp01',301,302,303,304,305,306,'EC666',1,1,2,'A1','A3',20),(4,'Comp03',401,402,403,404,405,406,'BG689',1,0,1,'A4','A2',0),(5,'Comp03',501,502,503,504,505,506,'BG689',1,0,1,'A2','A3',22),(6,'Comp03',601,602,603,604,605,606,'BG689',1,0,1,'A3','A1',40);
/*!40000 ALTER TABLE `flights` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `matrizuso`
--

DROP TABLE IF EXISTS `matrizuso`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `matrizuso` (
  `AirlineId` varchar(20) NOT NULL,
  `Flight_Id` int(10) unsigned NOT NULL,
  `Route_Id` int(10) unsigned NOT NULL,
  `SeqNum` int(10) unsigned NOT NULL,
  `BeginPoint` varchar(20) NOT NULL,
  `BeginTime` int(10) NOT NULL,
  `MinUseTime` int(10) NOT NULL,
  `MaxUseTime` int(10) NOT NULL,
  `Aircraft_Id` varchar(20) NOT NULL DEFAULT '',
  PRIMARY KEY (`AirlineId`,`Flight_Id`,`Route_Id`,`SeqNum`,`Aircraft_Id`),
  KEY `Flight_Id` (`Flight_Id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `matrizuso`
--

LOCK TABLES `matrizuso` WRITE;
/*!40000 ALTER TABLE `matrizuso` DISABLE KEYS */;
/*!40000 ALTER TABLE `matrizuso` ENABLE KEYS */;
UNLOCK TABLES;

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
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `objfunctionsparameters`
--

LOCK TABLES `objfunctionsparameters` WRITE;
/*!40000 ALTER TABLE `objfunctionsparameters` DISABLE KEYS */;
INSERT INTO `objfunctionsparameters` VALUES (0,1,1,1,1,1,1,1,3,1,1),(1,1,0,1,0,0,1,1,2,1,1),(2,1,0,1,0,0,1,1,4,1,1),(3,1,0,1,0,0,1,1,5,1,1);
/*!40000 ALTER TABLE `objfunctionsparameters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `objfunctionsparametersnet`
--

DROP TABLE IF EXISTS `objfunctionsparametersnet`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `objfunctionsparametersnet` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `pesoObj1` double DEFAULT NULL,
  `pesoObj2` double DEFAULT NULL,
  `pesoObj3` double DEFAULT NULL,
  `pesoObj4` double DEFAULT NULL,
  `tipoObj1` int(11) DEFAULT NULL,
  `tipoObj2` int(11) DEFAULT NULL,
  `tipoObj3` int(11) DEFAULT NULL,
  `tipoObj4` int(11) DEFAULT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `objfunctionsparametersnet`
--

LOCK TABLES `objfunctionsparametersnet` WRITE;
/*!40000 ALTER TABLE `objfunctionsparametersnet` DISABLE KEYS */;
INSERT INTO `objfunctionsparametersnet` VALUES (0,1,1,1,1,1,1,2,1),(1,1,1,1,1,2,1,3,2),(2,1,0,1,0,1,1,2,1),(3,1,0,1,0,1,1,4,1);
/*!40000 ALTER TABLE `objfunctionsparametersnet` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `results`
--

DROP TABLE IF EXISTS `results`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `results` (
  `AirlineId` varchar(20) NOT NULL,
  `Flight_Id` int(10) unsigned NOT NULL,
  `Route_Id` int(10) unsigned NOT NULL,
  `SeqNum` int(10) unsigned NOT NULL,
  `BeginPoint` varchar(20) NOT NULL,
  `BeginTime` int(10) NOT NULL,
  `MinUseTime` int(10) NOT NULL,
  `MaxUseTime` int(10) NOT NULL,
  `Scenario` int(10) unsigned NOT NULL,
  PRIMARY KEY (`Scenario`,`Flight_Id`,`Route_Id`,`SeqNum`),
  KEY `Flight_Id` (`Flight_Id`),
  CONSTRAINT `results_ibfk_1` FOREIGN KEY (`Flight_Id`) REFERENCES `flights` (`Flight_Id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `results`
--

LOCK TABLES `results` WRITE;
/*!40000 ALTER TABLE `results` DISABLE KEYS */;
/*!40000 ALTER TABLE `results` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `scenariotree`
--

DROP TABLE IF EXISTS `scenariotree`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `scenariotree` (
  `node` int(11) NOT NULL,
  `parent` int(11) NOT NULL,
  `t_init` int(11) NOT NULL,
  `weigth` double NOT NULL,
  PRIMARY KEY (`node`,`parent`,`t_init`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `scenariotree`
--

LOCK TABLES `scenariotree` WRITE;
/*!40000 ALTER TABLE `scenariotree` DISABLE KEYS */;
INSERT INTO `scenariotree` VALUES (0,-1,0,1),(1,0,63,1);
/*!40000 ALTER TABLE `scenariotree` ENABLE KEYS */;
UNLOCK TABLES;

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
INSERT INTO `sectorcapacitiesdiscrete` VALUES ('S01',1,0,63),('S02',1,0,63),('S03',1,0,63),('S04',0,0,63),('S05',1,0,63),('S06',1,0,63),('S07',1,0,63),('S08',1,0,63),('S09',1,0,63),('S10',1,0,63),('S11',1,0,63),('S12',1,0,63),('S13',0,0,63),('S14',1,0,63),('S15',1,0,63),('S16',1,0,63);
/*!40000 ALTER TABLE `sectorcapacitiesdiscrete` ENABLE KEYS */;
UNLOCK TABLES;

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
  PRIMARY KEY (`Sector_Id`),
  CONSTRAINT `sectorcapacitiestree_ibfk_1` FOREIGN KEY (`Sector_Id`) REFERENCES `sectors` (`Sector_Id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sectorcapacitiestree`
--

LOCK TABLES `sectorcapacitiestree` WRITE;
/*!40000 ALTER TABLE `sectorcapacitiestree` DISABLE KEYS */;
INSERT INTO `sectorcapacitiestree` VALUES ('S01',-1,11,20,0),('S03',1,15,27,0);
/*!40000 ALTER TABLE `sectorcapacitiestree` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sectors`
--

DROP TABLE IF EXISTS `sectors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sectors` (
  `Sector_Id` varchar(20) NOT NULL,
  PRIMARY KEY (`Sector_Id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sectors`
--

LOCK TABLES `sectors` WRITE;
/*!40000 ALTER TABLE `sectors` DISABLE KEYS */;
INSERT INTO `sectors` VALUES ('S01'),('S02'),('S03'),('S04'),('S05'),('S06'),('S07'),('S08'),('S09'),('S10'),('S11'),('S12'),('S13'),('S14'),('S15'),('S16');
/*!40000 ALTER TABLE `sectors` ENABLE KEYS */;
UNLOCK TABLES;

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

--
-- Table structure for table `settimesarcslist`
--

DROP TABLE IF EXISTS `settimesarcslist`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `settimesarcslist` (
  `Flight_Id` int(11) NOT NULL,
  `Arc_Id` varchar(40) NOT NULL,
  `Time` int(11) NOT NULL,
  PRIMARY KEY (`Flight_Id`,`Arc_Id`,`Time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `settimesarcslist`
--

LOCK TABLES `settimesarcslist` WRITE;
/*!40000 ALTER TABLE `settimesarcslist` DISABLE KEYS */;
INSERT INTO `settimesarcslist` VALUES (1,'A1\'A1',4),(1,'A1\'A1',5),(1,'A1\'A1',6),(1,'A1\'A1',7),(1,'A1\'A1',8),(1,'A1\'A1',9),(1,'A2\'P3',1),(1,'A2\'P3',2),(1,'A2\'P3',3),(1,'A2\'P3',4),(1,'A2\'P3',5),(1,'A2A2\'',0),(1,'A2A2\'',1),(1,'A2A2\'',2),(1,'A2A2\'',3),(1,'P1A1\'',4),(1,'P1A1\'',5),(1,'P1A1\'',6),(1,'P1A1\'',7),(1,'P1A1\'',8),(1,'P1A1\'',9),(1,'P20P2',5),(1,'P20P2',6),(1,'P20P2',7),(1,'P2P1',3),(1,'P2P1',4),(1,'P2P1',5),(1,'P2P1',6),(1,'P2P1',7),(1,'P2P1',8),(1,'P3P2',2),(1,'P3P2',3),(1,'P3P2',4),(1,'P3P2',5),(1,'P3P2',6),(1,'P3P2',7),(1,'P3P20',3),(1,'P3P20',4),(1,'P3P20',5),(2,'A2\'P7',3),(2,'A2\'P7',4),(2,'A2A2\'',1),(2,'A4\'A4',8),(2,'A4\'A4',9),(2,'P15P19',7),(2,'P15P19',8),(2,'P19A4\'',8),(2,'P19A4\'',9),(2,'P7P15',5),(2,'P7P15',6),(3,'A1\'P4',22),(3,'A1\'P4',23),(3,'A1\'P4',24),(3,'A1\'P4',25),(3,'A1A1\'',20),(3,'A1A1\'',21),(3,'A1A1\'',22),(3,'A3\'A3',28),(3,'A3\'A3',29),(3,'A3\'A3',30),(3,'A3\'A3',31),(3,'P11P12',25),(3,'P11P12',26),(3,'P11P12',27),(3,'P11P12',28),(3,'P12P16',27),(3,'P12P16',28),(3,'P12P16',29),(3,'P12P16',30),(3,'P16A3\'',28),(3,'P16A3\'',29),(3,'P16A3\'',30),(3,'P16A3\'',31),(3,'P4P11',24),(3,'P4P11',25),(3,'P4P11',26),(3,'P4P11',27),(4,'A2\'A2',5),(4,'A2\'A2',6),(4,'A2\'A2',7),(4,'A4\'P19',1),(4,'A4\'P19',2),(4,'A4\'P19',3),(4,'A4A4\'',0),(4,'A4A4\'',1),(4,'P10P7',4),(4,'P10P7',5),(4,'P10P7',6),(4,'P15P10',3),(4,'P15P10',4),(4,'P15P10',5),(4,'P19P15',2),(4,'P19P15',3),(4,'P19P15',4),(4,'P7A2\'',5),(4,'P7A2\'',6),(4,'P7A2\'',7),(5,'A2\'P3',23),(5,'A2\'P3',24),(5,'A2A2\'',22),(5,'A2A2\'',23),(5,'A3\'A3',29),(5,'A3\'A3',30),(5,'A3\'A3',31),(5,'P13P32',27),(5,'P13P32',28),(5,'P13P32',29),(5,'P16A3\'',29),(5,'P16A3\'',30),(5,'P16A3\'',31),(5,'P32P16',28),(5,'P32P16',29),(5,'P32P16',30),(5,'P3P6',24),(5,'P3P6',25),(5,'P6P9',25),(5,'P6P9',26),(5,'P6P9',27),(5,'P9P13',26),(5,'P9P13',27),(5,'P9P13',28),(6,'A1\'A1',48),(6,'A1\'A1',49),(6,'A1\'A1',50),(6,'A3\'P16',42),(6,'A3\'P16',43),(6,'A3\'P16',44),(6,'A3A3\'',40),(6,'A3A3\'',41),(6,'P12P8',45),(6,'P12P8',46),(6,'P12P8',47),(6,'P16P12',44),(6,'P16P12',45),(6,'P16P12',46),(6,'P4A1\'',48),(6,'P4A1\'',49),(6,'P4A1\'',50),(6,'P8P4',47),(6,'P8P4',48),(6,'P8P4',49);
/*!40000 ALTER TABLE `settimesarcslist` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `settimesnodesinterval`
--

DROP TABLE IF EXISTS `settimesnodesinterval`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `settimesnodesinterval` (
  `Flight_Id` int(11) NOT NULL,
  `Node_Id` varchar(30) NOT NULL,
  `BeginInterval` int(11) NOT NULL,
  `EndInterval` int(11) NOT NULL,
  PRIMARY KEY (`Flight_Id`,`Node_Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `settimesnodesinterval`
--

LOCK TABLES `settimesnodesinterval` WRITE;
/*!40000 ALTER TABLE `settimesnodesinterval` DISABLE KEYS */;
INSERT INTO `settimesnodesinterval` VALUES (1,'A1',4,9),(1,'A1\'',4,9),(1,'A2\'',0,3),(1,'P1',3,8),(1,'P2',2,7),(1,'P20',3,5),(1,'P3',1,5),(2,'A2\'',1,1),(2,'A4',8,9),(2,'A4\'',8,9),(2,'P15',5,6),(2,'P19',7,8),(2,'P7',3,4),(3,'A1\'',20,22),(3,'A3',28,31),(3,'A3\'',28,31),(3,'P11',24,27),(3,'P12',25,28),(3,'P16',27,30),(3,'P4',22,25),(4,'A2',5,7),(4,'A2\'',5,7),(4,'A4\'',0,1),(4,'P10',3,5),(4,'P15',2,4),(4,'P19',1,3),(4,'P7',4,6),(5,'A2\'',22,23),(5,'A3',29,31),(5,'A3\'',29,31),(5,'P13',26,28),(5,'P16',28,30),(5,'P3',23,24),(5,'P32',27,29),(5,'P6',24,25),(5,'P9',25,27),(6,'A1',48,50),(6,'A1\'',48,50),(6,'A3\'',40,41),(6,'P12',44,46),(6,'P16',42,44),(6,'P4',47,49),(6,'P8',45,47);
/*!40000 ALTER TABLE `settimesnodesinterval` ENABLE KEYS */;
UNLOCK TABLES;

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

--
-- Table structure for table `solverparameters`
--

DROP TABLE IF EXISTS `solverparameters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `solverparameters` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `maxTime` double NOT NULL,
  `numbSol` int(11) NOT NULL,
  `optGap` double NOT NULL,
  `intGap` double NOT NULL,
  `screen` int(11) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `solverparameters`
--

LOCK TABLES `solverparameters` WRITE;
/*!40000 ALTER TABLE `solverparameters` DISABLE KEYS */;
INSERT INTO `solverparameters` VALUES (1,7200,10,0.000001,0.00001,1);
/*!40000 ALTER TABLE `solverparameters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `times`
--

DROP TABLE IF EXISTS `times`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `times` (
  `First` int(10) NOT NULL,
  `Last` int(10) NOT NULL,
  PRIMARY KEY (`First`,`Last`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `times`
--

LOCK TABLES `times` WRITE;
/*!40000 ALTER TABLE `times` DISABLE KEYS */;
INSERT INTO `times` VALUES (0,63);
/*!40000 ALTER TABLE `times` ENABLE KEYS */;
UNLOCK TABLES;

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

--
-- Table structure for table `usercancelflight`
--

DROP TABLE IF EXISTS `usercancelflight`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `usercancelflight` (
  `Flight_Id` varchar(20) NOT NULL,
  `Node` int(11) NOT NULL,
  PRIMARY KEY (`Flight_Id`,`Node`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `usercancelflight`
--

LOCK TABLES `usercancelflight` WRITE;
/*!40000 ALTER TABLE `usercancelflight` DISABLE KEYS */;
/*!40000 ALTER TABLE `usercancelflight` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `waypoints`
--

DROP TABLE IF EXISTS `waypoints`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `waypoints` (
  `Waypoint` varchar(20) NOT NULL,
  `Sector_Id` varchar(20) NOT NULL,
  PRIMARY KEY (`Waypoint`,`Sector_Id`),
  KEY `waypoints_ibfk_1` (`Sector_Id`),
  CONSTRAINT `waypoints_ibfk_1` FOREIGN KEY (`Sector_Id`) REFERENCES `sectors` (`Sector_Id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `waypoints`
--

LOCK TABLES `waypoints` WRITE;
/*!40000 ALTER TABLE `waypoints` DISABLE KEYS */;
INSERT INTO `waypoints` VALUES ('P1','S01'),('P4','S01'),('P11','S02'),('P12','S02'),('P4','S02'),('P8','S02'),('P12','S03'),('P16','S03'),('P32','S03'),('P16','S04'),('P1','S05'),('P2','S05'),('P13','S06'),('P9','S06'),('P13','S07'),('P32','S07'),('P2','S09'),('P20','S09'),('P3','S09'),('P6','S09'),('P6','S10'),('P9','S10'),('P3','S13'),('P7','S13'),('P10','S14'),('P15','S14'),('P7','S14'),('P15','S15'),('P19','S15'),('P19','S16');
/*!40000 ALTER TABLE `waypoints` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-05-24 21:11:50
