#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QCloseEvent>

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

    void getInfosEmploye();

    void setTab_profil();

    bool quitConfirm();
    void closeEvent(QCloseEvent *event);

    QString escapeString(QString myQString);

private slots:
    void on_action_Quitter_triggered();

    void on_pushButton_sauvegarderInfosEmploye_clicked();

    void on_pushButton_sauvegarderNewMotDePasseEmploye_clicked();

private:
    Ui::MainWindow *ui;

    //Propriétés
    QString numeroEmploye, libelleTypeEmploye;
    QString login, nom, prenom;
    QString adresse, codePostal, ville;
    QString mail, tel;

    //Méthodes
    QString verifChangePassword();
};

#endif // MAINWINDOW_H
