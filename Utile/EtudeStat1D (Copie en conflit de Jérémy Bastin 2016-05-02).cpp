#include <math.h>
#include "EtudeStat1D.h"
extern QApplication* a;

#include "graphstat1ddiscrete.h"             // ???????????????????????????
#include "graphstat1dcontinue.h" 
EtudeStat1D::EtudeStat1D()
{
}

EtudeStat1D::EtudeStat1D(const EtudeStat1D& Etude)
{

}
EtudeStat1D::~EtudeStat1D()
{

}

EtudeStat1D::EtudeStat1D(const char* NomFichier,int Colonne)
{
	E = new Echantillon(NomFichier, Colonne);
  setMoyenne();
  setMediane();
  setEcartType();
  setMin();
  setMax();
  setMode();
  AfficheRapport();

	Affiche();
}
float EtudeStat1D::getMin()
{
  return Min;
}
float EtudeStat1D::getMax()
{
  return Max;
}
float EtudeStat1D::getMoyenne()
{
  return Moyenne;
}
void EtudeStat1D::setMoyenne()
{
  float temp = 0;
  Noeud<Data1D> *pTemp;
  DataSourceSerieDiscrete* SeDis;
  DataSourceSerieContinue* SeCon;

  SeDis = dynamic_cast<DataSourceSerieDiscrete*>(E->getSource());
  if(SeDis)
    pTemp = SeDis->getL()->getpTete();
  else 
  {
    SeCon = dynamic_cast<DataSourceSerieContinue*>((E->getSource()));
    if(SeCon)
      pTemp = SeCon->getL()->getpTete();
  }

  while(pTemp != NULL)
  {
    temp += pTemp->Type->getVal() * pTemp->Type->getEff();
    pTemp = pTemp->pSuivant;
  }
  if(SeDis)
    temp = temp / (SeDis->getEffTotal());
  else
    temp = temp / (SeCon->getEffTotal());
  
  Moyenne = temp;
}
void EtudeStat1D::setMediane()
{
  DataSourceSerieDiscrete* SeDis;
  DataSourceSerieContinue* SeCon;
  float tmp;
  int cpt;
  if (SeDis = dynamic_cast<DataSourceSerieDiscrete*>(E->getSource()))
  {
    Noeud<Data1D>* pTemp;
    ListeTriee<float> ListeComplete;
    pTemp = SeDis->getL()->getpTete();
    
    while(pTemp!= NULL)
    {
      for (int cpt = 0; cpt < pTemp->Type->getEff(); cpt++)
        ListeComplete.Ajout(pTemp->Type->getVal());
      pTemp = pTemp->pSuivant;
    }

    if ((SeDis->getEffTotal()%2) != 0) // impaire
    {
      tmp = SeDis->getEffTotal() / 2; 
      cpt = 0;

      Mediane = ListeComplete.getElement(tmp);
    }
      
    else  // paire
    {
      tmp = SeDis->getEffTotal() / 2; // + 1 implicite à la sortie de la boucle for suivante
      float val1 = 0, val2 = 0;
      cpt = 0;

      val1 = ListeComplete.getElement(tmp);
      val2 = ListeComplete.getElement(tmp + 1);

      Mediane = (val1 + val2) / 2;
    }
  }

  else if (SeCon = dynamic_cast<DataSourceSerieContinue*>(E->getSource()))
  {
    int SommeEff = 0;
    Liste<Data1D>* liste = SeCon->getL();
    cpt = 1;
    while ((SommeEff + liste->getElement(cpt).getEff()) < (SeCon->getEffTotal() / 2))
    {
      SommeEff += liste->getElement(cpt).getEff();
      cpt++;
    }
    Mediane = (liste->getElement(cpt).getVal() - (SeCon->getIntervalle() / 2)) + ((SeCon->getIntervalle() / liste->getElement(cpt).getEff()) * (((float)(SeCon->getEffTotal()) / 2) - SommeEff));
  }
}
const float* EtudeStat1D::getMode()
{
  return Mode;
}
float EtudeStat1D::getMediane()
{
  return  Mediane;
}
void EtudeStat1D::setMode(float a, float b, float c, float d, float e)
{
  Mode[0] = a;
  Mode[1] = b;
  Mode[2] = c;
  Mode[3] = d;
  Mode[4] = e;
}
void EtudeStat1D::setMode()
{
  Liste<Data1D>* liste;
  DataSourceSerieDiscrete* SeDis;
  DataSourceSerieContinue* SeCon;
  float val1 = 0, val2 = 0, val3 = 0, val4 = 0, val5 = 0, eff = 0;

  //Trop de probleme a mettre getL en virtuel
  if (SeDis = dynamic_cast<DataSourceSerieDiscrete*>(E->getSource()))
  {
    liste = SeDis->getL();
    for(int i = 1; i <= liste->Size(); i++)
    {
      if ((liste->getElement(i).getEff()) > eff)
      {
        eff = liste->getElement(i).getEff();
        val1 = liste->getElement(i).getVal();
        val2 = val3 = val4 = val5 = 0;
      }
      else if (liste->getElement(i).getEff() == eff)
      {
        if (val2 == 0)
          val2 = liste->getElement(i).getVal();
        else if (val3 == 0)
          val3 = liste->getElement(i).getVal();
        else if (val4 == 0)
          val4 = liste->getElement(i).getVal();
        else if (val5 == 0)
          val5 = liste->getElement(i).getVal();

      }
    }

    setMode(val1, val2, val3, val4, val5);
  }

  else if (SeCon = dynamic_cast<DataSourceSerieContinue*>(E->getSource()))
  {
    liste = SeCon->getL();
    for(int i = 1; i <= liste->Size(); i++)
    {
      if ((liste->getElement(i).getEff()) > eff)
      {
        eff = liste->getElement(i).getEff();
        val1 = liste->getElement(i).getVal();
        val2 = val3 = val4 = val5 = 0;
      }
      else if (liste->getElement(i).getEff() == eff)
      {
        if (val2 == 0)
          val2 = liste->getElement(i).getVal();
        else if (val3 == 0)
          val3 = liste->getElement(i).getVal();
        else if (val4 == 0)
          val4 = liste->getElement(i).getVal();
        else if (val5 == 0)
          val5 = liste->getElement(i).getVal();

      }
    }

    setMode(val1, val2, val3, val4, val5);
  }

  else
  {
    cout << endl << "Probleme de type de donnees (au niveau du mode) !" << endl;
    exit(1);
  }
}
void EtudeStat1D::setMax()
{
  DataSourceSerieDiscrete* SeDis;
  DataSourceSerieContinue* SeCon;
  Max = 0;

  if (SeDis = dynamic_cast<DataSourceSerieDiscrete*>(E->getSource()))
  {
    Max = SeDis->getL()->getElement(1).getVal();
  }

  else if (SeCon = dynamic_cast<DataSourceSerieContinue*>(E->getSource()))
  {
    Max = SeCon->getL()->getElement(1).getVal();
  }

  else
  {
    cout << endl << "Probleme de type de donnees (au niveau du min) !" << endl;
    exit(1);
  }
}
void EtudeStat1D::setMin()
{
  DataSourceSerieDiscrete* SeDis;
  DataSourceSerieContinue* SeCon;
  Min = 0;

  if (SeDis = dynamic_cast<DataSourceSerieDiscrete*>(E->getSource()))
  {
    Min = SeDis->getL()->getElement(SeDis->getL()->Size()).getVal();
  }

  else if (SeCon = dynamic_cast<DataSourceSerieContinue*>(E->getSource()))
  {
    Min = SeCon->getL()->getElement(SeCon->getL()->Size()).getVal();
  }

  else
  {
    cout << endl << "Probleme de type de donnees (au niveau du min) !" << endl;
    exit(1);
  }
}
void EtudeStat1D::setEcartType()
{
  Liste<Data1D>* liste;
  DataSourceSerieDiscrete* SeDis;
  DataSourceSerieContinue* SeCon;
  float tmp = 0;
  if (SeDis = dynamic_cast<DataSourceSerieDiscrete*>(E->getSource()))
  {
    liste = SeDis->getL();
    for(int i = 0; i < liste->Size(); i++)
    {
      tmp = tmp + (liste->getElement(i).getEff()) * (pow((liste->getElement(i).getVal() - getMoyenne()), 2));
    }
    EcartType = sqrt(tmp / (SeDis->getEffTotal()));
  }

  else if (SeCon = dynamic_cast<DataSourceSerieContinue*>(E->getSource()))
  {
    liste = SeCon->getL();
    for(int i = 1; i <= liste->Size(); i++)
    {
      tmp = tmp + (liste->getElement(i).getEff()) * (pow((liste->getElement(i).getVal() - getMoyenne()), 2));
    }
    EcartType = sqrt(tmp / (SeCon->getEffTotal()));
  }
  else
  {
    cout << endl << "Probleme de type de donnees (au niveau de l'ecart type) !" << endl;
    exit(1);
  }
 }
