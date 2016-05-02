#ifndef CLISTES_H_INCLUDED
#define CLISTES_H_INCLUDED

#include "ListeBase.h"
template <class T> class Iterateur;
template <class T> class Liste : public ListeBase<T>
{
	public:
		Liste();
		Liste(const Liste<T>&);
		Liste(const Liste<T>*);
		~Liste();
		void Ajout(const T &element);
		void Suppression(const T &element);
		bool operator==(const T &element);
		friend class Iterateur<T>;
};

#endif
