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
    //ui->tableWidget_producteursInvalides->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //on affiche le contenu des tableaux
    afficherTableProducteurEnAttente();
    afficherTableProducteurValides();
    afficherTableProducteurInvalides();
}

/**
 * @brief MainWindow::afficherTableProducteurEnAttente
 * Méthode public de la classe MainWindow qui affiche dans un tableau les producteurs en attente de validation
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
        ui->statusBar->showMessage("Erreur lors de l'affichage des producteurs en attente !",5000);
    }
}

/**
 * @brief MainWindow::afficherTableProducteurValides
 * Méthode public de la classe MainWindow qui affiche dans un tableau les producteurs validés
 */
void MainWindow::afficherTableProducteurValides()
{
    qDebug()<<"void MainWindow::afficherTableProducteurValides()";
    //requête qui récupère les données des producteurs validés
    QString reqProducteursValides = "SELECT p.numeroProducteur, p.nomProducteur, p.prenomProducteur, "
                                      "p.adresseProducteur, p.codePostalProducteur, p.villeProducteur, "
                                      "p.mailProducteur, p.telProducteur, p.dateInscriptionProducteur, "
                                      "p.activationProducteur FROM Producteur p "
                                      "WHERE p.validationProducteur = 1";
    qDebug()<<reqProducteursValides;
    QSqlQuery resultProducteursValides(reqProducteursValides);
    //si la requête a fonctionné
    if(resultProducteursValides.numRowsAffected() != -1){
        //on affiche chaque ligne
        while(resultProducteursValides.next()){
            //on ajoute une ligne au tableau
            int row = ui->tableWidget_producteursValides->rowCount();
            ui->tableWidget_producteursValides->setRowCount(row+1);
            //on insère le contenu de chaque cellule
            ui->tableWidget_producteursValides->setItem(row,0,new QTableWidgetItem(resultProducteursValides.value("numeroProducteur").toString()));
            ui->tableWidget_producteursValides->setItem(row,1,new QTableWidgetItem(resultProducteursValides.value("nomProducteur").toString()));
            ui->tableWidget_producteursValides->setItem(row,2,new QTableWidgetItem(resultProducteursValides.value("prenomProducteur").toString()));
            ui->tableWidget_producteursValides->setItem(row,3,new QTableWidgetItem(resultProducteursValides.value("adresseProducteur").toString()));
            ui->tableWidget_producteursValides->setItem(row,4,new QTableWidgetItem(resultProducteursValides.value("codePostalProducteur").toString()));
            ui->tableWidget_producteursValides->setItem(row,5,new QTableWidgetItem(resultProducteursValides.value("villeProducteur").toString()));
            ui->tableWidget_producteursValides->setItem(row,6,new QTableWidgetItem(resultProducteursValides.value("mailProducteur").toString()));
            ui->tableWidget_producteursValides->setItem(row,7,new QTableWidgetItem(resultProducteursValides.value("telProducteur").toString()));
            ui->tableWidget_producteursValides->setItem(row,8,new QTableWidgetItem(resultProducteursValides.value("dateInscriptionProducteur").toString()));
            ui->tableWidget_producteursValides->setItem(row,9,new QTableWidgetItem());
            //si l'utilisateur est activé
            if (resultProducteursValides.value("activationProducteur").toBool()){
                setTableProducteurValidesActivationColor(row,"green");
            } else {
                setTableProducteurValidesActivationColor(row,"red");
            }
        }
    }else {
        ui->statusBar->showMessage("Erreur lors de l'affichage des producteurs validés !",5000);
    }
}

/**
 * @brief MainWindow::afficherTableProducteurInvalides
 * Méthode public de la classe MainWindow qui affiche dans un tableau les producteurs invalidés
 */
