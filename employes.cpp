#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::afficherTableEmployes
 * Méthode publique de la classe MainWindow qui permet d'afficher la liste des employés
 */
void MainWindow::afficherTableEmployes()
{
    qDebug()<<"void MainWindow::afficherTableEmployes()";
    //requête qui récupère les données des employés
    QString reqTableEmployes = "SELECT e.numeroEmploye, e.loginEmploye, e.nomEmploye, e.prenomEmploye, "
                               "e.adresseEmploye, e.codePostalEmploye, e.villeEmploye, e.mailEmploye, "
                               "e.telEmploye, te.libelleTypeEmploye, e.estActif, e.numeroTypeEmploye FROM Employe e "
                               "INNER JOIN TypeEmploye te ON te.numeroTypeEmploye = e.numeroTypeEmploye "
                               "WHERE e.numeroTypeEmploye > "+numeroTypeEmploye;
    qDebug()<<reqTableEmployes;
    QSqlQuery resultTableEmployes(reqTableEmployes);
    //si la requête a fontionné
    if(resultTableEmployes.numRowsAffected() != -1){
        //on affiche chaque ligne
        while(resultTableEmployes.next()){
            qDebug()<<resultTableEmployes.value("numeroTypeEmploye").toString()<<" > "<<numeroTypeEmploye;
            //si l'employé est visible on l'affiche
            if(resultTableEmployes.value("estActif").toInt()){
                //on ajoute une ligne au tableau
                int row = ui->tableWidget_employes->rowCount();
                ui->tableWidget_employes->setRowCount(row+1);
                //on insère le contenu de chaque cellule
                ui->tableWidget_employes->setCellWidget(row,0,new QCheckBox());
                ui->tableWidget_employes->setItem(row,1,new QTableWidgetItem(resultTableEmployes.value("numeroEmploye").toString()));
                ui->tableWidget_employes->setItem(row,2,new QTableWidgetItem(resultTableEmployes.value("libelleTypeEmploye").toString()));
                ui->tableWidget_employes->setItem(row,3,new QTableWidgetItem(resultTableEmployes.value("loginEmploye").toString()));
                ui->tableWidget_employes->setItem(row,4,new QTableWidgetItem(resultTableEmployes.value("nomEmploye").toString()));
                ui->tableWidget_employes->setItem(row,5,new QTableWidgetItem(resultTableEmployes.value("prenomEmploye").toString()));
                ui->tableWidget_employes->setItem(row,6,new QTableWidgetItem(resultTableEmployes.value("adresseEmploye").toString()));
                ui->tableWidget_employes->setItem(row,7,new QTableWidgetItem(resultTableEmployes.value("codePostalEmploye").toString()));
                ui->tableWidget_employes->setItem(row,8,new QTableWidgetItem(resultTableEmployes.value("villeEmploye").toString()));
                ui->tableWidget_employes->setItem(row,9,new QTableWidgetItem(resultTableEmployes.value("mailEmploye").toString()));
                ui->tableWidget_employes->setItem(row,10,new QTableWidgetItem(resultTableEmployes.value("telEmploye").toString()));
            }
        }
    }else {
        ui->statusBar->showMessage("Erreur lors de l'affichage des employés !",2000);
    }
}

/**
 * @brief MainWindow::fill_comboBox_employesTypeEmploye
 * Méthode publique de la classe MainWindow qui remplie la comboBox_employesTypeEmploye
 */
void MainWindow::fill_comboBox_employesTypeEmploye()
{
    qDebug()<<"void MainWindow::fill_comboBox_employesTypeEmploye()";
    QString reqComboBoxTypeEmploye = "SELECT numeroTypeEmploye, libelleTypeEmploye FROM TypeEmploye "
                                     "WHERE numeroTypeEmploye >"+numeroTypeEmploye;
    qDebug()<<reqComboBoxTypeEmploye;
    QSqlQuery resultComboBoxTypeEmploye(reqComboBoxTypeEmploye);
    int index = 0;
    ui->comboBox_employesTypeEmploye->insertItem(index,"Choisir un type","0");
    //on affiche dans la comboBox tous les types Employé que peut choisir l'utilisateur
    while(resultComboBoxTypeEmploye.next()){
        index++;
        QString libelle = resultComboBoxTypeEmploye.value("libelleTypeEmploye").toString();
        QString numeroTypeEmp = resultComboBoxTypeEmploye.value("numeroTypeEmploye").toString();
        ui->comboBox_employesTypeEmploye->insertItem(index,libelle,numeroTypeEmp);

    }
}

/**
 * @brief MainWindow::on_pushButton_ajouterEmploye_clicked
 * Méthode private slots de la classe MainWindow qui ajoute un employé dans la base et rajoute une ligne dans le tableau
 */
void MainWindow::on_pushButton_ajouterEmploye_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_ajouterEmploye_clicked()";
}
