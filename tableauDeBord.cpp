#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::initTableauDeBord
 * Méthode publique de la classe MainWindow qui initialise le tab Tableau de bord
 */
void MainWindow::initTableauDeBord()
{
    qDebug()<<"void MainWindow::initTableauDeBord()";
    chiffresDAffaires = 0;

    //on stretch les tableaux
    ui->tableWidget_tdbVarietesParRayon->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    nbNewProducteurs();
    nbNewVarietes();
    afficherNbVarietesParRayon();
    nbNewLotsDeProductions();
    nbChiffreDAffairesAbonnements();
}

/**
 * @brief MainWindow::nbNewProducteurs
 * Méthode publique de la classe MainWindow qui affiche le nombre de nouveaux producteurs dans le tableau de bord
 */
void MainWindow::nbNewProducteurs()
{
    qDebug()<<"void MainWindow::nbNewProducteurs()";
    QString reqNbNewProducteurs = "SELECT COUNT(*) FROM Producteur "
                               "WHERE DATEDIFF(NOW(),dateInscriptionProducteur) BETWEEN 0 AND "+nbJourTableauDeBord;
    qDebug()<<reqNbNewProducteurs;
    QSqlQuery reqsultNbNewProducteurs(reqNbNewProducteurs);
    //si la requête a fonctionné
    if(reqsultNbNewProducteurs.numRowsAffected() != -1){
        reqsultNbNewProducteurs.next();
        ui->spinBox_tdbNbNewProducteurs->setValue(reqsultNbNewProducteurs.value(0).toInt());
    } else {
        ui->statusBar->showMessage("Erreur lors de l'affichage du nombre de nouveaux producteurs !");
    }
}

/**
 * @brief MainWindow::nbNewVarietes
 * Méthode publique de la classe MainWindow qui affiche le nombre de nouvelles variétés dans le tableau de bord
 */
void MainWindow::nbNewVarietes()
{
    qDebug()<<"void MainWindow::nbNewVarietes()";
    QString reqNbNewVarietes = "SELECT COUNT(*) FROM Variete "
                               "WHERE DATEDIFF(NOW(),dateInscriptionVariete) BETWEEN 0 AND "+nbJourTableauDeBord;
    qDebug()<<reqNbNewVarietes;
    QSqlQuery resultNbNewVarietes(reqNbNewVarietes);
    //si la requête a fonctionné
    if(resultNbNewVarietes.numRowsAffected() != -1){
        resultNbNewVarietes.next();
        ui->spinBox_tdbNbNewVarietes->setValue(resultNbNewVarietes.value(0).toInt());
    } else {
        ui->statusBar->showMessage("Erreur lors de l'affichage du nombre de nouvelles variétés !");
    }
}

/**
 * @brief MainWindow::afficherNbVarietesParRayon
 * Méthode publique de la classe MainWindow qui affiche le nombre de variétés par rayons dans un QTableWidget du tab Tableau de bord
 */
void MainWindow::afficherNbVarietesParRayon()
{
    qDebug()<<"void MainWindow::afficherNbVarietesParRayon()";
    //on initialise le tableau
    ui->tableWidget_tdbVarietesParRayon->clearContents();
    ui->tableWidget_tdbVarietesParRayon->setRowCount(0);
    //requête qui récupère le nombre de variétés par rayons
    QString reqVarietesParRayon = "SELECT r.libelleRayon, COUNT(v.numeroVariete) as nbVariete FROM Rayon r "
                                  "INNER JOIN Produit p ON p.numeroRayon = r.numeroRayon "
                                  "LEFT OUTER JOIN Variete v ON v.numeroProduit = p.numeroProduit "
                                  "WHERE DATEDIFF(NOW(),v.dateInscriptionVariete) BETWEEN 0 AND "+nbJourTableauDeBord+" "
                                  "GROUP BY r.libelleRayon "
                                  "ORDER BY r.libelleRayon ASC ";
    qDebug()<<reqVarietesParRayon;
    QSqlQuery resultVarietesParRayon(reqVarietesParRayon);
    //si la requête a fonctionné
    if(resultVarietesParRayon.numRowsAffected() != -1){
        //on affiche chaque ligne
        while(resultVarietesParRayon.next()){
            //on ajoute une ligne au tableau
            int row = ui->tableWidget_tdbVarietesParRayon->rowCount();
            ui->tableWidget_tdbVarietesParRayon->setRowCount(row+1);
            //on insère le contenu de chaque cellule
            ui->tableWidget_tdbVarietesParRayon->setItem(row,0,new QTableWidgetItem(resultVarietesParRayon.value("libelleRayon").toString()));
            ui->tableWidget_tdbVarietesParRayon->setItem(row,1,new QTableWidgetItem(resultVarietesParRayon.value("nbVariete").toString()));
        }
    }else {
        ui->statusBar->showMessage("Erreur lors de l'affichage des variétés par rayon !",5000);
    }

}

