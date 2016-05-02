#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
#include <stdlib.h>

#include "Echantillon.h"
#include "DataSource.h"
#include "DataSourceSerie2D.h"
#include "DataSourceSerieDiscrete.h"
#include "DataSourceSerieContinue.h"
#include "Data1D.h"

using namespace std;

Echantillon::Echantillon()
{
	this->Source = NULL;
}

Echantillon::Echantillon(const string &NomFichier,  int Colonne)
{
	string Buf, Nom, ligne, Lecture, Sujet;
	int val(0), i(1);
	ifstream fichier;
	fichier.open(NomFichier.c_str(), ios::in);
/* check colonne existe */
	if(fichier.is_open())
	{
		getline(fichier, ligne);
		getline(fichier, ligne);
		getline(fichier, ligne);
		while(1)
		{
			fichier.get(ligne[i]);
			if(ligne[i] == ':')
				i++;
			else
			{
				if(ligne[i] == '\0'||ligne[i] == '\n')
					break;
			}
		}

		fichier.close();
	}
	else
	{
		cout << "Le fichier n'est pas ouvert" << endl;
		exit(0);
	}

	if(Colonne > i)
	{
		cout << "Il n'y a que " << i << " colonnes dans le fichier de donnees" << endl;
		exit(0);
	}

	fichier.open(NomFichier.c_str(), ios::in); // c_str nous permet de recuperer un char

	if(fichier.is_open())
	{
		/** NOM **/
		getline(fichier, ligne);
		Nom = ligne;

		/** SUJET **/
		getline(fichier, ligne);

		istringstream iss(ligne);
		i = 0;
		do
		{
			getline(iss, Lecture, ':');
			i++;
		} while (i < Colonne);

		Sujet = Lecture;

		/** DISCRETE OR CONTINUE **/
		getline(fichier, ligne);
		iss.clear();
		iss.str(ligne);

		i = 0;
		do
		{
			getline(iss, Lecture, ':');
			i++;
		} while (i < Colonne);

		if(Lecture == "C")
			val = 2;
		else
			val = 1;

		fichier.close();
	}
	else
	{
		cout << "Le fichier n'est pas ouvert" << endl;
	}

	if(val == 1)
	{
		Source = new DataSourceSerieDiscrete(Nom, Sujet, val, NomFichier, Colonne);

	}
	else
	{
		Source = new DataSourceSerieContinue(Nom, Sujet, val, NomFichier, Colonne);
	}
	cout << *Source;
}

Echantillon::Echantillon(const string &NomFichier, int Colonne1, int Colonne2)
{
	string ligne, Nom, Sujet1, Sujet2, Lecture;
	int i(1), val1(0), val2(0);
	ifstream fichier;
	fichier.open(NomFichier.c_str(), ios::in);

	if(Colonne2 == Colonne1)
	{
		cout << "ERREUR - Impossible de faire une etude sur 2 meme colonnes" << endl;
		exit(0);
	}

	if(fichier.is_open())
	{
		getline(fichier, ligne);
		getline(fichier, ligne);
		getline(fichier, ligne);
		while(1)
		{
			fichier.get(ligne[i]);
			if(ligne[i] == ':')
				i++;
			else
			{
				if(ligne[i] == '\0'||ligne[i] == '\n')
					break;
			}
		}

		fichier.close();
	}
	else
	{
		cout << "Le fichier n'est pas ouvert" << endl;
		exit(0);
	}

	if(Colonne1 > i || Colonne2 > i)
	{
		cout << "Il n'y a que " << i << " colonnes dans le fichier de donnees" << endl;
		exit(0);
	}

	fichier.open(NomFichier.c_str(), ios::in); // c_str nous permet de recuperer un char

	if(fichier.is_open())
	{
		/** NOM **/
		getline(fichier, ligne);
		Nom = ligne;

		/** SUJET **/
		getline(fichier, ligne);
		i = 0;
		istringstream iss(ligne);

		do
		{
			getline(iss, Lecture, ':');
			i++;
		} while (i < Colonne1);

		Sujet1 = Lecture;

		iss.clear();
		iss.str(ligne);
		i = 0;

		do
		{
			getline(iss, Lecture, ':');
			i++;
		} while (i < Colonne2);

		Sujet2 = Lecture;

		/** DISCRETE OR CONTINUE **/
		getline(fichier, ligne);
		iss.clear();
		iss.str(ligne);

		i = 0;
		do
		{
			getline(iss, Lecture, ':');
			i++;
		} while (i < Colonne1);

		if(Lecture == "C")
			val1 = 2;
		else
			val1 = 1;

		iss.clear();
		iss.str(ligne);
		i = 0;
		do
		{
			getline(iss, Lecture, ':');
			i++;
		} while (i < Colonne2);

		if(Lecture == "C")
			val2 = 2;
		else
			val2 = 1;

		fichier.close();

		this->Source = new DataSourceSerie2D(Nom, Sujet1, Sujet2, val1, val2, NomFichier, Colonne1, Colonne2);
		cout << *Source;
	}
}


Echantillon::~Echantillon()
{
	if(this->Source != NULL)
		delete(this->Source);
}
DataSource* Echantillon::getSource() const
{
	return this->Source;
}

void Echantillon::setSource(DataSource *Data)
{
	Source = Data;
}

Echantillon& Echantillon::operator=(Echantillon const& v)
{
    setSource(v.getSource());

    return *this;
}
