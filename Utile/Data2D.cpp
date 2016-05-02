#include <iostream>
#include <string>

using namespace std;

#include "Data2D.h"

Data2D::Data2D()
{
	setVal1(0.0);
	setVal2(0.0);
}

Data2D::Data2D(const float V1, const float V2)
{
	setVal1(V1);
	setVal2(V2);
}

Data2D::Data2D(const Data2D &CD2)
{
	setVal1(CD2.getVal1());
	setVal2(CD2.getVal2());
}

Data2D::~Data2D()
{}

void Data2D::setVal1(const float V1)
{
	Val1 = V1;
}

void Data2D::setVal2(const float V2)
{
	Val2 = V2;
}

float Data2D::getVal1() const
{
	return Val1;
}

float Data2D::getVal2() const
{
	return Val2;
}

Data2D& Data2D::operator=(Data2D const& c)
{
	setVal1(c.getVal1());
	setVal2(c.getVal2());
	return *this;
}

ostream &operator<<(ostream &flux, Data2D const& CD2)
{
    flux << "(" << CD2.getVal1() << ", " << CD2.getVal2() << ")";
    return flux;
}

bool Data2D::operator==(Data2D const& v)
{
	if(this -> Val1 == v.Val1 || this -> Val2 == v.Val2)
		return true;
	return false;
}

bool Data2D::operator!=(Data2D const& v)
{

	if(this -> Val1 != v.Val1 || this -> Val2 != v.Val2)
		return true;
	return false;
}


