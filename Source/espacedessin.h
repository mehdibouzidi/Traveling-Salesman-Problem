#ifndef ESPACEDESSIN_H
#define ESPACEDESSIN_H

#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QDialog>
#include <QProgressBar>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <map>

#include "sommet.h"

class EspaceDessin : public QWidget
{
    Q_OBJECT
public:
    explicit EspaceDessin(QWidget *parent = 0);
             EspaceDessin(QWidget *parent ,std::vector<std::vector<double> > mat,std::vector<double> coor, double max,int may);

             void paintEvent(QPaintEvent *e);
             int aleaInt();
             double aleatoireD();
             bool existX(int x);
             bool existY(int y);
             int aleatoire(int b);
             void suppElt(std::vector<int> &vect,int i);
             std::vector<std::vector<double> > getCouts()const;
             std::vector<int>   getSolution()const;
             double valeurFctObject(std::vector<int> const& sol);
             int minimum(std::vector<int> vect,int i);
            /************** Heuristiques ************/
            double plusProcheVoisin();
            double plusProcheVoisinAleatoire();
            double plusProcheVoisinSystematique();

            double plusLointainVoisinSystematique();

            double HB();
            double HBReel();
            /************** Transformation ************/
            std::vector<int> opt2(std::vector<int>  sol);
            double opt2Aleatoire();
            double opt2Inser(int x, int y);
            /*************** Métaheuristiques *********/
            double recuitSimule();

            /************** Hybridations ***************/
signals:

public slots:

private:
    int x,y,nbClick;
    QPoint *pt1,*pt2;
    bool B,solt;
    std::vector<std::vector<double> > matriceCouts;
    std::vector<Sommet*>  ensembleSommets;
    std::vector<int> solution;
};

#endif // ESPACEDESSIN_H
