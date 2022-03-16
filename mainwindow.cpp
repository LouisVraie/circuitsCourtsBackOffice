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
    this->loginMinimumSize = 3;

    //initialisation des éléments de l'UI
    setWindowTitle("CircuitsCourts - BackOffice");
    ui->tabWidget->setCurrentIndex(0);

    //on stretch les colonnes des QTableWidget
    ui->tableWidget_employes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    /* Méthodes d'initialisation */
    getInfosEmploye();
    hideTabs();
    //Employés
    afficherTableEmployes();
    fill_comboBox_employesTypeEmploye();
    //Profil
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
    //si la requête a fonctionné
    if (updateEmployeInfos(newLogin,newAdresse,newCodePostal,newVille,newMail,newTel)){
        ui->statusBar->showMessage("Votre profil a été mis à jour !",5000);
    } else {
        ui->statusBar->showMessage("Une erreur est survenue lors du changement de vos informations personnelles !",5000);
    }
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

/**
 * @brief MainWindow::verifEmployeInfos
 * Méthode private de la classe MainWindow qui permet de vérifier qu'un des arguments n'est pas déjà renseigné ailleur
 * @param leLogin: QString Login de l'employé
 * @param leMail: QString Mail de l'employé
 * @param leTel: QString Numéro de téléphone de l'employé
 * @return bool Retourne true si aucune donnée est déjà existante
 */
bool MainWindow::verifEmployeInfos(QString leLogin, QString leMail, QString leTel)
{
    qDebug()<<"bool MainWindow::verifEmployeInfos()";
    //Vérification pour savoir que certaines données enregistrées n'existes pas déjà
    QString reqVerifEmployeInfos = "SELECT COUNT(*) FROM Employe "
                                   "WHERE numeroEmploye <> "+numeroEmploye+" "
                                   "AND numeroEmploye IN (SELECT numeroEmploye FROM Employe "
                                   "WHERE loginEmploye = '"+leLogin+"' "
                                   "OR mailEmploye = '"+leMail+"' "
                                   "OR telEmploye = '"+leTel+"')";
    qDebug()<<reqVerifEmployeInfos;
    QSqlQuery resultVerifEmployeInfos(reqVerifEmployeInfos);
    resultVerifEmployeInfos.next();
    qDebug()<<resultVerifEmployeInfos.value(0).toInt();
    return resultVerifEmployeInfos.value(0).toInt() == 0;
}

/**
 * @brief MainWindow::updateEmployeInfos
 * Méthode private de la classe MainWindow qui permet de mettre à jour les informations personnelles du profil de l'employé
 * @param leLogin: QString Login de l'employé
 * @param lAdresse: QString Adresse de l'employé
 * @param leCodePostal: QString Code postal de l'employé
 * @param laVille: QString Ville de l'employé
 * @param leMail: QString Mail de l'employé
 * @param leTel: QString Numéro de téléphone de l'employé
 * @return bool État de l'exécution de la requête de mise à jour des informations personnelles
 */
bool MainWindow::updateEmployeInfos(QString leLogin, QString lAdresse, QString leCodePostal,
                                    QString laVille, QString leMail, QString leTel)
{
    qDebug()<<"bool MainWindow::updateEmployeInfos()";
    if(verifEmployeInfos(leLogin,leMail,leTel)){
        //Mise à jour des inforamtions personnelles
        QString reqUpdateEmployeInfos = "UPDATE Employe SET "
                                        "loginEmploye = '"+leLogin+"', "
                                        "adresseEmploye = '"+lAdresse+"', "
                                        "codePostalEmploye = '"+leCodePostal+"', "
                                        "villeEmploye = '"+laVille+"', "
                                        "mailEmploye = '"+leMail+"', "
                                        "telEmploye = '"+leTel+"' "
                                        "WHERE numeroEmploye = "+numeroEmploye;
        qDebug()<<reqUpdateEmployeInfos;
        QSqlQuery resultUpdateEmployeInfos(reqUpdateEmployeInfos);
        //on retourne si la requête a fonctionné
        return resultUpdateEmployeInfos.numRowsAffected() != -1;
    } else {
        return false;
    }
}

/**
 * @brief MainWindow::on_pushButton_annulerInfosEmploye_clicked
 * Méthode private slots de la classe MainWindow qui restaure le contenu des champs d'informations personnelles du profil
 */
void MainWindow::on_pushButton_annulerInfosEmploye_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_annulerInfosEmploye_clicked()";
    //si la restauration a fonctionné
    if(updateEmployeInfos(login,adresse,codePostal,ville,mail,tel)){
        ui->lineEdit_loginEmploye->setText(login);
        ui->lineEdit_adresseEmploye->setText(adresse);
        ui->lineEdit_codePostalEmploye->setText(codePostal);
        ui->lineEdit_villeEmploye->setText(ville);
        ui->lineEdit_mailEmploye->setText(mail);
        ui->lineEdit_telEmploye->setText(tel);
        ui->statusBar->showMessage("Vos informations personnelles ont été restaurés !",5000);
    } else {
        ui->statusBar->showMessage("Une erreur est survenue lors de la restauration vos informations personnelles !",5000);
    }
}

/**
 * @brief MainWindow::on_pushButton_effacerNewMotDePasseEmploye_clicked
 * Méthode private slots de la classe MainWindow qui efface les champs des mots de passes dans le tab Profil
 */
void MainWindow::on_pushButton_effacerNewMotDePasseEmploye_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_effacerNewMotDePasseEmploye_clicked()";
    ui->lineEdit_newMotDePasseEmploye->clear();
    ui->lineEdit_confirmMotDePasseEmploye->clear();
}

/**
 * @brief MainWindow::on_lineEdit_loginEmploye_textChanged
 * Méthode private slots de la classe MainWindow qui met à jour dans le tab Profil, l'état du bouton Sauvegarder des informations personnelles
 * @param arg1: QString Texte du lineEdit
 */
void MainWindow::on_lineEdit_loginEmploye_textChanged(const QString &arg1)
{
    qDebug()<<"void MainWindow::on_lineEdit_loginEmploye_textChanged()";
    if(arg1.length() >= loginMinimumSize){
        ui->pushButton_sauvegarderInfosEmploye->setDisabled(false);
    } else {
        ui->pushButton_sauvegarderInfosEmploye->setDisabled(true);
    }
}

