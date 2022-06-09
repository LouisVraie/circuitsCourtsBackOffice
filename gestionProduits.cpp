#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::initGestionProduits
 * Méthode publique de la classe MainWindow qui initialise les méthodes du tab 'Gestion Produits'
 */
void MainWindow::initGestionProduits()
{
    qDebug()<<"void MainWindow::initGestionProduits()";

    //on stretch les tableaux
    ui->tableWidget_gestionProduitsRayons->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_gestionProduitsProduits->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_gestionProduitsVarietes->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //taille des images en pixel
    imageSize = 125;

    //on clear les inputs
    clearGestionProduitsRayonInputs();
    clearGestionProduitsProduitsInputs();
    clearGestionProduitsVarietesInputs();

    //on désactive les boutons et on crée des connect
    ui->pushButton_gestionProduitsRayonsAjouter->setDisabled(true);
    ui->pushButton_gestionProduitsRayonsModifier->setDisabled(true);
    connect(ui->lineEdit_gestionProduitsRayonsLibelle,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditGestionProduitsRayons_textChanged()));
    connect(ui->lineEdit_gestionProduitsRayonsImage,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditGestionProduitsRayons_textChanged()));
    ui->pushButton_gestionProduitsProduitsAjouter->setDisabled(true);
    ui->pushButton_gestionProduitsProduitsModifier->setDisabled(true);
    connect(ui->comboBox_gestionProduitsProduitsRayon,SIGNAL(currentIndexChanged(int)),this,SLOT(on_allLineEditGestionProduitsProduits_textChanged()));
    connect(ui->lineEdit_gestionProduitsProduitsLibelle,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditGestionProduitsProduits_textChanged()));
    connect(ui->lineEdit_gestionProduitsProduitsImage,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditGestionProduitsProduits_textChanged()));
    ui->pushButton_gestionProduitsVarietesAjouter->setDisabled(true);
    ui->pushButton_gestionProduitsVarietesValider->setDisabled(true);
    ui->pushButton_gestionProduitsVarietesModifier->setDisabled(true);
    connect(ui->comboBox_gestionProduitsVarietesProduit,SIGNAL(currentIndexChanged(int)),this,SLOT(on_allLineEditGestionProduitsVarietes_textChanged()));
    connect(ui->lineEdit_gestionProduitsVarietesLibelle,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditGestionProduitsVarietes_textChanged()));
    connect(ui->lineEdit_gestionProduitsVarietesImage,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditGestionProduitsVarietes_textChanged()));


    //on affiche le contenu des tableaux
    afficherTableGestionProduitsRayons();
    afficherTableGestionProduitsProduits();
    afficherTableGestionProduitsVarietes();
}

/**
 * @brief MainWindow::afficherTableGestionProduitsRayons
 * Méthode publique de la classe MainWindow qui affiche les rayons des produits dans le tableau de l'onglet Rayons de Gestion Produits
 */
void MainWindow::afficherTableGestionProduitsRayons()
{
    qDebug()<<"void MainWindow::afficherTableGestionProduitsRayons()";
    ui->tableWidget_gestionProduitsRayons->setRowCount(0);
    //requête qui récupère les rayons
    QString reqSelectRayons = "SELECT r.numeroRayon, r.libelleRayon, r.imageRayon, r.dateInscriptionRayon FROM Rayon r";
    qDebug()<<reqSelectRayons;
    QSqlQuery resultSelectRayons(reqSelectRayons);

    while(resultSelectRayons.next()){
        //on récupère le numéro de la dernière ligne
        int row = ui->tableWidget_gestionProduitsRayons->rowCount();
        ui->tableWidget_gestionProduitsRayons->setRowCount(row+1);
        //on crée une instance de QLabel qui va contenir l'image du rayon
        QLabel *labelImage= new QLabel();
        labelImage->setPixmap(QPixmap(resultSelectRayons.value("imageRayon").toString()).scaled(imageSize,imageSize));
        labelImage->setScaledContents(true);
        //inserer les valeur dans le tableau
        ui->tableWidget_gestionProduitsRayons->setCellWidget(row,0, new QCheckBox());
        ui->tableWidget_gestionProduitsRayons->setItem(row,1, new QTableWidgetItem(resultSelectRayons.value("numeroRayon").toString()));
        ui->tableWidget_gestionProduitsRayons->setItem(row,2, new QTableWidgetItem(resultSelectRayons.value("dateInscriptionRayon").toString()));
        ui->tableWidget_gestionProduitsRayons->setCellWidget(row,3,labelImage);
        ui->tableWidget_gestionProduitsRayons->setItem(row,4, new QTableWidgetItem(resultSelectRayons.value("libelleRayon").toString()));
        ui->tableWidget_gestionProduitsRayons->setItem(row,5, new QTableWidgetItem(resultSelectRayons.value("imageRayon").toString()));

    }
    ui->tableWidget_gestionProduitsRayons->hideColumn(5);
    //ui->tableWidget_gestionProduitsRayons->resizeColumnsToContents();
    ui->tableWidget_gestionProduitsRayons->resizeRowsToContents();
    ui->tableWidget_gestionProduitsRayons->update();
}

/**
 * @brief MainWindow::afficherTableGestionProduitsProduits
 * Méthode publique de la classe MainWindow qui affiche les produits dans le tableau de l'onglet Produits de Gestion Produits
 */
