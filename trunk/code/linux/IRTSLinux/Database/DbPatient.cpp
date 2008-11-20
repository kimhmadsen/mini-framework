#include "DbPatient.h"

DbPatient::DbPatient(string record)
{
	 if (isigopen(record, _sigInfo, 2) < 2) return 0;
	 char* description;


}
DbPatient::~DbPatient(){}

string DbPatient::getName()
{
	return "";
}
int DbPatient::getAge()
{
	return 1;
}

Sex DbPatient::getSex()
{
	return male;
}

SignalIterator* DbPatient::getSignals()
{
	return _signalIterator;
}

AnnotIterator*  DbPatient::getAnnotations()
{
	return _annotIterator;
}

