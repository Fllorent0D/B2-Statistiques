#ifndef ECHANTILLON_H_INCLUDED
#define ECHANTILLON_H_INCLUDED

using namespace std;

#include "DataSource.h"

class Echantillon
{
private:
	DataSource* Source;
public:
	Echantillon();
	Echantillon(const string &, int);
	Echantillon(const string &, int, int);
	~Echantillon();

	DataSource* getSource() const;
	Echantillon& operator=(Echantillon const& v);
	void setSource(DataSource *);
};

#endif //ECHANTILLON_H_INCLUDED