void MainWindow::afficherTableGestionProduitsProduits()
{
    qDebug()<<"void MainWindow::afficherTableGestionProduitsProduits()";
    ui->tableWidget_gestionProduitsProduits->setRowCount(0);
    //requête qui récupère les produits
    QString reqSelectProduits = "SELECT p.numeroProduit, p.libelleProduit, p.imageProduit, p.dateInscriptionProduit, r.libelleRayon "
                                "FROM Produit p "
                                "INNER JOIN Rayon r ON r.numeroRayon = p.numeroRayon "
                                "ORDER BY p.numeroProduit ASC";
    qDebug()<<reqSelectProduits;
    QSqlQuery resultSelectProduits(reqSelectProduits);

    while(resultSelectProduits.next()){
        //on récupère le numéro de la dernière ligne
        int row = ui->tableWidget_gestionProduitsProduits->rowCount();
        ui->tableWidget_gestionProduitsProduits->setRowCount(row+1);
        //on crée une instance de QLabel qui va contenir l'image du produit
        QLabel *labelImage= new QLabel();
        labelImage->setPixmap(QPixmap(resultSelectProduits.value("imageProduit").toString()).scaled(imageSize,imageSize));
        labelImage->setScaledContents(true);
        //inserer les valeur dans le tableau
        ui->tableWidget_gestionProduitsProduits->setCellWidget(row,0, new QCheckBox());
        ui->tableWidget_gestionProduitsProduits->setItem(row,1, new QTableWidgetItem(resultSelectProduits.value("numeroProduit").toString()));
        ui->tableWidget_gestionProduitsProduits->setItem(row,2, new QTableWidgetItem(resultSelectProduits.value("dateInscriptionProduit").toString()));
        ui->tableWidget_gestionProduitsProduits->setCellWidget(row,3,labelImage);
        ui->tableWidget_gestionProduitsProduits->setItem(row,4, new QTableWidgetItem(resultSelectProduits.value("libelleRayon").toString()));
        ui->tableWidget_gestionProduitsProduits->setItem(row,5, new QTableWidgetItem(resultSelectProduits.value("libelleProduit").toString()));
        ui->tableWidget_gestionProduitsProduits->setItem(row,6, new QTableWidgetItem(resultSelectProduits.value("imageProduit").toString()));
    }
    ui->tableWidget_gestionProduitsProduits->hideColumn(6);
    //ui->tableWidget_gestionProduitsProduits->resizeColumnsToContents();
    ui->tableWidget_gestionProduitsProduits->resizeRowsToContents();
    ui->tableWidget_gestionProduitsProduits->update();
}

/**
 * @brief MainWindow::afficherTableGestionProduitsVarietes
 * Méthode publique de la classe MainWindow qui affiche les variétés dans le tableau de l'onglet Variétés de Gestion Produits
 */
void MainWindow::afficherTableGestionProduitsVarietes()
{
    qDebug()<<"void MainWindow::afficherTableGestionProduitsVarietes()";
    ui->tableWidget_gestionProduitsVarietes->setRowCount(0);
    //requête qui récupère les variétés
    QString reqSelectVarietes = "SELECT v.numeroVariete, v.libelleVariete, v.imageVariete, v.dateInscriptionVariete, p.libelleProduit, "
                                "v.estValide FROM Variete v "
                                "INNER JOIN Produit p ON p.numeroProduit = v.numeroProduit "
                                "ORDER BY v.numeroVariete ASC";
    qDebug()<<reqSelectVarietes;
    QSqlQuery resultSelectVarietes(reqSelectVarietes);

    while(resultSelectVarietes.next()){
        //on récupère le numéro de la dernière ligne
        int row = ui->tableWidget_gestionProduitsVarietes->rowCount();
        ui->tableWidget_gestionProduitsVarietes->setRowCount(row+1);
        //on crée une instance de QLabel qui va contenir l'image de la variété
        QLabel *labelImage= new QLabel();
        labelImage->setPixmap(QPixmap(resultSelectVarietes.value("imageVariete").toString()).scaled(imageSize,imageSize));
        labelImage->setScaledContents(true);
        //inserer les valeur dans le tableau
        ui->tableWidget_gestionProduitsVarietes->setCellWidget(row,0, new QCheckBox());
        ui->tableWidget_gestionProduitsVarietes->setItem(row,1, new QTableWidgetItem(resultSelectVarietes.value("numeroVariete").toString()));
        ui->tableWidget_gestionProduitsVarietes->setItem(row,2, new QTableWidgetItem(resultSelectVarietes.value("dateInscriptionVariete").toString()));
        ui->tableWidget_gestionProduitsVarietes->setCellWidget(row,3,labelImage);
        ui->tableWidget_gestionProduitsVarietes->setItem(row,4, new QTableWidgetItem(resultSelectVarietes.value("libelleProduit").toString()));
        ui->tableWidget_gestionProduitsVarietes->setItem(row,5, new QTableWidgetItem(resultSelectVarietes.value("libelleVariete").toString()));
        ui->tableWidget_gestionProduitsVarietes->setItem(row,6, new QTableWidgetItem(resultSelectVarietes.value("imageVariete").toString()));
        //si la variété est validée
        if(resultSelectVarietes.value("estValide").toBool()){
            setTableGestionProduitsVarietesEstValideColor(row,"green");
        } else {
            setTableGestionProduitsVarietesEstValideColor(row,"red");
        }
    }
    ui->tableWidget_gestionProduitsVarietes->hideColumn(6);
    //ui->tableWidget_gestionProduitsVarietes->resizeColumnsToContents();
    ui->tableWidget_gestionProduitsVarietes->resizeRowsToContents();
    ui->tableWidget_gestionProduitsVarietes->update();
}

/**
 * @brief MainWindow::setTableGestionProduitsVarietesEstValideColor
 * Méthode publique de la classe MainWindow qui change la couleur du QTableWidgetItem de la colonne EstActive de tableWidget_gestionProduitsVarietes
 * @param row: int La ligne du tableau
 * @param backgroundColor: QString La couleur de fond
 */
void MainWindow::setTableGestionProduitsVarietesEstValideColor(int row, QString backgroundColor)
{
    qDebug()<<"void MainWindow::setTableGestionProduitsVarietesEstValideColor(int row, QString backgroundColor)";
    qDebug()<<row<<backgroundColor;
    ui->tableWidget_gestionProduitsVarietes->item(row,1)->setBackgroundColor(backgroundColor);
}

