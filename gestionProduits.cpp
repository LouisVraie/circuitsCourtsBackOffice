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

    //taille des images en pixel
    imageSize = 125;

    //on affiche le contenu des tableaux
    afficherTableGestionProduitsRayons();

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
        QLabel *labelimage= new QLabel();
        labelimage->setPixmap(QPixmap(resultSelectRayons.value("imageRayon").toString()).scaled(imageSize,imageSize));
        labelimage->setScaledContents(true);
        //inserer les valeur dans le tableau
        ui->tableWidget_gestionProduitsRayons->setItem(row,0, new QTableWidgetItem(resultSelectRayons.value("numeroRayon").toString()));
        ui->tableWidget_gestionProduitsRayons->setItem(row,1, new QTableWidgetItem(resultSelectRayons.value("libelleRayon").toString()));
        ui->tableWidget_gestionProduitsRayons->setCellWidget(row,2,labelimage);
        ui->tableWidget_gestionProduitsRayons->setItem(row,3, new QTableWidgetItem(resultSelectRayons.value("dateInscriptionRayon").toString()));
    }
    ui->tableWidget_gestionProduitsRayons->resizeColumnsToContents();
    ui->tableWidget_gestionProduitsRayons->resizeRowsToContents();
    ui->tableWidget_gestionProduitsRayons->update();
}
