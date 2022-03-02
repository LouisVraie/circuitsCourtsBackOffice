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
    numeroEmploye = "";
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
 * @brief DialogConnexion::getNumeroEmploye
 * Méthode publique de la classe DialogConnexion
 * @return QString Chaîne de caractère qui renvoie le numeroEmploye
 */
QString DialogConnexion::getNumeroEmploye()
{
    return numeroEmploye;
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
        QString reqNumeroEmploye = "SELECT numeroEmploye FROM Employe "
                               "WHERE loginEmploye = '"+login+"' "
                               "AND motDePasseEmploye = PASSWORD('"+mdp+"')";
        qDebug()<<reqNumeroEmploye;
        QSqlQuery resultNumeroEmploye(reqNumeroEmploye);

        resultNumeroEmploye.next();
        numeroEmploye = resultNumeroEmploye.value(0).toString();
        accept();
    } else {
        ui->labelConnexionError->setText("Le login ou le mot de passe est incorrect !");
    }
}