/**
 * @brief MainWindow::clearGestionProduitsRayonInputs
 * Méthode publique de la classe MainWindow qui efface tous les inputs de l'onglet Rayons de Gestion Produits
 */
void MainWindow::clearGestionProduitsRayonInputs()
{
    qDebug()<<"void MainWindow::clearGestionProduitsRayonInputs()";
    ui->lineEdit_gestionProduitsRayonsLibelle->clear();
    ui->lineEdit_gestionProduitsRayonsImage->clear();
}

/**
 * @brief MainWindow::on_pushButton_gestionProduitsRayonsImage_clicked()
 * Méthode private slots de la classe MainWindow qui upload une image dans l'onglet Rayons de Gestion Produits
 */
void MainWindow::on_pushButton_gestionProduitsRayonsImage_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_gestionProduitsRayonsImage_clicked()";
    QFileDialog filename;
    filename.setFileMode(QFileDialog::ExistingFile);
    ui->lineEdit_gestionProduitsRayonsImage->setText(filename.getOpenFileName(this,tr("Choisir une image de rayon"), "", tr("Image (*.png *.jpg *.jpeg)")));
}

/**
 * @brief MainWindow::on_allLineEditGestionProduitsRayons_textChanged
 * Méthode private slots de la classe MainWindow qui active ou non les boutons de l'onglet Rayons de l'onglet Gestion Produits
 */
void MainWindow::on_allLineEditGestionProduitsRayons_textChanged()
{
    qDebug()<<"void MainWindow::on_allLineEditGestionProduitsRayons_textChanged()";
    bool libelleRayon, imageRayon;
    libelleRayon = ui->lineEdit_gestionProduitsRayonsLibelle->text().size() >= libelleMinimumSize;
    imageRayon = ui->lineEdit_gestionProduitsRayonsImage->text().size() >= imagePathMinimumSize;
    //si les champs sont remplis
    if(libelleRayon && imageRayon){
        //on active le bouton ajouter
        ui->pushButton_gestionProduitsRayonsAjouter->setEnabled(true);
    }else {
        //on désactive le bouton ajouter
        ui->pushButton_gestionProduitsRayonsAjouter->setEnabled(false);
    }

    //si une ligne est sélectionnée
    if(!ui->tableWidget_gestionProduitsRayons->selectedItems().empty()){
        if(libelleRayon && imageRayon){
            //on active le bouton modifier
            ui->pushButton_gestionProduitsRayonsModifier->setEnabled(true);
        }else {
            //on désactive le bouton modifier
            ui->pushButton_gestionProduitsRayonsModifier->setEnabled(false);
        }
    }
}

/**
 * @brief MainWindow::on_pushButton_gestionProduitsRayonsAjouter_clicked
 * Méthode private slots de la classe MainWindow qui ajoute un rayon dans l'onglet Rayons de l'onglet Gestion Produits
 */
void MainWindow::on_pushButton_gestionProduitsRayonsAjouter_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_gestionProduitsRayonsAjouter_clicked()";
    QString numeroRayon, libelleRayon, imageRayon, dateRayon;
    numeroRayon = setNextId("numeroRayon","Rayon");
    libelleRayon = escapeString(ui->lineEdit_gestionProduitsRayonsLibelle->text());
    imageRayon = escapeString(ui->lineEdit_gestionProduitsRayonsImage->text());
    dateRayon = QDate::currentDate().toString("yyyy-MM-dd");
    //si le libelle n'existe pas
    if(verifDoublon("Rayon","libelleRayon",libelleRayon) == 0){
        QString reqInsertRayon = "INSERT INTO Rayon (numeroRayon,libelleRayon,imageRayon,dateInscriptionRayon) VALUES "
                                 "("+numeroRayon+",'"+libelleRayon+"','"+imageRayon+"','"+dateRayon+"')";
        qDebug()<<reqInsertRayon;
        QSqlQuery resultInsertRayon(reqInsertRayon);
        //si l'inserion a fonctionné
        if(resultInsertRayon.numRowsAffected() != -1){
            ui->statusBar->showMessage(libelleRayon+" a été ajouté à la liste des rayons !",5000);
            afficherTableGestionProduitsRayons();
            clearGestionProduitsRayonInputs();
            updateComboBoxGestionProduitsProduitsRayon();
        }else{
            ui->statusBar->showMessage("Erreur lors de l'insertion du rayon : "+libelleRayon+" !",5000);
        }
    }else{
        ui->statusBar->showMessage("Erreur, le rayon : "+libelleRayon+" existe déjà !",5000);
    }
}

/**
 * @brief MainWindow::on_tableWidget_gestionProduitsRayons_itemSelectionChanged
 * Méthode private slots de la classe MainWindow qui transmet les informations d'un rayon dans les inputs
 *  de l'onglet Rayons de l'onglet Gestion Produits lorsque la selection change
 */
void MainWindow::on_tableWidget_gestionProduitsRayons_itemSelectionChanged()
{
    qDebug()<<"void MainWindow::on_tableWidget_gestionProduitsRayons_itemSelectionChanged()";
    if(!ui->tableWidget_gestionProduitsRayons->selectedItems().empty()){
        //on récupère le numéro de la ligne
        rowGestionProduitsRayon = ui->tableWidget_gestionProduitsRayons->currentRow();
        //on active le bouton modifier
        ui->pushButton_gestionProduitsRayonsModifier->setEnabled(true);
        //on transmet les données du tableau dans les inputs
        ui->lineEdit_gestionProduitsRayonsLibelle->setText(ui->tableWidget_gestionProduitsRayons->item(rowGestionProduitsRayon,4)->text());
        ui->lineEdit_gestionProduitsRayonsImage->setText(ui->tableWidget_gestionProduitsRayons->item(rowGestionProduitsRayon,5)->text());
    }else{
        //on désactive le bouton modifier
        ui->pushButton_gestionProduitsRayonsModifier->setEnabled(false);
    }
}

