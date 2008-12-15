
/**
 * @file
 * Implements the DbPatient class
 */
#include "DbPatient.h"
#include <wfdb/wfdb.h>
#include <sstream>

/**
 * Constructor for DbPatient
 * @param record record name of the database
 */
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

/**
 * Default destructor for DbPatient
 */
DbPatient::~DbPatient(){}

/**
 * Gets the number of samples in the signal file
 * @return number of samples
 */
long DbPatient::getNumECGSamples()
{
	return _ECGsize;
}

/**
 * Gets the information string from the database
 * @return information string
 */
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

/**
 * Gets the sample frequency for the ECG signals
 * @return sample frequency
 */
double DbPatient::getSampleFreq()
{
	return sampfreq(_record);
}

/**
 * Gets and object to calculate EDR
 * @return EdrGenerator
 */
EdrGenerator* DbPatient::getEdrGenerator()
{
	return _edrGenerator;
}

/**
 * Gets the name (or patient record id) of the patient
 * @return string name
 */
string DbPatient::getName()
{
	return _record;
}

/**
 * Gets the age of the patient
 * @return integer representing years. Returns -1 if the age is not known.
 */
int DbPatient::getAge()
{
	return _age;
}

/**
 * Gets the sex of the patient
 * @return enum Sex
 */
Sex DbPatient::getSex()
{
	return _sex;
}

/**
 * Gets a pointer to the iterator for the signals
 * @return SignalIterator
 */
SignalIterator* DbPatient::getSignals()
{
	return _signalIterator;
}


/**
 * Gets a pointer to the iterator for the annotations
 * @return AnnotIterator
 */
AnnotIterator*  DbPatient::getAnnotations()
{
	return _annotIterator;
}

