#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

#include "DataSourceSerieContinue.h"
#include "Liste.h"

#include "ListeTriee.h"

DataSourceSerieContinue::DataSourceSerieContinue() : DataSource()
{
	L = NULL;
	setDebut(0.0);
	setIntervalle(0.0);
}

DataSourceSerieContinue::DataSourceSerieContinue(const DataSourceSerieContinue &v) : DataSource(v)
{
	setDebut(v.getDebut());
	setIntervalle(v.getIntervalle());
	L = v.getL();
}

DataSourceSerieContinue::DataSourceSerieContinue(const string & Nom, const string & Sujet, const int Type, const string & NomFichier, const int Colonne) : DataSource(Nom, Sujet, 0, Type)
{
	string ligne, Lecture;
	ListeTriee<float> CLT;
	float minimum(0), maximum(0), Interval, End;
	int i = 0, count_eff = 0;

	ifstream fichier;
	fichier.open(NomFichier.c_str(), ios::in);

	if(fichier.is_open())
	{
		//On ignore les trois lignes du debut
		getline(fichier, ligne);
		getline(fichier, ligne);
		getline(fichier, ligne);
		
		getline(fichier, ligne);
		istringstream iss(ligne);
		count_eff++;
		i = 0;
		do
		{
			getline(iss, Lecture, ':');
			i++;
		} while (i < Colonne);

		minimum = atof(Lecture.c_str());
		maximum = atof(Lecture.c_str());
		i = 0;
		CLT.Ajout(atof(Lecture.c_str()));

		while(fichier)
		{
			if(fichier.peek() == EOF)
                break; //Return le carac suivant
            count_eff++;
            getline(fichier, ligne);
			iss.clear();
			iss.str(ligne);
			//Première
			do
			{
				getline(iss, Lecture, ':');
				i++;
			} while (i < Colonne);
			i = 0;

			float temp = atof(Lecture.c_str());
			cout << temp << endl;
			CLT.Ajout(atof(Lecture.c_str()));

			if(temp > maximum)
				maximum = temp;
			
			if(temp < minimum)
				minimum = temp;
		}

		setEffTotal(count_eff);

		cout << "Valeurs comprises dans l'intervalle [" << minimum << "," << maximum <<"]" << endl;
		setDebut(minimum);
		End  = maximum;
		do
		{
			cout << "\nChoix de l'intervalle : " ;
			cin >> Interval;
		}while(Interval > (End - Debut));
		setIntervalle(Interval);
		
		fichier.close();

		L = new Liste<Data1D>();
		Data1D *pTemp;

		
		int i;
		float borne;
		for(i = 0; i < count_eff && CLT.getElement(i) < Debut; i++);
		borne = Debut + Interval; //Première fin de borne
		while(i < count_eff && CLT.getElement(i) <= End)
		{
			pTemp = new Data1D;
			pTemp->setVal(borne - (Interval/2));
			pTemp->setEff(0);
			while (i < count_eff && CLT.getElement(i) < borne)
			{
				pTemp->setEff(pTemp->getEff() + 1);
				i++;
			}
			L->Ajout(*pTemp);
			borne = borne + Interval; 
			free(pTemp);

		}


	}
	else
		cout << "Le fichier n'est pas ouvert" << endl;

}

DataSourceSerieContinue::~DataSourceSerieContinue()
{
	if(L)
		delete L;
}

void DataSourceSerieContinue::setDebut(const float Deb)
{
	Debut = Deb;
}

void DataSourceSerieContinue::setIntervalle(const float Int)
{
	Intervalle = Int;
}

float DataSourceSerieContinue::getDebut() const
{
	return Debut;
}

float DataSourceSerieContinue::getIntervalle() const
{
	return Intervalle;
}

Liste<Data1D>* DataSourceSerieContinue::getL() const
{
	return L;
}

float DataSourceSerieContinue::getXi(float i)
{
	return L->getElement(i).getVal();
}

float DataSourceSerieContinue::getYi(float i)
{
	return L->getElement(i).getEff();
}