/**
 * @brief MainWindow::on_pushButton_gestionProduitsRayonsModifier_clicked
 * Méthode private slots de la classe MainWindow qui modifie les informations d'un rayon dans l'onglet Rayons de l'onglet Gestion Produits
 */
void MainWindow::on_pushButton_gestionProduitsRayonsModifier_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_gestionProduitsRayonsModifier_clicked()";
    QString numeroRayon, libelleRayon, imageRayon;
    numeroRayon = ui->tableWidget_gestionProduitsRayons->item(rowGestionProduitsRayon,1)->text();
    libelleRayon = escapeString(ui->lineEdit_gestionProduitsRayonsLibelle->text());
    imageRayon = escapeString(ui->lineEdit_gestionProduitsRayonsImage->text());
    //si le rayon n'existe pas
    if(verifDoublon("Rayon","libelleRayon",libelleRayon) == 0 || imageRayon != ui->tableWidget_gestionProduitsRayons->item(rowGestionProduitsRayon,5)->text()){
        //requête qui update le rayon
        QString reqUpdateRayon = "UPDATE Rayon SET "
                                 "libelleRayon='"+libelleRayon+"',"
                                 "imageRayon='"+imageRayon+"' "
                                 "WHERE numeroRayon="+numeroRayon;
        qDebug()<<reqUpdateRayon;
        QSqlQuery resultUpdateRayon(reqUpdateRayon);
        //si la requête a fonctionné
        if(resultUpdateRayon.numRowsAffected() != -1){
            afficherTableGestionProduitsRayons();
            clearGestionProduitsRayonInputs();
            updateComboBoxGestionProduitsProduitsRayon();
        } else {
            ui->statusBar->showMessage("Erreur lors de la modification du rayon : "+numeroRayon+" !",5000);
        }
    } else {
        ui->statusBar->showMessage("Erreur, le rayon : "+libelleRayon+" existe déjà !",5000);
    }
}

/**
 * @brief MainWindow::on_pushButton_gestionProduitsRayonsSupprimer_clicked
 * Méthode private slots de la classe MainWindow qui supprime les rayons sélectionnées dans l'onglet Rayons de l'onglet Gestion Produits
 */
void MainWindow::on_pushButton_gestionProduitsRayonsSupprimer_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_gestionProduitsRayonsSupprimer_clicked()";
    bool supprOk = false;
    int nbLigneSuppr = 0;
    for (int ligne = ui->tableWidget_gestionProduitsRayons->rowCount()-1;ligne>=0;ligne--) {
        //si la QCheckBox est cochée
        if(((QCheckBox*)ui->tableWidget_gestionProduitsRayons->cellWidget(ligne,0))->isChecked()){
            QString reqUpdateDeleteRayon = "DELETE FROM Rayon WHERE numeroRayon = "+ui->tableWidget_gestionProduitsRayons->item(ligne,1)->text();
            qDebug()<<reqUpdateDeleteRayon;
            QSqlQuery resultUpdateDeleteRayon(reqUpdateDeleteRayon);
            if(resultUpdateDeleteRayon.numRowsAffected() != -1){
                ui->tableWidget_gestionProduitsRayons->removeRow(ligne);
                nbLigneSuppr++;
                supprOk = true;
            } else {
                ui->statusBar->showMessage("Erreur lors de la suppression du/des rayon(s) !",5000);
                break;
            }
        }
    }
    if(supprOk){
        ui->statusBar->showMessage("Suppression de "+QString::number(nbLigneSuppr)+" rayons(s) !",5000);
        ui->tableWidget_gestionProduitsRayons->clearSelection();
        clearGestionProduitsRayonInputs();
        updateComboBoxGestionProduitsProduitsRayon();
    }
}

/**
 * @brief MainWindow::updateComboBoxGestionProduitsProduitsRayon
 * Méthode publique de la classe MainWindow qui met à jour la comboBox_gestionProduitsProduitsRayon dans l'onglet Produits de Gestion Produits
 */
void MainWindow::updateComboBoxGestionProduitsProduitsRayon()
{
    qDebug()<<"void MainWindow::updateComboBoxGestionProduitsProduitsRayon()";
    //on clear la comboBox
    ui->comboBox_gestionProduitsProduitsRayon->clear();
    QString reqSelectRayon = "SELECT numeroRayon,libelleRayon FROM Rayon ORDER BY libelleRayon ASC";
    qDebug()<<reqSelectRayon;
    QSqlQuery resultSelectRayon(reqSelectRayon);
    //si la requête a fonctionné
    if(resultSelectRayon.numRowsAffected() != -1){
        while(resultSelectRayon.next()){
            QString numeroRayon = resultSelectRayon.value("numeroRayon").toString();
            QString libelleRayon = resultSelectRayon.value("libelleRayon").toString();
            ui->comboBox_gestionProduitsProduitsRayon->addItem(libelleRayon,numeroRayon);
        }
    }
}

/**
 * @brief MainWindow::clearGestionProduitsProduitsInputs
 * Méthode publique de la classe MainWindow qui efface tous les inputs de l'onglet Produits de Gestion Produits
 */
void MainWindow::clearGestionProduitsProduitsInputs()
{
    qDebug()<<"void MainWindow::clearGestionProduitsProduitsInputs()";
    updateComboBoxGestionProduitsProduitsRayon();
    ui->lineEdit_gestionProduitsProduitsLibelle->clear();
    ui->lineEdit_gestionProduitsProduitsImage->clear();
}

/**
 * @brief MainWindow::on_pushButton_gestionProduitsProduitsImage_clicked
 * Méthode private slots de la classe MainWindow qui upload une image dans l'onglet Produits de Gestion Produits
 */
