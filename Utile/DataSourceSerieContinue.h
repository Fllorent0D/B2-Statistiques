#ifndef DATASOURCESERIECONTINUE_H_INCLUDED
#define DATASOURCESERIECONTINUE_H_INCLUDED

#include "DataSource.h"
#include "Data1D.h"
#include "ListeTriee.h"

using namespace std;

class DataSourceSerieContinue: public DataSource
{
	private:
		Liste<Data1D>* L;
		float Debut;
		float Intervalle;
	public:
		DataSourceSerieContinue();
		DataSourceSerieContinue(const DataSourceSerieContinue&);
		DataSourceSerieContinue(const string &, const string &, const int, const string &, const int);
		~DataSourceSerieContinue();
		
		void setDebut(const float);
		void setIntervalle(const float);
		float getDebut() const;
		float getIntervalle() const;
		
		float getXi(float i);
		float getYi(float i);

		Liste<Data1D>* getL() const;
};

#endif //DATASOURCESERIECONTINUE_H_INCLUDED
