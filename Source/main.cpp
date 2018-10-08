#include <QApplication>
#include <QtGui>
#include "fenetreprincipale.h"



int main(int argc,char *argv[])
{
    QApplication app(argc,argv);

    FenetrePrincipale fen;

    fen.show();

    return app.exec();
}

