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
    ui->lineEditLogin->setText("ADMIN");
    ui->lineEditMotDePasse->setText("XITgfUibs1456");
    numeroEmploye = "";
    nbTentativeConnexion = 0;
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
    QString login = ui->lineEditLogin->text().replace(";","").replace("'","''");
    QString mdp = ui->lineEditMotDePasse->text().replace(";","").replace("'","''");
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
        nbTentativeConnexion++;
        if(nbTentativeConnexion >= 3){
            reject();
        }
    }
}

/**
 * @brief DialogConnexion::quitConfirm()
 * Méthode publique de la classe DialogConnexion qui sert à afficher un message de confirmation pour quitter
 * @return Retourne un booléen vrai si l'utilisateur confirme, sinon renvoie faux
 */
bool DialogConnexion::quitConfirm()
{
    if(QMessageBox::warning(this,this->windowTitle(),"Voulez-vous vraiment quitter l'application ?", QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief DialogConnexion::closeEvent
 * Méthode publique de la classe DialogConnexion qui execute la méthode quitConfirm() quand l'utilisateur cherche à fermer la fenêtre
 * @param event Événement de fermeture
 */
void DialogConnexion::closeEvent(QCloseEvent *event)
{
    if(quitConfirm())
    {
        event->accept();
    }
    else {
        event->ignore();
    }
}

/**
 * @brief DialogConnexion::on_pushButtonQuitter_clicked
 * Méthode private slots de la classe DialogConnexion qui créer un événement de fermeture de fenêtre
 */
void DialogConnexion::on_pushButtonQuitter_clicked()
{
    close();
}
