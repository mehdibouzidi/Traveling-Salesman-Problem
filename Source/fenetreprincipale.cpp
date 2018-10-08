#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"

using namespace std;
FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    /*~~~~~~~~~~~~~ Boutons ~~~~~~~~~~~~~*/
   executerBtn=new QPushButton("Dessiner");
   executerBtn->setFixedSize(100,40);
   executerBtn->setIcon(QIcon("exec.png"));

   parcourrirBtn=new QPushButton("Parcourrir");
   parcourrirBtn->setFixedSize(100,40);
   parcourrirBtn->setIcon(QIcon("recherche.png"));

    opt2Btn = new QPushButton("Interchanger");
    opt2Btn->setIcon(QIcon("arrows3.png"));

    /*~~~~~~~~~~~~~ Radio Boutons ~~~~~~~~~~~~~*/
    QGridLayout *layOptions = new QGridLayout;
    xy = new QRadioButton("XY"); layOptions->addWidget(xy,0,0); xy->setToolTip(QString("L'instance contient les valeurs des coordonnés X et Y"));
    xyNeg = new QRadioButton("XY+Valeurs Négatives"); layOptions->addWidget(xyNeg,0,1); xyNeg->setToolTip(QString("L'instance contient des valeurs négatives des coordonnés X et Y"));
    xyMatSup = new QRadioButton("XY+Matrice Supérieure"); layOptions->addWidget(xyMatSup,1,1); xyMatSup->setToolTip(QString("De plus des valeurs des coordonés X et Y,\n l'instance contient la mtrice supérieure des coûts"));
    xy00 = new QRadioButton("XY+e00"); layOptions->addWidget(xy00,1,0); xy00->setToolTip(QString("L'instance contient des valeurs des coordonnés X et Y,\n sous la forme : 0.00000e+00"));
    xyMat = new QRadioButton("XY+Matrice"); layOptions->addWidget(xyMat,3,0); xyMat->setToolTip(QString("De plus des valeurs des coordonés X et Y,\n l'instance contient la mtrice des coûts"));
    xyMatSupCaree = new QRadioButton("XY+Matrice Supérieure Carrée"); layOptions->addWidget(xyMatSupCaree,2,0); xyMatSupCaree->setToolTip(QString("De plus des valeurs des coordonés X et Y,\n l'instance contient la mtrice supérieure des coûts sous une forme carrée"));
    MatSupCarre = new QRadioButton("Matrice Supérieure Carrée"); layOptions->addWidget(MatSupCarre,2,1); MatSupCarre->setToolTip(QString("L'instance ne contient que la matrice supérieure des coûts sous une forme carrée"));
    xy00->setEnabled(false);
    xyMatSupCaree->setEnabled(false);
    MatSupCarre->setEnabled(false);
    xyNeg->setEnabled(false);
    xy->setChecked(true);

   /*~~~~~~~~~~~~~ Editeurs de text ~~~~~~~~~~~~~*/
    parcourrirEdit=new QLineEdit;
    parcourrirEdit->setText(QString(""));
    parcourrirEdit->setReadOnly(true);
    parcourrirEdit->setFixedSize(500,30);

    tailleGraphe = new QSpinBox;
    tailleGraphe->setMinimum(1);
    tailleGraphe->setMaximum(10000);
   /*~~~~~~~~~~~~~ Tableaux ~~~~~~~~~~~~~*/
    table=new QTableView;
    table->setFixedHeight(450);
    tab=new QStandardItemModel;
     tab->setRowCount(1);
     tab->setColumnCount(1);
     table->setModel(tab);
   /*~~~~~~~~~~~~~ Les Groupes de Boites ~~~~~~~~~~~~~*/
      grapheBox=new QGroupBox;   modificateur=new QGroupBox;   tableau=new QGroupBox;
      grapheBox->setTitle("Carte"); modificateur->setTitle("Type de l'instance"); tableau->setTitle("Matrice des coûts");
      grapheBox->setFixedSize(800,800); modificateur->setFixedHeight(250);

   /*~~~~~~~~~~~~~ Textes ~~~~~~~~~~~~~*/
    tailleGrapheLbl=new QLabel("Le nombre de clients est ");

      /*~~~~~~~~~~~~~ Progression ~~~~~~~~~~~~~*/
     pourcentage  =   new QProgressBar;
     pourcentage->setFixedSize(350,20);
     pourcentage->setValue(0);
   /*~~~~~~~~~~~~~ Layouts ~~~~~~~~~~~~~*/
    QGridLayout *layoutGeneral=new QGridLayout;
    QGridLayout *layParcou=new QGridLayout;
    QGridLayout *layAdja=new QGridLayout;
    QHBoxLayout *layoutMan= new QHBoxLayout;
    QVBoxLayout *layModif = new QVBoxLayout;

     /*layModif->addWidget(pourcentage,0,Qt::AlignCenter);*/
    layModif->addLayout(layOptions);
     modificateur->setLayout(layModif);
   layAdja->addWidget(table,0,0,1,10);
   layParcou->addWidget(parcourrirEdit,0,0);
   layParcou->addWidget(parcourrirBtn,0,1); layParcou->addWidget(executerBtn,0,2); //executerBtn->setHidden(true);
    layoutMan->addWidget(tailleGrapheLbl);
    layoutMan->addWidget(tailleGraphe);
   // layoutMan->addWidget(symetrique);

   layAdja->addLayout(layoutMan,1,0,1,10,Qt::AlignCenter);
   layAdja->addLayout(layParcou,2,0,1,10,Qt::AlignCenter);
   tableau->setLayout(layAdja);

   layoutGeneral->addWidget(grapheBox,0,0,2,1);
   layoutGeneral->addWidget(modificateur,0,1,1,1);
   layoutGeneral->addWidget(tableau,1,1,1,1);
    ui->centralwidget->setLayout(layoutGeneral);

    parc=false;
    setGeometry((int)(QApplication::desktop()->width() - 400) / 2, (int)(QApplication::desktop()->height() - 500 - 50) / 2, 400, 500);

