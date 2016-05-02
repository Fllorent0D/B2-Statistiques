#ifndef ETUDESTAT1D_H
#define ETUDESTAT1D_H
#include <iostream>
using namespace std;
#include "Echantillon.h"
//#include "graphstat1ddiscrete.h"                //   ???????????????????
#include <QApplication>
#include "Liste.h"
#include "DataSourceSerieContinue.h"
#include "DataSourceSerieDiscrete.h"
class EtudeStat1D
{
private:
	Echantillon*	E;
	float				Moyenne;
	float				EcartType;
	float				Mediane;
   float          Min;
   float          Max;
	float				Mode[5];

public:
   EtudeStat1D();
   EtudeStat1D(const EtudeStat1D&);
	EtudeStat1D(const char*,int);
   ~EtudeStat1D();
   void Rapport() const;
   Echantillon* getE() const {return E;};
   void Affiche();
   void setMoyenne();
   float getMoyenne();
   void setEcartType( );
   float getEcartType();
   void setMediane();
   float getMediane();
   float getCoefVar();
   void setMin();
   void setMax();
   float getMin();
   float getMax();
   bool VerifStat();
   void setMode();
   void setMode(float, float, float, float, float);
   const float* getMode();
   void AfficheRapport();
};

#endif
