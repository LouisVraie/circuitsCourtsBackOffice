#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * Constructeur de la classe MainWindow qui crée la fenêtre de notre application
 * @param parent: QWidget
 */
MainWindow::MainWindow(QString numeroEmploye,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("CircuitsCourtsBackOffice - Tableau de Bord : ");

    getInfosEmploye();
}

/**
 * @brief MainWindow::~MainWindow
 * Destructeur de la classe MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::getInfosEmploye
 * Méthode publique de la classe MainWindow qui récupère les informations de l'employé
 */
void MainWindow::getInfosEmploye()
{
    qDebug()<<"void MainWindow::getInfosEmploye()";
    //selon le numeroEmploye on exécute une requête SQL qui nous récupère toutes les informations
    QString reqInfosEmploye = "SELECT loginEmploye, nomEmploye, prenomEmploye, adresseEmploye, codePostalEmploye, villeEmploye, "
                              "mailEmploye, telEmploye, libelleTypeEmploye FROM Employe e"
                              "INNER JOIN TypeEmploye te ON te.numeroTypeEmploye = e.numeroTypeEmploye"
                              "WHERE numeroEmploye = "+numeroEmploye;
    qDebug()<<reqInfosEmploye;
    QSqlQuery resultInfosEmploye(reqInfosEmploye);

    resultInfosEmploye.next();
    login = resultInfosEmploye.value("loginEmploye").toString();
    nom = resultInfosEmploye.value("nomEmploye").toString();
    prenom = resultInfosEmploye.value("prenomEmploye").toString();
    adresse = resultInfosEmploye.value("adresseEmploye").toString();
    codePostal = resultInfosEmploye.value("codePostalEmploye").toString();
    ville = resultInfosEmploye.value("villeEmploye").toString();
    mail = resultInfosEmploye.value("mailEmploye").toString();
    tel = resultInfosEmploye.value("telEmploye").toString();
    libelleTypeEmploye = resultInfosEmploye.value("libelleTypeEmploye").toString();
}