qsrand(0);
    /******** Connexions ***********/
    connect(tailleGraphe,SIGNAL(valueChanged(int)),this,SLOT(changementTab(int)));
    connect(parcourrirBtn,SIGNAL(clicked()),this,SLOT(parcourrir()));
    connect(executerBtn,SIGNAL(clicked()),this,SLOT(executer()));
    connect(ui->actionPlus_proche_voisin,SIGNAL(triggered()),this,SLOT(plusProcheVoisin()));
    connect(ui->actionPlus_Proche_Voisin_Al_atoire,SIGNAL(triggered()),this,SLOT(plusProcheVoisinAleatoire()));
    connect(ui->actionPlus_Proche_Voisin_Syt_matique,SIGNAL(triggered()),this,SLOT(plusProcheVoisinSystematique()));
    connect(ui->actionR_cuit_Simul,SIGNAL(triggered()),this,SLOT(recuitSimule()));
    connect(ui->action2_Opt,SIGNAL(triggered()),this,SLOT(opt2()));
    connect(ui->actionNouvelle_instance,SIGNAL(triggered()),this,SLOT(nouvelleInstance()));
    connect(ui->actionPlus_Lointain_Voisin_Syst_matique,SIGNAL(triggered()),this,SLOT(plusLointainVoisinSystematique()));
    connect(ui->actionHeure_de_Bouf,SIGNAL(triggered()),this,SLOT(HB()));
    connect(ui->actionHeure_de_Bouf_Yagouni_Mouhammed_Temps_R_el,SIGNAL(triggered()),this,SLOT(HBReel()));
    connect(ui->action_propos,SIGNAL(triggered()),this,SLOT(aPropos()));
    connect(opt2Btn,SIGNAL(clicked()),this,SLOT(interchange()));

    setWindowTitle("Problème du Voyageur de Commerce V1.0");
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

/************************ Scripts *************************/