void MainWindow::afficherTableProducteurInvalides()
{
    qDebug()<<"void MainWindow::afficherTableProducteurInvalides()";
    //requête qui récupère les données des producteurs invalidés
    QString reqProducteursInvalides = "SELECT p.numeroProducteur, p.nomProducteur, p.prenomProducteur, "
                                      "p.adresseProducteur, p.codePostalProducteur, p.villeProducteur, "
                                      "p.mailProducteur, p.telProducteur, p.dateInscriptionProducteur, "
                                      "p.raisonInvalidationProducteur FROM Producteur p "
                                      "WHERE p.validationProducteur = 0";
    qDebug()<<reqProducteursInvalides;
    QSqlQuery resultProducteursInvalides(reqProducteursInvalides);
    //si la requête a fonctionné
    if(resultProducteursInvalides.numRowsAffected() != -1){
        //on affiche chaque ligne
        while(resultProducteursInvalides.next()){
            //on ajoute une ligne au tableau
            int row = ui->tableWidget_producteursInvalides->rowCount();
            ui->tableWidget_producteursInvalides->setRowCount(row+1);
            //on insère le contenu de chaque cellule
            ui->tableWidget_producteursInvalides->setItem(row,0,new QTableWidgetItem(resultProducteursInvalides.value("numeroProducteur").toString()));
            ui->tableWidget_producteursInvalides->setItem(row,1,new QTableWidgetItem(resultProducteursInvalides.value("nomProducteur").toString()));
            ui->tableWidget_producteursInvalides->setItem(row,2,new QTableWidgetItem(resultProducteursInvalides.value("prenomProducteur").toString()));
            ui->tableWidget_producteursInvalides->setItem(row,3,new QTableWidgetItem(resultProducteursInvalides.value("adresseProducteur").toString()));
            ui->tableWidget_producteursInvalides->setItem(row,4,new QTableWidgetItem(resultProducteursInvalides.value("codePostalProducteur").toString()));
            ui->tableWidget_producteursInvalides->setItem(row,5,new QTableWidgetItem(resultProducteursInvalides.value("villeProducteur").toString()));
            ui->tableWidget_producteursInvalides->setItem(row,6,new QTableWidgetItem(resultProducteursInvalides.value("mailProducteur").toString()));
            ui->tableWidget_producteursInvalides->setItem(row,7,new QTableWidgetItem(resultProducteursInvalides.value("telProducteur").toString()));
            ui->tableWidget_producteursInvalides->setItem(row,8,new QTableWidgetItem(resultProducteursInvalides.value("dateInscriptionProducteur").toString()));
            ui->tableWidget_producteursInvalides->setItem(row,9,new QTableWidgetItem(resultProducteursInvalides.value("raisonInvalidationProducteur").toString()));
        }
    }else {
        ui->statusBar->showMessage("Erreur lors de l'affichage des producteurs invalidés !",5000);
    }
}

/**
 * @brief MainWindow::setTableProducteurValidesActivationColor
 * Méthode publique de la classe MainWindow qui change la couleur du QTableWidgetItem de la colonne Activation de tableWidget_producteursValides
 * @param row: int La ligne du tableau
 * @param backgroundColor: QString La couleur de fond
 */
void MainWindow::setTableProducteurValidesActivationColor(int row, QString backgroundColor)
{
    qDebug()<<"void MainWindow::setTableProducteurValidesActivationColor(int row, QString backgroundColor)";
    ui->tableWidget_producteursValides->item(row,9)->setBackgroundColor(backgroundColor);
}

/**
 * @brief MainWindow::on_pushButton_producteursEnAttenteValider_clicked
 * Méthode private slots de la classe MainWindow qui valide un producteur
 */
