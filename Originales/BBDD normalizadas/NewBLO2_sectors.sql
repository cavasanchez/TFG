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
-- Table structure for table `sectors`
--

DROP TABLE IF EXISTS `sectors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sectors` (
  `Sector_Id` varchar(20) NOT NULL,
  PRIMARY KEY (`Sector_Id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sectors`
--

LOCK TABLES `sectors` WRITE;
/*!40000 ALTER TABLE `sectors` DISABLE KEYS */;
INSERT INTO `sectors` VALUES ('0.00'),('1.00'),('10.00'),('100.00'),('101.00'),('102.00'),('103.00'),('104.00'),('105.00'),('106.00'),('107.00'),('108.00'),('109.00'),('11.00'),('110.00'),('111.00'),('12.00'),('13.00'),('14.00'),('15.00'),('16.00'),('17.00'),('18.00'),('19.00'),('2.00'),('20.00'),('21.00'),('22.00'),('23.00'),('24.00'),('25.00'),('26.00'),('27.00'),('28.00'),('29.00'),('3.00'),('30.00'),('31.00'),('32.00'),('33.00'),('34.00'),('35.00'),('36.00'),('37.00'),('38.00'),('39.00'),('4.00'),('40.00'),('41.00'),('42.00'),('43.00'),('44.00'),('45.00'),('46.00'),('47.00'),('48.00'),('49.00'),('5.00'),('50.00'),('51.00'),('52.00'),('53.00'),('54.00'),('55.00'),('56.00'),('57.00'),('58.00'),('59.00'),('6.00'),('60.00'),('61.00'),('62.00'),('63.00'),('64.00'),('65.00'),('66.00'),('67.00'),('68.00'),('69.00'),('7.00'),('70.00'),('71.00'),('72.00'),('73.00'),('74.00'),('75.00'),('76.00'),('77.00'),('78.00'),('79.00'),('8.00'),('80.00'),('81.00'),('82.00'),('83.00'),('84.00'),('85.00'),('86.00'),('87.00'),('88.00'),('89.00'),('9.00'),('90.00'),('91.00'),('92.00'),('93.00'),('94.00'),('95.00'),('96.00'),('97.00'),('98.00'),('99.00');
/*!40000 ALTER TABLE `sectors` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-06-25 13:22:04
