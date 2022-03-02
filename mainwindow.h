#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlQuery>

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
private:
    Ui::MainWindow *ui;

    QString numeroEmploye;
};

#endif // MAINWINDOW_H
