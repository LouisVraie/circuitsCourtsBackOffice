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
    //initialisation des propriétés
    this->numeroEmploye = numeroEmploye;
    this->loginMinimumSize = 4;
    nomPrenomMinimumSize = 3;
    mdpMinimumSize = 3;
    adresseMinimumSize = 10;
    codePostalMinimumSize = 5;
    villeMinimumSize = 2;
    mailMinimumSize = 5;
    telMinimumSize = 10;

    //initialisation des éléments de l'UI
    setWindowTitle("CircuitsCourts - BackOffice");

    /* Méthodes d'initialisation */
    getInfosEmploye();
    hideTabs();

    /* employes.cpp */
    initEmployes();

    /* producteurs.cpp */
    initProducteurs();

    /* gestionProduits.cpp */
    initGestionProduits();

    /* profil.cpp */
    setTab_profil();
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
                              "mailEmploye, telEmploye, libelleTypeEmploye, e.numeroTypeEmploye FROM Employe e "
                              "INNER JOIN TypeEmploye te ON te.numeroTypeEmploye = e.numeroTypeEmploye "
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
    numeroTypeEmploye = resultInfosEmploye.value("numeroTypeEmploye").toString();
}

/**
 * @brief MainWindow::hideTabs
 * Méthode publique de la classe MainWindow qui cache les tabs que n'est pas censé voir l'employé connecté
 */
void MainWindow::hideTabs()
{
    qDebug()<<"void MainWindow::hideTabs()";
    switch (numeroTypeEmploye.toInt()) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            //On retire le tab Employés
            ui->tabWidget->removeTab(1);
            //On retire le tab Tableau de bord
            ui->tabWidget->removeTab(0);
            break;
    }
    ui->tabWidget->setCurrentIndex(0);
}



/**
 * @brief MainWindow::quitConfirm()
 * Méthode publique de la classe MainWindow qui sert à afficher un message de confirmation pour quitter
 * @return Retourne un booléen vrai si l'utilisateur confirme, sinon renvoie faux
 */
bool MainWindow::quitConfirm()
{
    if(QMessageBox::warning(this,this->windowTitle(),"Voulez-vous vraiment quitter l'application ?", QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief MainWindow::closeEvent
 * Méthode publique de la classe MainWindow qui execute la méthode quitConfirm() quand l'utilisateur cherche à fermer la fenêtre
 * @param event Événement de fermeture
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(quitConfirm())
    {
        event->accept();
    }
    else {
        event->ignore();
    }
}

/**
 * @brief MainWindow::on_action_Quitter_triggered
 * Méthode private slots de la classe MainWindow qui créer un événement de fermeture de fenêtre
 */
void MainWindow::on_action_Quitter_triggered()
{
    close();
}

/**
 * @brief MainWindow::escapeString
 * Méthode statique publique de la classe MainWindow qui permet d'échapper à certain caractères
 * @param myQString: QString Chaîne de caractère quelconque
 * @return QString
 */
QString MainWindow::escapeString(QString myQString)
{
    //on enlève les caractères non voulus
    myQString = myQString.replace(";","");
    //on double les simples quotes
    myQString = myQString.replace("'","''");
    return myQString;
}

/**
 * @brief MainWindow::verifMdp
 * Méthode publique de la classe MainWindow qui vérifie les champs de mots de passes
 * @param newMdp: QString Mot de passe
 * @param newCMdp: QString Confirmation de mot de passe
 * @return bool Booléen qui détermine si un mot de passe répond aux critères ou non
 */
bool MainWindow::verifMdp(QString newMdp, QString newCMdp)
{
    qDebug()<<"bool MainWindow::verifMdp()";
    //si les deux variables sont équivalentes
    if(newMdp == newCMdp){
        //si le mot de passe fait au minimum 8 caractères
        if(newMdp.length() >= 8){
            return true;
        } else {
            ui->statusBar->showMessage("Votre mot de passe doit faire au minimum 8 caractères !",5000);
        }
    } else {
        ui->statusBar->showMessage("Les mots de passe saisis ne correspondent pas !",5000);
    }
    return false;
}





