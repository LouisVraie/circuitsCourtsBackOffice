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
-- Create Database
--
CREATE DATABASE dbCircuitsCourts;
USE dbCircuitsCourts;

--
-- Database user
--
GRANT ALL PRIVILEGES ON dbCircuitsCourts.* TO userCircuitsCourts@localhost IDENTIFIED BY '57-Ze!_eR';

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
INSERT INTO `Abonnement` VALUES (1,'2022-03-23','2023-03-23',100,2),(2,'2022-05-26','2023-05-26',101,2),(3,'2022-06-03','2022-12-03',102,3);
/*!40000 ALTER TABLE `Abonnement` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Activite`
--

DROP TABLE IF EXISTS `Activite`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Activite` (
  `numeroActivite` varchar(5) NOT NULL,
  `libelleActivite` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`numeroActivite`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Activite`
--

LOCK TABLES `Activite` WRITE;
/*!40000 ALTER TABLE `Activite` DISABLE KEYS */;
INSERT INTO `Activite` VALUES ('0111Z','Culture de céréales (à l\'exception du riz), de légumineuses et de graines oléagineuses'),('0112Z','Culture du riz'),('0113Z','Culture de légumes, de melons, de racines et de tubercules'),('0114Z','Culture de la canne à sucre'),('0115Z','Culture du tabac'),('0116Z','Culture de plantes à fibres'),('0119Z','Autres cultures non permanentes'),('0121Z','Culture de la vigne'),('0122Z','Culture de fruits tropicaux et subtropicaux'),('0123Z','Culture d\'agrumes'),('0124Z','Culture de fruits à pépins et à noyau'),('0125Z','Culture d\'autres fruits d\'arbres ou d\'arbustes et de fruits à coque'),('0126Z','Culture de fruits oléagineux'),('0127Z','Culture de plantes à boissons'),('0128Z','Culture de plantes à épices, aromatiques, médicinales et pharmaceutiques'),('0129Z','Autres cultures permanentes'),('0130Z','Reproduction de plantes'),('0141Z','Élevage de vaches laitières'),('0142Z','Élevage d\'autres bovins et de buffles'),('0143Z','Élevage de chevaux et d\'autres équidés'),('0144Z','Élevage de chameaux et d\'autres camélidés'),('0145Z','Élevage d\'ovins et de caprins'),('0146Z','Élevage de porcins'),('0147Z','Élevage de volailles'),('0149Z','Élevage d\'autres animaux'),('0150Z','Culture et élevage associés'),('0170Z','Chasse, piégeage et services annexes'),('0230Z','Récolte de produits forestiers non ligneux poussant à l\'état sauvage'),('0311Z','Pêche en mer'),('0312Z','Pêche en eau douce'),('0321Z','Aquaculture en mer'),('0322Z','Aquaculture en eau douce'),('0893Z','Production de sel'),('1011Z','Transformation et conservation de la viande de boucherie'),('1012Z','Transformation et conservation de la viande de volaille'),('1013B','Charcuterie'),('1020Z','Transformation et conservation de poisson, de crustacés et de mollusques'),('1031Z','Transformation et conservation de pommes de terre'),('1032Z','Préparation de jus de fruits et légumes'),('1039A','Autre transformation et conservation de légumes'),('1039B','Transformation et conservation de fruits'),('1041A','Fabrication d\'huiles et graisses brutes'),('1041B','Fabrication d\'huiles et graisses raffinées'),('1042Z','Fabrication de margarine et graisses comestibles similaires'),('1051A','Fabrication de lait liquide et de produits frais'),('1051B','Fabrication de beurre'),('1051C','Fabrication de fromage'),('1051D','Fabrication d\'autres produits laitiers'),('1052Z','Fabrication de glaces et sorbets'),('1061A','Meunerie'),('1061B','Autres activités du travail des grains'),('1062Z','Fabrication de produits amylacés'),('1071C','Boulangerie et boulangerie-pâtisserie'),('1071D','Pâtisserie'),('1072Z','Fabrication de biscuits, biscottes et pâtisseries de conservation'),('1073Z','Fabrication de pâtes alimentaires'),('1081Z','Fabrication de sucre'),('1082Z','Fabrication de cacao, chocolat et de produits de confiserie'),('1083Z','Transformation du thé et du café'),('1084Z','Fabrication de condiments et assaisonnements'),('1085Z','Fabrication de plats préparés'),('1086Z','Fabrication d\'aliments homogénéisés et diététiques'),('1089Z','Fabrication d\'autres produits alimentaires n.c.a.'),('1101Z','Production de boissons alcooliques distillées'),('1102A','Fabrication de vins effervescents'),('1102B','Vinification'),('1103Z','Fabrication de cidre et de vins de fruits'),('1104Z','Production d\'autres boissons fermentées non distillées'),('1105Z','Fabrication de bière'),('1106Z','Fabrication de malt'),('1107B','Production de boissons rafraîchissantes');
/*!40000 ALTER TABLE `Activite` ENABLE KEYS */;
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
INSERT INTO `Client` VALUES (1000,'Martin','Olivier','olivier.martin@gmail.com','06 74 45 38 78','31 Boulevard de la Libération','Gap','05000'),(1001,'Dotri','Fanny','fanny.dotri@gmail.com','06 15 61 35 36','89 Route de Tokoro','Gap','05000'),(1002,'Pemmari','Louis','louis.pemmari@gmail.com','07 15 78 39 36','Chemin des Abeilles','Chorges','05230'),(1003,'Oblir','Sabrina','sabrina.oblir@gmail.com','06 75 24 30 61','64 Avenue Commandant Dumond','Gap','05000'),(1004,'Kebir','Marc','marc.kebir@gmail.com','07 64 31 08 20','12 Route de Neffes','Gap','05000');
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
INSERT INTO `Commande` VALUES (100000,6.2,'2022-06-10',1000,1),(100001,12.5,'2022-06-11',1001,1),(100002,21.04,'2022-06-11',1002,1),(100003,23.86,'2022-06-13',1004,2),(100004,38.44,'2022-06-13',1001,2);
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
INSERT INTO `Contient` VALUES (2,100000,1),(1,100000,2),(1,100001,3),(2,100002,4),(1,100003,5),(1,100004,6),(1,100004,7);
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
INSERT INTO `Employe` VALUES (1,'ADMIN',NULL,NULL,'22 Rue de la Bastille','05070','Gap','super.admin@gmail.com','06 08 54 59 45','*2D1058E7C081583392B50D63C68CB22293A789E3',1,1),(2,'jdupond','Dupond','Jean','5 Boulevard Henri IV','06000','Nice','jean.dupont@gmail.com','06 58 49 87 78','*22B8C4410798DA75DD3200A96972A79AFC20CAC9',2,1),(3,'ldumas','Dumas','Lisa','78 Avenue Louis XIV','84000','Avignon','lisa.dumas@gmail.com','07 05 46 78 95','*22B8C4410798DA75DD3200A96972A79AFC20CAC9',3,1),(4,'jdubois','Dubois','Jeannette','45 Rue du Mazelle','05000','Gap','jeanne.dubois@gmail.com','06 85 47 78 98','*22B8C4410798DA75DD3200A96972A79AFC20CAC9',3,1),(5,'hlopez','Lopez','Henri','62 Lotissement des Papillons','05230','La Bâtie Neuve','henri.lopez@gmail.com','06 74 35 97 25','*22B8C4410798DA75DD3200A96972A79AFC20CAC9',2,1),(6,'jdupond2','Dupond','Jean','5 Boulevard Henri IV','06000','Nice','jean.dupont2@gmail.com','06 58 49 87 79','*22B8C4410798DA75DD3200A96972A79AFC20CAC9',2,0),(7,'jdupond500','Dupond','Jean','5 Boulevard Henri IV','06000','Nice','jean.dupont21@gmail.com','06 58 49 87 21','*2DF3063C523DF16DEFB8A454F9DA045D92D509BA',2,0);
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
  `cheminImageProducteur` varchar(256) DEFAULT NULL,
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
INSERT INTO `ImageProducteur` VALUES (1,'/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/imageProducteur/100scarole.png',100,10000,1);
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
INSERT INTO `Possede` VALUES (1000,100),(1001,101),(1001,102),(1002,102),(1003,100),(1003,102),(1004,101);
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
  `nomProducteur` varchar(30) DEFAULT NULL,
  `prenomProducteur` varchar(30) DEFAULT NULL,
  `adresseProducteur` varchar(50) DEFAULT NULL,
  `villeProducteur` varchar(30) DEFAULT NULL,
  `codePostalProducteur` varchar(5) DEFAULT NULL,
  `mailProducteur` varchar(50) DEFAULT NULL,
  `telProducteur` varchar(14) DEFAULT NULL,
  `mdpProducteur` varchar(30) DEFAULT NULL,
  `dateInscriptionProducteur` date DEFAULT NULL,
  `validationProducteur` tinyint(1) DEFAULT NULL,
  `raisonInvalidationProducteur` varchar(300) DEFAULT NULL,
  `activationProducteur` tinyint(1) NOT NULL DEFAULT 1,
  `numeroSirenProducteur` int(9) NOT NULL,
  `confirmationMailProducteur` tinyint(1) NOT NULL DEFAULT 0,
  `codeConfirmationMailProducteur` varchar(40) DEFAULT NULL,
  `latitudeProducteur` double(10,7) DEFAULT NULL,
  `longitudeProducteur` double(10,7) DEFAULT NULL,
  PRIMARY KEY (`numeroProducteur`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Producteur`
--

LOCK TABLES `Producteur` WRITE;
/*!40000 ALTER TABLE `Producteur` DISABLE KEYS */;
INSERT INTO `Producteur` VALUES (100,'Dupont','Jean','La Renardière, Route d\'Avançon','Valserres','05130','jean.dupont@gmail.com','06 45 24 03 27',NULL,'2022-03-23',1,NULL,1,589712421,0,NULL,NULL,NULL),(101,'Larade','Henri','466 Route des Papillons','La Bâtie-Neuve','05230','henri.larade@gmail.com','06 78 65 35 78',NULL,'2022-05-26',1,NULL,1,154229635,1,NULL,6.2078140,44.5676680),(102,'Gature','Emma','5 Chemin des Oliviers','Veynes','05400','emma.gature@gmail.com','07 29 35 54 35',NULL,'2022-06-03',1,NULL,1,207891568,1,NULL,5.8004170,44.5265800),(103,'Jezi','Antoine','Route de Côme','Toulon','83000','antoine.jezi@gmail.com','07 89 15 24 54',NULL,'2022-06-05',0,'Zone géographique incorrecte',0,300489261,1,NULL,NULL,NULL),(104,'Plomeri','Lara','Chemin du Moulin','Romette','05000','lara.plomeri@gmail.com','06 48 62 34 65',NULL,'2022-06-05',NULL,NULL,1,780064541,1,NULL,6.1113720,44.5804750);
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
  `imageProduit` varchar(256) DEFAULT NULL,
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
INSERT INTO `Produit` VALUES (1000,'Salade','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/produit/salade.png',4,'2022-04-12'),(1001,'Carotte','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/produit/carotte.png',4,'2022-04-12'),(1002,'Porc','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/produit/porc.png',2,'2022-04-12'),(1003,'Poire','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/produit/poire.png',3,'2022-06-09');
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
INSERT INTO `ProduitProducteur` VALUES (1,35.3,1.2,'2022-06-07',100,1,1,10000,1),(2,20.5,4,'2022-06-07',100,1,1,10003,NULL),(3,6,12.5,'2022-06-09',102,1,2,10004,NULL),(4,4,10.52,'2022-06-09',102,1,2,10005,NULL),(5,5.76,23.86,'2022-06-13',101,2,1,10008,NULL),(6,4.6,18.99,'2022-06-13',101,2,1,10006,NULL),(7,3.25,19.45,'2022-06-13',101,2,1,10007,NULL);
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
INSERT INTO `Profession` VALUES (100,1),(101,2),(101,3),(102,4),(103,2),(104,1),(104,4);
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
  `imageRayon` varchar(256) DEFAULT NULL,
  `dateInscriptionRayon` date DEFAULT NULL,
  PRIMARY KEY (`numeroRayon`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Rayon`
--

LOCK TABLES `Rayon` WRITE;
/*!40000 ALTER TABLE `Rayon` DISABLE KEYS */;
INSERT INTO `Rayon` VALUES (1,'Volaille, oeuf','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/rayon/volailleOeuf.png','2022-04-12'),(2,'Boucherie','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/rayon/boucherie.png','2022-04-12'),(3,'Fruit','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/rayon/fruit.png','2022-04-12'),(4,'Légume','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/rayon/legume.png','2022-04-12');
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
INSERT INTO `Semaine` VALUES (1,'2022-06-06','2022-06-12'),(2,'2022-06-13','2022-06-19');
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
INSERT INTO `Ticket` VALUES (1,'348e88567bdce2f8ac47cd3c9121950f',1,100,1000),(2,'890e5c57afcea4d5293f246b90bf689b',1,102,1001),(3,'4397626badee48658e2f86945fed80df',1,102,1002),(4,'657eef5ca28b6f457752c34e56d74424',2,101,1001),(5,'b5eb852aac5044b151d398b51ef92f72',2,101,1004);
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
INSERT INTO `TypeAbonnement` VALUES (1,'Mensuel',20,1),(2,'Annuel',100,12),(3,'Semestriel',70,6);
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
INSERT INTO `TypeProducteur` VALUES (1,'Maraîcher'),(2,'Boucher'),(3,'Charcutier'),(4,'Arboriculteur'),(5,'Éleveur');
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
  `imageVariete` varchar(256) DEFAULT NULL,
  `numeroProduit` int(11) NOT NULL,
  `dateInscriptionVariete` date DEFAULT NULL,
  `estValide` tinyint(1) NOT NULL DEFAULT 0,
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
INSERT INTO `Variete` VALUES (10000,'Scarole','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/variete/scarole.png',1000,'2022-04-12',1),(10001,'Frisée','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/variete/frisee.png',1000,'2022-04-12',0),(10002,'Mâche','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/variete/mache.png',1000,'2022-04-12',1),(10003,'Mesclun','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/variete/mesclun.png',1000,'2022-04-12',1),(10004,'William','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/variete/william.png',1003,'2022-06-09',1),(10005,'Général Leclerc','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/variete/general-leclerc.png',1003,'2022-06-09',1),(10006,'Saucisses aux herbes','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/variete/saucisses-aux-herbes.png',1002,'2022-06-13',1),(10007,'Merguez','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/variete/merguez.png',1002,'2022-06-13',1),(10008,'Rôti dans l\'échine','/home/lvraie/sio2/GitHub/circuitsCourtsBackOffice/images/variete/roti-echine-de-porc.png',1002,'2022-06-13',1);
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

-- Dump completed on 2022-06-13 10:39:39
