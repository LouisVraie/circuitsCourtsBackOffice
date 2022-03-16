#include "mainwindow.h"
#include "dialogconnexion.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    bool okConnexion = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
          db.setHostName("localhost");
          db.setDatabaseName("dbCircuitsCourts");
          db.setUserName("userCircuitsCourts");
          db.setPassword("57-Ze!_eR");
          okConnexion = db.open();
    if(okConnexion){
        qDebug()<<"Connecté à la base de données !";
    }else {
        qDebug()<<"Erreur lors de la connexion à la base de données !";
    }

    QApplication a(argc, argv);
    DialogConnexion connexion;
    if(connexion.exec() == QDialog::Accepted){
        MainWindow w(connexion.getNumeroEmploye());
        w.showMaximized();
        return a.exec();
    }
}
