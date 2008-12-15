
/**
 * @file
 * Defines the Patient class
 */
#ifndef PATIENT_H_
#define PATIENT_H_

#include <vector>
#include <string>
#include "PatientSignalIterator.h"
#include "SignalValue.h"
#include "Database/DbPatient.h"
#include "EdrGenerator.h"

using namespace std;


/**
 * Implements a simulated patient
 *
 */
class Patient
{
 public:
	Patient(DbPatient*);

	string          getName();
	Sex             getSex();
	int             getAge();

	string 			getInfo();
	SignalIterator*	getECG();
	AnnotIterator*	getAnn();
	EdrGenerator*	getEdrGenerator();
	long 			getNumECGSamples();

	double          samplefreq;

 private:
	DbPatient* _patient;

};

#endif /*PATIENT_H_*/


