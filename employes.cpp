#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::initEmployes
 * Méthode publique de la classe MainWindow qui initialise l'onglet Employés
 */
void MainWindow::initEmployes()
{
    qDebug()<<"void MainWindow::initEmployes()";

    //on stretch les colonnes des QTableWidget
    ui->tableWidget_employes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    afficherTableEmployes();
    fill_comboBox_employesTypeEmploye();

    //on désactive le bouton Ajouter Employés et on connecte les lineEdit
    ui->pushButton_ajouterEmploye->setEnabled(false);
    connect(ui->comboBox_employesTypeEmploye,SIGNAL(currentIndexChanged(int)),this,SLOT(on_allLineEditEmploye_textChanged()));
    connect(ui->lineEdit_employesNom,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditEmploye_textChanged()));
    connect(ui->lineEdit_employesPrenom,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditEmploye_textChanged()));
    connect(ui->lineEdit_employesLogin,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditEmploye_textChanged()));
    connect(ui->lineEdit_employesMdp,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditEmploye_textChanged()));
    connect(ui->lineEdit_employesConfirmMdp,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditEmploye_textChanged()));
    connect(ui->lineEdit_employesAdresse,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditEmploye_textChanged()));
    connect(ui->lineEdit_employesCodePostal,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditEmploye_textChanged()));
    connect(ui->lineEdit_employesVille,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditEmploye_textChanged()));
    connect(ui->lineEdit_employesMail,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditEmploye_textChanged()));
    connect(ui->lineEdit_employesTel,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditEmploye_textChanged()));

    //on désactive le bouton modifier par défaut
    ui->pushButton_modifierEmploye->setEnabled(false);
}

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
                               "WHERE e.numeroTypeEmploye > "+numeroTypeEmploye+" "
                               "ORDER BY e.numeroTypeEmploye ASC";
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
    ui->comboBox_employesTypeEmploye->insertItem(index,"Sélectionner","0");
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
    //on récupère le texte des lineEdits des informations personnelles
    getEmployesInputs();

    //si le login n'existe pas
    if(verifEmployeInfos(newLogin,newMail,newTel)){
        //si les deux mots de passe sont les mêmes
        if(verifMdp(newMdp, newCMdp)){
            //requête pour obtenir un nouveau numéro d'employé
            QSqlQuery resultNumEmploye("SELECT IFNULL((SELECT MAX(numeroEmploye)+1 FROM Employe),1)");
            resultNumEmploye.next();
            QString numEmploye = resultNumEmploye.value(0).toString();
            qDebug()<<numEmploye;
            //requête d'ajout de l'employé
            QString reqInsertEmploye="INSERT INTO Employe (numeroEmploye, loginEmploye, nomEmploye, prenomEmploye, "
                                     "adresseEmploye, codePostalEmploye, villeEmploye, mailEmploye, telEmploye, "
                                     "motDePasseEmploye, numeroTypeEmploye) VALUES ("
                                     ""+numEmploye+","
                                     "'"+newLogin+"',"
                                     "'"+newNom+"',"
                                     "'"+newPrenom+"',"
                                     "'"+newAdresse+"',"
                                     "'"+newCodePostal+"',"
                                     "'"+newVille+"',"
                                     "'"+newMail+"',"
                                     "'"+newTel+"',"
                                     "PASSWORD('"+newMdp+"'),"
                                     ""+newTypeEmploye+")";
            qDebug()<<reqInsertEmploye;
            QSqlQuery resultInsertEmploye(reqInsertEmploye);
            //si l'insertion a fonctionné
            if(resultInsertEmploye.numRowsAffected() != -1){
                //on ajoute une ligne au tableau
                int row = ui->tableWidget_employes->rowCount();
                ui->tableWidget_employes->setRowCount(row+1);
                //on insert le contenu de chaque cellule
                ui->tableWidget_employes->setCellWidget(row,0,new QCheckBox());
                ui->tableWidget_employes->setItem(row,1,new QTableWidgetItem(numEmploye));
                ui->tableWidget_employes->setItem(row,2,new QTableWidgetItem(ui->comboBox_employesTypeEmploye->currentText()));
                ui->tableWidget_employes->setItem(row,3,new QTableWidgetItem(newLogin));
                ui->tableWidget_employes->setItem(row,4,new QTableWidgetItem(newNom));
                ui->tableWidget_employes->setItem(row,5,new QTableWidgetItem(newPrenom));
                ui->tableWidget_employes->setItem(row,6,new QTableWidgetItem(newAdresse));
                ui->tableWidget_employes->setItem(row,7,new QTableWidgetItem(newCodePostal));
                ui->tableWidget_employes->setItem(row,8,new QTableWidgetItem(newVille));
                ui->tableWidget_employes->setItem(row,9,new QTableWidgetItem(newMail));
                ui->tableWidget_employes->setItem(row,10,new QTableWidgetItem(newTel));

                //on réinitialise tous les champs de saisies
                clearEmployesInputs();

            } else {
                QMessageBox::warning(this,windowTitle()+" - Ajout d'employé","Une erreur est survenue lors de l'insertion de l'employé !",QMessageBox::Ok);
            }
        }
    } else {
        QMessageBox::warning(this,windowTitle()+" - Ajout d'employé","Le login saisit existe déjà !",QMessageBox::Ok);
    }
}