void MainWindow::on_pushButton_gestionProduitsProduitsImage_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_gestionProduitsProduitsImage_clicked()";
    QFileDialog filename;
    filename.setFileMode(QFileDialog::ExistingFile);
    ui->lineEdit_gestionProduitsProduitsImage->setText(filename.getOpenFileName(this,tr("Choisir une image de produit"), "", tr("Image (*.png *.jpg *.jpeg)")));
}

/**
 * @brief MainWindow::on_allLineEditGestionProduitsProduits_textChanged
 * Méthode private slots de la classe MainWindow qui active ou non les boutons de l'onglet Produits de l'onglet Gestion Produits
 */
void MainWindow::on_allLineEditGestionProduitsProduits_textChanged()
{
    qDebug()<<"void MainWindow::on_allLineEditGestionProduitsProduits_textChanged()";
    bool numeroRayon, libelleProduit, imageProduit;
    numeroRayon = ui->comboBox_gestionProduitsProduitsRayon->currentData().toInt() > 0;
    libelleProduit = ui->lineEdit_gestionProduitsProduitsLibelle->text().size() >= libelleMinimumSize;
    imageProduit = ui->lineEdit_gestionProduitsProduitsImage->text().size() >= imagePathMinimumSize;
    //si les champs sont remplis
    if(numeroRayon && libelleProduit && imageProduit){
        //on active le bouton ajouter
        ui->pushButton_gestionProduitsProduitsAjouter->setEnabled(true);
    }else {
        //on désactive le bouton ajouter
        ui->pushButton_gestionProduitsProduitsAjouter->setEnabled(false);
    }

    //si une ligne est sélectionnée
    if(!ui->tableWidget_gestionProduitsProduits->selectedItems().empty()){
        if(numeroRayon && libelleProduit && imageProduit){
            //on active le bouton modifier
            ui->pushButton_gestionProduitsProduitsModifier->setEnabled(true);
        }else {
            //on désactive le bouton modifier
            ui->pushButton_gestionProduitsProduitsModifier->setEnabled(false);
        }
    }
}

/**
 * @brief MainWindow::on_pushButton_gestionProduitsProduitsAjouter_clicked
 * Méthode private slots de la classe MainWindow qui ajoute un produit dans l'onglet Produits de l'onglet Gestion Produits
 */
void MainWindow::on_pushButton_gestionProduitsProduitsAjouter_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_gestionProduitsProduitsAjouter_clicked()";
    QString numeroProduit, libelleProduit, imageProduit, dateProduit, numeroRayon;
    numeroProduit = setNextId("numeroProduit","Produit");
    libelleProduit = escapeString(ui->lineEdit_gestionProduitsProduitsLibelle->text());
    imageProduit = escapeString(ui->lineEdit_gestionProduitsProduitsImage->text());
    dateProduit = QDate::currentDate().toString("yyyy-MM-dd");
    numeroRayon = ui->comboBox_gestionProduitsProduitsRayon->currentData().toString();
    //si le libelle n'existe pas
    if(verifDoublon("Produit","libelleProduit",libelleProduit) == 0){
        QString reqInsertProduit = "INSERT INTO Produit (numeroProduit,libelleProduit,imageProduit,dateInscriptionProduit,numeroRayon) VALUES "
                                 "("+numeroProduit+",'"+libelleProduit+"','"+imageProduit+"','"+dateProduit+"',"+numeroRayon+")";
        qDebug()<<reqInsertProduit;
        QSqlQuery resultInsertProduit(reqInsertProduit);
        //si l'inserion a fonctionné
        if(resultInsertProduit.numRowsAffected() != -1){
            ui->statusBar->showMessage(libelleProduit+" a été ajouté à la liste des produits !",5000);
            afficherTableGestionProduitsProduits();
            clearGestionProduitsProduitsInputs();
            updateComboBoxGestionProduitsVarietesProduit();
        }else{
            ui->statusBar->showMessage("Erreur lors de l'insertion du produit : "+libelleProduit+" !",5000);
        }
    }else{
        ui->statusBar->showMessage("Erreur, le produit : "+libelleProduit+" existe déjà !",5000);
    }
}

/**
 * @brief MainWindow::on_tableWidget_gestionProduitsProduits_itemSelectionChanged
 * Méthode private slots de la classe MainWindow qui transmet les informations d'un produit dans les inputs
 *  de l'onglet Produits de l'onglet Gestion Produits lorsque la selection change
 */
void MainWindow::on_tableWidget_gestionProduitsProduits_itemSelectionChanged()
{
    qDebug()<<"void MainWindow::on_tableWidget_gestionProduitsProduits_itemSelectionChanged()";
    if(!ui->tableWidget_gestionProduitsProduits->selectedItems().empty()){
        //on récupère le numéro de la ligne
        rowGestionProduitsProduit = ui->tableWidget_gestionProduitsProduits->currentRow();
        //on active le bouton modifier
        ui->pushButton_gestionProduitsProduitsModifier->setEnabled(true);
        //on transmet les données du tableau dans les inputs
        for (int i=0;i<ui->comboBox_gestionProduitsProduitsRayon->count();i++) {
            //si le rayon de la comboBox est le même que celui du tableau
            if(ui->comboBox_gestionProduitsProduitsRayon->itemText(i) == ui->tableWidget_gestionProduitsProduits->item(rowGestionProduitsProduit,4)->text()){
                //on sélectionne l'item correspodant dans la comboBox
                ui->comboBox_gestionProduitsProduitsRayon->setCurrentIndex(i);
                break;
            }
        }
        ui->lineEdit_gestionProduitsProduitsLibelle->setText(ui->tableWidget_gestionProduitsProduits->item(rowGestionProduitsProduit,5)->text());
        ui->lineEdit_gestionProduitsProduitsImage->setText(ui->tableWidget_gestionProduitsProduits->item(rowGestionProduitsProduit,6)->text());
    }else{
        //on désactive le bouton modifier
        ui->pushButton_gestionProduitsProduitsModifier->setEnabled(false);
    }
}

