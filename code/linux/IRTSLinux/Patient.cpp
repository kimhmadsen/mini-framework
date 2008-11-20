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
}

/**
 * Get the name of the patient.
 * @return The name of the patient
 */
string Patient::getName()
{
  return _patient->getName();
}

/**
 * Get the sex of the patient
 * @return the sex of the patient
 */
Sex Patient::getSex()
{
  return _patient->getSex();
}


/**
 * Get the age of the patient
 * @return the age of the patient
 */
int Patient::getAge()
{
  return _patient->getAge();
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

