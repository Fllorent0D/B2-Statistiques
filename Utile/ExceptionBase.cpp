#include "ExceptionBase.h"
#include <string.h>
ExceptionBase::ExceptionBase()
{
	message = NULL;
}

ExceptionBase::ExceptionBase(int argc,char** argv)
{
	message = NULL;
}
ExceptionBase::ExceptionBase(char** msg)
{
	strcpy(message, *msg);
}
ExceptionBase::ExceptionBase(char* msg)
{
	strcpy(message,msg);
}

ExceptionBase::~ExceptionBase()
{
	if(message) delete message;
}

char * ExceptionBase::getMessage() const
{
	return message;
}