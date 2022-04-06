#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::initGestionProduits
 * Méthode publique de la classe MainWindow qui initialise les méthodes du tab 'Gestion Produits'
 */
void MainWindow::initGestionProduits()
{
    qDebug()<<"void MainWindow::initGestionProduits()";

    //on stretch les tableaux
    ui->tableWidget_gestionProduitsRayons->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_gestionProduitsProduits->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //taille des images en pixel
    imageSize = 125;

    //on affiche le contenu des tableaux
    afficherTableGestionProduitsRayons();
    afficherTableGestionProduitsProduits();
}

/**
 * @brief MainWindow::afficherTableGestionProduitsRayons
 * Méthode publique de la classe MainWindow qui affiche les rayons des produits dans le tableau de l'onglet Rayons de Gestion Produits
 */
void MainWindow::afficherTableGestionProduitsRayons()
{
    qDebug()<<"void MainWindow::afficherTableGestionProduitsRayons()";
    //requête qui récupère les rayons
    QString reqSelectRayons = "SELECT r.numeroRayon, r.libelleRayon, r.imageRayon, r.dateInscriptionRayon FROM Rayon r";
    qDebug()<<reqSelectRayons;
    QSqlQuery resultSelectRayons(reqSelectRayons);

    while(resultSelectRayons.next()){
        //on récupère le numéro de la dernière ligne
        int row = ui->tableWidget_gestionProduitsRayons->rowCount();
        ui->tableWidget_gestionProduitsRayons->setRowCount(row+1);
        //on crée une instance de QLabel qui va contenir l'image du rayon
        QLabel *labelImage= new QLabel();
        labelImage->setPixmap(QPixmap(resultSelectRayons.value("imageRayon").toString()).scaled(imageSize,imageSize));
        labelImage->setScaledContents(true);
        //inserer les valeur dans le tableau
        ui->tableWidget_gestionProduitsRayons->setCellWidget(row,0, new QCheckBox());
        ui->tableWidget_gestionProduitsRayons->setItem(row,1, new QTableWidgetItem(resultSelectRayons.value("numeroRayon").toString()));
        ui->tableWidget_gestionProduitsRayons->setItem(row,2, new QTableWidgetItem(resultSelectRayons.value("dateInscriptionRayon").toString()));
        ui->tableWidget_gestionProduitsRayons->setCellWidget(row,3,labelImage);
        ui->tableWidget_gestionProduitsRayons->setItem(row,4, new QTableWidgetItem(resultSelectRayons.value("libelleRayon").toString()));
    }
    ui->tableWidget_gestionProduitsRayons->resizeColumnsToContents();
    ui->tableWidget_gestionProduitsRayons->resizeRowsToContents();
    ui->tableWidget_gestionProduitsRayons->update();
}

/**
 * @brief MainWindow::afficherTableGestionProduitsProduits
 * Méthode publique de la classe MainWindow qui affiche les produits dans le tableau de l'onglet Produits de Gestion Produits
 */
