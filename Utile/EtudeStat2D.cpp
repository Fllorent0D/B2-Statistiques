#include <math.h>
#include "EtudeStat2D.h"
extern QApplication* ap;
#include "graphstat2d.h" 
#include <math.h>
#include "DataSourceSerie2D.h"
EtudeStat2D::EtudeStat2D()
{
}

EtudeStat2D::EtudeStat2D(const EtudeStat2D& Etude)
{

}

EtudeStat2D::EtudeStat2D(const char* NomFichier,int Colonne1, int Colonne2)
{
	E = new Echantillon(NomFichier, Colonne1, Colonne2);
	setMoyenne1();
	setMoyenne2();
	setAB();
	//AfficheRapport();
	Affiche();
}
Echantillon* EtudeStat2D::getE()
{
	return E;
}

EtudeStat2D::~EtudeStat2D()
{
    
}
void EtudeStat2D::setA(const float a)
{
	this->a = a;
}
void EtudeStat2D::setB(const float b)
{
	this->b = b;
}
float EtudeStat2D::getA()
{
	return a;
}
float EtudeStat2D::getB()
{
	return b;
}
void EtudeStat2D::setCorrel(const float c)
{
	this->Correl = c;
}
void EtudeStat2D::Affiche()
{
	pthread_t threadHandle;
	pthread_create(&threadHandle,NULL,(void*(*)(void*))EtudeStat2D::calculPrevision,this);

	GraphStat2D w(this);
  	w.show();
  	ap->exec();
}
void* EtudeStat2D::calculPrevision(void* param)
{
	bool Continuer = true;
	char	Buffer[255];

	EtudeStat2D* etude = static_cast<EtudeStat2D*>(param);
	DataSourceSerie2D* Se2D = static_cast<DataSourceSerie2D*>(etude->getE()->getSource());
	while(Continuer)
	{
		float val = 0, reponse = 0;
		etude->AfficheRapport();
		cout << endl << endl;
		cout << "PREVISIONS" << endl;
		cout << "-----------"<<endl;
		cout << "1. Prevision pour " << Se2D->getSujet() << " " << endl;
		cout << "2. Prevision pour " << Se2D->getSujet2() << " " << endl;

		char choix = 'q';
		cout << endl << "\tChoix : ";
		cin >> choix;
		//cin.ignore();

		switch (choix)
		{				
			case '1' :
				cout << endl << "\tEntrer la valeur pour " << Se2D->getSujet() << " : ";
				cin >> val;
				reponse = etude->Xi(val);
				cout << endl << "\tValeur prevue : " << reponse << endl;
				break;

			case '2' :
				cout << endl << "\tEntrer la valeur pour " << Se2D->getSujet2() << " : ";
				cin >> val;
				reponse = etude->Yi(val);
				cout << endl << "\tValeur prevue : " << reponse << endl;
				break;

			default :
				break;
		}
		cout << "\tAppuyer sur un enter pour continuer..." ;
		std::cin.ignore();
		std::cin.ignore();

	}
}
float EtudeStat2D::Xi(const float x)
{
	return getA() * x + getB();
}

float EtudeStat2D::Yi(const float y)
{
	return (y - getB()) / getA();
}
void EtudeStat2D::setMoyenne1()
{
	DataSourceSerie2D *data;
	Liste<Data2D> *L;
	Noeud<Data2D> *pTemp;
	float temp = 0;
	//L = getE()->getSource()->getL();
	data = dynamic_cast<DataSourceSerie2D*>((getE())->getSource());
	if(data != NULL)
	{
		L = data->getL();
		pTemp = L->getpTete();

		while(pTemp != NULL)
		{
			temp += pTemp->Type->getVal1();
			pTemp = pTemp->pSuivant;
		}

		temp /= data->getEffTotal();
		moyenne1 = temp;
	}
	else
	{
		cout << "\nERREUR - Probleme au niveau du dynamic cast pour la MOYENNE 2" << endl;
		exit(0);
	}

}
void EtudeStat2D::setMoyenne2()
{
	DataSourceSerie2D *data;
	Liste<Data2D> *L;
	Noeud<Data2D> *pTemp;
	float temp = 0;
	//L = getE()->getSource()->getL();
	data = dynamic_cast<DataSourceSerie2D*>((getE())->getSource());
	if(data != NULL)
	{
		L = data->getL();
		pTemp = L->getpTete();

		while(pTemp != NULL)
		{
			temp += pTemp->Type->getVal2();
			pTemp = pTemp->pSuivant;
		}

		temp /= data->getEffTotal();
		moyenne2 = temp;
	}
	else
	{
		cout << "\nERREUR - Probleme au niveau du dynamic cast pour la MOYENNE 2" << endl;
		exit(0);
	}
}
float EtudeStat2D::getMoyenne1()
{
	return moyenne1;
}
float EtudeStat2D::getMoyenne2()
{
	return moyenne2;
}
void EtudeStat2D::AfficheRapport()
{
  printf ("\033c");
  cout << "******* RAPPORT DE L'ETUDE ********\n" << endl;
  cout << *(E->getSource()) << endl;
  cout << endl << "Moyenne val 1 : " << getMoyenne1() << endl;
  cout << "Moyenne val 2 : " << getMoyenne2() << endl << endl;
  cout << "Corrélation : " << endl;
  cout << "\tCoéficient a : " << getA() << endl;
  cout << "\tCoéficient b : " << getB() << endl;


}
void EtudeStat2D::setAB()
{
	DataSourceSerie2D* SeCon;
	Noeud<Data2D> *pTemp;
	float   SommeXiYi = 0, 
			SommeXi = 0, 
			SommeYi = 0, 
			SommeXi2 = 0, 
			SommeYi2 = 0 , 
			tmp = 0, 
			top = 0, 
			botX = 0, 
			botY = 0, 
			a = 0 ;
	SeCon = dynamic_cast<DataSourceSerie2D*>((getE())->getSource());
	if(SeCon != NULL)
	{
		pTemp = SeCon->getL()->getpTete();

		while(pTemp != NULL)
		{
			SommeXiYi += pTemp->Type->getVal1() * pTemp->Type->getVal2(); // Somme de XiYi
			SommeXi += pTemp->Type->getVal1(); // Somme de Xi
			SommeYi += pTemp->Type->getVal2(); // Somme de Yi
			SommeXi2 += pow(pTemp->Type->getVal1(), 2); // Somme de Xi2
			SommeYi2 += pow(pTemp->Type->getVal2(), 2); // Somme de Yi2
			pTemp = pTemp->pSuivant;
		}

		botX = SommeXi2 - pow(SommeXi, 2) / SeCon->getEffTotal();
		botY = SommeYi2 - pow(SommeYi, 2) / SeCon->getEffTotal();
		top = SommeXiYi - SommeXi * SommeYi / SeCon->getEffTotal();

		tmp = top / (sqrt(botX * botY));
		setCorrel(tmp);

		tmp = top / botX;
		setA(tmp);
		a = tmp;
// y = a x + b

		tmp = getMoyenne2() - a * getMoyenne1();
		setB(tmp);
	}
	else
	{
		cout << "\nERREUR - Probleme au niveau du dynamic cast pour la CAB" << endl;
		exit(0);
	}

}
