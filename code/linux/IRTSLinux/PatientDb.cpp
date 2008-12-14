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


PatientDb::PatientDb()
{
	_patients.push_back("100s");
	_patients.push_back("101");
	_patients.push_back("102");
	_patients.push_back("103");

/*	DbPatient* dbPatient0 = new DbPatient("100s");
	Patient* patient0 = new Patient(dbPatient0);
	_patientVector.push_back(patient0);

	DbPatient*  dbPatient1 = new DbPatient("101");
	Patient* patient1 = new Patient(dbPatient1);
	_patientVector.push_back(patient1);

	DbPatient* dbPatient2 = new DbPatient("102");
	Patient* patient2 = new Patient(dbPatient2);
	_patientVector.push_back(patient2);

	DbPatient* dbPatient3 = new DbPatient("103");
	Patient* patient3 = new Patient(dbPatient3);
	_patientVector.push_back(patient3);

	DbPatient* dbPatient4 = new DbPatient("104");
	Patient* patient4 = new Patient(dbPatient4);
	_patientVector.push_back(patient4);

	DbPatient* dbPatient5 = new DbPatient("105");
	Patient* patient5 = new Patient(dbPatient5);
	_patientVector.push_back(patient5);

	DbPatient* dbPatient6 = new DbPatient("106");
	Patient* patient6 = new Patient(dbPatient6);
	_patientVector.push_back(patient6);

	DbPatient*	dbPatient7 = new DbPatient("107");
	Patient* patient7 = new Patient(dbPatient7);
	_patientVector.push_back(patient7);

	DbPatient* dbPatient8 = new DbPatient("108");
	Patient* patient8 = new Patient(dbPatient8);
	_patientVector.push_back(patient8);

	DbPatient* dbPatient9 = new DbPatient("109");
	Patient* patient9 = new Patient(dbPatient9);
	_patientVector.push_back(patient9);

*/

}

/**
 * Get the patient list
 * @TODO: implement
 */
string PatientDb::GetPatientList()
{
	string list = "";
/*	if( _patientVector.size() > 0 )
	{
		vector<Patient*>::iterator it;
		for ( it=_patientVector.begin() ; it < _patientVector.end(); it++ )
		{
			Patient* patient = *it;
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
*/
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
 *
 * @TODO: implement
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
/*	if( _patientVector.size() > 0 )
	{
		vector<Patient*>::iterator it;
		for ( it=_patientVector.begin() ; it < _patientVector.end(); it++ )
		{
			Patient* patient = *it;
			if(strcmp(patient->getName().c_str(), name.c_str())==0)
				return *it;
		}

	}
*/
	else
		return NULL;
}



