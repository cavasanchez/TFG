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
INSERT INTO `airportcapacitiesdiscrete` VALUES ('A145',38,35,0,360),('A146',38,35,0,360),('A147',38,35,0,360),('A148',38,35,0,360),('A149',38,35,0,360),('A150',38,35,0,360),('A151',38,35,0,360),('A152',38,35,0,360),('A153',38,35,0,360),('A154',38,35,0,360),('A155',38,35,0,360),('A156',38,35,0,360),('A157',38,35,0,360),('A158',38,35,0,360),('A159',38,35,0,360),('A160',38,35,0,360),('A161',38,35,0,360),('A162',38,35,0,360),('A163',38,35,0,360),('A164',38,35,0,360),('A165',38,35,0,360),('A166',38,35,0,360),('A167',38,35,0,360),('A168',38,35,0,360),('A169',38,35,0,360),('A170',38,35,0,360),('A171',38,35,0,360),('A172',38,35,0,360),('A173',38,35,0,360),('A174',38,35,0,360);
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

-- Dump completed on 2017-06-25 13:22:06