void FenetrePrincipale::scriptXY()
{
    double maxX(-1),maxY(-1);
    std::vector<double> coordonees(tailleGraphe->value()*2,0);
        int n(tailleGraphe->value());
    QString ligne;
    std::vector<double> vect(tailleGraphe->value(),0);
    std::vector<std::vector<double> > matri;
    bool lesChiffres(false);
    for(int i=0;i<tailleGraphe->value();i++)
    {
        matri.push_back(vect);
    }
             QString mot("");

             matriceTxt=new QFile(fichier);
             if (!matriceTxt->open(QIODevice::ReadOnly | QIODevice::Text))
                    return;

             int j(0),k(0);
             while (!matriceTxt->atEnd())
             {
                 ligne = matriceTxt->readLine();

                 for(int i=0;i<ligne.size();i++)
                 {

                     while(ligne[i] != ' ' && i<ligne.size() )
                     {
                        mot.push_back(ligne[i]);
                        i++;
                     }

                     if(mot != "")
                     {
                        if(mot[0]!='1' && mot[0]!='2' && mot[0]!='3' && mot[0]!='4' && mot[0]!='5'
                                && mot[0]!='6' && mot[0]!='7' && mot[0]!='8' && mot[0]!='9' && mot[0]!='0') // Si le premier caractere du mot lu n'est pas un chiffre
                        {
                            i=ligne.size();// on saute la ligne
                        }
                        else // si le 1er caractère de la ligne est un chiffre
                        {
                            lesChiffres=true;
                            if(k==1)
                            {
                                coordonees[j]=mot.toDouble();
                                if(maxX<coordonees[j]){maxX=coordonees[j];}

                            }
                            else
                                if(k==2)
                                {
                                    coordonees[j+n]=mot.toDouble();
                                    if(maxY<coordonees[j+n]){maxY=coordonees[j+n];}
                                }

                        }
                            k++;
                     }
                     mot="";

                 }


                  if(lesChiffres){j++; }

                  k=0;

             }

             for(int l=0;l<tailleGraphe->value();l++)
             {
                 for(int m=l;m<tailleGraphe->value();m++)
                 {
                     matri[l][m]=sqrt(pow(coordonees[l]-coordonees[m],2)+pow(coordonees[l+n]-coordonees[m+n],2));
                    matri[m][l]=matri[l][m];

                    tab->setItem(l,m,new QStandardItem(QString::number( matri[l][m])));
                    tab->setItem(m,l,new QStandardItem(QString::number( matri[m][l])));


                 }

             }

             graphe=new EspaceDessin(grapheBox,matri,coordonees,maxX,maxY);
             graphe->setHidden(false);


}

/* --------------------------------------------------------- */

void FenetrePrincipale::scriptXYSuperieur()
{

    double maxX(-1),maxY(-1);
    std::vector<double> coordonees(tailleGraphe->value()*2,0);
        int n(tailleGraphe->value());
    QString ligne;
    std::vector<double> vect(tailleGraphe->value(),0);
    std::vector<std::vector<double> > matri;
    bool lesChiffres(false),type(false);
    for(int i=0;i<tailleGraphe->value();i++)
    {
        matri.push_back(vect);
    }
             QString mot("");

             matriceTxt=new QFile(fichier);
             if (!matriceTxt->open(QIODevice::ReadOnly | QIODevice::Text))
                    return;

             int j(0),k(0);
             while (!matriceTxt->atEnd())
             {
                 ligne = matriceTxt->readLine();

                 for(int i=0;i<ligne.size();i++)
                 {

                     while(ligne[i] != ' ' && i<ligne.size() )
                     {
                        mot.push_back(ligne[i]);
                        i++;
                     }

                     if(mot != "")
                     {
                        if(mot[0]!='1' && mot[0]!='2' && mot[0]!='3' && mot[0]!='4' && mot[0]!='5'
                                && mot[0]!='6' && mot[0]!='7' && mot[0]!='8' && mot[0]!='9' && mot[0]!='0') // Si le premier caractere du mot lu n'est pas un chiffre
                        {
                            i=ligne.size();// on saute la ligne
                        }
                        else // si le 1er caractère de la ligne est un chiffre
                        {
                            lesChiffres=true;
                            if(type)
                            {
                            if(k==1)
                            {
                                coordonees[j]=mot.toDouble();
                                if(maxX<coordonees[j]){maxX=coordonees[j];}

                            }
                            else
                                if(k==2)
                                {
                                    coordonees[j+n]=mot.toDouble();
                                    if(maxY<coordonees[j+n]){maxY=coordonees[j+n];}
                                }
                            }
                            else
                            {
                                if(k==j)
                                {
                                    matri[j][k]=0; matri[k][j]=0;
                                    tab->setItem(j,k,new QStandardItem(QString::number(0)));
                                    tab->setItem(k,j,new QStandardItem(QString::number(0)));
                                    if(k!=tailleGraphe->value())
                                    {
                                    matri[j][k+1]=mot.toDouble(); matri[k+1][j]=mot.toDouble();
                                    tab->setItem(j,k+1,new QStandardItem(mot));
                                    tab->setItem(k+1,j,new QStandardItem(mot));
                                    }
                                }
                                else
                                {
                                    matri[j][k+1]=mot.toDouble(); matri[k+1][j]=mot.toDouble();
                                    tab->setItem(j,k+1,new QStandardItem(mot));
                                    tab->setItem(k+1,j,new QStandardItem(mot));
                                }
                            }

                        }

                            k++;
                     }
                     mot="";

                 }


                  if(lesChiffres)
                  {

                      if(j==tailleGraphe->value()-1)
                      {
                          j=0;
                          type=true;
                      }
                      j++;
                  }
                if(type)k=0;
                else k=j;


             }

        tab->setItem(tailleGraphe->value()-1,tailleGraphe->value()-1,new QStandardItem(QString::number(0)));
             graphe=new EspaceDessin(grapheBox,matri,coordonees,maxX,maxY);
             graphe->setHidden(false);

}

