#include <iostream>
#include <cstring>

#include "ListeTriee.h"
#include "Data1D.h"
using namespace std;


template <class T> ListeTriee<T>::ListeTriee()
{}


template <class T> ListeTriee<T>::~ListeTriee()
{}


template <class T> void ListeTriee<T>::Ajout(const T &element)
{
	Noeud<T> *pNew, *pPrec, *pTemp;
	float *temp;
	temp = new float(element);

	pNew = new Noeud<T>;

	if(pNew != NULL)
	{
		pNew->Type = temp; // Necessaire : operator=, constructeur c/c, operator<<

		if(this->pTete == NULL) //1er element de la liste
		{
			this->pTete = pNew;
			pNew->pSuivant = NULL;
		}
		else
		{
			pPrec = NULL;
			pTemp = this->pTete;

			while(pTemp != NULL && *pTemp->Type < *pNew->Type)
			{
				pPrec = pTemp;
				pTemp = pTemp->pSuivant;
			}
			
			if(pPrec == NULL) //insertion en debut de liste
			{
				pNew->pSuivant = this->pTete;
				this->pTete = pNew;
			}
			else
			{
				pNew->pSuivant = pTemp;
				pPrec->pSuivant = pNew;
			}
		}
	}
	else
		cout << "Erreur lors de l'allocation de memoire";
}

template <class T> void ListeTriee<T>::Suppression(const T &element)
{}

template class ListeTriee<float>;
