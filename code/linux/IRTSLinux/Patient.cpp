
/**
 * @file
 * Implements the Patient class
 */
#include "Patient.h"

using namespace std;

/**
 * Default constructor for the Patient class.
 */
Patient::Patient(DbPatient* dbPatient)
{
	_patient = dbPatient;
	samplefreq = _patient->getSampleFreq();
}

/**
 * Gets the patient information from the database
 */
string Patient::getInfo()
{
	return _patient->getInformation();
}

/**
 * Gets the number of samples of the ECG signals
 */
long Patient::getNumECGSamples()
{
	return _patient->getNumECGSamples();
}



/**
 * Gets the ECG values for the patient
 * @return A pointer to the iterator containing the ecg values.
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

/**
 * Gets and object to calculate EDR
 * @return EdrGenerator
 */
EdrGenerator*	Patient::getEdrGenerator()
{
	return _patient->getEdrGenerator();
}

/**
 * Gets the name (or patient record id) of the patient
 * @return string name
 */
string Patient::getName()
{
	return _patient->getName();
}

/**
 * Gets the sex of the patient
 * @return enum Sex
 */
Sex Patient::getSex()
{
	return _patient->getSex();
}

/**
 * Gets the age of the patient
 * @return integer representing years. Returns -1 if the age is not known.
 */
int Patient::getAge()
{
	return _patient->getAge();
}