void FenetrePrincipale::scriptXYMatrice()
{
    double maxX(-1),maxY(-1);
    std::vector<double> coordonees(tailleGraphe->value()*2,0);
        int n(tailleGraphe->value());
    QString ligne;
    std::vector<double> vect(tailleGraphe->value(),0);
    std::vector<std::vector<double> > matri;
    bool lesChiffres(false),type(false);
    for(int i=0;i<tailleGraphe->value();i++)
    {
        matri.push_back(vect);
    }
             QString mot("");

             matriceTxt=new QFile(fichier);
             if (!matriceTxt->open(QIODevice::ReadOnly | QIODevice::Text))
                    return;

             int j(0),k(0);
             while (!matriceTxt->atEnd())
             {
                 ligne = matriceTxt->readLine();

                 for(int i=0;i<ligne.size();i++)
                 {

                     while(ligne[i] != ' ' && i<ligne.size() )
                     {
                        mot.push_back(ligne[i]);
                        i++;
                     }

                     if(mot != "")
                     {
                        if(mot[0]!='1' && mot[0]!='2' && mot[0]!='3' && mot[0]!='4' && mot[0]!='5'
                                && mot[0]!='6' && mot[0]!='7' && mot[0]!='8' && mot[0]!='9' && mot[0]!='0') // Si le premier caractere du mot lu n'est pas un chiffre
                        {
                            i=ligne.size();// on saute la ligne
                        }
                        else // si le 1er caractère de la ligne est un chiffre
                        {
                            lesChiffres=true;
                            if(type)
                            {
                            if(k==1)
                            {
                                coordonees[j]=mot.toDouble();
                                if(maxX<coordonees[j]){maxX=coordonees[j];}

                            }
                            else
                                if(k==2)
                                {
                                    coordonees[j+n]=mot.toDouble();
                                    if(maxY<coordonees[j+n]){maxY=coordonees[j+n];}
                                }
                            }
                            else
                            {

                                    matri[j][k]=mot.toDouble();
                                    tab->setItem(j,k,new QStandardItem(mot));
                                   // cerr<<"j = "<<j<<" ,k = "<<k<<"\n";
                            }

                        }

                            k++;
                     }
                     mot="";

                 }


                  if(lesChiffres)
                  {

                      if(j==tailleGraphe->value()-1)
                      {
                          j=0;
                          type=true;
                      }
                      j++;
                  }
                k=0;



             }


             graphe=new EspaceDessin(grapheBox,matri,coordonees,maxX,maxY);
             graphe->setHidden(false);

}

/* --------------------------------------------------------- */

void FenetrePrincipale::scriptXYNegatif()
{

}

/* --------------------------------------------------------- */

void FenetrePrincipale::scriptXY00()
{

}

/* --------------------------------------------------------- */

void FenetrePrincipale::scriptXYSupCarr()
{

}

/* --------------------------------------------------------- */

void FenetrePrincipale::scriptSupCarr()
{

}

/***************************************************************/
void FenetrePrincipale::parcourrir()
{
    fichier=QFileDialog::getOpenFileName(this, "Ouvrir une instance du TSP",QString(),"Text (*.txt)");
    parcourrirEdit->setText(fichier);
    parc=true;
}


