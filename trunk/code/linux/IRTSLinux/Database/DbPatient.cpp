#include "DbPatient.h"
#include <wfdb/wfdb.h>
#include <sstream>


DbPatient::DbPatient(char* record)
{
	_record = record;
	DbSignals* signals = new DbSignals(_record);
	DbAnnotations* annotations = new DbAnnotations(_record);
	_ECGsize = signals->Size();
	_signalIterator = new SignalIterator(signals);
	_annotIterator = new AnnotIterator(annotations);
	DbEdr* dbEdr = new DbEdr(_record);
	_edrGenerator = new EdrGenerator(dbEdr);


	//Get age and sex
	//cout << "record " << _record << endl;
	string info = getinfo(_record);
	//cout << "info: " << info << endl;
	string buf; // Have a buffer string
	stringstream ss(info); // Insert the string into a stream
    vector<string> tokens; // Create vector to hold our words
	while (ss >> buf)
	{
		//cout << "info strings: " << buf << endl;
		tokens.push_back(buf);
	}

	_age = atoi(tokens[0].c_str());
	_sex = tokens[1][0] == 'M'? male: female;



}
DbPatient::~DbPatient(){}

long DbPatient::getNumECGSamples()
{
	return _ECGsize;
}
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
EdrGenerator* DbPatient::getEdrGenerator()
{
	return _edrGenerator;
}

string DbPatient::getName()
{
	return _record;
}
int DbPatient::getAge()
{
	return _age;
}

Sex DbPatient::getSex()
{
	return _sex;
}

SignalIterator* DbPatient::getSignals()
{
	return _signalIterator;
}

AnnotIterator*  DbPatient::getAnnotations()
{
	return _annotIterator;
}

