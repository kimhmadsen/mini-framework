#ifndef DBPATIENT_H_
#define DBPATIENT_H_

#include <string>
#include "DbSignals.h"
#include "DbAnnotations.h"
#include "../PatientSignalIterator.h"
#include <wfdb/wfdb.h>

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
/*	string          getName();
	Sex             getSex();
	int             getAge();
*/
private:
	SignalIterator* _signalIterator;
	AnnotIterator* _annotIterator;

	char* _record;
};

#endif /*DBPATIENT_H_*/
