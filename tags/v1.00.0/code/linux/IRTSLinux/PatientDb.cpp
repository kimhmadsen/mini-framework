
/**
 * @file
 * Implements the PatientDb class
 */
#include "PatientDb.h"
#include <stdlib.h>
#include <sstream>
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

/**
 * Default constructor for PatientDb
 */
PatientDb::PatientDb()
{
	_patients.push_back("100s");
	_patients.push_back("101");
	_patients.push_back("102");
	_patients.push_back("103");
	_patients.push_back("104");
	_patients.push_back("105");
	_patients.push_back("106");
	_patients.push_back("107");
	_patients.push_back("108");
	_patients.push_back("109");

}

/**
 * Get the patient list
 * @return a string with patient info in each line
 */
string PatientDb::GetPatientList()
{
	string list = "";
	if( _patients.size() > 0 )
	{
		vector<char*>::iterator it;
		for ( it=_patients.begin() ; it < _patients.end(); it++ )
		{
			Patient* patient = new Patient(new DbPatient((*it)));
			list.append(patient->getName());
			list.append(" ");

			stringstream out;
			out << patient->getAge();
			list.append(out.str());
			list.append(" ");
			if(patient->getSex() == male)
				list.append("M");
			else
				list.append("F");
			list.append("\n");

		}

		return list;
	}
	else
		return "";

}

/**
 * Gets a patient from the patients database
 * @param name
 * @return the patient object
 */
Patient* PatientDb::GetPatient( char* name )
{

	if(_patients.size() > 0 )
	{
		vector<char*>::iterator it;
		for ( it=_patients.begin() ; it < _patients.end(); it++ )
		{
			if(strcmp(*it, name)==0)
				return new Patient(new DbPatient((*it)));
		}
	}
	else
		return NULL;
}



