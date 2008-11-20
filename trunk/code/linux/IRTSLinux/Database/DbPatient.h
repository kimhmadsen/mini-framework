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
	DbPatient(string record);
	virtual ~DbPatient();
	SignalIterator* getSignals();
	AnnotIterator*  getAnnotations();
	string          getName();
	Sex             getSex();
	int             getAge();

private:
	DbSignals* _signals;
	DbAnnotations* _annotations;
	SignalIterator* _signalIterator;
	AnnotIterator* _annotIterator;

	WFDB_Sample _sample[2];
	WFDB_Siginfo _sigInfo[2];
};

#endif /*DBPATIENT_H_*/
