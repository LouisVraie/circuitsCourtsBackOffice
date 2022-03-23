#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::initProducteurs
 * Méthode public de la classe MainWindow qui initialise tous les éléments nécessaires de l'onglet Producteurs
 */
void MainWindow::initProducteurs()
{
    qDebug()<<"void MainWindow::initProducteurs()";

    //on stretch les tableaux
    ui->tableWidget_producteursEnAttente->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_producteursValides->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_producteursInvalides->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //on affiche le contenu des tableaux
    afficherTableProducteurEnAttente();
}

/**
 * @brief MainWindow::afficherTableProducteurEnAttente
 */
void MainWindow::afficherTableProducteurEnAttente()
{
    qDebug()<<"void MainWindow::afficherTableProducteurEnAttente()";
    //requête qui récupère les données des producteurs en attentes
    QString reqProducteursEnAttente = "SELECT p.numeroProducteur, p.nomProducteur, p.prenomProducteur, "
                                      "p.adresseProducteur, p.codePostalProducteur, p.villeProducteur, "
                                      "p.mailProducteur, p.telProducteur, p.dateInscriptionProducteur FROM Producteur p "
                                      "WHERE p.validationProducteur IS NULL";
    qDebug()<<reqProducteursEnAttente;
    QSqlQuery resultProducteursEnAttente(reqProducteursEnAttente);
    //si la requête a fonctionné
    if(resultProducteursEnAttente.numRowsAffected() != -1){
        //on affiche chaque ligne
        while(resultProducteursEnAttente.next()){
            //on ajoute une ligne au tableau
            int row = ui->tableWidget_producteursEnAttente->rowCount();
            ui->tableWidget_producteursEnAttente->setRowCount(row+1);
            //on insère le contenu de chaque cellule
            ui->tableWidget_producteursEnAttente->setItem(row,0,new QTableWidgetItem(resultProducteursEnAttente.value("numeroProducteur").toString()));
            ui->tableWidget_producteursEnAttente->setItem(row,1,new QTableWidgetItem(resultProducteursEnAttente.value("nomProducteur").toString()));
            ui->tableWidget_producteursEnAttente->setItem(row,2,new QTableWidgetItem(resultProducteursEnAttente.value("prenomProducteur").toString()));
            ui->tableWidget_producteursEnAttente->setItem(row,3,new QTableWidgetItem(resultProducteursEnAttente.value("adresseProducteur").toString()));
            ui->tableWidget_producteursEnAttente->setItem(row,4,new QTableWidgetItem(resultProducteursEnAttente.value("codePostalProducteur").toString()));
            ui->tableWidget_producteursEnAttente->setItem(row,5,new QTableWidgetItem(resultProducteursEnAttente.value("villeProducteur").toString()));
            ui->tableWidget_producteursEnAttente->setItem(row,6,new QTableWidgetItem(resultProducteursEnAttente.value("mailProducteur").toString()));
            ui->tableWidget_producteursEnAttente->setItem(row,7,new QTableWidgetItem(resultProducteursEnAttente.value("telProducteur").toString()));
            ui->tableWidget_producteursEnAttente->setItem(row,8,new QTableWidgetItem(resultProducteursEnAttente.value("dateInscriptionProducteur").toString()));
        }
    }else {
        ui->statusBar->showMessage("Erreur lors de l'affichage des employés !",2000);
    }
}
