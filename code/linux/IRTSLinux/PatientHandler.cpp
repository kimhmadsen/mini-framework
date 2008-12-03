/*
 * PatientHandler.cpp
 *
 *  Created on: mar 31, 2008
 *      Author: MSO
 */

#include "PatientHandler.h"
#include "PatientSignalIterator.h"
#include "PatientDb.h"
#include <iostream>
#include <pthread.h>
/*
 * Default constructor
 */

PatientHandler::PatientHandler(Patient* patient)
{
	_patient = patient;
	//_taskDiscrete_id = -1;
	//_taskContinuous_id = -1;
	_lastECG = 0;
}

/*
 * Default destructor
 */
PatientHandler::~PatientHandler()
{

}

void PatientHandler::start()
{
	int s = pthread_create(&_continuousThread, NULL, tcontinuous_wrapper,  (void *)int(this));


	//_taskDiscrete_id = taskSpawn("taskDiscrete",150,0x08,7000,(FUNCPTR)PatientHandler::tdiscrete_wrapper, int(this),0,0,0,0,0,0,0,0,0);
	//_taskContinuous_id = taskSpawn("taskContinuous",150,0x08,7000,(FUNCPTR)PatientHandler::tcontinuous_wrapper, int(this),0,0,0,0,0,0,0,0,0);
}

void PatientHandler::stop()
{
	int s = pthread_cancel(_continuousThread);

	//taskDelete(_taskContinuous_id);
	//taskDelete(_taskDiscrete_id);
}

//static wrapper function to callback non-static member function
void* PatientHandler::tcontinuous_wrapper(void* thisObject)
{
	int s = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	// explicit cast pointer to Class pointer
	PatientHandler* myself = (PatientHandler*) thisObject;
	// call member function
	myself->task_continuous();
}

//static wrapper function to callback non-static member function
void PatientHandler::tdiscrete_wrapper(void* thisObject)
{
	// explicit cast pointer to Class pointer
	PatientHandler* myself = (PatientHandler*) thisObject;
	// call member function
	myself->task_discrete();
}

void PatientHandler::task_continuous()
{

	SignalIterator* iterator = _patient->getECG();
	SignalValue signalValue;
	int counter = 0;

	while(true)
	{
		signalValue = iterator->CurrentItem();

		if(counter== 0)
		{
			_lastECG = signalValue.value;
			Notify(Observer::ECG);
		}

		counter++;
		if (counter == 10) counter = 0;

		iterator->Next();
		sleep(1.0/(double)_patient->samplefreq);
	}


}

float PatientHandler::getECG(){
	return _lastECG;
}
void PatientHandler::task_discrete()
{
	AnnotIterator* iterator = _patient->getAnn();
	AnnotValue annotValue;

	AnnotValue next_annotValue = iterator->CurrentItem();
	while(true)
	{
		annotValue = next_annotValue;;

		//cout << "pulse " << annotValue.time << " " << annotValue.value << " " << annotValue.sample <<"\n"; //print pulse

		iterator->Next();
		next_annotValue = iterator->CurrentItem();
		sleep(next_annotValue.time - annotValue.time);
	}

}




int PatientHandler::edr(long t0, long t1)
{
	/*
	double x , y;
	for(x = y =0.0; t0 <= t1; t0++)
	{

	}
	*/
	return 0;
}
// create a simple delay routine
unsigned PatientHandler::sleep(double seconds)
{
	return 0;
	//return (int) taskDelay((int) (seconds*(double)sysClkRateGet()));
}
