-- MySQL dump 10.13  Distrib 5.7.18, for Linux (x86_64)
--
-- Host: 127.0.0.1    Database: NewBLO2
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
INSERT INTO `sectorcapacitiesdiscrete` VALUES ('0.00',88,0,360),('1.00',88,0,360),('10.00',88,0,360),('100.00',88,0,360),('101.00',88,0,360),('102.00',88,0,360),('103.00',88,0,360),('104.00',88,0,360),('105.00',88,0,360),('106.00',88,0,360),('107.00',88,0,360),('108.00',88,0,360),('109.00',88,0,360),('11.00',88,0,360),('110.00',88,0,360),('111.00',88,0,360),('12.00',88,0,360),('13.00',88,0,360),('14.00',88,0,360),('15.00',88,0,360),('16.00',88,0,360),('17.00',88,0,360),('18.00',88,0,360),('19.00',88,0,360),('2.00',88,0,360),('20.00',88,0,360),('21.00',88,0,360),('22.00',88,0,360),('23.00',88,0,360),('24.00',88,0,360),('25.00',88,0,360),('26.00',88,0,360),('27.00',88,0,360),('28.00',88,0,360),('29.00',88,0,360),('3.00',88,0,360),('30.00',88,0,360),('31.00',88,0,360),('32.00',88,0,360),('33.00',88,0,360),('34.00',88,0,360),('35.00',88,0,360),('36.00',88,0,360),('37.00',88,0,360),('38.00',88,0,360),('39.00',88,0,360),('4.00',88,0,360),('40.00',88,0,360),('41.00',88,0,360),('42.00',88,0,360),('43.00',88,0,360),('44.00',88,0,360),('45.00',88,0,360),('46.00',88,0,360),('47.00',88,0,360),('48.00',88,0,360),('49.00',88,0,360),('5.00',88,0,360),('50.00',88,0,360),('51.00',88,0,360),('52.00',88,0,360),('53.00',88,0,360),('54.00',88,0,360),('55.00',88,0,360),('56.00',88,0,360),('57.00',88,0,360),('58.00',88,0,360),('59.00',88,0,360),('6.00',88,0,360),('60.00',88,0,360),('61.00',88,0,360),('62.00',88,0,360),('63.00',88,0,360),('64.00',88,0,360),('65.00',88,0,360),('66.00',88,0,360),('67.00',88,0,360),('68.00',88,0,360),('69.00',88,0,360),('7.00',88,0,360),('70.00',88,0,360),('71.00',88,0,360),('72.00',88,0,360),('73.00',88,0,360),('74.00',88,0,360),('75.00',88,0,360),('76.00',88,0,360),('77.00',88,0,360),('78.00',88,0,360),('79.00',88,0,360),('8.00',88,0,360),('80.00',88,0,360),('81.00',88,0,360),('82.00',88,0,360),('83.00',88,0,360),('84.00',88,0,360),('85.00',88,0,360),('86.00',88,0,360),('87.00',88,0,360),('88.00',88,0,360),('89.00',88,0,360),('9.00',88,0,360),('90.00',88,0,360),('91.00',88,0,360),('92.00',88,0,360),('93.00',88,0,360),('94.00',88,0,360),('95.00',88,0,360),('96.00',88,0,360),('97.00',88,0,360),('98.00',88,0,360),('99.00',88,0,360);
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

-- Dump completed on 2017-06-25 13:22:05