/**
 * @brief MainWindow::on_pushButton_gestionProduitsProduitsModifier_clicked
 * Méthode private slots de la classe MainWindow qui modifie les informations d'un produit dans l'onglet Produits de Gestion Produits
 */
void MainWindow::on_pushButton_gestionProduitsProduitsModifier_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_gestionProduitsProduitsModifier_clicked()";
    QString numeroProduit, numeroRayon, libelleRayon, libelleProduit, imageProduit;
    numeroProduit = ui->tableWidget_gestionProduitsProduits->item(rowGestionProduitsProduit,1)->text();
    numeroRayon = ui->comboBox_gestionProduitsProduitsRayon->currentData().toString();
    libelleRayon = ui->comboBox_gestionProduitsProduitsRayon->currentText();
    libelleProduit = escapeString(ui->lineEdit_gestionProduitsProduitsLibelle->text());
    imageProduit = escapeString(ui->lineEdit_gestionProduitsProduitsImage->text());
    //si le produit n'existe pas
    if(verifDoublon("Produit","libelleProduit",libelleProduit) == 0
       || imageProduit != ui->tableWidget_gestionProduitsProduits->item(rowGestionProduitsProduit,6)->text()
       || libelleRayon != ui->tableWidget_gestionProduitsProduits->item(rowGestionProduitsProduit,4)->text()){
        //requête qui update le produit
        QString reqUpdateProduit = "UPDATE Produit SET "
                                 "libelleProduit='"+libelleProduit+"',"
                                 "imageProduit='"+imageProduit+"', "
                                 "numeroRayon="+numeroRayon+" "
                                 "WHERE numeroProduit="+numeroProduit;
        qDebug()<<reqUpdateProduit;
        QSqlQuery resultUpdateProduit(reqUpdateProduit);
        //si la requête a fonctionné
        if(resultUpdateProduit.numRowsAffected() != -1){
            afficherTableGestionProduitsProduits();
            clearGestionProduitsProduitsInputs();
            updateComboBoxGestionProduitsVarietesProduit();
        } else {
            ui->statusBar->showMessage("Erreur lors de la modification du produit : "+numeroProduit+" !",5000);
        }
    } else {
        ui->statusBar->showMessage("Erreur, le produit : "+libelleProduit+" existe déjà !",5000);
    }
}

/**
 * @brief MainWindow::on_pushButton_gestionProduitsProduitsSupprimer_clicked
 * Méthode private slots de la classe MainWindow qui supprime les produits sélectionnées dans l'onglet Produits de Gestion Produits
 */
void MainWindow::on_pushButton_gestionProduitsProduitsSupprimer_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_gestionProduitsProduitsSupprimer_clicked()";
    bool supprOk = false;
    int nbLigneSuppr = 0;
    for (int ligne = ui->tableWidget_gestionProduitsProduits->rowCount()-1;ligne>=0;ligne--) {
        //si la QCheckBox est cochée
        if(((QCheckBox*)ui->tableWidget_gestionProduitsProduits->cellWidget(ligne,0))->isChecked()){
            QString reqUpdateDeleteProduit = "DELETE FROM Produit WHERE numeroProduit = "+ui->tableWidget_gestionProduitsProduits->item(ligne,1)->text();
            qDebug()<<reqUpdateDeleteProduit;
            QSqlQuery resultUpdateDeleteProduit(reqUpdateDeleteProduit);
            if(resultUpdateDeleteProduit.numRowsAffected() != -1){
                ui->tableWidget_gestionProduitsProduits->removeRow(ligne);
                nbLigneSuppr++;
                supprOk = true;
            } else {
                ui->statusBar->showMessage("Erreur lors de la suppression du/des produit(s) !",5000);
                break;
            }
        }
    }
    if(supprOk){
        ui->statusBar->showMessage("Suppression de "+QString::number(nbLigneSuppr)+" produit(s) !",5000);
        ui->tableWidget_gestionProduitsProduits->clearSelection();
        clearGestionProduitsProduitsInputs();
        updateComboBoxGestionProduitsVarietesProduit();
    }
}

/**
 * @brief MainWindow::updateComboBoxGestionProduitsVarietesProduit
 * Méthode publique de la classe MainWindow qui met à jour la comboBox_gestionProduitsVarietesProduit dans l'onglet Variétés de Gestion Produits
 */
void MainWindow::updateComboBoxGestionProduitsVarietesProduit()
{
    qDebug()<<"void MainWindow::updateComboBoxGestionProduitsVarietesProduit()";
    //on clear la comboBox
    ui->comboBox_gestionProduitsVarietesProduit->clear();
    QString reqSelectProduit = "SELECT numeroProduit,libelleProduit FROM Produit ORDER BY libelleProduit ASC";
    qDebug()<<reqSelectProduit;
    QSqlQuery resultSelectProduit(reqSelectProduit);
    //si la requête a fonctionné
    if(resultSelectProduit.numRowsAffected() != -1){
        while(resultSelectProduit.next()){
            QString numeroProduit = resultSelectProduit.value("numeroProduit").toString();
            QString libelleProduit = resultSelectProduit.value("libelleProduit").toString();
            ui->comboBox_gestionProduitsVarietesProduit->addItem(libelleProduit,numeroProduit);
        }
    }
}

/**
 * @brief MainWindow::clearGestionProduitsVarietesInputs
 * Méthode publique de la classe MainWindow qui efface tous les inputs de l'onglet Variétés de Gestion Produits
 */
void MainWindow::clearGestionProduitsVarietesInputs()
{
    qDebug()<<"void MainWindow::clearGestionProduitsVarietesInputs()";
    updateComboBoxGestionProduitsVarietesProduit();
    ui->lineEdit_gestionProduitsVarietesLibelle->clear();
    ui->lineEdit_gestionProduitsVarietesImage->clear();
}

