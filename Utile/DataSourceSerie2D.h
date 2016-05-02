#ifndef DSOURCE2D_H_INCLUDED
#define DSOURCE2D_H_INCLUDED

#include "DataSource.h"
#include "Data2D.h"

class DataSourceSerie2D: public DataSource
{
	private:
		Liste<Data2D>* L;
		string Sujet2;
		int Type2;

	public:
		DataSourceSerie2D();
		DataSourceSerie2D(const DataSourceSerie2D&);
		DataSourceSerie2D(const string &, const string &, const string &, const int, const int, const string &, const int, const int);
		~DataSourceSerie2D();

		void setSujet2(const string &);
		void setType2(const int);

		string getSujet2() const;
		int getType2() const;

		float getXi(float i);
		float getYi(float i);
		Liste<Data2D>* getL() const;
};

#endif //DataSourceSerie2D_H_INCLUDED