void FenetrePrincipale::executer()
{

    if(tab->item(0,0)==0 && !parc)
    {
        QMessageBox::warning(this,"Graphe Inexistant","Veuillez introduir la matrice des coûts en parcourant un fichier ou bien directement sur le tableau");
    }else
    {
        ui->actionNouvelle_instance->setEnabled(true);
    std::vector<double> vect,init;
    std::vector<std::vector<double> > matrice;
    if(!parc)
    {
        for(int i=0;i<tab->rowCount();i++)
        {
            for(int j=0;j<tab->columnCount();j++)
            {
                vect.push_back(tab->item(i,j)->text().toDouble());
            }
            matrice.push_back(vect);
            vect=init;
        }
        /*graphe=new EspaceDessin(grapheBox,matrice);
        graphe->setHidden(false);*/
    }
    else
    {

    if(xy->isChecked()) scriptXY();
    else if(xyNeg->isChecked()) scriptXYNegatif();
    else if(xyMatSup->isChecked()) scriptXYSuperieur();
    else if(xyMat->isChecked()) scriptXYMatrice();
    else if(xy00->isChecked()) scriptXY00();
    else if(xyMatSupCaree->isChecked()) scriptXYSupCarr();
    else if(MatSupCarre->isChecked()) scriptSupCarr();
}
    }

}

void FenetrePrincipale::changementTab(int i)
{
    tab->setRowCount(i);
    tab->setColumnCount(i);
}

void FenetrePrincipale::plusProcheVoisin()
{
    QWidget *glout = new QWidget;
    glout->setFixedSize(500,200);
    glout->setHidden(false);
    QString inf("Z(T) = <strong> ");

    inf+=QString::number(graphe->plusProcheVoisin());
    inf+=" </strong>";
    QLabel *gloutLbl = new QLabel(inf);
    QVBoxLayout *layoutGlout =new QVBoxLayout;
    layoutGlout->addWidget(gloutLbl,0,Qt::AlignCenter);
    glout->setLayout(layoutGlout);
    glout->setHidden(false);

}

void FenetrePrincipale::plusProcheVoisinAleatoire()
{
    QWidget *glout = new QWidget;
    glout->setFixedSize(500,200);
    glout->setHidden(false);
    QString inf("Z(T) = <strong> ");

    inf+=QString::number(graphe->plusProcheVoisinAleatoire());
    inf+=" </strong>";
    QLabel *gloutLbl = new QLabel(inf);
    QVBoxLayout *layoutGlout =new QVBoxLayout;
    layoutGlout->addWidget(gloutLbl,0,Qt::AlignCenter);
    glout->setLayout(layoutGlout);
    glout->setHidden(false);
}

void FenetrePrincipale::plusProcheVoisinSystematique()
{
    QWidget *glout = new QWidget;
    glout->setFixedSize(500,200);
    glout->setHidden(false);
    QString inf("Z(T) = <strong> ");

    inf+=QString::number(graphe->plusProcheVoisinSystematique());
    inf+=" </strong>";
    QLabel *gloutLbl = new QLabel(inf);
    QVBoxLayout *layoutGlout =new QVBoxLayout;
    layoutGlout->addWidget(gloutLbl,0,Qt::AlignCenter);
    glout->setLayout(layoutGlout);

}

void FenetrePrincipale::plusLointainVoisinSystematique()
{
    QWidget *glout = new QWidget;
    glout->setFixedSize(500,200);
    glout->setHidden(false);
    QString inf("Z(T) = <strong> ");

    inf+=QString::number(graphe->plusLointainVoisinSystematique());
    inf+=" </strong>";
    QLabel *gloutLbl = new QLabel(inf);
    QVBoxLayout *layoutGlout =new QVBoxLayout;
    layoutGlout->addWidget(gloutLbl,0,Qt::AlignCenter);
    glout->setLayout(layoutGlout);
}

void FenetrePrincipale::opt2()
{
    widgOpt2 = new QWidget;
    widgOpt2->setFixedSize(350,150);
    widgOpt2->setHidden(false);


    QLabel *aLbl = new QLabel("Ville 1 = ");
    QLabel *bLbl = new QLabel("Ville 2 = ");
    aSpn = new QSpinBox;
        aSpn->setMinimum(1);
        aSpn->setMaximum(tailleGraphe->value());
    bSpn = new QSpinBox;
        bSpn->setMinimum(1);
        bSpn->setMaximum(tailleGraphe->value());

    aBtn = new QRadioButton("Aléatoire");


    QHBoxLayout *lay1=new QHBoxLayout;
    lay1->addWidget(aLbl);
    lay1->addWidget(aSpn);
    lay1->addWidget(bLbl);
    lay1->addWidget(bSpn);
    QHBoxLayout *lay2=new QHBoxLayout;
    lay2->addWidget(aBtn);
    lay2->addWidget(opt2Btn);
    QVBoxLayout *layoutGlout =new QVBoxLayout;
    layoutGlout->addLayout(lay1);
    layoutGlout->addLayout(lay2);
    widgOpt2->setLayout(layoutGlout);

}

