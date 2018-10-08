#include "espacedessin.h"

using namespace std;
EspaceDessin::EspaceDessin(QWidget *parent) : QWidget(parent)
{

}

EspaceDessin::EspaceDessin(QWidget *parent, std::vector<std::vector<double> > mat, std::vector<double> coor, double max, int may)
{
    setParent(parent);
    x=0;y=0; nbClick=0; B=false;


    matriceCouts=mat;



    int n=mat.size();
    for(int i=0;i<n;i++)
    {
        Sommet *sommet=new Sommet(this,i+1,coor[i]*750/max,coor[i+n]*750/may+12);
        ensembleSommets.push_back(sommet);
    }

    solt=false;

}



void EspaceDessin::paintEvent(QPaintEvent *e)
{
    QPainter *painter=new QPainter(this);

    if(solt)
    {
        QPen stilo;


        stilo.setColor(Qt::red);
        stilo.setWidth(3);
        painter->setPen(stilo);

        for(int i=0;i<solution.size();i++)
        {
                  if(i==solution.size()-1)
                  {
                      painter->drawLine(ensembleSommets[solution[0]]->getX()+12,ensembleSommets[solution[0]]->getY()+12,ensembleSommets[solution[solution.size()-1]]->getX()+12,ensembleSommets[solution[solution.size()-1]]->getY()+12);
                  }else
                  {
                    painter->drawLine(ensembleSommets[solution[i]]->getX()+12,ensembleSommets[solution[i]]->getY()+12,ensembleSommets[solution[i+1]]->getX()+12,ensembleSommets[solution[i+1]]->getY()+12);
                  }
        }


    }
}

int EspaceDessin::aleaInt()
{
    return qrand() % 780;
}

double EspaceDessin::aleatoireD()
{
     return ((double)(qrand()%100) /(double) 100);
}

bool EspaceDessin::existX(int x)
{
    bool k=false;
        if(!ensembleSommets.empty()){

            for(int i=0;i<ensembleSommets.size()&& !k;i++)
            {
                if(ensembleSommets[i]->getX()==x){k=true;}
            }
        }

return k;
}

bool EspaceDessin::existY(int y)
{
    bool k=false;
        if(!ensembleSommets.empty()){

            for(int i=0;i<ensembleSommets.size()&& !k;i++)
            {
                if(ensembleSommets[i]->getY()==y){k=true;}
            }
        }

        return k;
}

int EspaceDessin::aleatoire(int b)
{
    return qrand() %  b;
}

void EspaceDessin::suppElt(std::vector<int> &vect, int i)
{
    std::vector<int> v;
    for(int j=0;j<vect.size();j++)
    {
        if(i!=vect[j])
        {
            v.push_back(vect[j]);
        }
    }
    vect=v;
}

std::vector<std::vector<double> > EspaceDessin::getCouts() const
{
    return matriceCouts;
}

std::vector<int> EspaceDessin::getSolution() const
{
    return solution;
}

double EspaceDessin::valeurFctObject(const std::vector<int> &sol)
{
    double somme(0);
    for(int i=0;i<sol.size();i++)
    {
        if(i==sol.size()-1)
        {
            somme+=matriceCouts[sol[i]][sol[0]];
        }
        else
        {
            somme+=matriceCouts[sol[i]][sol[i+1]];
        }

    }
    return somme;}

int EspaceDessin::minimum(std::vector<int> vect, int i)
{
    double minD(INFINITY);
    int min;
    for(int j=0;j<vect.size();j++)
    {
        if(matriceCouts[i][vect[j]]<minD)
        {
            minD=matriceCouts[i][vect[j]];
            min=vect[j];
        }
    }

return min;}

/*********************** Heuristiques **********************/

double EspaceDessin::plusProcheVoisin()
{
   vector<int>  solProvisoire,sommetsRestants;
   solProvisoire.push_back(aleatoire(ensembleSommets.size()));
    double somme(0);

   for(int i=0;i<ensembleSommets.size();i++)
   {
       if(i!=solProvisoire[0])
       {
           sommetsRestants.push_back(i);
       }
   }

   double min(INFINITY),s;

while(!sommetsRestants.empty())
{

       for(int i=0;i<sommetsRestants.size();i++)
       {
           if(matriceCouts[solProvisoire[solProvisoire.size()-1]][sommetsRestants[i]]<min)
           {
               min=matriceCouts[solProvisoire[solProvisoire.size()-1]][sommetsRestants[i]];
               s=sommetsRestants[i];
           }
       }
        solProvisoire.push_back(s);
        suppElt(sommetsRestants,s);
        min=INFINITY;

}
//Calcul de la valeur de la fonction objectif
somme=valeurFctObject(solProvisoire);

    solt=true;
    solution=solProvisoire;
    setHidden(true);
    setHidden(false);
    return somme;
}

