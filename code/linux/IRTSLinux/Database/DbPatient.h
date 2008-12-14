#ifndef DBPATIENT_H_
#define DBPATIENT_H_

#include <string>
#include "DbSignals.h"
#include "DbAnnotations.h"
#include "../PatientSignalIterator.h"
#include "../EdrGenerator.h"
#include <wfdb/wfdb.h>
#include "DbEdr.h"

using namespace std;

enum Sex {male, female};

class DbPatient
{
public:
	DbPatient(char* record);
	virtual ~DbPatient();
	SignalIterator* getSignals();
	AnnotIterator*  getAnnotations();
	string          getInformation();
	double			getSampleFreq();
	long			getNumECGSamples();
	EdrGenerator*	getEdrGenerator();
	string          getName();
	Sex             getSex();
	int             getAge();

private:
	SignalIterator* _signalIterator;
	AnnotIterator*  _annotIterator;
	EdrGenerator*	_edrGenerator;
	long			_ECGsize;
	Sex				_sex;
	int				_age;

	char* _record;
};

#endif /*DBPATIENT_H_*/
