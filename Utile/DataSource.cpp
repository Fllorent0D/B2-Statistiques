#include <iostream>
#include <string>
#include "Data1D.h"
#include "DataSource.h"
#include "DataSourceSerie2D.h"
#include "DataSourceSerieDiscrete.h"
#include "DataSourceSerieContinue.h"

DataSource::DataSource()
{
   setNom("NULL");
   setSujet("NULL");
   setEffTotal(0);
   setType(0);
}

DataSource::DataSource(const string & Nom, const string & Sujet,  int EffTotal,  int Type)
{
   setNom(Nom);
   setSujet(Sujet);
   setEffTotal(EffTotal);
   setType(Type);
}

DataSource::DataSource(const DataSource &v)
{
   setNom(v.getNom());
   setSujet(v.getSujet());
   setEffTotal(v.getEffTotal());
   setType(v.getType());
}

DataSource::~DataSource()
{}

/*************** SETTERS ***************/

void DataSource::setNom(const string &str)
{
   Nom = str;
}

void DataSource::setSujet(const string &str)
{
   Sujet = str;
}

void DataSource::setEffTotal(const int aff)
{
   EffTotal = aff;
}

void DataSource::setType(const int aff)
{
   Type = aff;
}

/*************** GETTERS ***************/

string DataSource::getNom() const
{
   return Nom;
}

string DataSource::getSujet() const
{
   return Sujet;
}

int DataSource::getEffTotal() const
{
   return EffTotal;
}

int DataSource::getType() const
{
   return Type;
}


DataSource& DataSource::operator=(DataSource const& v)
{
    setNom(v.getNom());
    setType(v.getType());
    setSujet(v.getSujet());
    setEffTotal(v.getEffTotal());

    return *this;
}

/******* OPERATORS *****/
ostream &operator<<(ostream &flux, DataSource const& CDS)
{
    //printf ("\033c");

    flux << "Nom : ";
    flux << CDS.getNom();
    flux << "\nSujet : ";
    flux << CDS.getSujet();

    if(const DataSourceSerie2D* new_cds = dynamic_cast<const DataSourceSerie2D*>(&CDS))
      flux << " -- " << new_cds->getSujet2();

    if(CDS.getType() == 1)
      flux << "\nType : Discrete";
    else
      flux << "\nType : Continue";

    if(const DataSourceSerie2D* new_cds = dynamic_cast<const DataSourceSerie2D*>(&CDS))
    {
      if(new_cds->getType2() == 1)
         flux << " -- Discrete";
      else
         flux << " -- Continue";
    }
    flux << "\nEffectif total : ";
    flux << CDS.getEffTotal();

    flux << "\n\nDonnees :" << endl;
    flux << "--------" << endl;
    if(const DataSourceSerieDiscrete* new_cdd = dynamic_cast<const DataSourceSerieDiscrete*>(&CDS))
      new_cdd->getL()->Affiche();
    else if(const DataSourceSerieContinue* new_cdc = dynamic_cast<const DataSourceSerieContinue*>(&CDS))
      new_cdc->getL()->Affiche();
    else if(const DataSourceSerie2D* new_cds = dynamic_cast<const DataSourceSerie2D*>(&CDS))
      new_cds->getL()->Affiche();

    return flux;
}