void MainWindow::on_pushButton_producteursEnAttenteValider_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_producteursEnAttenteValider_clicked()";
    //si une ligne est sélectionnée
    if (!ui->tableWidget_producteursEnAttente->selectedItems().isEmpty()){
        QString nomPrenomProducteur = ui->tableWidget_producteursEnAttente->selectedItems()[1]->text()+" "+ui->tableWidget_producteursEnAttente->selectedItems()[2]->text();
        //on demande une confirmation
        if(QMessageBox::warning(this,this->windowTitle()+" - Valider un producteur",
                                "Êtes-vous sûr de vouloir valider le producteur : "+nomPrenomProducteur,
                                QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
            //mise à jour dans la base de données
            QString reqUpdateProducteurValidation = "UPDATE Producteur SET validationProducteur = TRUE "
                                                    "WHERE numeroProducteur = "+ui->tableWidget_producteursEnAttente->selectedItems()[0]->text();
            qDebug()<<reqUpdateProducteurValidation;
            QSqlQuery resultUpdateProducteurValidation(reqUpdateProducteurValidation);
            qDebug()<<resultUpdateProducteurValidation.numRowsAffected();
            //si l'update a fonctionné
            if(resultUpdateProducteurValidation.numRowsAffected() != -1){
                //on supprime la ligne du tableau des producteurs en attente
                ui->tableWidget_producteursEnAttente->removeRow(ui->tableWidget_producteursEnAttente->currentRow());
                //on actualise le tableau des producteurs validés
                afficherTableProducteurValides();
                //on affiche un message de réussite
                ui->statusBar->showMessage("Le producteur "+nomPrenomProducteur+" ont été validé avec succès !",5000);
            } else {
                ui->statusBar->showMessage("Erreur lors de la validation du producteur "+nomPrenomProducteur+" !",5000);
            }
        }
    }
}

/**
 * @brief MainWindow::on_pushButton_producteursEnAttenteInvalider_clicked
 * Méthode private slots de la classe MainWindow qui invalide un producteur
 */
void MainWindow::on_pushButton_producteursEnAttenteInvalider_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_producteursEnAttenteInvalider_clicked()";
    //si une ligne est sélectionnée
    if (!ui->tableWidget_producteursEnAttente->selectedItems().isEmpty()){
        QString nomPrenomProducteur = ui->tableWidget_producteursEnAttente->selectedItems()[1]->text()+" "+ui->tableWidget_producteursEnAttente->selectedItems()[2]->text();
        //on demande une confirmation
        if(QMessageBox::warning(this,this->windowTitle()+" - Invalider un producteur",
                                "Êtes-vous sûr de vouloir invalider le producteur : "+nomPrenomProducteur,
                                QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
            //On demande d'écrire la raison
            bool okRaison;
            QString raisonInvalidation;
            do{
                raisonInvalidation = escapeString(QInputDialog::getText(this, this->windowTitle()+" - Invalider un producteur",
                                                           tr("Raison d'invalidation :"), QLineEdit::Normal,
                                                           "", &okRaison));
            }while(!okRaison || raisonInvalidation.size() < 5);

            //mise à jour dans la base de données
            QString reqUpdateProducteurInvalidation = "UPDATE Producteur SET validationProducteur = FALSE, "
                                                      "raisonInvalidationProducteur = '"+raisonInvalidation+"' "
                                                      "WHERE numeroProducteur = "+ui->tableWidget_producteursEnAttente->selectedItems()[0]->text();
            qDebug()<<reqUpdateProducteurInvalidation;
            QSqlQuery resultUpdateProducteurInvalidation(reqUpdateProducteurInvalidation);
            qDebug()<<resultUpdateProducteurInvalidation.numRowsAffected();
            //si l'update a fonctionné
            if(resultUpdateProducteurInvalidation.numRowsAffected() != -1){
                //on supprime la ligne du tableau des producteurs en attente
                ui->tableWidget_producteursEnAttente->removeRow(ui->tableWidget_producteursEnAttente->currentRow());
                //on actualise le tableau des producteurs invalidés
                afficherTableProducteurInvalides();

                //on affiche un message de réussite
                ui->statusBar->showMessage("Le producteur "+nomPrenomProducteur+" ont été invalidé avec succès !",5000);
            } else {
                ui->statusBar->showMessage("Erreur lors de l'invalidation du producteur "+nomPrenomProducteur+" !",5000);
            }
        }
    }

}
