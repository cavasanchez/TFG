-- MySQL dump 10.13  Distrib 5.1.31, for debian-linux-gn(i486)
--
-- Host: localhost    Database: NewFlightsEstocastico
-- ------------------------------------------------------
-- Server version	5.1.31-1ubuntu2

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
-- Table structure for table `Sectors`
--

DROP TABLE IF EXISTS `Sectors`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `Sectors` (
  `Sector_Id` varchar(20) NOT NULL,
  PRIMARY KEY (`Sector_Id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `Sectors`
--

LOCK TABLES `Sectors` WRITE;
/*!40000 ALTER TABLE `Sectors` DISABLE KEYS */;
/*!40000 ALTER TABLE `Sectors` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Airports`
--

DROP TABLE IF EXISTS `airports`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `airports` (
  `Airport_Id` varchar(20) NOT NULL,
  `AirportSector` varchar(20) NOT NULL DEFAULT '',
  PRIMARY KEY (`Airport_Id`,`AirportSector`),
  FOREIGN KEY (`AirportSector`) 
	REFERENCES Sectors(`Sector_Id`)
  	ON DELETE NO ACTION
  	ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Airports`
--

LOCK TABLES `Airports` WRITE;
/*!40000 ALTER TABLE `Airports` DISABLE KEYS */;
/*!40000 ALTER TABLE `Airports` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `AirportCapacitiesDiscrete`
--

DROP TABLE IF EXISTS `AirportCapacitiesDiscrete`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `AirportCapacitiesDiscrete` (
  `Airport_Id` varchar(20) NOT NULL,
  `DepartureCapacity` int(10) NOT NULL,
  `ArrivalCapacity` int(10) NOT NULL,
  `InitialTimeStep` int(10) NOT NULL,
  `FinalTimeStep` int(10) NOT NULL,
  PRIMARY KEY (`Airport_Id`,`InitialTimeStep`,`FinalTimeStep`),
  FOREIGN KEY (`Airport_Id`) 
	REFERENCES Airports(`Airport_Id`)
  	ON DELETE NO ACTION
  	ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `AirportCapacitiesDiscrete`
--

LOCK TABLES `AirportCapacitiesDiscrete` WRITE;
/*!40000 ALTER TABLE `AirportCapacitiesDiscrete` DISABLE KEYS */;
/*!40000 ALTER TABLE `AirportCapacitiesDiscrete` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `AirportCapacitiesTree`
--

DROP TABLE IF EXISTS `AirportCapacitiesTree`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `AirportCapacitiesTree` (
  `Airport_Id` varchar(20) NOT NULL,
  `DepartureCapacity` int(10) NOT NULL,
  `ArrivalCapacity` int(10) NOT NULL,
  `InitialTimeStep` int(10) NOT NULL,
  `FinalTimeStep` int(10) NOT NULL,
  `Node` int(10) NOT NULL,
  PRIMARY KEY (`Airport_Id`,`InitialTimeStep`,`FinalTimeStep`),
  FOREIGN KEY (`Airport_Id`) 
	REFERENCES Airports(`Airport_Id`)
  	ON DELETE NO ACTION
  	ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `AirportCapacitiesTree`
--

LOCK TABLES `AirportCapacitiesTree` WRITE;
/*!40000 ALTER TABLE `AirportCapacitiesTree` DISABLE KEYS */;
/*!40000 ALTER TABLE `AirportCapacitiesTree` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `UserCancelFlight`
--

DROP TABLE IF EXISTS `usercancelflight`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `usercancelflight` (
  `Flight_Id` varchar(20) NOT NULL,
  `Node` int(11) NOT NULL,
  PRIMARY KEY (`Flight_Id`, `Node`),
  FOREIGN KEY (`Flight_Id`) 
	REFERENCES flights(`Flight_Id`)
  	ON DELETE NO ACTION
  	ON UPDATE NO ACTION
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `UserCancelFlight`
--

LOCK TABLES `UserCancelFlight` WRITE;
/*!40000 ALTER TABLE `UserCancelFlight` DISABLE KEYS */;
/*!40000 ALTER TABLE `UserCancelFlight` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `CancelFlight`
--

DROP TABLE IF EXISTS `CancelFlight`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `CancelFlight` (
  `Flight_Id` varchar(20) NOT NULL,
  `Scenario` int(10) unsigned NOT NULL,
  PRIMARY KEY (`Flight_Id`,`Scenario`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `CancelFlight`
--

LOCK TABLES `CancelFlight` WRITE;
/*!40000 ALTER TABLE `CancelFlight` DISABLE KEYS */;
/*!40000 ALTER TABLE `CancelFlight` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `MatrizUso`
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
  FOREIGN KEY (`Flight_Id`) 
	REFERENCES flights(`Flight_Id`)
  	ON DELETE NO ACTION
  	ON UPDATE NO ACTION
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `MatrizUso`
--

LOCK TABLES `MatrizUso` WRITE;
/*!40000 ALTER TABLE `MatrizUso` DISABLE KEYS */;
/*!40000 ALTER TABLE `MatrizUso` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ObjFunctionsParameters`
--

DROP TABLE IF EXISTS `ObjFunctionsParameters`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ObjFunctionsParameters` (
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
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `ObjFunctionsParameters`
--

LOCK TABLES `ObjFunctionsParameters` WRITE;
/*!40000 ALTER TABLE `ObjFunctionsParameters` DISABLE KEYS */;
INSERT INTO `ObjFunctionsParameters` VALUES 
(0,1,1,1,1,1,1,1,3,1,1),
(1,1,0,1,0,0,1,1,2,1,1),
(2,1,0,1,0,0,1,1,4,1,1),
(3,1,0,1,0,0,1,1,5,1,1);
/*!40000 ALTER TABLE `ObjFunctionsParameters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ObjFunctionsParametersNet`
--

DROP TABLE IF EXISTS `ObjFunctionsParametersNet`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ObjFunctionsParametersNet` (
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
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `ObjFunctionsParametersNet`
--

LOCK TABLES `ObjFunctionsParametersNet` WRITE;
/*!40000 ALTER TABLE `ObjFunctionsParametersNet` DISABLE KEYS */;
INSERT INTO `ObjFunctionsParametersNet` VALUES 
(0,1,1,1,1,1,1,2,1),
(1,1,1,1,1,2,1,3,2),
(2,1,0,1,0,1,1,2,1),
(3,1,0,1,0,1,1,4,1);
/*!40000 ALTER TABLE `ObjFunctionsParametersNet` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Results`
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
  FOREIGN KEY (`Flight_Id`) 
	REFERENCES flights(`Flight_Id`)
  	ON DELETE NO ACTION
  	ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Results`
--

LOCK TABLES `Results` WRITE;
/*!40000 ALTER TABLE `Results` DISABLE KEYS */;
/*!40000 ALTER TABLE `Results` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ScenarioTree`
--

DROP TABLE IF EXISTS `scenariotree`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `scenariotree` (
  `node` int(11) NOT NULL,
  `parent` int(11) NOT NULL,
  `t_init` int(11) NOT NULL,
  `weight` double NOT NULL,
  PRIMARY KEY (`node`, `parent`,`t_init`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ScenarioTree`
--

LOCK TABLES `ScenarioTree` WRITE;
/*!40000 ALTER TABLE `ScenarioTree` DISABLE KEYS */;
/*!40000 ALTER TABLE `ScenarioTree` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SectorCapacitiesDiscrete`
--

DROP TABLE IF EXISTS `SectorCapacitiesDiscrete`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `SectorCapacitiesDiscrete` (
  `Sector_Id` varchar(20) NOT NULL,
  `Capacity` int(11) NOT NULL,
  `InitialTimeStep` int(11) NOT NULL,
  `FinalTimeStep` int(11) NOT NULL,
  PRIMARY KEY (`Sector_Id`,`InitialTimeStep`,`FinalTimeStep`),
  FOREIGN KEY (`Sector_Id`) 
	REFERENCES Sectors(`Sector_Id`)
  	ON DELETE NO ACTION
  	ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `SectorCapacitiesDiscrete`
--

LOCK TABLES `SectorCapacitiesDiscrete` WRITE;
/*!40000 ALTER TABLE `SectorCapacitiesDiscrete` DISABLE KEYS */;
/*!40000 ALTER TABLE `SectorCapacitiesDiscrete` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SectorCapacitiesTree`
--

DROP TABLE IF EXISTS `SectorCapacitiesTree`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `SectorCapacitiesTree` (
  `Sector_Id` varchar(20) NOT NULL,
  `Capacity` int(11) NOT NULL,
  `InitialTimeStep` int(11) NOT NULL,
  `FinalTimeStep` int(11) NOT NULL,
  `Node` int(11) NOT NULL,
  FOREIGN KEY (`Sector_Id`) 
	REFERENCES Sectors(`Sector_Id`)
  	ON DELETE NO ACTION
  	ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `SectorCapacitiesTree`
--

LOCK TABLES `SectorCapacitiesTree` WRITE;
/*!40000 ALTER TABLE `SectorCapacitiesTree` DISABLE KEYS */;
/*!40000 ALTER TABLE `SectorCapacitiesTree` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SolverParameters`
--

DROP TABLE IF EXISTS `SolverParameters`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `SolverParameters` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `maxTime` double NOT NULL,
  `numbSol` int(11) NOT NULL,
  `optGap` double NOT NULL,
  `intGap` double NOT NULL,
  `screen` int(11) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `SolverParameters`
--

LOCK TABLES `SolverParameters` WRITE;
/*!40000 ALTER TABLE `SolverParameters` DISABLE KEYS */;
INSERT INTO `SolverParameters` VALUES (1,7200,10,1e-06,1e-05,1);
/*!40000 ALTER TABLE `SolverParameters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Flights`
--

DROP TABLE IF EXISTS `Flights`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `Flights` (
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
  `AirportArrival`varchar(20) NOT NULL,
  `TimeDeparture` int(11) NOT NULL,
  PRIMARY KEY (`Flight_Id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `Flights`
--

LOCK TABLES `Flights` WRITE;
/*!40000 ALTER TABLE `Flights` DISABLE KEYS */;
/*!40000 ALTER TABLE `Flights` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

--
-- Table structure for table `Trajectories`
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
  FOREIGN KEY (`Flight_Id`) 
	REFERENCES flights(`Flight_Id`)
  	ON DELETE NO ACTION
  	ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Trajectories`
--

LOCK TABLES `Trajectories` WRITE;
/*!40000 ALTER TABLE `Trajectories` DISABLE KEYS */;
/*!40000 ALTER TABLE `Trajectories` ENABLE KEYS */;
UNLOCK TABLES;



--
-- Table structure for table `Times`
--

DROP TABLE IF EXISTS `times`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `times` (
  `First` int(10) NOT NULL,
  `Last` int(10) NOT NULL,
  PRIMARY KEY (`First`, `Last`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Times`
--

LOCK TABLES `Times` WRITE;
/*!40000 ALTER TABLE `Times` DISABLE KEYS */;
/*!40000 ALTER TABLE `Times` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Waypoints`
--

DROP TABLE IF EXISTS `Waypoints`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `Waypoints` (
  `Waypoint` varchar(20) NOT NULL,
  `Sector_Id` varchar(20) NOT NULL,
  PRIMARY KEY (`Waypoint`, `Sector_Id`),
  FOREIGN KEY (`Sector_Id`) 
	REFERENCES Sectors(`Sector_Id`)
  	ON DELETE NO ACTION
  	ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `Waypoints`
--

LOCK TABLES `Waypoints` WRITE;
/*!40000 ALTER TABLE `Waypoints` DISABLE KEYS */;
/*!40000 ALTER TABLE `Waypoints` ENABLE KEYS */;
UNLOCK TABLES;


/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;