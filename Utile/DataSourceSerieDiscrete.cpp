#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;
#include "ListeTriee.h"
#include "Liste.h"
#include "DataSourceSerieDiscrete.h"

DataSourceSerieDiscrete::DataSourceSerieDiscrete() : DataSource()
{
	L = NULL;
}

DataSourceSerieDiscrete::DataSourceSerieDiscrete(const DataSourceSerieDiscrete &v) : DataSource(v)
{
	L = v.getL();
}

DataSourceSerieDiscrete::DataSourceSerieDiscrete(const string & Nom, const string & Sujet, const int Type, const string & NomFichier, const int Colonne) : DataSource(Nom, Sujet, 0, Type)
{
	string ligne, Lecture;
	ListeTriee<float> stListe;
	Data1D *pData1D;

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
		while(!fichier.eof())
		{
			if(fichier.peek() == EOF) //Dernier caractère fait chier
                break; 
            
            count_eff++;
            getline(fichier, ligne);
			istringstream iss(ligne);
			i = 0;
			do
			{
				getline(iss, Lecture, ':');
				i++;
			} while (i < Colonne);
			
			stListe.Ajout(atof(Lecture.c_str()));
		}

		setEffTotal(count_eff);

		L = new Liste<Data1D>();
		Noeud<float> *pTemp;

		pTemp = stListe.getpTete();

		while(pTemp != NULL)
		{
			float Test;
			int eff = 0;

			Test = *pTemp->Type;
			while(pTemp != NULL && Test == *pTemp->Type) //on augmente l'effectif tant que c'est le meme nombre
			{
				eff++;
				pTemp = pTemp->pSuivant;
			}

			pData1D = new Data1D(Test, eff);
			L->Ajout(*pData1D);
		}

		fichier.close();
	}
	else
		cout << "Le fichier n'est pas ouvert" << endl;
}

DataSourceSerieDiscrete::~DataSourceSerieDiscrete()
{
	if(L)
		delete L;
}

Liste<Data1D>* DataSourceSerieDiscrete::getL() const
{
	return L;
}

float DataSourceSerieDiscrete::getXi(float i)
{

	return L->getElement(i).getVal();
}

float DataSourceSerieDiscrete::getYi(float i)
{

	return L->getElement(i).getEff();
}

