#include <iostream>
#include <cstring>

#include "ListeBase.h"
#include "Data1D.h"
#include "Data2D.h"

using namespace std;

template <class T> ListeBase<T>::ListeBase()
{
	pTete = NULL;
}

template <class T> ListeBase<T>::~ListeBase()
{
	if(pTete)
		delete pTete;
}

template <class T> void ListeBase<T>::Affiche()
{
	Noeud<T> *pTemp;

	pTemp = this->pTete;

	while(pTemp != NULL)
	{
		cout << *(pTemp->Type) << endl;
		pTemp = pTemp->pSuivant;
	}
}

template <class T> T ListeBase<T>::getElement(const int i)
{
	int cpt(0);
	Noeud<T> *pTemp;

	pTemp = this->pTete;

	while(pTemp->pSuivant != NULL && cpt < i)
	{
		cpt++;
		pTemp = pTemp->pSuivant;
	}

	return *pTemp->Type;
}

template <class T> int ListeBase<T>::Size()
{
	Noeud<T> *pTemp;
	int i = 0;

	pTemp = this->pTete;

	while(pTemp != NULL)
	{
		i++;
		pTemp = pTemp->pSuivant;
	}

	return i;
}

template <class T> bool ListeBase<T>::vide()
{
	if(pTete)
		return false;
	else
		return true;
}

template <class T> Noeud<T>* ListeBase<T>::getpTete()
{
    return pTete;
}

template <class T> void ListeBase<T>::setpTete(Noeud<T>* pTemp)
{
	pTete = pTemp;
}

template class ListeBase<float>;
//template class ListeBase<Data>;
template class ListeBase<Data1D>;
template class ListeBase<Data2D>;
