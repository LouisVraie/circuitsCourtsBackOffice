#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QCloseEvent>
#include <QCheckBox>
#include <QTableWidgetItem>
#include <QInputDialog>
#include <QFileDialog>
#include <QDate>

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
    void setTableProducteurValidesActivationColor(int row, QString backgroundColor);

    /* gestionProduits.cpp */
    void initGestionProduits();
    //rayons
    void afficherTableGestionProduitsRayons();
    void clearGestionProduitsRayonInputs();

    //produits
    void afficherTableGestionProduitsProduits();
    void updateComboBoxGestionProduitsProduitsRayon();
    void clearGestionProduitsProduitsInputs();

    //varietes
    void afficherTableGestionProduitsVarietes();
    void setTableGestionProduitsVarietesEstValideColor(int row, QString backgroundColor);
    void updateComboBoxGestionProduitsVarietesProduit();
    void clearGestionProduitsVarietesInputs();

    /* profil.cpp */
    void setTab_profil();

    /* méthodes de fermeture de l'application*/
    bool quitConfirm();
    void closeEvent(QCloseEvent *event);

    /* méthode de vérification de caractères */
    static QString escapeString(QString myQString);
    bool verifMdp(QString newMdp, QString newCMdp);

    QString setNextId(QString idColumn, QString table, int increment = 1, int baseId = 1);
    int verifDoublon(QString table, QString columnName, QString conditionValue);

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

    /* producteurs.cpp */
    void on_pushButton_producteursEnAttenteValider_clicked();
    void on_pushButton_producteursEnAttenteInvalider_clicked();
    void on_pushButton_producteursValidesDesactiver_clicked();
    void on_pushButton_producteursValidesActiver_clicked();

    /* gestionProduits.cpp */
    //rayons
    void on_pushButton_gestionProduitsRayonsImage_clicked();
    void on_allLineEditGestionProduitsRayons_textChanged();
    void on_pushButton_gestionProduitsRayonsAjouter_clicked();
    void on_tableWidget_gestionProduitsRayons_itemSelectionChanged();
    void on_pushButton_gestionProduitsRayonsModifier_clicked();
    void on_pushButton_gestionProduitsRayonsSupprimer_clicked();
    //produits
    void on_pushButton_gestionProduitsProduitsImage_clicked();
    void on_allLineEditGestionProduitsProduits_textChanged();
    void on_pushButton_gestionProduitsProduitsAjouter_clicked();
    void on_tableWidget_gestionProduitsProduits_itemSelectionChanged();
    void on_pushButton_gestionProduitsProduitsModifier_clicked();
    void on_pushButton_gestionProduitsProduitsSupprimer_clicked();
    //variétés
    void on_pushButton_gestionProduitsVarietesImage_clicked();
    void on_allLineEditGestionProduitsVarietes_textChanged();

    void on_pushButton_gestionProduitsVarietesAjouter_clicked();

private:
    Ui::MainWindow *ui;

    //Propriétés
    QString appPath;
    QString numeroEmploye, libelleTypeEmploye, numeroTypeEmploye;
    QString login, nom, prenom;
    QString adresse, codePostal, ville;
    QString mail, tel;

    int loginMinimumSize, nomPrenomMinimumSize, mdpMinimumSize;
    int adresseMinimumSize, codePostalMinimumSize, villeMinimumSize, mailMinimumSize, telMinimumSize;
    int libelleMinimumSize, imagePathMinimumSize;

    /* employes.cpp */
    int rowEmploye;
    QString newTypeEmploye, newNom, newPrenom, newLogin, newMdp, newCMdp, newAdresse, newCodePostal, newVille, newMail, newTel;

    /* gestionProduits.cpp */
    int imageSize;
    int rowGestionProduitsRayon, rowGestionProduitsProduit, rowGestionProduitsVariete;

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
