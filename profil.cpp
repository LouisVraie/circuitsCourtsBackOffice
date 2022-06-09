#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    ui->pushButton_sauvegarderInfosEmploye->setDisabled(true);
    connect(ui->lineEdit_loginEmploye,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditProfilInformationPersonnelles_textChanged()));
    connect(ui->lineEdit_adresseEmploye,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditProfilInformationPersonnelles_textChanged()));
    connect(ui->lineEdit_codePostalEmploye,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditProfilInformationPersonnelles_textChanged()));
    connect(ui->lineEdit_villeEmploye,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditProfilInformationPersonnelles_textChanged()));
    connect(ui->lineEdit_mailEmploye,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditProfilInformationPersonnelles_textChanged()));
    connect(ui->lineEdit_telEmploye,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditProfilInformationPersonnelles_textChanged()));
    ui->pushButton_sauvegarderNewMotDePasseEmploye->setDisabled(true);
    connect(ui->lineEdit_newMotDePasseEmploye,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditProfilMdp_textChanged()));
    connect(ui->lineEdit_confirmMotDePasseEmploye,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditProfilMdp_textChanged()));

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
    if (verifMdp(newMdp,newConfirmMdp)){
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

/**
 * @brief MainWindow::on_allLineEditProfilInformationPersonnelles_textChanged
 * Méthode private slots de la classe MainWindow qui active ou non le bouton Sauvegarder des informations personnelles de l'onglet Profil
 */
void MainWindow::on_allLineEditProfilInformationPersonnelles_textChanged()
{
    qDebug()<<"void MainWindow::on_allLineEditProfilInformationPersonnelles_textChanged()";
    bool login, adresse, cp, ville, mail, tel;
    login = ui->lineEdit_loginEmploye->text().size() >= loginMinimumSize;
    adresse = ui->lineEdit_adresseEmploye->text().size() >= adresseMinimumSize;
    cp = ui->lineEdit_codePostalEmploye->text().size() >= codePostalMinimumSize;
    ville = ui->lineEdit_villeEmploye->text().size() >= villeMinimumSize;
    mail = ui->lineEdit_mailEmploye->text().size() >= mailMinimumSize;
    tel = ui->lineEdit_telEmploye->text().size() >= telMinimumSize;
    //si les champs sont remplis
    if(login && adresse && cp && ville && mail && tel){
        //on active le bouton sauvegarder
        ui->pushButton_sauvegarderInfosEmploye->setEnabled(true);
    }else {
        //on désactive le bouton sauvegarder
        ui->pushButton_sauvegarderInfosEmploye->setEnabled(false);
    }
}

/**
 * @brief MainWindow::on_allLineEditProfilMdp_textChanged
 * Méthode private slots de la classe MainWindow qui active ou non le bouton Sauvegarder d'un nouveau mot de passe de l'onglet Profil
 */
void MainWindow::on_allLineEditProfilMdp_textChanged()
{
    qDebug()<<"void MainWindow::on_allLineEditProfilMdp_textChanged()";
    bool mdp, cmdp;
    mdp = ui->lineEdit_newMotDePasseEmploye->text().size() >= mdpMinimumSize;
    cmdp = ui->lineEdit_confirmMotDePasseEmploye->text().size() >= mdpMinimumSize;
    //si les champs sont remplis
    if(mdp && cmdp){
        //on active le bouton sauvegarder
        ui->pushButton_sauvegarderNewMotDePasseEmploye->setEnabled(true);
    }else {
        //on désactive le bouton sauvegarder
        ui->pushButton_sauvegarderNewMotDePasseEmploye->setEnabled(false);
    }
}