bool EtudeStat1D::VerifStat()
{
  float inf = 0, sup = 0;

  inf = getMoyenne() - (2 * getEcartType());
  sup = getMoyenne() + (2 * getEcartType());

  if (getMin() < inf || sup < getMax())
    return false;

  return true;
}

float EtudeStat1D::getEcartType()
{
  return EcartType;
}
float EtudeStat1D::getCoefVar() 
{
  return  (getEcartType()/getMoyenne()) * 100;
}
void EtudeStat1D::AfficheRapport()
{
  printf ("\033c");
  cout << "******* RAPPORT DE L'ETUDE ********\n" << endl;
  cout << *(E->getSource()) << endl;
  cout << endl << "Moyenne : " << getMoyenne() << endl << endl;
  
  cout << "Mediane : " << getMediane() << endl << endl;

  cout << "Mode : " << Mode[0] << " : " << Mode[1] << " : " << Mode[2] <<" : " << Mode[3]<<" : " << Mode[4] << endl << endl;

  cout << "Ecart type : " << getEcartType() << endl << endl;
/*
  cout << "\tEtendue : " << getEtendue() << endl << endl;
*/
  cout << "Coefficient de variation : " << getCoefVar() << " %" << endl << endl;

  cout << "Controle de qualite  : " << endl ;

  cout << "\tValeur min : " << getMin() << endl;

  cout << "\tValeur max : " << getMax() << endl;

  cout << "\tStatistique sous controle : ";
  if (VerifStat())
    cout << "Oui" << endl;
  else
    cout << "Non" << endl;
}
void EtudeStat1D::Affiche()
{
  if (this->getE()->getSource()->getType() == 1)
  {  
     	GraphStat1DDiscrete w(*this);
      w.show();
      a->exec();
  }
  else
  { 
      GraphStat1DContinue w(*this);
      w.show();
      a->exec();
  }
}

