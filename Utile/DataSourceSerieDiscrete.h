#ifndef DATASOURCESERIEDISCRETE_H_INCLUDED
#define DATASOURCESERIEDISCRETE_H_INCLUDED

#include "DataSource.h"
#include "Data1D.h"

using namespace std;

class DataSourceSerieDiscrete: public DataSource
{
	private:
		Liste<Data1D>* L;
	public:
		DataSourceSerieDiscrete();
		DataSourceSerieDiscrete(const DataSourceSerieDiscrete&);
		DataSourceSerieDiscrete(const string &, const string &, const int, const string &, const int);
		~DataSourceSerieDiscrete();

		float getXi(float i);
		float getYi(float i);

		Liste<Data1D>* getL() const;
};

#endif //DATASOURCESERIEDISCRETE_H_INCLUDED