/*---------------------------------------------------------------------------*/

double EspaceDessin::plusProcheVoisinAleatoire()
{
    vector<int>  solProvisoire,sommetsRestants;


    for(int i=0;i<ensembleSommets.size();i++)
    {
            sommetsRestants.push_back(i);
    }

    int s;
    double somme(0);

 while(!sommetsRestants.empty())
 {
    s=aleatoire(sommetsRestants.size());
    solProvisoire.push_back(sommetsRestants[s]);
    suppElt(sommetsRestants,sommetsRestants[s]);
 }

 //Calcul de la valeur de la fonction objectif
somme=valeurFctObject(solProvisoire);
     solt=true;
     solution=solProvisoire;
     setHidden(true);
     setHidden(false);

     return somme;
}

/*---------------------------------------------------------------------------*/


double EspaceDessin::plusProcheVoisinSystematique()
{
    vector<int>  BKS;
    double somme,sommeBKS(INFINITY);

    for(int k=0;k<ensembleSommets.size();k++)
    {
        vector<int>  solProvisoire,sommetsRestants;
        solProvisoire.push_back(k);
         somme=0;

        for(int i=0;i<ensembleSommets.size();i++)
        {
            if(i!=solProvisoire[0])
            {
                sommetsRestants.push_back(i);
            }
        }

        double min(INFINITY);
               int s;

     while(!sommetsRestants.empty())
     {

            for(int i=0;i<sommetsRestants.size();i++)
            {
                if(matriceCouts[solProvisoire[solProvisoire.size()-1]][sommetsRestants[i]]<min)
                {
                    min=matriceCouts[solProvisoire[solProvisoire.size()-1]][sommetsRestants[i]];
                    s=sommetsRestants[i];
                }
            }
             solProvisoire.push_back(s);
             suppElt(sommetsRestants,s);
             min=INFINITY;


    }

     //Calcul de la valeur de la fonction objectif
 somme=valeurFctObject(solProvisoire);


     if(somme<=sommeBKS)
     {
         BKS=solProvisoire;
         sommeBKS=somme;
     }

    }

    solt=true;
    solution=BKS;
    setHidden(true);
    setHidden(false);

    return sommeBKS;}

/*---------------------------------------------------------------------------*/

double EspaceDessin::plusLointainVoisinSystematique()
{


    vector<int>  BKS;
    double minBKS=INFINITY;
    double somme,sommeBKS;

    for(int k=0;k<ensembleSommets.size();k++)
    {
        vector<int>  solProvisoire,sommetsRestants;
        solProvisoire.push_back(k);
         somme=0;

        for(int i=0;i<ensembleSommets.size();i++)
        {
            if(i!=solProvisoire[0])
            {
                sommetsRestants.push_back(i);
            }
        }

        double max(-1);
               int s;

     while(!sommetsRestants.empty())
     {

            for(int i=0;i<sommetsRestants.size();i++)
            {
                if(matriceCouts[solProvisoire[solProvisoire.size()-1]][sommetsRestants[i]]>max)
                {
                    max=matriceCouts[solProvisoire[solProvisoire.size()-1]][sommetsRestants[i]];
                    s=sommetsRestants[i];
                }
            }
             solProvisoire.push_back(s);
             suppElt(sommetsRestants,s);
             max=-1;


    }

     //Calcul de la valeur de la fonction objectif
 somme=valeurFctObject(solProvisoire);

     if(somme<minBKS)
     {
         BKS=solProvisoire;
         sommeBKS=somme;
     }

    }

    solt=true;
    solution=BKS;
    setHidden(true);
    setHidden(false);

    return sommeBKS;
}

double EspaceDessin::HB()
{
    // les indices commences de 0
    solt=true;
    double max(-1);
    double somme(0);
    int indiceMax(-1);
    vector<int> solProvisoire(ensembleSommets.size(),0);
    vector<int> sommetsRestants;
    for(int i=0;i<matriceCouts.size();i++)
    {
        for(int j=0;j<matriceCouts.size();j++)
        {
            somme+=matriceCouts[i][j];
        }
        if(max<somme)
        {
            max=somme;
            indiceMax=i;

        }
        somme=0;
        sommetsRestants.push_back(i);
    }

    solProvisoire[solProvisoire.size()-1]=indiceMax;
    suppElt(sommetsRestants,indiceMax);



    solProvisoire[solProvisoire.size()-2]=minimum(sommetsRestants,indiceMax);
    suppElt(sommetsRestants,solProvisoire[solProvisoire.size()-2]);



    solProvisoire[0]=minimum(sommetsRestants,indiceMax);
    suppElt(sommetsRestants,solProvisoire[0]);


    int i=0;
    while(!sommetsRestants.empty())
    {
        solProvisoire[i+1]=minimum(sommetsRestants,solProvisoire[i]);
        suppElt(sommetsRestants,solProvisoire[i+1]);
    i++;
    }

solution=solProvisoire;
solt=true;
setHidden(true);
setHidden(false);
return valeurFctObject(solution);}