/**
 * @brief MainWindow::on_pushButton_gestionProduitsVarietesImage_clicked
 * Méthode private slots de la classe MainWindow qui upload une image dans l'onglet Variétés de Gestion Produits
 */
void MainWindow::on_pushButton_gestionProduitsVarietesImage_clicked()
{
        qDebug()<<"void MainWindow::on_pushButton_gestionProduitsVarietesImage_clicked()";
        QFileDialog filename;
        filename.setFileMode(QFileDialog::ExistingFile);
        ui->lineEdit_gestionProduitsVarietesImage->setText(filename.getOpenFileName(this,tr("Choisir une image d'une variété"), "", tr("Image (*.png *.jpg *.jpeg)")));
}

/**
 * @brief MainWindow::on_allLineEditGestionProduitsProduits_textChanged
 * Méthode private slots de la classe MainWindow qui active ou non les boutons de l'onglet Variétés de Gestion Produits
 */
void MainWindow::on_allLineEditGestionProduitsVarietes_textChanged()
{
    qDebug()<<"void MainWindow::on_allLineEditGestionProduitsVarietes_textChanged()";
    bool numeroProduit, libelleVariete, imageVariete;
    numeroProduit = ui->comboBox_gestionProduitsVarietesProduit->currentData().toInt() > 0;
    libelleVariete = ui->lineEdit_gestionProduitsVarietesLibelle->text().size() >= libelleMinimumSize;
    imageVariete = ui->lineEdit_gestionProduitsVarietesImage->text().size() >= imagePathMinimumSize;
    //si les champs sont remplis
    if(numeroProduit && libelleVariete && imageVariete){
        //on active le bouton ajouter
        ui->pushButton_gestionProduitsVarietesAjouter->setEnabled(true);
    }else {
        //on désactive le bouton ajouter
        ui->pushButton_gestionProduitsVarietesAjouter->setEnabled(false);
    }

    //si une ligne est sélectionnée
    if(!ui->tableWidget_gestionProduitsVarietes->selectedItems().empty()){
        if(numeroProduit && libelleVariete && imageVariete){
            //on active les boutons valider et modifier
            ui->pushButton_gestionProduitsVarietesValider->setEnabled(true);
            ui->pushButton_gestionProduitsVarietesModifier->setEnabled(true);
        }else {
            //on désactive les boutons valider et modifier
            ui->pushButton_gestionProduitsVarietesValider->setEnabled(false);
            ui->pushButton_gestionProduitsVarietesModifier->setEnabled(false);
        }
    }
}

/**
 * @brief MainWindow::on_pushButton_gestionProduitsVarietesAjouter_clicked
 * Méthode private slots de la classe MainWindow qui ajoute une variété dans l'onglet Variétés de Gestion Produits
 */
void MainWindow::on_pushButton_gestionProduitsVarietesAjouter_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_gestionProduitsVarietesAjouter_clicked()";
    QString numeroVariete, libelleVariete, imageVariete, dateVariete, numeroProduit;
    numeroVariete = setNextId("numeroVariete","Variete");
    libelleVariete = escapeString(ui->lineEdit_gestionProduitsVarietesLibelle->text());
    imageVariete = escapeString(ui->lineEdit_gestionProduitsVarietesImage->text());
    dateVariete = QDate::currentDate().toString("yyyy-MM-dd");
    numeroProduit = ui->comboBox_gestionProduitsVarietesProduit->currentData().toString();
    //si le libelle n'existe pas
    if(verifDoublon("Variete","libelleVariete",libelleVariete) == 0){
        QString reqInsertVariete = "INSERT INTO Variete (numeroVariete,libelleVariete,imageVariete,dateInscriptionVariete,numeroProduit) VALUES "
                                 "("+numeroVariete+",'"+libelleVariete+"','"+imageVariete+"','"+dateVariete+"',"+numeroProduit+")";
        qDebug()<<reqInsertVariete;
        QSqlQuery resultInsertVariete(reqInsertVariete);
        //si l'inserion a fonctionné
        if(resultInsertVariete.numRowsAffected() != -1){
            ui->statusBar->showMessage(libelleVariete+" a été ajouté à la liste des variétés !",5000);
            afficherTableGestionProduitsVarietes();
            clearGestionProduitsVarietesInputs();
        }else{
            ui->statusBar->showMessage("Erreur lors de l'insertion de la variété : "+libelleVariete+" !",5000);
        }
    }else{
        ui->statusBar->showMessage("Erreur, la variété : "+libelleVariete+" existe déjà !",5000);
    }
}

/**
 * @brief MainWindow::on_tableWidget_gestionProduitsVarietes_itemSelectionChanged
 * Méthode private slots de la classe MainWindow qui transmet les informations d'une variété dans les inputs
 *  de l'onglet Variétés de Gestion Produits lorsque la selection change
 */
void MainWindow::on_tableWidget_gestionProduitsVarietes_itemSelectionChanged()
{
    qDebug()<<"void MainWindow::on_tableWidget_gestionProduitsVarietes_itemSelectionChanged()";
    if(!ui->tableWidget_gestionProduitsVarietes->selectedItems().empty()){
        //on récupère le numéro de la ligne
        rowGestionProduitsVariete = ui->tableWidget_gestionProduitsVarietes->currentRow();
        //on active les boutons valider et modifier
        ui->pushButton_gestionProduitsVarietesValider->setEnabled(true);
        ui->pushButton_gestionProduitsVarietesModifier->setEnabled(true);
        //on transmet les données du tableau dans les inputs
        for (int i=0;i<ui->comboBox_gestionProduitsVarietesProduit->count();i++) {
            //si le produit de la comboBox est le même que celui du tableau
            if(ui->comboBox_gestionProduitsVarietesProduit->itemText(i) == ui->tableWidget_gestionProduitsVarietes->item(rowGestionProduitsVariete,4)->text()){
                //on sélectionne l'item correspodant dans la comboBox
                ui->comboBox_gestionProduitsVarietesProduit->setCurrentIndex(i);
                break;
            }
        }
        ui->lineEdit_gestionProduitsVarietesLibelle->setText(ui->tableWidget_gestionProduitsVarietes->item(rowGestionProduitsVariete,5)->text());
        ui->lineEdit_gestionProduitsVarietesImage->setText(ui->tableWidget_gestionProduitsVarietes->item(rowGestionProduitsVariete,6)->text());
    }else{
        //on désactive les boutons valider et modifier
        ui->pushButton_gestionProduitsVarietesValider->setEnabled(false);
        ui->pushButton_gestionProduitsVarietesModifier->setEnabled(false);
    }
}