/**
 * @brief MainWindow::on_allLineEditEmploye_textChanged
 * Méthode private slots qui active ou non les boutons de l'onglet Employés
 */
void MainWindow::on_allLineEditEmploye_textChanged()
{
    qDebug()<<"bool MainWindow::on_allLineEditEmploye_textChanged()";
    //on récupère le texte des lineEdits des informations personnelles
    getEmployesInputs();
    bool newTypeEmploye, newNom, newPrenom, newLogin, newMdp, newCMdp, newAdresse, newCodePostal, newVille, newMail, newTel;
    newTypeEmploye = this->newTypeEmploye.toInt() != 0;
    newNom = this->newNom.size()>=nomPrenomMinimumSize;
    newPrenom = this->newPrenom.size()>=nomPrenomMinimumSize;
    newLogin = this->newLogin.size()>=loginMinimumSize;
    newMdp = this->newMdp.size()>=mdpMinimumSize;
    newCMdp = this->newCMdp.size()>=mdpMinimumSize;
    newAdresse = this->newAdresse.size()>=adresseMinimumSize;
    newCodePostal = this->newCodePostal.size()==codePostalMinimumSize;
    newVille = this->newVille.size()>=villeMinimumSize;
    newMail = this->newMail.size()>=mailMinimumSize;
    newTel = this->newTel.size()>=telMinimumSize;
    //si les champs sont remplis et que le type employé est sélectionné
    if(newTypeEmploye && newNom && newPrenom && newLogin && newMdp && newCMdp &&
            newAdresse && newCodePostal && newVille && newMail && newTel){
        //on active le bouton
        ui->pushButton_ajouterEmploye->setEnabled(true);
    }else {
        //on désactive le bouton
        ui->pushButton_ajouterEmploye->setEnabled(false);
    }

    //si une ligne est sélectionnée
    if(!ui->tableWidget_employes->selectedItems().empty()){
        //si les champs sont remplis et que le type employé est sélectionné
        if(newTypeEmploye && newNom && newPrenom && newLogin &&
                newAdresse && newCodePostal && newVille && newMail && newTel){
            //on active le bouton
            ui->pushButton_modifierEmploye->setEnabled(true);
        }else {
            //on désactive le bouton
            ui->pushButton_modifierEmploye->setEnabled(false);
        }
    }

}

/**
 * @brief MainWindow::getEmployesInputs
 * Méthode private de la classe MainWindow qui récupère le contenu des lineEdits de l'onglet Employés
 */
void MainWindow::getEmployesInputs()
{
    qDebug()<<"void MainWindow::fillEmployesInputs()";
    newTypeEmploye = ui->comboBox_employesTypeEmploye->currentData().toString();
    newNom = escapeString(ui->lineEdit_employesNom->text());
    newPrenom = escapeString(ui->lineEdit_employesPrenom->text());
    newLogin = escapeString(ui->lineEdit_employesLogin->text());
    newMdp = escapeString(ui->lineEdit_employesMdp->text());
    newCMdp = escapeString(ui->lineEdit_employesConfirmMdp->text());
    newAdresse = escapeString(ui->lineEdit_employesAdresse->text());
    newCodePostal = escapeString(ui->lineEdit_employesCodePostal->text());
    newVille = escapeString(ui->lineEdit_employesVille->text());
    newMail = escapeString(ui->lineEdit_employesMail->text());
    newTel = escapeString(ui->lineEdit_employesTel->text());
}

