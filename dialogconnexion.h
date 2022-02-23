#ifndef DIALOGCONNEXION_H
#define DIALOGCONNEXION_H

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>

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

    bool getVerifConnexion();
private slots:
    void on_pushButtonConnexion_clicked();

private:
    Ui::DialogConnexion *ui;
    bool verifConnexion;
};

#endif // DIALOGCONNEXION_H
