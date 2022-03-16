-- MySQL dump 10.19  Distrib 10.3.31-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: dbCircuitsCourts
-- ------------------------------------------------------
-- Server version	10.3.31-MariaDB-0+deb10u1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Abonnement`
--

DROP TABLE IF EXISTS `Abonnement`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Abonnement` (
  `numeroAbonnement` int(11) NOT NULL,
  `dateDebAbonnement` date DEFAULT NULL,
  `dateFinAbonnement` date DEFAULT NULL,
  `numeroProducteur` int(11) NOT NULL,
  `numeroTypeAbonnement` int(11) NOT NULL,
  PRIMARY KEY (`numeroAbonnement`),
  KEY `numeroProducteur` (`numeroProducteur`),
  KEY `numeroTypeAbonnement` (`numeroTypeAbonnement`),
  CONSTRAINT `Abonnement_ibfk_1` FOREIGN KEY (`numeroProducteur`) REFERENCES `Producteur` (`numeroProducteur`),
  CONSTRAINT `Abonnement_ibfk_2` FOREIGN KEY (`numeroTypeAbonnement`) REFERENCES `TypeAbonnement` (`numeroTypeAbonnement`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Abonnement`
--

LOCK TABLES `Abonnement` WRITE;
/*!40000 ALTER TABLE `Abonnement` DISABLE KEYS */;
INSERT INTO `Abonnement` VALUES (1,'2021-09-09','2022-09-09',100,2);
/*!40000 ALTER TABLE `Abonnement` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Client`
--

DROP TABLE IF EXISTS `Client`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Client` (
  `numeroClient` int(11) NOT NULL,
  `nomClient` varchar(25) DEFAULT NULL,
  `prenomClient` varchar(25) DEFAULT NULL,
  `mailClient` varchar(50) DEFAULT NULL,
  `telClient` varchar(14) DEFAULT NULL,
  `adresseClient` varchar(50) DEFAULT NULL,
  `villeClient` varchar(30) DEFAULT NULL,
  `codePostalClient` varchar(5) DEFAULT NULL,
  PRIMARY KEY (`numeroClient`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Client`
--

LOCK TABLES `Client` WRITE;
/*!40000 ALTER TABLE `Client` DISABLE KEYS */;
INSERT INTO `Client` VALUES (1000,NULL,NULL,'olivier.martin@gmail.com',NULL,NULL,NULL,NULL);
/*!40000 ALTER TABLE `Client` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Commande`
--

DROP TABLE IF EXISTS `Commande`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Commande` (
  `numeroCommande` int(11) NOT NULL,
  `prixCommande` float DEFAULT NULL,
  `dateRetraitCommande` date DEFAULT NULL,
  `numeroClient` int(11) NOT NULL,
  `numeroSemaine` int(11) NOT NULL,
  PRIMARY KEY (`numeroCommande`),
  KEY `numeroClient` (`numeroClient`),
  KEY `numeroSemaine` (`numeroSemaine`),
  CONSTRAINT `Commande_ibfk_1` FOREIGN KEY (`numeroClient`) REFERENCES `Client` (`numeroClient`),
  CONSTRAINT `Commande_ibfk_2` FOREIGN KEY (`numeroSemaine`) REFERENCES `Semaine` (`numeroSemaine`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Commande`
--

LOCK TABLES `Commande` WRITE;
/*!40000 ALTER TABLE `Commande` DISABLE KEYS */;
INSERT INTO `Commande` VALUES (100000,6.2,'2021-11-25',1000,1);
/*!40000 ALTER TABLE `Commande` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Contient`
--

DROP TABLE IF EXISTS `Contient`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Contient` (
  `quantiteContient` float DEFAULT NULL,
  `numeroCommande` int(11) NOT NULL,
  `numeroProduitProducteur` int(11) NOT NULL,
  PRIMARY KEY (`numeroCommande`,`numeroProduitProducteur`),
  KEY `numeroProduitProducteur` (`numeroProduitProducteur`),
  CONSTRAINT `Contient_ibfk_1` FOREIGN KEY (`numeroCommande`) REFERENCES `Commande` (`numeroCommande`),
  CONSTRAINT `Contient_ibfk_2` FOREIGN KEY (`numeroProduitProducteur`) REFERENCES `ProduitProducteur` (`numeroProduitProducteur`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Contient`
--

LOCK TABLES `Contient` WRITE;
/*!40000 ALTER TABLE `Contient` DISABLE KEYS */;
INSERT INTO `Contient` VALUES (2,100000,1),(1,100000,2);
/*!40000 ALTER TABLE `Contient` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Employe`
--

DROP TABLE IF EXISTS `Employe`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Employe` (
  `numeroEmploye` int(11) NOT NULL,
  `loginEmploye` varchar(25) DEFAULT NULL,
  `nomEmploye` varchar(25) DEFAULT NULL,
  `prenomEmploye` varchar(25) DEFAULT NULL,
  `adresseEmploye` varchar(50) DEFAULT NULL,
  `codePostalEmploye` varchar(5) DEFAULT NULL,
  `villeEmploye` varchar(30) DEFAULT NULL,
  `mailEmploye` varchar(50) DEFAULT NULL,
  `telEmploye` varchar(17) DEFAULT NULL,
  `motDePasseEmploye` varchar(41) DEFAULT NULL,
  `numeroTypeEmploye` int(11) NOT NULL,
  `estActif` tinyint(1) NOT NULL DEFAULT 1,
  PRIMARY KEY (`numeroEmploye`),
  KEY `numeroTypeEmploye` (`numeroTypeEmploye`),
  CONSTRAINT `Employe_ibfk_1` FOREIGN KEY (`numeroTypeEmploye`) REFERENCES `TypeEmploye` (`numeroTypeEmploye`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Employe`
--

LOCK TABLES `Employe` WRITE;
/*!40000 ALTER TABLE `Employe` DISABLE KEYS */;
INSERT INTO `Employe` VALUES (1,'ADMIN',NULL,NULL,'22 Rue de la Bastille','05070','Gap','super.admin@gmail.com','06 08 54 59 45','*2D1058E7C081583392B50D63C68CB22293A789E3',1,1),(2,'jdupond','Dupond','Jean','5 Boulevard Henri IV','06000','Nice','jean.dupont@gmail.com','06 58 49 87 78','*22B8C4410798DA75DD3200A96972A79AFC20CAC9',2,1),(3,'ldumas','Dumas','Lisa','78 Avenue LouisXIV','84000','Avignon','lisa.dumas@gmail.com','07 05 46 78 95','*22B8C4410798DA75DD3200A96972A79AFC20CAC9',3,1);
/*!40000 ALTER TABLE `Employe` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ImageProducteur`
--

DROP TABLE IF EXISTS `ImageProducteur`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ImageProducteur` (
  `numeroImageProducteur` int(11) NOT NULL,
  `cheminImageProducteur` varchar(75) DEFAULT NULL,
  `numeroProducteur` int(11) NOT NULL,
  `numeroVariete` int(11) NOT NULL,
  `numeroSemaine` int(11) NOT NULL,
  PRIMARY KEY (`numeroImageProducteur`),
  KEY `numeroProducteur` (`numeroProducteur`),
  KEY `numeroVariete` (`numeroVariete`),
  KEY `numeroSemaine` (`numeroSemaine`),
  CONSTRAINT `ImageProducteur_ibfk_1` FOREIGN KEY (`numeroProducteur`) REFERENCES `Producteur` (`numeroProducteur`),
  CONSTRAINT `ImageProducteur_ibfk_2` FOREIGN KEY (`numeroVariete`) REFERENCES `Variete` (`numeroVariete`),
  CONSTRAINT `ImageProducteur_ibfk_3` FOREIGN KEY (`numeroSemaine`) REFERENCES `Semaine` (`numeroSemaine`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ImageProducteur`
--

LOCK TABLES `ImageProducteur` WRITE;
/*!40000 ALTER TABLE `ImageProducteur` DISABLE KEYS */;
INSERT INTO `ImageProducteur` VALUES (1,'images/imageProducteur/100scarole.png',100,10000,1);
/*!40000 ALTER TABLE `ImageProducteur` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Possede`
--

DROP TABLE IF EXISTS `Possede`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Possede` (
  `numeroClient` int(11) NOT NULL,
  `numeroProducteur` int(11) NOT NULL,
  PRIMARY KEY (`numeroClient`,`numeroProducteur`),
  KEY `numeroProducteur` (`numeroProducteur`),
  CONSTRAINT `Possede_ibfk_1` FOREIGN KEY (`numeroClient`) REFERENCES `Client` (`numeroClient`),
  CONSTRAINT `Possede_ibfk_2` FOREIGN KEY (`numeroProducteur`) REFERENCES `Producteur` (`numeroProducteur`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Possede`
--

LOCK TABLES `Possede` WRITE;
/*!40000 ALTER TABLE `Possede` DISABLE KEYS */;
INSERT INTO `Possede` VALUES (1000,100);
/*!40000 ALTER TABLE `Possede` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Producteur`
--

DROP TABLE IF EXISTS `Producteur`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Producteur` (
  `numeroProducteur` int(11) NOT NULL,
  `nomProducteur` varchar(25) DEFAULT NULL,
  `prenomProducteur` varchar(25) DEFAULT NULL,
  `adresseProducteur` varchar(50) DEFAULT NULL,
  `villeProducteur` varchar(30) DEFAULT NULL,
  `codePostalProducteur` varchar(5) DEFAULT NULL,
  `mailProducteur` varchar(50) DEFAULT NULL,
  `telProducteur` varchar(14) DEFAULT NULL,
  `mdpProducteur` varchar(30) DEFAULT NULL,
  `dateInscriptionProducteur` date DEFAULT NULL,
  `validationProducteur` tinyint(1) DEFAULT 0,
  `raisonInvalidationProducteur` varchar(300) DEFAULT NULL,
  `activationProducteur` tinyint(1) DEFAULT 1,
  PRIMARY KEY (`numeroProducteur`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Producteur`
--

LOCK TABLES `Producteur` WRITE;
/*!40000 ALTER TABLE `Producteur` DISABLE KEYS */;
INSERT INTO `Producteur` VALUES (100,'Dupont','Jean','La Renardière, Route d\'Avançon','Valserres','05130','jean.dupont@gmail.com','06 45 24 03 27',NULL,NULL,NULL,NULL,NULL);
/*!40000 ALTER TABLE `Producteur` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Produit`
--

DROP TABLE IF EXISTS `Produit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Produit` (
  `numeroProduit` int(11) NOT NULL,
  `libelleProduit` varchar(25) DEFAULT NULL,
  `imageProduit` varchar(75) DEFAULT NULL,
  `numeroRayon` int(11) NOT NULL,
  `dateInscriptionProduit` date DEFAULT NULL,
  PRIMARY KEY (`numeroProduit`),
  KEY `numeroRayon` (`numeroRayon`),
  CONSTRAINT `Produit_ibfk_1` FOREIGN KEY (`numeroRayon`) REFERENCES `Rayon` (`numeroRayon`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Produit`
--

LOCK TABLES `Produit` WRITE;
/*!40000 ALTER TABLE `Produit` DISABLE KEYS */;
INSERT INTO `Produit` VALUES (1000,'Salade','images/produit/salade.png',4,NULL),(1001,'Carotte','images/produit/carotte.png',4,NULL),(1002,'Porc','images/produit/porc.png',2,NULL);
/*!40000 ALTER TABLE `Produit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ProduitProducteur`
--

DROP TABLE IF EXISTS `ProduitProducteur`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ProduitProducteur` (
  `numeroProduitProducteur` int(11) NOT NULL,
  `quantiteProduitProducteur` float DEFAULT NULL,
  `prixUnitaireProduitProducteur` float DEFAULT NULL,
  `dateAjoutProduitProducteur` date DEFAULT NULL,
  `numeroProducteur` int(11) NOT NULL,
  `numeroSemaine` int(11) NOT NULL,
  `numeroUnite` int(11) NOT NULL,
  `numeroVariete` int(11) NOT NULL,
  `numeroImageProducteur` int(11) DEFAULT NULL,
  PRIMARY KEY (`numeroProduitProducteur`),
  KEY `numeroProducteur` (`numeroProducteur`),
  KEY `numeroSemaine` (`numeroSemaine`),
  KEY `numeroUnite` (`numeroUnite`),
  KEY `numeroVariete` (`numeroVariete`),
  KEY `numeroImageProducteur` (`numeroImageProducteur`),
  CONSTRAINT `ProduitProducteur_ibfk_1` FOREIGN KEY (`numeroProducteur`) REFERENCES `Producteur` (`numeroProducteur`),
  CONSTRAINT `ProduitProducteur_ibfk_2` FOREIGN KEY (`numeroSemaine`) REFERENCES `Semaine` (`numeroSemaine`),
  CONSTRAINT `ProduitProducteur_ibfk_3` FOREIGN KEY (`numeroUnite`) REFERENCES `Unite` (`numeroUnite`),
  CONSTRAINT `ProduitProducteur_ibfk_4` FOREIGN KEY (`numeroVariete`) REFERENCES `Variete` (`numeroVariete`),
  CONSTRAINT `ProduitProducteur_ibfk_5` FOREIGN KEY (`numeroImageProducteur`) REFERENCES `ImageProducteur` (`numeroImageProducteur`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ProduitProducteur`
--

LOCK TABLES `ProduitProducteur` WRITE;
/*!40000 ALTER TABLE `ProduitProducteur` DISABLE KEYS */;
INSERT INTO `ProduitProducteur` VALUES (1,35.3,1.2,'2021-11-23',100,1,1,10000,1),(2,20.5,4,'2021-11-23',100,1,1,10003,NULL);
/*!40000 ALTER TABLE `ProduitProducteur` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Profession`
--

DROP TABLE IF EXISTS `Profession`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Profession` (
  `numeroProducteur` int(11) NOT NULL,
  `numeroTypeProducteur` int(11) NOT NULL,
  PRIMARY KEY (`numeroProducteur`,`numeroTypeProducteur`),
  KEY `numeroTypeProducteur` (`numeroTypeProducteur`),
  CONSTRAINT `Profession_ibfk_1` FOREIGN KEY (`numeroProducteur`) REFERENCES `Producteur` (`numeroProducteur`),
  CONSTRAINT `Profession_ibfk_2` FOREIGN KEY (`numeroTypeProducteur`) REFERENCES `TypeProducteur` (`numeroTypeProducteur`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Profession`
--

LOCK TABLES `Profession` WRITE;
/*!40000 ALTER TABLE `Profession` DISABLE KEYS */;
INSERT INTO `Profession` VALUES (100,1);
/*!40000 ALTER TABLE `Profession` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Rayon`
--

DROP TABLE IF EXISTS `Rayon`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Rayon` (
  `numeroRayon` int(11) NOT NULL,
  `libelleRayon` varchar(25) DEFAULT NULL,
  `imageRayon` varchar(75) DEFAULT NULL,
  `dateInscriptionRayon` date DEFAULT NULL,
  PRIMARY KEY (`numeroRayon`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Rayon`
--

LOCK TABLES `Rayon` WRITE;
/*!40000 ALTER TABLE `Rayon` DISABLE KEYS */;
INSERT INTO `Rayon` VALUES (1,'Volaille, oeuf','images/rayon/volailleOeuf.png',NULL),(2,'Boucherie','images/rayon/boucherie.png',NULL),(3,'Fruit','images/rayon/fruit.png',NULL),(4,'Légume','images/rayon/legume.png',NULL);
/*!40000 ALTER TABLE `Rayon` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Semaine`
--

DROP TABLE IF EXISTS `Semaine`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Semaine` (
  `numeroSemaine` int(11) NOT NULL,
  `dateDebSemaine` date DEFAULT NULL,
  `dateFinSemaine` date DEFAULT NULL,
  PRIMARY KEY (`numeroSemaine`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Semaine`
--

LOCK TABLES `Semaine` WRITE;
/*!40000 ALTER TABLE `Semaine` DISABLE KEYS */;
INSERT INTO `Semaine` VALUES (1,'2021-11-22','2021-11-28');
/*!40000 ALTER TABLE `Semaine` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Ticket`
--

DROP TABLE IF EXISTS `Ticket`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Ticket` (
  `numeroTicket` int(11) NOT NULL,
  `cleTicket` varchar(75) DEFAULT NULL,
  `numeroSemaine` int(11) NOT NULL,
  `numeroProducteur` int(11) NOT NULL,
  `numeroClient` int(11) NOT NULL,
  PRIMARY KEY (`numeroTicket`),
  KEY `numeroSemaine` (`numeroSemaine`),
  KEY `numeroProducteur` (`numeroProducteur`),
  KEY `numeroClient` (`numeroClient`),
  CONSTRAINT `Ticket_ibfk_1` FOREIGN KEY (`numeroSemaine`) REFERENCES `Semaine` (`numeroSemaine`),
  CONSTRAINT `Ticket_ibfk_2` FOREIGN KEY (`numeroProducteur`) REFERENCES `Producteur` (`numeroProducteur`),
  CONSTRAINT `Ticket_ibfk_3` FOREIGN KEY (`numeroClient`) REFERENCES `Client` (`numeroClient`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Ticket`
--

LOCK TABLES `Ticket` WRITE;
/*!40000 ALTER TABLE `Ticket` DISABLE KEYS */;
INSERT INTO `Ticket` VALUES (1,'348e88567bdce2f8ac47cd3c9121950f',1,100,1000);
/*!40000 ALTER TABLE `Ticket` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TypeAbonnement`
--

DROP TABLE IF EXISTS `TypeAbonnement`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TypeAbonnement` (
  `numeroTypeAbonnement` int(11) NOT NULL,
  `libelleTypeAbonnement` varchar(25) DEFAULT NULL,
  `prixTypeAbonnement` float DEFAULT NULL,
  `dureeMoisAbonnement` int(11) DEFAULT NULL,
  PRIMARY KEY (`numeroTypeAbonnement`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TypeAbonnement`
--

LOCK TABLES `TypeAbonnement` WRITE;
/*!40000 ALTER TABLE `TypeAbonnement` DISABLE KEYS */;
INSERT INTO `TypeAbonnement` VALUES (1,'Mensuel',20,1),(2,'Annuel',100,12);
/*!40000 ALTER TABLE `TypeAbonnement` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TypeEmploye`
--

DROP TABLE IF EXISTS `TypeEmploye`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TypeEmploye` (
  `numeroTypeEmploye` int(11) NOT NULL,
  `libelleTypeEmploye` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`numeroTypeEmploye`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TypeEmploye`
--

LOCK TABLES `TypeEmploye` WRITE;
/*!40000 ALTER TABLE `TypeEmploye` DISABLE KEYS */;
INSERT INTO `TypeEmploye` VALUES (1,'SuperAdmin'),(2,'Administrateur'),(3,'Modérateur');
/*!40000 ALTER TABLE `TypeEmploye` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TypeProducteur`
--

DROP TABLE IF EXISTS `TypeProducteur`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `TypeProducteur` (
  `numeroTypeProducteur` int(11) NOT NULL,
  `libelleTypeProducteur` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`numeroTypeProducteur`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TypeProducteur`
--

LOCK TABLES `TypeProducteur` WRITE;
/*!40000 ALTER TABLE `TypeProducteur` DISABLE KEYS */;
INSERT INTO `TypeProducteur` VALUES (1,'Maraicher'),(2,'Boucher');
/*!40000 ALTER TABLE `TypeProducteur` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Unite`
--

DROP TABLE IF EXISTS `Unite`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Unite` (
  `numeroUnite` int(11) NOT NULL,
  `libelleUnite` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`numeroUnite`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Unite`
--

LOCK TABLES `Unite` WRITE;
/*!40000 ALTER TABLE `Unite` DISABLE KEYS */;
INSERT INTO `Unite` VALUES (1,'kg'),(2,'Cagette'),(3,'Barquette');
/*!40000 ALTER TABLE `Unite` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Variete`
--

DROP TABLE IF EXISTS `Variete`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Variete` (
  `numeroVariete` int(11) NOT NULL,
  `libelleVariete` varchar(25) DEFAULT NULL,
  `imageVariete` varchar(75) DEFAULT NULL,
  `numeroProduit` int(11) NOT NULL,
  `dateInscriptionVariete` date DEFAULT NULL,
  PRIMARY KEY (`numeroVariete`),
  KEY `numeroProduit` (`numeroProduit`),
  CONSTRAINT `Variete_ibfk_1` FOREIGN KEY (`numeroProduit`) REFERENCES `Produit` (`numeroProduit`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Variete`
--

LOCK TABLES `Variete` WRITE;
/*!40000 ALTER TABLE `Variete` DISABLE KEYS */;
INSERT INTO `Variete` VALUES (10000,'Scarole','images/variete/scarole.png',1000,NULL),(10001,'Frisée','images/variete/frisee.png',1000,NULL),(10002,'Mâche','images/variete/mache.png',1000,NULL),(10003,'Mesclun','images/variete/mesclun.png',1000,NULL);
/*!40000 ALTER TABLE `Variete` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-03-16 16:43:07
