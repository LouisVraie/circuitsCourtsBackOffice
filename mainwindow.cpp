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
    this->numeroEmploye = numeroEmploye;

    setWindowTitle("CircuitsCourts - BackOffice");

    getInfosEmploye();
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
                              "mailEmploye, telEmploye, libelleTypeEmploye FROM Employe e "
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
}

/**
 * @brief MainWindow::setTab_profil
 * Méthode publique de la classe MainWindow qui remplit les informations du tab Profil
 */
void MainWindow::setTab_profil()
{
    qDebug()<<"void MainWindow::setTab_profil()";
    ui->lineEdit_nomEmploye->setText(nom);
    ui->lineEdit_prenomEmploye->setText(prenom);
    ui->lineEdit_typeEmploye->setText(libelleTypeEmploye);
    ui->lineEdit_loginEmploye->setText(login);
    ui->lineEdit_adresseEmploye->setText(adresse);
    ui->lineEdit_codePostalEmploye->setText(codePostal);
    ui->lineEdit_villeEmploye->setText(ville);
    ui->lineEdit_mailEmploye->setText(mail);
    ui->lineEdit_telEmploye->setText(tel);

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
 * @brief MainWindow::escapeString
 * Méthode publique de la classe MainWindow qui permet d'échapper à certain caractères
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
 * @brief MainWindow::on_action_Quitter_triggered
 * Méthode private slots de la classe MainWindow qui créer un événement de fermeture de fenêtre
 */
void MainWindow::on_action_Quitter_triggered()
{
    close();
}

/**
 * @brief MainWindow::on_pushButton_sauvegarderInfosEmploye_clicked
 * Méthode private slots de la classe MainWindow qui enregistre les informations de l'utilisateur
 */
void MainWindow::on_pushButton_sauvegarderInfosEmploye_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_sauvegarderInfosEmploye_clicked()";
    //on récupère le texte des lineEdits des informations personnelles
    QString newLogin, newAdresse, newCodePostal, newVille, newMail, newTel;
    newLogin = escapeString(ui->lineEdit_loginEmploye->text());
    newAdresse = escapeString(ui->lineEdit_adresseEmploye->text());
    newCodePostal = escapeString(ui->lineEdit_codePostalEmploye->text());
    newVille = escapeString(ui->lineEdit_villeEmploye->text());
    newMail = escapeString(ui->lineEdit_mailEmploye->text());
    newTel = escapeString(ui->lineEdit_telEmploye->text());
}

/**
 * @brief MainWindow::on_pushButton_sauvegarderNewMotDePasseEmploye_clicked
 * Méthode private slots de la classe MainWindow qui enregistre le nouveau mot de passe
 */
void MainWindow::on_pushButton_sauvegarderNewMotDePasseEmploye_clicked()
{
    qDebug()<<"QString MainWindow::on_pushButton_sauvegarderNewMotDePasseEmploye_clicked()";
    QString newMdp, newConfirmMdp;
    newMdp = escapeString(ui->lineEdit_newMotDePasseEmploye->text());
    newConfirmMdp = escapeString(ui->lineEdit_confirmMotDePasseEmploye->text());

    //si les deux mots de passe sont les mêmes
    if (newMdp == newConfirmMdp){
        //si le mot de passe est supérieur ou égal à 8 caractères
        if (newMdp.length() >= 8) {
            //requête qui met à jour le mot de passe
            QString reqUpdateMdp = "UPDATE Employe SET motDePasseEmploye = PASSWORD('"+newMdp+"') WHERE numeroEmploye ="+numeroEmploye;
            qDebug()<<reqUpdateMdp;
            QSqlQuery resultUpdateMdp(reqUpdateMdp);
            //si la requête a fonctionné
            if (resultUpdateMdp.numRowsAffected() != -1){
                ui->statusBar->showMessage("Votre mot de passe a été mis à jour !",5000);
            } else {
                ui->statusBar->showMessage("Une erreur est survenue lors du changement de votre mot de passe !",5000);
            }
        } else {
            ui->statusBar->showMessage("Votre mot de passe doit faire au minimum 8 caractères !",5000);
        }
    } else {
        ui->statusBar->showMessage("Les mots de passe saisis ne correspondent pas !",5000);
    }
}