/**
 * @brief MainWindow::on_pushButton_tdbActualiser_clicked
 * Méthode private slots de la classe MainWindow qui lorsque le bouton Actualiser de l'onglet Tableau de bord est cliqué actualise les données de l'onglet
 */
void MainWindow::on_pushButton_tdbActualiser_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_tdbActualiser_clicked()";
    initTableauDeBord();
}

/**
 * @brief MainWindow::nbNewLotsDeProductions
 * Méthode publique de la classe MainWindow qui affiche le nombre de nouveaux lots de productions dans le tableau de bord
 */
void MainWindow::nbNewLotsDeProductions()
{
    qDebug()<<"void MainWindow::nbNewLotsDeProductions()";
    QString reqNbNewLotsDeProductions = "SELECT COUNT(*) FROM ProduitProducteur "
                               "WHERE DATEDIFF(NOW(),dateAjoutProduitProducteur) BETWEEN 0 AND "+nbJourTableauDeBord;
    qDebug()<<reqNbNewLotsDeProductions;
    QSqlQuery resultNbNewLotsDeProductions(reqNbNewLotsDeProductions);
    //si la requête a fonctionné
    if(resultNbNewLotsDeProductions.numRowsAffected() != -1){
        resultNbNewLotsDeProductions.next();
        ui->spinBox_tdbNbLotsDeProductions->setValue(resultNbNewLotsDeProductions.value(0).toInt());
    } else {
        ui->statusBar->showMessage("Erreur lors de l'affichage du nombre de nouveaux lots de productions !");
    }
}

/**
 * @brief MainWindow::nbChiffreDAffairesAbonnements
 * Méthode publique de la classe MainWindow qui affiche le chiffre d'affaires des abonnements dans le tableau de bord
 */
void MainWindow::nbChiffreDAffairesAbonnements()
{
    qDebug()<<"void MainWindow::nbChiffreDAffairesAbonnements()";
    QString reqChiffreDAffairesAbonnements = "SELECT SUM(ta.prixTypeAbonnement) FROM TypeAbonnement ta "
                                             "INNER JOIN Abonnement a ON a.numeroTypeAbonnement = ta.numeroTypeAbonnement "
                                             "WHERE DATEDIFF(NOW(),a.dateDebAbonnement) BETWEEN 0 AND "+nbJourTableauDeBord;
    qDebug()<<reqChiffreDAffairesAbonnements;
    QSqlQuery resultChiffreDAffairesAbonnements(reqChiffreDAffairesAbonnements);
    //si la requête a fonctionné
    if(resultChiffreDAffairesAbonnements.numRowsAffected() != -1){
        resultChiffreDAffairesAbonnements.next();
        chiffresDAffaires = resultChiffreDAffairesAbonnements.value(0).toInt();
        ui->doubleSpinBox_tdbNbCAAbonnements->setValue(chiffresDAffaires);
    } else {
        ui->statusBar->showMessage("Erreur lors de l'affichage du nombre du chiffre d'affaires des abonnements !");
    }
}
