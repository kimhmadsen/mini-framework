/**
 * @file
 * Implements the PatientHandler class
 */
#include "PatientHandler.h"
#include "PatientSignalIterator.h"
#include "PatientDb.h"
#include "EdrGenerator.h"
#include <iostream>
#include <pthread.h>



static long bbuf[2][VBL];
static int nsig = 2;

/*
 * Default constructor
 */

PatientHandler::PatientHandler(Patient* patient)
{
	setPatient(patient);
	_lastECG = 0;
	_lastEDR = 0;
	_lastPulse = 0;

	_running = false;

	//creation of timer
	_sig_spec.sigev_notify = SIGEV_SIGNAL;
	_sig_spec.sigev_signo = SIGRTMAX;
	_sig_spec.sigev_value.sival_int = int(this);


	//note: replace NULL for _sig_spec
	if (timer_create (CLOCK_REALTIME, &_sig_spec, &_timerid)<0 )
		cout << "timer create";

	struct sigaction action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handler_wrapper;
	sigemptyset (&action.sa_mask);

	if(sigaction(_sig_spec.sigev_signo, &action, NULL))
		cout << "timer not connected";

}

/*
 * Default destructor
 */
PatientHandler::~PatientHandler()
{
	if (timer_delete (_timerid)<0 )
			cout << "timer delete";

}

void PatientHandler::start()
{
	_value.it_value.tv_sec = 0;
	_value.it_value.tv_nsec = 1;

	double interval = (double)1E9/(double)_patient->samplefreq;
	_value.it_interval.tv_sec = (long)interval/(long)1E9;
	_value.it_interval.tv_nsec = (long)interval%(long)1E9;

	if (timer_settime (_timerid, 0, &_value, NULL)<0 )
		cout << "timer settime";

	_running = true;

	Notify(Observer::STATE_CHANGE);
}

void PatientHandler::setPatient( Patient* patient )
{
	_patient = patient;
	_iterator = _patient->getECG();
	_pulseIterator = _patient->getAnn();
	_edrGenerator = _patient->getEdrGenerator();

	Notify(Observer::PATIENT_CHANGE);

}

void PatientHandler::stop()
{
	_value.it_value.tv_sec = 0;
	_value.it_value.tv_nsec = 0;

	_value.it_interval.tv_sec = 0;
	_value.it_interval.tv_nsec = 0;

	if (timer_settime (_timerid, 0, &_value, NULL)<0 )
			cout << "timer settime";

	_running = false;

	Notify(Observer::STATE_CHANGE);
}

/**
 * Static wrapper for the handler of the timer
 * @param timerid Id of the timer
 * @param pointerToObject pointer to "this" (PatientHandler)
 */
void PatientHandler::handler_wrapper(int signo, siginfo_t *info, void *notUsed)
{
	PatientHandler* myself = (PatientHandler*) (info->si_value.sival_int);
	myself->handler();
}

/**
 * Handler the timer signal and has all the logic
 */
void PatientHandler::handler()
{
	bool pulse = false;
	bool ecg = false;
	//struct timespec time_beginning;
	//struct timespec time_end;

	SignalValue signalValue;
	AnnotValue pulseValue;
	static int counter = 0;
	static float lastPulseTime = 0;

	//clock_gettime(CLOCK_REALTIME, &time_beginning);

	signalValue = _iterator->CurrentItem();
	pulseValue = _pulseIterator->CurrentItem();


	if(signalValue.sample == pulseValue.sample)
	{
		//_lastEDR = this->edr();

		//Notify(Observer::EDR);

		/*Beats per minute*/
		if((pulseValue.sample - lastPulseTime)>0 && _pulseIterator->CurrentIsPulse()) //if it is <0, we have just restarted the iterator
		{
			_lastPulse = ((pulseValue.sample - lastPulseTime)/(_patient->samplefreq))*60.0;
			Notify(Observer::PULSE);
		}
		if(_pulseIterator->CurrentHasEdr())
		{
			_lastEDR = _edrGenerator->GetEdr(pulseValue.sample);
			Notify(Observer::EDR);
		}
		lastPulseTime = pulseValue.sample;
		_pulseIterator->Next();
		pulse = true;

		/* the pulse record has more values than the signal record,
		 * so we have to go to the start of the pulse when we go to the start of the signal
		 */
		if(pulseValue.sample >= _patient->getNumECGSamples())
			_pulseIterator->First();
	}
	if(counter== 0) //putting out only 1 every 10 values
	{
		_lastECG = signalValue.value;
		Notify(Observer::ECG);
		ecg = true;
	}

	counter++;
	if (counter == 10) counter = 0;

	_iterator->Next();

	//clock_gettime(CLOCK_REALTIME, &time_end);
	//long nanos = (long)(time_end.tv_sec)*1E9 + time_end.tv_nsec -
	//				((long)(time_beginning.tv_sec)*1E9 + time_beginning.tv_nsec);

	if(pulse || ecg)
	{
		//cout << "\nhandler time: " << nanos << " ms\n" ;
		pulse = false;
		ecg = false;
	}
}

/**
 * Get the current ECG value
 * @return the current ECG value
 */
float PatientHandler::getECG(){
	return _lastECG;
}

/**
 * Get the current EDR value
 * @return the current EDR value
 */
float PatientHandler::getEDR(){
	return _lastEDR;
}

/**
 * Get the current pulse value
 * @return the current pulse value
 */
float PatientHandler::getPulse(){
	return _lastPulse;
}

string PatientHandler::getName()
{
	return _patient->getName();
}

bool PatientHandler::getState()
{
	return _running;
}


