#include "DbPatient.h"
#include <wfdb/wfdb.h>

DbPatient::DbPatient(char* record)
{
	_record = record;
	DbSignals* signals = new DbSignals(_record);
	DbAnnotations* annotations = new DbAnnotations(_record);
	_signalIterator = new SignalIterator(signals);
	_annotIterator = new AnnotIterator(annotations);

}
DbPatient::~DbPatient(){}

string DbPatient::getInformation()
{
	string info = "";
	char* infoPart = getinfo(_record);

	if ((infoPart = getinfo(_record)))
	{
		do {

	        info.append(infoPart);
	    } while ((infoPart = getinfo(NULL)));

	}
	return info;
}
double DbPatient::getSampleFreq()
{
	return sampfreq(_record);
}

/*
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
*/
SignalIterator* DbPatient::getSignals()
{
	return _signalIterator;
}

AnnotIterator*  DbPatient::getAnnotations()
{
	return _annotIterator;
}

