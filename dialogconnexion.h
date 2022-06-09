#ifndef DIALOGCONNEXION_H
#define DIALOGCONNEXION_H

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class DialogConnexion;
}

/**
 * @brief La classe DialogConnexion
 */
class DialogConnexion : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConnexion(QWidget *parent = nullptr);
    ~DialogConnexion();

    QString getNumeroEmploye();

    bool quitConfirm();
    void closeEvent(QCloseEvent *event);
private slots:
    void on_pushButtonConnexion_clicked();

    void on_pushButtonQuitter_clicked();

private:
    Ui::DialogConnexion *ui;
    QString numeroEmploye;
    int nbTentativeConnexion;
};

#endif // DIALOGCONNEXION_H
