#ifndef ETUDESTATDATA2D
#define ETUDESTATDATA2D

#include <iostream>
#include <stdlib.h>
#include "Echantillon.h"
#include <QApplication>

class EtudeStat2D
{
private:
	Echantillon* E;
	float moyenne1;
	float moyenne2;
	float a;
	float b;
	float Correl;

public:
	EtudeStat2D();

	EtudeStat2D(const EtudeStat2D&);

	EtudeStat2D(const char* ,int , int);

	~EtudeStat2D();
	Echantillon * getE();
	void Affiche();
	void setMoyenne1();
	void setMoyenne2();
	void setAB();
	void setA(const float);
	void setB(const float);
	void setCorrel(const float);
	float getB();
	float getA();
	float getMoyenne1();
	float getMoyenne2();
	float Yi(const float y);
	float Xi(const float y);
	void AfficheRapport();
	static void* calculPrevision(void *);
};

#endif