/**
 * @brief MainWindow::clearEmployesInputs
 * Méthode private de la classe MainWindow qui permet d'effacer le contenu des champs de saisies
 */
void MainWindow::clearEmployesInputs()
{
    qDebug()<<"void MainWindow::clearEmployesInputs()";
    ui->comboBox_employesTypeEmploye->setCurrentIndex(0);
    ui->lineEdit_employesNom->clear();
    ui->lineEdit_employesPrenom->clear();
    ui->lineEdit_employesLogin->clear();
    ui->lineEdit_employesMdp->clear();
    ui->lineEdit_employesConfirmMdp->clear();
    ui->lineEdit_employesAdresse->clear();
    ui->lineEdit_employesCodePostal->clear();
    ui->lineEdit_employesVille->clear();
    ui->lineEdit_employesMail->clear();
    ui->lineEdit_employesTel->clear();

    newTypeEmploye = "";
    newNom = "";
    newPrenom = "";
    newLogin = "";
    newMdp = "";
    newCMdp = "";
    newAdresse = "";
    newCodePostal = "";
    newVille = "";
    newMail = "";
    newTel = "";

    //on désactive les boutons
    ui->pushButton_ajouterEmploye->setDisabled(true);
    ui->pushButton_modifierEmploye->setDisabled(true);
}

/**
 * @brief MainWindow::on_tableWidget_employes_itemSelectionChanged
 * Méthode private slots de la classe MainWindow qui affiche les données d'un employé de la ligne sélectionnée
 * dans les champs associés
 */
void MainWindow::on_tableWidget_employes_itemSelectionChanged()
{
    qDebug()<<"void MainWindow::on_tableWidget_employes_itemSelectionChanged()";
    if(!ui->tableWidget_employes->selectedItems().empty()){
        //on récupère le numéro de ligne
        rowEmploye = ui->tableWidget_employes->row(ui->tableWidget_employes->selectedItems()[0]);
        //on active le bouton modifier
        ui->pushButton_modifierEmploye->setEnabled(true);
        //on récupère les données de la ligne sélectionné
        for (int i=0;i<ui->comboBox_employesTypeEmploye->count();i++) {
            //si le type employé de la comboBox est le même que celui du tableau
            if(ui->comboBox_employesTypeEmploye->itemText(i) == ui->tableWidget_employes->selectedItems()[1]->text()){
                //on sélectionne l'item correspodant dans la comboBox
                ui->comboBox_employesTypeEmploye->setCurrentIndex(i);
            }
        }
        ui->lineEdit_employesNom->setText(ui->tableWidget_employes->selectedItems()[3]->text());
        ui->lineEdit_employesPrenom->setText(ui->tableWidget_employes->selectedItems()[4]->text());
        ui->lineEdit_employesLogin->setText(ui->tableWidget_employes->selectedItems()[2]->text());
        ui->lineEdit_employesAdresse->setText(ui->tableWidget_employes->selectedItems()[5]->text());
        ui->lineEdit_employesCodePostal->setText(ui->tableWidget_employes->selectedItems()[6]->text());
        ui->lineEdit_employesVille->setText(ui->tableWidget_employes->selectedItems()[7]->text());
        ui->lineEdit_employesMail->setText(ui->tableWidget_employes->selectedItems()[8]->text());
        ui->lineEdit_employesTel->setText(ui->tableWidget_employes->selectedItems()[9]->text());

        //on efface par précaution les champs de mot de passe
        ui->lineEdit_employesMdp->clear();
        ui->lineEdit_employesConfirmMdp->clear();
    }else {
        //on désactive le bouton modifier
        ui->pushButton_modifierEmploye->setEnabled(false);
    }
}

/**
 * @brief MainWindow::on_pushButton_modifierEmploye_clicked
 * Méthode private slots de la classe MainWindow qui met à jour les informations d'un employé sélectionné
 */
