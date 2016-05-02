#include <iostream>
using namespace std;
#include "Utile/EtudeStatDescriptive.h"
#include "Utile/ExceptionBase.h"
#include "Utile/Data1D.h"
#include <QApplication>

QApplication* a;

int main(int argc,char* argv[])
{
	a = new QApplication(argc,argv);
	
	try
	{
		EtudeStatDescriptive E(argc,argv);
	}
	catch (ExceptionBase e)
	{
		cout << "Err. " << e.getMessage() << endl;
	}
}
