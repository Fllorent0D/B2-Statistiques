#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

#include "DataSourceSerie2D.h"
#include "Liste.h"

DataSourceSerie2D::DataSourceSerie2D() : DataSource()
{
	L = NULL;
	setSujet2("Aucun");
	setType2(0);
}

DataSourceSerie2D::DataSourceSerie2D(const string & Nom, const string & Sj1, const string & Sj2, const int T1, const int T2, const string & NomFichier, const int Colonne1, const int Colonne2) : DataSource(Nom, Sj1, 0, T1)
{
	setSujet2(Sj2);
	setType2(T2);

	string ligne, Lecture;
	float tempX(0), tempY(0);
	int i = 0;

	ifstream fichier;
	fichier.open(NomFichier.c_str(), ios::in);

	if(fichier.is_open())
	{
		//On ignore les trois lignes du debut
		getline(fichier, ligne);
		getline(fichier, ligne);
		getline(fichier, ligne);

		int count_eff(0);
		L = new Liste<Data2D>();

		while(fichier)
		{
			if(fichier.peek() == EOF)
                break; //Return le carac suivant

            count_eff++;
            getline(fichier, ligne);
			istringstream iss(ligne);

			i = 0;
			do
			{
				getline(iss, Lecture, ':');
				i++;
			} while (i < Colonne1);
			tempX = atof(Lecture.c_str());

			iss.clear();
			iss.str(ligne);
			i = 0;

			do
			{
				getline(iss, Lecture, ':');
				i++;
			} while (i < Colonne2);
			tempY = atof(Lecture.c_str());
			Data2D *tempCD2;
			tempCD2 = new Data2D(tempX, tempY); 
			L->Ajout(*tempCD2);
		}

		setEffTotal(count_eff);

		fichier.close();
	}
}

DataSourceSerie2D::DataSourceSerie2D(const DataSourceSerie2D &v) : DataSource(v)
{
	setSujet2(v.getSujet2());
	setType2(v.getType2());
	L = new Liste<Data2D>();
	L = v.getL();
}

DataSourceSerie2D::~DataSourceSerie2D()
{
	if(L)
		delete L;
}

void DataSourceSerie2D::setSujet2(const string &s)
{
	Sujet2 = s;
}

void DataSourceSerie2D::setType2(const int T2)
{
	Type2 = T2;
}

string DataSourceSerie2D::getSujet2() const
{
	return Sujet2;
}

int DataSourceSerie2D::getType2() const
{
	return Type2;
}

Liste<Data2D>* DataSourceSerie2D::getL() const
{
	return L;
}

float DataSourceSerie2D::getXi(float i)
{
	return L->getElement(i).getVal1();
}

float DataSourceSerie2D::getYi(float i)
{
	return L->getElement(i).getVal2();
}
