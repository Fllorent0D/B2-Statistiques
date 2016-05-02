#ifndef DATASOURCE_H_INCLUDED
#define DATASOURCE_H_INCLUDED
using namespace std;

#include "ListeBase.h"
#include "Liste.h"
#include "Data1D.h"

class DataSource
{
   private:
      string Nom;
      string Sujet;
      int EffTotal;
      int Type;
      
   public:
      DataSource();
      DataSource(const string &, const string &, int, int);
      DataSource(const DataSource&);
      virtual ~DataSource();

      /***** SETTERS *****/
      void setNom(const string &);
      void setSujet(const string &);
      void setEffTotal(const int);
      void setType(const int);

      /***** GETTERS *****/
      string getNom() const;
      string getSujet() const;
      int getEffTotal() const;
      int getType() const;
      DataSource& operator=(DataSource const& v);
      friend std::ostream &operator<<(std::ostream &flux, DataSource const&);
};

#endif //DATASOURCE_H_INCLUDED
