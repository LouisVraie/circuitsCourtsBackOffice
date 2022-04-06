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
 * Méthode publique de la classe MainWindow qui affiche les rayons des produits
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
 * Méthode publique de la classe MainWindow qui affiche les produits
 */
void MainWindow::afficherTableGestionProduitsProduits()
{
    qDebug()<<"void MainWindow::afficherTableGestionProduitsProduits()";
    //requête qui récupère les produits
    QString reqSelectProduits = "SELECT p.numeroProduit, p.libelleProduit, p.imageProduit, p.dateInscriptionProduit, r.libelleRayon "
                                "FROM Produit p "
                                "INNER JOIN Rayon r ON r.numeroRayon = p.numeroRayon";
    qDebug()<<reqSelectProduits;
    QSqlQuery resultSelectProduits(reqSelectProduits);

    while(resultSelectProduits.next()){
        //on récupère le numéro de la dernière ligne
        int row = ui->tableWidget_gestionProduitsProduits->rowCount();
        ui->tableWidget_gestionProduitsProduits->setRowCount(row+1);
        //on crée une instance de QLabel qui va contenir l'image du rayon
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
