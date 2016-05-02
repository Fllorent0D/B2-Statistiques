#include <iostream>
#include <string>

#include "Data1D.h"

using namespace std;

Data1D::Data1D()
{
	setEff(0);
	setVal(0.0);
}

Data1D::Data1D(const float val, const int eff)
{
	setVal(val);
	setEff(eff);
}

Data1D::Data1D(const Data1D & v)
{
	setVal(v.getVal());
	setEff(v.getEff());
}

Data1D::~Data1D()
{}

void Data1D::setVal(const float val)
{
	Val = val;
}

void Data1D::setEff(const int Ef)
{
	Eff = Ef;
}

int Data1D::getEff() const
{
	return Eff;
}
void Data1D::Affiche()
{
	printf("%d\n", getEff());
	printf("%f\n", getVal());
}
float Data1D::getVal() const
{
	return Val;
}

/******* OPERATORS *****/
ostream &operator<<(ostream &flux, Data1D const& CD1)
{
    flux << "("<< CD1.getVal() << ", " << CD1.getEff() << ")";
    return flux;
}

Data1D& Data1D::operator=(Data1D const& c)
{
	setVal(c.getVal());
	setEff(c.getEff());
	return *this;
}

bool Data1D::operator==(Data1D const& v)
{
	if(getVal() == v.getVal())
		return true;
	
	return false;
}

bool Data1D::operator!=(Data1D const& v)
{
	if(getVal() == v.getVal())
		return false;
	return true;
}

