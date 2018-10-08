#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <vector>
#include <QtGui>
#include <QtCore>
#include <QProgressBar>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QGridLayout>
#include <QLabel>
#include <QDesktopWidget>
#include <QMessageBox>
#include <vector>
#include <string>
#include <QSpinBox>
#include <iostream>

#include "espacedessin.h"

#include <QRadioButton>

namespace Ui {
class FenetrePrincipale;
}

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();

    /************ Scripts *************/

    void scriptXY();
    void scriptXYSuperieur();
    void scriptXYMatrice();
    void scriptXYNegatif();
    void scriptXY00();
    void scriptXYSupCarr();
    void scriptSupCarr();


private slots:
    void parcourrir();
    void executer();
    void changementTab(int i);
    void plusProcheVoisin();
    void plusProcheVoisinAleatoire();
    void plusProcheVoisinSystematique();
    void plusLointainVoisinSystematique();
    void opt2();
    void recuitSimule();
    void interchange();
    void nouvelleInstance();
    void HB();
    void HBReel();
    void aPropos();
private:
    Ui::FenetrePrincipale *ui;
    QGroupBox *grapheBox,*modificateur,*tableau,*FctObjBox;
    QPushButton *parcourrirBtn,*executerBtn, *opt2Btn;
    QRadioButton *aBtn,*xy,*xyNeg,*xyMatSup,*xyMat,*xy00,*xyMatSupCaree,*MatSupCarre;
    QLineEdit *parcourrirEdit;
    QTableView *table;
    QString fichier;
    QFile *matriceTxt;
    QStandardItemModel *tab;
    EspaceDessin *graphe;
    QSpinBox            *tailleGraphe, *aSpn, *bSpn;
    QLabel              *tailleGrapheLbl,*valFctObjLbl;
    QProgressBar        *pourcentage;
    QWidget     *widgOpt2;
    bool parc;
};

#endif // FENETREPRINCIPALE_H
