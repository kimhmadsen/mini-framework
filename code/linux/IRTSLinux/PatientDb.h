#ifndef PATIENTDB_H_
#define PATIENTDB_H_

#include <string.h>
#include <iostream>
#include <vector>
#include "Patient.h"
using namespace std;

class PatientDb
{
public:
	static PatientDb* Instance();
	string GetPatientList();
	Patient* GetPatient( string id );

	vector<Patient*> _patientVector;

protected:
	PatientDb();

private:
	static PatientDb* _instance;

};

#endif /*PATIENTDB_H_*/
