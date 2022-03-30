#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QCloseEvent>
#include <QCheckBox>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

/**
 * @brief La classe MainWindow
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString numeroEmploye, QWidget *parent = nullptr);
    ~MainWindow();

    /* méthodes d'initialisations */
    void getInfosEmploye();
    void hideTabs();

    /* employes.cpp */
    void initEmployes();
    void afficherTableEmployes();
    void fill_comboBox_employesTypeEmploye();

    /* producteurs.cpp */
    void initProducteurs();
    void afficherTableProducteurEnAttente();
    void afficherTableProducteurValides();
    void afficherTableProducteurInvalides();

    /* profil.cpp */
    void setTab_profil();

    /* méthodes de fermeture de l'application*/
    bool quitConfirm();
    void closeEvent(QCloseEvent *event);

    /* méthode de vérification de caractères */
    static QString escapeString(QString myQString);
    bool verifMdp(QString newMdp, QString newCMdp);

private slots:
    void on_action_Quitter_triggered();

    /* profil.cpp */
    void on_pushButton_sauvegarderInfosEmploye_clicked();
    void on_pushButton_sauvegarderNewMotDePasseEmploye_clicked();
    void on_pushButton_annulerInfosEmploye_clicked();
    void on_pushButton_effacerNewMotDePasseEmploye_clicked();
    void on_lineEdit_loginEmploye_textChanged(const QString &arg1);

    /* employes.cpp */
    void on_allLineEditEmploye_textChanged();
    void on_pushButton_ajouterEmploye_clicked();
    void on_tableWidget_employes_itemSelectionChanged();
    void on_pushButton_modifierEmploye_clicked();
    void on_pushButton_supprimerEmploye_clicked();

    void on_pushButton_producteursEnAttenteValider_clicked();

private:
    Ui::MainWindow *ui;

    //Propriétés
    QString numeroEmploye, libelleTypeEmploye, numeroTypeEmploye;
    QString login, nom, prenom;
    QString adresse, codePostal, ville;
    QString mail, tel;

    int loginMinimumSize, nomPrenomMinimumSize, mdpMinimumSize;
    int adresseMinimumSize, codePostalMinimumSize, villeMinimumSize, mailMinimumSize, telMinimumSize;

    /* employes.cpp */
    int rowEmploye;
    QString newTypeEmploye, newNom, newPrenom, newLogin, newMdp, newCMdp, newAdresse, newCodePostal, newVille, newMail, newTel;

    //Méthodes
    /* employes.cpp */
    void getEmployesInputs();
    void clearEmployesInputs();
    bool verifEmployesMail();

    /* profil.cpp */
    QString verifChangePassword();
    bool verifEmployeInfos(QString leLogin, QString leMail, QString leTel);
    bool updateEmployeInfos(QString leLogin, QString lAdresse, QString leCodePostal, QString laVille, QString leMail, QString leTel);

};

#endif // MAINWINDOW_H
