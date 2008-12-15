
/**
 * @file
 * Defines the PatientDb class
 */
#ifndef PATIENTDB_H_
#define PATIENTDB_H_

#include <string.h>
#include <iostream>
#include <vector>
#include "Patient.h"
using namespace std;

/**
 * Patient database which holds all the patients
 *
 */
class PatientDb
{
public:
	static PatientDb* Instance();
	string GetPatientList();
	Patient* GetPatient( char* name );
	vector<Patient*> _patientVector;
	vector<char*> _patients;

protected:
	PatientDb();


private:
	static PatientDb* _instance;



};

#endif /*PATIENTDB_H_*/
