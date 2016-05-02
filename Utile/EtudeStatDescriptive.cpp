#include "EtudeStatDescriptive.h"
#include "ExceptionBase.h"
#include "EtudeStat1D.h"
#include "EtudeStat2D.h"
#include <string.h>

EtudeStatDescriptive::EtudeStatDescriptive(int argc, char*argv[])
{

	if (argc == 2)
	   EtudeStat1D E(argv[1],0);
	if (argc == 3)
	   EtudeStat1D E(argv[1],atoi(argv[2]));
	if (argc == 4)
	   EtudeStat2D E(argv[1],atoi(argv[2]),atoi(argv[3]));
	else 
	{
		char *msg = new char[19];
		strcpy(msg, "mauvais parametres");
		throw ExceptionBase(msg);
	}
}