double EspaceDessin::HBReel()
{
    // les indices commences de 0
    solt=true;
    double max(-1);
    double somme(0);
    int indiceMax(-1);
    vector<int> solProvisoire(ensembleSommets.size(),0);
    vector<int> sommetsRestants;
    for(int i=0;i<matriceCouts.size();i++)
    {
        for(int j=0;j<matriceCouts.size();j++)
        {
            somme+=matriceCouts[i][j];
        }
        if(max<somme)
        {
            max=somme;
            indiceMax=i;

        }
        somme=0;
        sommetsRestants.push_back(i);
    }

    solProvisoire[solProvisoire.size()-1]=indiceMax;
    suppElt(sommetsRestants,indiceMax);


//
    solution=solProvisoire;
    repaint();
    solProvisoire[solProvisoire.size()-2]=minimum(sommetsRestants,indiceMax);
    suppElt(sommetsRestants,solProvisoire[solProvisoire.size()-2]);
//
    solution=solProvisoire;
    repaint();

    max=matriceCouts[indiceMax][solProvisoire[solProvisoire.size()-2]];
    matriceCouts[indiceMax][solProvisoire[solProvisoire.size()-2]]=INFINITY;
    solProvisoire[0]=minimum(sommetsRestants,indiceMax);
    suppElt(sommetsRestants,solProvisoire[0]);
    matriceCouts[indiceMax][solProvisoire[solProvisoire.size()-2]]=max;


    int i=0;
    while(!sommetsRestants.empty())
    {
//
        solution=solProvisoire;
        repaint();
        solProvisoire[i+1]=minimum(sommetsRestants,solProvisoire[i]);
        suppElt(sommetsRestants,solProvisoire[i+1]);
    i++;
    }

solution=solProvisoire;
solt=true;
setHidden(true);
setHidden(false);
return valeurFctObject(solution);
}

/************** Transformation ************/

std::vector<int> EspaceDessin::opt2( std::vector<int> sol)
{

    int a,b,c;
    a=aleatoire(sol.size());
    b=a;
    while(a==b)
    {
        b=aleatoire(sol.size());
    }

    if(a>b) // On suppose que l'indice 'a' est toujours plus petit que l'indice b à cause du a++; b--;
    {
        c=b;
        b=a;
        a=c;
    }
    while(a<b)
    {
        c=sol[a];
        sol[a]=sol[b];
        sol[b]=c;
        a++;
        b--;
    }
    return sol;}

double EspaceDessin::opt2Aleatoire()
{
    int a,b,c;
    a=aleatoire(solution.size());
    b=a;
    while(a==b)
    {
        b=aleatoire(solution.size());
    }


    while(a<b)
    {
        c=solution[a];
        solution[a]=solution[b];
        solution[b]=c;
        a++;
        b--;
    }

    return valeurFctObject(solution);
}

double EspaceDessin::opt2Inser(int x, int y)
{

    int a,b,c;
    for(int i=0;i<solution.size();i++)
    {
        if(solution[i]==x) a=i;
        else if(solution[i]==y) b=i;
    }
    if(a>b) // On suppose que l'indice 'a' est toujours plus petit que l'indice b à cause du a++; b--;
    {
        c=b;
        b=a;
        a=c;
    }
    while(a<b)
    {
        c=solution[a];
        solution[a]=solution[b];
        solution[b]=c;
        a++;
        b--;
    }

    return valeurFctObject(solution);
}





/****************** Métaheuristiques ********************/

double EspaceDessin::recuitSimule()
{

    vector<int> T,Tp,BCS;


    double zT,zTp,zBCS; zBCS=HB();
    double tetta(1000*solution.size());
    double p,alpha(0.99);

    int netta(solution.size()*solution.size()/8);

       zT=zBCS;

    T=solution; BCS=solution;

    while(0.01<tetta)
    {
        for(int i=0;i<netta;i++)
        {
            Tp=opt2(T);
            zTp=valeurFctObject(Tp);
            if(zTp-zT<=0)
            {
                T=Tp;
                zT=zTp;
                /*solution=T;
                repaint();*/
                    if(zTp-zBCS<0)
                    {
                        BCS=Tp;
                        zBCS=zTp;

                    }

            }else
            {
                p=aleatoireD();
                if(p<=exp((zT-zTp)/tetta))
                {
                    T=Tp;
                    zT=zTp;

                }
            }

        }

        tetta*=alpha;
        T=BCS;  //continu de la meilleure solution
        zT=zBCS;

    }

zBCS=valeurFctObject(BCS);
solution=BCS;
return zBCS;}

/******************* Hybridations ************************/


