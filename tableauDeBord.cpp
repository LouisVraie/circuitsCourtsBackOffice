#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::initTableauDeBord
 * Méthode publique de la classe MainWindow qui initialise le tab Tableau de bord
 */
void MainWindow::initTableauDeBord()
{
    qDebug()<<"void MainWindow::initTableauDeBord()";

    nbNewVarietes();
}

/**
 * @brief MainWindow::nbNewVarietes
 * Méthode publique de la classe MainWindow qui affiche le nombre de nouvelles variétés dans le tableau de bord
 */
void MainWindow::nbNewVarietes()
{
    qDebug()<<"void MainWindow::nbNewVarietes()";
    QString reqNbNewVarietes = "SELECT COUNT(*) FROM Variete "
                               "WHERE DATEDIFF(dateInscriptionVariete,NOW()) BETWEEN 0 AND "+nbJourTableauDeBord;
    qDebug()<<reqNbNewVarietes;
    QSqlQuery resultNbNewVarietes(reqNbNewVarietes);
    //si la requête a fonctionné
    if(resultNbNewVarietes.numRowsAffected() != -1){
        resultNbNewVarietes.next();
        ui->spinBox_tdbNbNewVarietes->setValue(resultNbNewVarietes.value(0).toInt());
    } else {
        ui->statusBar->showMessage("Erreur lors de l'affichage du nombre de variété !");
    }
}

/**
 * @brief MainWindow::afficherNbVarietesParRayon
 * Méthode publique de la classe MainWindow qui affiche le nombre de variétés par rayons dans un QTableWidget du tab Tableau de bord
 */
void MainWindow::afficherNbVarietesParRayon()
{
    qDebug()<<"void MainWindow::afficherNbVarietesParRayon()";

}