void FenetrePrincipale::recuitSimule()
{


    QWidget *glout = new QWidget;
    glout->setFixedSize(500,200);
    glout->setHidden(false);
    QString inf("Z(T) = <strong> ");

    inf+=QString::number(graphe->recuitSimule());
    inf+=" </strong>";
    QLabel *gloutLbl = new QLabel(inf);
    QVBoxLayout *layoutGlout =new QVBoxLayout;
    layoutGlout->addWidget(gloutLbl,0,Qt::AlignCenter);
    glout->setLayout(layoutGlout);

}

void FenetrePrincipale::interchange()
{
    if(aBtn->isChecked())
    {
         widgOpt2->setHidden(true);
        QWidget *glout = new QWidget;
        glout->setFixedSize(500,200);
        glout->setHidden(false);
        QString inf("Z(T) = <strong> ");

        inf+=QString::number(graphe->opt2Aleatoire());
        inf+=" </strong>";
        QLabel *gloutLbl = new QLabel(inf);
        QVBoxLayout *layoutGlout =new QVBoxLayout;
        layoutGlout->addWidget(gloutLbl,0,Qt::AlignCenter);
        glout->setLayout(layoutGlout);
       graphe->setHidden(true);
       graphe->setHidden(false);

    }else
    {
        if(aSpn->value()==bSpn->value())
        {
            QMessageBox::critical(opt2Btn,"Insertion invalide","Veuillez choisir deux clients différents");
        }else
        {
            if(aSpn->value()>bSpn->value())
            {
                QMessageBox::critical(opt2Btn,"Insertion invalide","Veuillez donne au 'Client 1' un indice plus petit que celui du 'Client 2'");
            }else
            {
                widgOpt2->setHidden(true);
               QWidget *glout = new QWidget;
               glout->setFixedSize(500,200);
               glout->setHidden(false);
               QString inf("Z(T) = <strong> ");

               inf+=QString::number(graphe->opt2Inser(aSpn->value()-1,bSpn->value()-1));
               inf+=" </strong>";
               QLabel *gloutLbl = new QLabel(inf);
               QVBoxLayout *layoutGlout =new QVBoxLayout;
               layoutGlout->addWidget(gloutLbl,0,Qt::AlignCenter);
               glout->setLayout(layoutGlout);
              graphe->setHidden(true);
              graphe->setHidden(false);
            }
        }
    }

}

void FenetrePrincipale::nouvelleInstance()
{
    if(parcourrirEdit->text()=="" && parc){parcourrirBtn->setEnabled(true);}
    else
    {
   graphe->setVisible(false);
    graphe->setHidden(true);
    tailleGraphe->setValue(1);
    tab->setRowCount(0);
    tab->setColumnCount(0);
    tab->setRowCount(1);
    tab->setColumnCount(1);
    parcourrirEdit->setText("");
    parc=false;
ui->actionNouvelle_instance->setEnabled(false);
parcourrirBtn->setEnabled(true);
executerBtn->setEnabled(true);
    }
}

void FenetrePrincipale::HB()
{

    QWidget *glout = new QWidget;
    glout->setFixedSize(500,200);
    glout->setHidden(false);
    QString inf("Z(T) = <strong> ");

    inf+=QString::number(graphe->HB());
    inf+=" </strong>";
    QLabel *gloutLbl = new QLabel(inf);
    QVBoxLayout *layoutGlout =new QVBoxLayout;
    layoutGlout->addWidget(gloutLbl,0,Qt::AlignCenter);
    glout->setLayout(layoutGlout);

}

void FenetrePrincipale::HBReel()
{
    graphe->HBReel();
}

void FenetrePrincipale::aPropos()
{
    QString inf("<br>Cette application a été créer par l'étudiant <strong>Mehdi BOUZiDi</strong>, en master R.O <br>");
    inf+="<br>Option : <strong>METHODES ET MODELES POUR L'INGENIERIE ET LA RECHERCHE </strong>.<br> ";
    inf+="<br>Date : <strong> 16/11/2015</strong> <br>";

    QWidget *infos = new QWidget;
infos->setWindowTitle("À propos");
infos->setWindowIcon(QIcon("info2.png"));
infos->setFixedSize(500,300);
 QLabel *auteur = new QLabel(inf);
 QVBoxLayout *layoutInfo =new QVBoxLayout;
 layoutInfo->addWidget(auteur);
 infos->setLayout(layoutInfo);
 infos->setHidden(false);
}
