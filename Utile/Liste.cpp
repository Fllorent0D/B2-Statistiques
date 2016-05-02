#include <iostream>
#include <cstring>
#include "Data1D.h"
#include "Data2D.h"
#include "Liste.h"

template <class T> Liste<T>::Liste()
{}

template <class T> Liste<T>::~Liste()
{}

template <class T> Liste<T>::Liste(const Liste<T>& l)
{
	this->pTete = NULL;
	Noeud<T> *parc;

	parc = l.pTete;

	while(parc != NULL)
	{
		this->Ajout(*parc->Type);
		parc = parc->pSuivant;
	}
}
template <class T> Liste<T>::Liste(const Liste<T>* l)
{
	this->pTete = NULL;
	Noeud<T> *parc;

	parc = l->pTete;

	while(parc != NULL)
	{
		this->Ajout(*parc->Type);
		parc = parc->pSuivant;
	}
}
template <class T> void Liste<T>::Ajout(const T &element)
{
	Noeud<T> *pNew;

	pNew = new Noeud<T>;
	pNew->Type = new T;

	if(pNew != NULL)
	{
		pNew->pSuivant = this->pTete;
		this->pTete = pNew;
		*(pNew->Type) = element; // Necessaire : operator=, constructeur c/c, operator<<
	}
	else
		cout << "Erreur lors de l'allocation de memoire";
}

template <class T> void Liste<T>::Suppression(const T &element)
{
	Noeud<T> *pTemp, *pPrec;

	pPrec = NULL;
	pTemp = this->pTete;

	if(*(pTemp->Type) == element)
	{
		pPrec = pTemp->pSuivant;
		delete pTemp;
		this->pTete = pPrec;
	}
	else
	{
		while(*(pTemp->Type) != element && pTemp != NULL)
		{
			pPrec = pTemp;
			pTemp = pTemp->pSuivant;
		}

		if(*(pTemp->Type) == element)
		{
			pPrec->pSuivant = pTemp->pSuivant;
			delete pTemp;
		}
	}
	
}


template class Liste<float>;
template class Liste<Data1D>;
template class Liste<Data2D>;
