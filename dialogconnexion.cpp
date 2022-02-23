#include "dialogconnexion.h"
#include "ui_dialogconnexion.h"

/**
 * @brief DialogConnexion::DialogConnexion
 * Constructeur de la classe DialogConnexion qui crée la fenêtre de connexion de notre application
 * @param parent: QWidget*
 */
DialogConnexion::DialogConnexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnexion)
{
    ui->setupUi(this);
    numeroTypeEmploye = 0;
}

/**
 * @brief DialogConnexion::~DialogConnexion
 * Destructeur de la classe DialoConnexion
 */
DialogConnexion::~DialogConnexion()
{
    delete ui;
}

/**
 * @brief DialogConnexion::getVerifConnexion
 * Méthode publique de la classe DialogConnexion
 * @return int Entier qui renvoie le numeroTypeEmploye
 */
int DialogConnexion::getNumeroTypeEmploye()
{
    return numeroTypeEmploye;
}

/**
 * @brief DialogConnexion::on_pushButtonConnexion_clicked
 * Méthode privée
 */
void DialogConnexion::on_pushButtonConnexion_clicked()
{
    qDebug()<<"void DialogConnexion::on_pushButtonConnexion_clicked()";
    QString login = ui->lineEditLogin->text();
    QString mdp = ui->lineEditMotDePasse->text();
    //on vérifie si l'utilisateur existe
    QString reqUserExists = "SELECT COUNT(*) FROM Employe "
                           "WHERE loginEmploye = '"+login+"' "
                           "AND motDePasseEmploye = PASSWORD('"+mdp+"')";
    qDebug()<<reqUserExists;
    QSqlQuery resultUserExists(reqUserExists);
    resultUserExists.next();
    int nbEmploye = resultUserExists.value(0).toInt();
    if (nbEmploye){
        QString reqNumeroTypeEmploye = "SELECT numeroTypeEmploye FROM Employe "
                               "WHERE loginEmploye = '"+login+"' "
                               "AND motDePasseEmploye = PASSWORD('"+mdp+"')";
        qDebug()<<reqNumeroTypeEmploye;
        QSqlQuery resultNumeroTypeEmploye(reqNumeroTypeEmploye);

        resultNumeroTypeEmploye.next();
        numeroTypeEmploye = resultNumeroTypeEmploye.value(0).toInt();
        accept();
    } else {
        ui->labelConnexionError->setText("Le login ou le mot de passe est incorrect !");
    }
}
