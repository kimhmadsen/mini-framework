#ifndef PATIENT_H_
#define PATIENT_H_

#include <vector>
#include <string>
#include "PatientSignalIterator.h"
#include "SignalValue.h"
#include "Database/DbPatient.h"
using namespace std;


class Patient
{
 public:
	Patient(DbPatient*);

	string          getName();
	Sex             getSex();
	int             getAge();
	SignalIterator*	getECG();
	AnnotIterator*	getAnn();

	int                  samplefreq;

 private:
	DbPatient* _patient;

};

#endif /*PATIENT_H_*/

