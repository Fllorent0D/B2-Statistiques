#ifndef EXCEPTIONBASE
#define EXCEPTIONBASE

#include <iostream>
#include <stdlib.h>

class ExceptionBase
{
private:
	char* message;
public:
	ExceptionBase();
	ExceptionBase(int,char**);
	ExceptionBase(char**);
	ExceptionBase(char*);
	~ExceptionBase();
	char * getMessage() const;
};

#endif