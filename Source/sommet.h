#ifndef SOMMET_H
#define SOMMET_H

#include<QtGui>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPaintEvent>
#include <QtCore>
#include <QVBoxLayout>
#include <vector>
#include <QGraphicsItem>

class Sommet : public QWidget
{
    Q_OBJECT
public:
    explicit Sommet(QWidget *parent = 0);
    Sommet();
    Sommet(QWidget *parent,int nomm,double xx,double yy);
    /*Sommet(const Sommet &sommetACopier);
    Sommet &operator=(Sommet const& sommetACopier);*/

    ~Sommet();
    /******* Setters *******/
    void setNom(int n);
    void setX(double xx);
    void setY(double yy);
    void setB(bool b);
    void setCouleur(QString coul);

    /******* Guetters *******/
    int getNom()const;
    double getX()const;
    double getY()const;
    bool getB()const;
    QString getCouleur()const;

    QPainter *painter;

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);

signals:
void sommetClicke();

private:
int nom;
double x,y;
QLabel *no;
bool B;
QString couleur;

private slots:
    void clicke();
};

#endif // SOMMET_H
