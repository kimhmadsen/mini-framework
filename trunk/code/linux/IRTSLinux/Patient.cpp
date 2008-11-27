/**
 *
 *
 */
#include "Patient.h"

using namespace std;

/**
 * Default constructor for the Patient class.
 */
Patient::Patient(DbPatient* dbPatient)
{
	_patient = dbPatient;
}
string Patient::getInfo()
{
	return _patient->getInformation();
}



/**
 * Gets the ECG values for the patient
 * @return A pointer to the vector containing the ecg values.
 */
SignalIterator* Patient::getECG()
{
	return _patient->getSignals();
}

/**
 * Gets the Annotation values for the patient
 * @return The reference the the vector with annotation values.
 */
AnnotIterator* Patient::getAnn()
{
	return  _patient->getAnnotations();
}