/**
 * @brief MainWindow::on_pushButton_gestionProduitsVarietesModifier_clicked
 * Méthode private slots de la classe MainWindow qui modifie les informations d'une variété dans l'onglet Variétés de Gestion Produits
 */
void MainWindow::on_pushButton_gestionProduitsVarietesModifier_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_gestionProduitsVarietesModifier_clicked()";
    QString numeroVariete, numeroProduit, libelleVariete, libelleProduit, imageVariete;
    numeroVariete = ui->tableWidget_gestionProduitsVarietes->item(rowGestionProduitsVariete,1)->text();
    numeroProduit = ui->comboBox_gestionProduitsVarietesProduit->currentData().toString();
    libelleProduit = ui->comboBox_gestionProduitsVarietesProduit->currentText();
    libelleVariete = escapeString(ui->lineEdit_gestionProduitsVarietesLibelle->text());
    imageVariete = escapeString(ui->lineEdit_gestionProduitsVarietesImage->text());
    //si la variété n'existe pas
    if(verifDoublon("Variete","libelleVariete",libelleVariete) == 0
       || imageVariete != ui->tableWidget_gestionProduitsVarietes->item(rowGestionProduitsVariete,6)->text()
       || libelleProduit != ui->tableWidget_gestionProduitsVarietes->item(rowGestionProduitsVariete,4)->text()){
        //requête qui update la variété
        QString reqUpdateVariete = "UPDATE Variete SET "
                                 "libelleVariete='"+libelleVariete+"',"
                                 "imageVariete='"+imageVariete+"', "
                                 "numeroProduit="+numeroProduit+" "
                                 "WHERE numeroVariete="+numeroVariete;
        qDebug()<<reqUpdateVariete;
        QSqlQuery resultUpdateVariete(reqUpdateVariete);
        //si la requête a fonctionné
        if(resultUpdateVariete.numRowsAffected() != -1){
            afficherTableGestionProduitsVarietes();
            clearGestionProduitsVarietesInputs();
        } else {
            ui->statusBar->showMessage("Erreur lors de la modification de la variété : "+numeroVariete+" !",5000);
        }
    } else {
        ui->statusBar->showMessage("Erreur, la variété : "+libelleVariete+" existe déjà !",5000);
    }
}

/**
 * @brief MainWindow::on_pushButton_gestionProduitsVarietesSupprimer_clicked
 * Méthode private slots de la classe MainWindow qui supprime les variétés sélectionnées dans l'onglet Variétés de Gestion Produits
 */
void MainWindow::on_pushButton_gestionProduitsVarietesSupprimer_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_gestionProduitsVarietesSupprimer_clicked()";
    bool supprOk = false;
    int nbLigneSuppr = 0;
    for (int ligne = ui->tableWidget_gestionProduitsVarietes->rowCount()-1;ligne>=0;ligne--) {
        //si la QCheckBox est cochée
        if(((QCheckBox*)ui->tableWidget_gestionProduitsVarietes->cellWidget(ligne,0))->isChecked()){
            QString reqUpdateDeleteVariete = "DELETE FROM Variete WHERE numeroVariete = "+ui->tableWidget_gestionProduitsVarietes->item(ligne,1)->text();
            qDebug()<<reqUpdateDeleteVariete;
            QSqlQuery resultUpdateDeleteVariete(reqUpdateDeleteVariete);
            if(resultUpdateDeleteVariete.numRowsAffected() != -1){
                ui->tableWidget_gestionProduitsVarietes->removeRow(ligne);
                nbLigneSuppr++;
                supprOk = true;
            } else {
                ui->statusBar->showMessage("Erreur lors de la suppression de la/des variété(s) !",5000);
                break;
            }
        }
    }
    if(supprOk){
        ui->statusBar->showMessage("Suppression de "+QString::number(nbLigneSuppr)+" variété(s) !",5000);
        ui->tableWidget_gestionProduitsVarietes->clearSelection();
        clearGestionProduitsVarietesInputs();
    }
}

/**
 * @brief MainWindow::on_pushButton_gestionProduitsVarietesValider_clicked
 * Méthode private slots de la classe MainWindow qui permet de valider les variétés lorsqu'on clic sur le bouton Valider de l'onglet Variétés de Gestion Produits
 */
void MainWindow::on_pushButton_gestionProduitsVarietesValider_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_gestionProduitsVarietesValider_clicked()";
    QString numeroVariete = ui->tableWidget_gestionProduitsVarietes->item(rowGestionProduitsVariete,1)->text();
    QString reqValiderVariete = "UPDATE Variete SET estValide = TRUE WHERE numeroVariete ="+numeroVariete;
    qDebug()<<reqValiderVariete;
    QSqlQuery resultValiderVariete(reqValiderVariete);
    //si la requête a fonctionné
    if(resultValiderVariete.numRowsAffected() != -1){
        //on change la couleur de validité
        setTableGestionProduitsVarietesEstValideColor(rowGestionProduitsVariete,"green");
        ui->tableWidget_gestionProduitsVarietes->clearSelection();
        ui->statusBar->showMessage("La variété n°"+numeroVariete+" a été validé !",5000);
    } else {
        ui->statusBar->showMessage("Erreur lors de la validation de la variété n°"+numeroVariete+" !",5000);
    }
}
