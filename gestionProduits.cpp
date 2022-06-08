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
    ui->tableWidget_gestionProduitsProduits->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //taille des images en pixel
    imageSize = 125;

    //on clear les inputs
    clearGestionProduitsRayonInputs();

    //on désactive les boutons et on crée des connect
    ui->pushButton_gestionProduitsRayonsAjouter->setDisabled(true);
    ui->pushButton_gestionProduitsRayonsModifier->setDisabled(true);
    connect(ui->lineEdit_gestionProduitsRayonsLibelle,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditGestionProduitsRayons_textChanged()));
    connect(ui->lineEdit_gestionProduitsRayonsImage,SIGNAL(textChanged(QString)),this,SLOT(on_allLineEditGestionProduitsRayons_textChanged()));

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
    ui->tableWidget_gestionProduitsRayons->resizeColumnsToContents();
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
    }
    ui->tableWidget_gestionProduitsProduits->resizeColumnsToContents();
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
        //si la variété est validée
        if(resultSelectVarietes.value("estValide").toBool()){
            setTableGestionProduitsVarietesEstValideColor(row,"green");
        } else {
            setTableGestionProduitsVarietesEstValideColor(row,"red");
        }
    }
    ui->tableWidget_gestionProduitsVarietes->resizeColumnsToContents();
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
 * Méthode publique de la classe MainWindow qui efface tous les inputs de l'onglet Rayons de GestionProduits
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
    qDebug()<<"void MainWindow::uploadImageRayonsGestionProduits()";
    QFileDialog filename;
    filename.setFileMode(QFileDialog::ExistingFile);
    ui->lineEdit_gestionProduitsRayonsImage->setText(filename.getOpenFileName(this,tr("Choisir une image"), "", tr("Image (*.png *.jpg *.jpeg)")));
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
}
