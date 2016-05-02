#ifndef CLISTETRIEE_H_INCLUDED
#define CLISTETRIEE_H_INCLUDED

#include "ListeBase.h"

template <class T> class ListeTriee : public ListeBase<T>
{
public:
	ListeTriee();
	virtual ~ListeTriee();
	void Ajout(const T &element);
	void Suppression(const T &element);
};

#endif
