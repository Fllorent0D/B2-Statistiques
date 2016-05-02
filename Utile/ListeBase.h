#ifndef CLISTE_H_INCLUDED
#define CLISTE_H_INCLUDED

using namespace std;

template <class T> struct Noeud
{
	T *Type;
	Noeud<T> *pSuivant;
};

template <class T> class ListeBase
{
	protected:
		Noeud<T> *pTete;

	public:
		ListeBase();
		virtual ~ListeBase();
		virtual void Ajout(const T &element) = 0;
		virtual void Suppression(const T &element) = 0;
		void Affiche();
		int Size();
		T getElement(const int);
		bool vide();
		Noeud<T>* getpTete();
		void setpTete(Noeud<T>*);
		
};

#endif
