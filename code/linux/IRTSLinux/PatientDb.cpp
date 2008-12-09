#include "PatientDb.h"

/**
 * Reference to and instance of the this class for implementing the singleton pattern.
 */
PatientDb* PatientDb::_instance = 0;

/**
 * Function for getting the PatientDb singleton.
 *
 * @remark This function is not thread safe!
 * @return Reference the the singleton.
 */
PatientDb* PatientDb::Instance()
{
	if( _instance == 0 )
	{
		_instance = new PatientDb;
	}
	return _instance;
}


PatientDb::PatientDb()
{
	DbPatient* dbPatient = new DbPatient("100s");
	Patient* patient = new Patient(dbPatient);
	_patientVector.push_back(patient);
}

/**
 * Get the patient list
 * @TODO: implement
 */
string PatientDb::GetPatientList()
{
	int n_patients = _patientVector.size();

	if( n_patients > 0 )
	{
		return _patientVector[0]->getInfo();
	}
	return "NO patients in the Database";
}

/**
 *
 * @TODO: implement
 */
Patient* PatientDb::GetPatient( string id )
{
	if( _patientVector.size() > 0 )
	{
		Patient* patientToReturn = _patientVector.front();
		return patientToReturn;
	}
	else
		return NULL;
}