void MainWindow::on_pushButton_modifierEmploye_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_modifierEmploye_clicked()";
    //récupération des champs
    getEmployesInputs();

    //mise à jour dans la base de données
    QString reqUpdateEmploye = "UPDATE Employe SET "
                        "loginEmploye = '"+newLogin+"', "
                        "nomEmploye = '"+newNom+"', "
                        "prenomEmploye = '"+newPrenom+"', "
                        "adresseEmploye = '"+newAdresse+"', "
                        "codePostalEmploye = '"+newCodePostal+"', "
                        "villeEmploye = '"+newVille+"', "
                        "mailEmploye = '"+newMail+"', "
                        "telEmploye = '"+newTel+"', "
                        "numeroTypeEmploye = "+newTypeEmploye+" "
                        "WHERE numeroEmploye = "+ui->tableWidget_employes->selectedItems()[0]->text();
    qDebug()<<reqUpdateEmploye;
    QSqlQuery resultUpdateEmploye(reqUpdateEmploye);
    qDebug()<<resultUpdateEmploye.numRowsAffected();
    //si l'update a fonctionné
    if(resultUpdateEmploye.numRowsAffected() != -1){
        //si un mdp est donné
        if(newMdp != "" && newCMdp != ""){
            //on vérifie les mots de passe
            if(verifMdp(newMdp, newCMdp)){
                QString reqUpdateMdpEmploye = "UPDATE Employe SET motDePasseEmploye = PASSWORD('"+newMdp+"') "
                                              "WHERE numeroEmploye = "+ui->tableWidget_employes->item(rowEmploye,1)->text();
                qDebug()<<reqUpdateMdpEmploye;
                QSqlQuery resultUpdateMdpEmploye(reqUpdateEmploye);
                //si l'update a fonctionné
                if(resultUpdateMdpEmploye.numRowsAffected() != -1){
                    ui->statusBar->showMessage("Le mot de passe de l'employé "+newLogin+" a bien été changé !");
                } else {
                    ui->statusBar->showMessage("Erreur lors de la modification du mot de passe de l'employé !");
                }
            }
        } else {
            ui->tableWidget_employes->setItem(rowEmploye,2,new QTableWidgetItem(ui->comboBox_employesTypeEmploye->currentText()));
            ui->tableWidget_employes->setItem(rowEmploye,3,new QTableWidgetItem(newLogin));
            ui->tableWidget_employes->setItem(rowEmploye,4,new QTableWidgetItem(newNom));
            ui->tableWidget_employes->setItem(rowEmploye,5,new QTableWidgetItem(newPrenom));
            ui->tableWidget_employes->setItem(rowEmploye,6,new QTableWidgetItem(newAdresse));
            ui->tableWidget_employes->setItem(rowEmploye,7,new QTableWidgetItem(newCodePostal));
            ui->tableWidget_employes->setItem(rowEmploye,8,new QTableWidgetItem(newVille));
            ui->tableWidget_employes->setItem(rowEmploye,9,new QTableWidgetItem(newMail));
            ui->tableWidget_employes->setItem(rowEmploye,10,new QTableWidgetItem(newTel));

            ui->statusBar->showMessage("Les données de l'employé "+newLogin+" ont été modifié avec succès !");

            //on clear les inputs
            clearEmployesInputs();
        }
    } else {
        ui->statusBar->showMessage("Erreur lors de la modification de l'employé !");
    }
}

/**
 * @brief MainWindow::on_pushButton_supprimerEmploye_clicked
 * Méthode private slots de la classe MainWindow qui supprime dans le tableau les lignes des employés sélectionnées
 */
void MainWindow::on_pushButton_supprimerEmploye_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_supprimerEmploye_clicked()";
    bool supprOk = false;
    int nbLigneSuppr = 0;
    for (int ligne = ui->tableWidget_employes->rowCount()-1;ligne>=0;ligne--) {
        //si la QCheckBox est cochée
        if(((QCheckBox*)ui->tableWidget_employes->cellWidget(ligne,0))->isChecked()){
            QString reqUpdateDeleteEmploye = "UPDATE Employe SET estActif = FALSE "
                                             "WHERE numeroEmploye = "+ui->tableWidget_employes->item(ligne,1)->text();
            qDebug()<<reqUpdateDeleteEmploye;
            QSqlQuery resultUpdateDeleteEmploye(reqUpdateDeleteEmploye);
            if(resultUpdateDeleteEmploye.numRowsAffected() != -1){
                ui->tableWidget_employes->removeRow(ligne);
                nbLigneSuppr++;
                supprOk = true;
            } else {
                ui->statusBar->showMessage("Erreur lors de la suppression !");
                break;
            }
        }
    }
    if(supprOk){
        ui->statusBar->showMessage("Suppression de "+QString::number(nbLigneSuppr)+" ligne(s) !");
    }
}
