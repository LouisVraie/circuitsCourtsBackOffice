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
    verifConnexion = false;
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
 * @return bool Booléen qui renvoie si la connexion est bonne
 */
bool DialogConnexion::getVerifConnexion()
{
    return verifConnexion;
}

/**
 * @brief DialogConnexion::on_pushButtonConnexion_clicked
 */
void DialogConnexion::on_pushButtonConnexion_clicked()
{
    qDebug()<<"void DialogConnexion::on_pushButtonConnexion_clicked()";
    QString login = ui->lineEditLogin->text();
    QString mdp = ui->lineEditMotDePasse->text();
    QString reqConnexion = "SELECT COUNT(*) FROM Employe "
                           "WHERE loginEmploye = '"+login+"' "
                           "AND motDePasseEmploye = PASSWORD('"+mdp+"')";
    qDebug()<<reqConnexion;
    QSqlQuery resultConnexion(reqConnexion);

    resultConnexion.next();
    int nbEmploye = resultConnexion.value(0).toInt();

    //si l'employé existe
    if(nbEmploye){
        verifConnexion = true;
    }
}