void MainWindow::afficherTableGestionProduitsProduits()
{
    qDebug()<<"void MainWindow::afficherTableGestionProduitsProduits()";
    //requête qui récupère les produits
    QString reqSelectProduits = "SELECT p.numeroProduit, p.libelleProduit, p.imageProduit, p.dateInscriptionProduit, r.libelleRayon "
                                "FROM Produit p "
                                "INNER JOIN Rayon r ON r.numeroRayon = p.numeroRayon "
                                "ORDER BY p.numeroProduit ASC";
    qDebug()<<reqSelectProduits;
    QSqlQuery resultSelectProduits(reqSelectProduits);

    while(resultSelectProduits.next()){
        //on récupère le numéro de la dernière ligne
        int row = ui->tableWidget_gestionProduitsProduits->rowCount();
        ui->tableWidget_gestionProduitsProduits->setRowCount(row+1);
        //on crée une instance de QLabel qui va contenir l'image du produit
        QLabel *labelImage= new QLabel();
        labelImage->setPixmap(QPixmap(resultSelectProduits.value("imageProduit").toString()).scaled(imageSize,imageSize));
        labelImage->setScaledContents(true);
        //inserer les valeur dans le tableau
        ui->tableWidget_gestionProduitsProduits->setCellWidget(row,0, new QCheckBox());
        ui->tableWidget_gestionProduitsProduits->setItem(row,1, new QTableWidgetItem(resultSelectProduits.value("numeroProduit").toString()));
        ui->tableWidget_gestionProduitsProduits->setItem(row,2, new QTableWidgetItem(resultSelectProduits.value("dateInscriptionProduit").toString()));
        ui->tableWidget_gestionProduitsProduits->setCellWidget(row,3,labelImage);
        ui->tableWidget_gestionProduitsProduits->setItem(row,4, new QTableWidgetItem(resultSelectProduits.value("libelleRayon").toString()));
        ui->tableWidget_gestionProduitsProduits->setItem(row,5, new QTableWidgetItem(resultSelectProduits.value("libelleProduit").toString()));
    }
    ui->tableWidget_gestionProduitsProduits->resizeColumnsToContents();
    ui->tableWidget_gestionProduitsProduits->resizeRowsToContents();
    ui->tableWidget_gestionProduitsProduits->update();
}

/**
 * @brief MainWindow::afficherTableGestionProduitsVarietes
 * Méthode publique de la classe MainWindow qui affiche les variétés dans le tableau de l'onglet Variétés de Gestion Produits
 */
void MainWindow::afficherTableGestionProduitsVarietes()
{
    qDebug()<<"void MainWindow::afficherTableGestionProduitsVarietes()";
    //requête qui récupère les variétés
    QString reqSelectVarietes = "SELECT v.numeroVariete, v.libelleVariete, v.imageVariete, v.dateInscriptionVariete, p.libelleProduit "
                                "FROM Variete v "
                                "INNER JOIN Produit p ON p.numeroProduit = v.numeroProduit "
                                "ORDER BY v.numeroVariete ASC";
    qDebug()<<reqSelectVarietes;
    QSqlQuery resultSelectVarietes(reqSelectVarietes);

    while(resultSelectVarietes.next()){
        //on récupère le numéro de la dernière ligne
        int row = ui->tableWidget_gestionProduitsVarietes->rowCount();
        ui->tableWidget_gestionProduitsVarietes->setRowCount(row+1);
        //on crée une instance de QLabel qui va contenir l'image de la variété
        QLabel *labelImage= new QLabel();
        labelImage->setPixmap(QPixmap(resultSelectVarietes.value("imageProduit").toString()).scaled(imageSize,imageSize));
        labelImage->setScaledContents(true);
        //inserer les valeur dans le tableau
        ui->tableWidget_gestionProduitsVarietes->setCellWidget(row,0, new QCheckBox());
        ui->tableWidget_gestionProduitsVarietes->setItem(row,1, new QTableWidgetItem(resultSelectVarietes.value("numeroVariete").toString()));
        ui->tableWidget_gestionProduitsVarietes->setItem(row,2, new QTableWidgetItem(resultSelectVarietes.value("dateInscriptionVariete").toString()));
        ui->tableWidget_gestionProduitsVarietes->setCellWidget(row,3,labelImage);
        ui->tableWidget_gestionProduitsVarietes->setItem(row,4, new QTableWidgetItem(resultSelectVarietes.value("libelleProduit").toString()));
        ui->tableWidget_gestionProduitsVarietes->setItem(row,5, new QTableWidgetItem(resultSelectVarietes.value("libelleVariete").toString()));
    }
    ui->tableWidget_gestionProduitsVarietes->resizeColumnsToContents();
    ui->tableWidget_gestionProduitsVarietes->resizeRowsToContents();
    ui->tableWidget_gestionProduitsVarietes->update();
}