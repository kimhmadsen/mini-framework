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
		return _patientVector[0]->getName();
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
		return _patientVector[0];
	else 
		return NULL;
}



