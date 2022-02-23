#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * Constructeur de la classe MainWindow qui crée la fenêtre de notre application
 * @param parent: QWidget
 */
MainWindow::MainWindow(int numeroTypeEmploye,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("CircuitsCourtsBackOffice - Tableau de Bord : ");

    //selon le numeroTypeEmploye on affiche le bon libelle dans le titre de la mainwindow
    switch(numeroTypeEmploye){
        case 1:
            setWindowTitle(windowTitle()+"SuperAdmin");
            ui->stackedWidget->setCurrentIndex(0);
            break;
        case 2:
            setWindowTitle(windowTitle()+"Administrateur");
            ui->stackedWidget->setCurrentIndex(1);
            break;
        case 3:
            setWindowTitle(windowTitle()+"Modérateur");
            ui->stackedWidget->setCurrentIndex(2);
            break;
    }
}

/**
 * @brief MainWindow::~MainWindow
 * Destructeur de la classe MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}
