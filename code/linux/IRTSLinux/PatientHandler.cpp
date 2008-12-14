/*
 * PatientHandler.cpp
 *
 *  Created on: mar 31, 2008
 *      Author: MSO
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
	_patient = patient;
	_lastECG = 0;
	_lastEDR = 0;
	_lastPulse = 0;

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


	//if (timer_connect (_timerid, (void *)PatientHandler::handler_wrapper, int(this))<0)
	//	cout << "timer connect";
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
}

void PatientHandler::setPatient( Patient* patient )
{
	_patient = patient;
}

void PatientHandler::stop()
{
	_value.it_value.tv_sec = 0;
	_value.it_value.tv_nsec = 0;

	_value.it_interval.tv_sec = 0;
	_value.it_interval.tv_nsec = 0;

	if (timer_settime (_timerid, 0, &_value, NULL)<0 )
			cout << "timer settime";
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

	static SignalIterator* iterator = _patient->getECG();
	static AnnotIterator* pulseIterator = _patient->getAnn();
	static EdrGenerator* edrGenerator = _patient->getEdrGenerator();

	SignalValue signalValue;
	AnnotValue pulseValue;
	static int counter = 0;
	static float lastPulseTime = 0;

	//clock_gettime(CLOCK_REALTIME, &time_beginning);

	signalValue = iterator->CurrentItem();
	pulseValue = pulseIterator->CurrentItem();


	if(signalValue.sample == pulseValue.sample)
	{
		//_lastEDR = this->edr();

		//Notify(Observer::EDR);

		/*Beats per minute*/
		if((pulseValue.sample - lastPulseTime)>0 && pulseIterator->CurrentIsPulse()) //if it is <0, we have just restarted the iterator
		{
			_lastPulse = ((pulseValue.sample - lastPulseTime)/(_patient->samplefreq))*60.0;
			Notify(Observer::PULSE);
		}
		if(pulseIterator->CurrentHasEdr())
		{
			_lastEDR = edrGenerator->GetEdr(pulseValue.sample);
			Notify(Observer::EDR);
		}
		lastPulseTime = pulseValue.sample;
		pulseIterator->Next();
		pulse = true;

		/* the pulse record has more values than the signal record,
		 * so we have to go to the start of the pulse when we go to the start of the signal
		 */
		if(pulseValue.sample >= _patient->getNumECGSamples())
			pulseIterator->First();
	}
	if(counter== 0) //putting out only 1 every 10 values
	{
		_lastECG = signalValue.value;
		Notify(Observer::ECG);
		ecg = true;
	}

	counter++;
	if (counter == 10) counter = 0;

	iterator->Next();

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

/**
 * Method to calculate the baseline of the signal.
 * Used for calculating the edr value.
 * The calculation is wrong, but it doesn't crash now!
 * @param signal_number signal 0 or signal 1
 * @param t sample number (time)
 * @return the baseline of the signal
 */
float PatientHandler::baseline(int signal_number, long t)
{
	int c, i;
	static long t0;
	int blen = _patient->samplefreq; /*baseline length*/

	if (signal_number < 0 || signal_number >= nsig) return 0; /* nsig = number of signals -> 1 o 2*/
	if (t0 == 0L)
		for (c = 0, bbuf[c][0] = sample(c, 0L) * (2*blen+1); c < nsig; c++)
			for (i = 1; i < VBL; i++)
				bbuf[c][i] = bbuf[c][0];
	while (t0 < t)
		for (c = 0; c < nsig; c++)
			bbuf[c][++t0 & (VBL-1)] += sample(c, t+blen) - sample(c, abs(t-blen)); //I decided to put abs myself, I'm sure it's wrong!
	return bbuf[signal_number][t & (VBL-1)]/blen;

}
/**
 * Method to calculate the x and y of the signal.
 * Used for calculating the edr value.
 * @param t0 sample number from
 * @param t1 sample number to
 * @return the x and y of the signal
 */
void PatientHandler::getxy(long t0, long t1)
{
	for (x = y = 0.0; t0 <= t1; t0++) {
		x += (sample(0, t0) - baseline(0, t0));
		if (nsig > 1) y += (sample(1, t0) - baseline(1, t0));
	}

}

/**
 * Method to get a sample of a signal.
 * Used for calculating the edr value.
 * @param signal_number signal 0 or signal 1
 * @param sample sample number (time)
 * @return the value of the sample
 */
/*
float PatientHandler::sample(int signal_number, long sample)
{
	SignalValue signalValue = _patient->getECG()->at(sample);
	switch(signal_number)
	{
		case 0:
			return signalValue.value;
		case 1:
			return signalValue.value2;
		default:
			return 0;
	}
}
*/

/**
 * Calculates the edr of the signal
 * @returns the edr value
 */

/*
float PatientHandler::edr()
{
	double d, dn, r, theta;
	static int xc, yc, thc;
	static double xd, yd, td, xdmax, ydmax, tdmax, xm, ym, tm;

	if (x == 0 && y == 0) return (0);
	switch (nsig) {
	  case 1:
	d = x - xm;
	if (xc < 500) dn = d/++xc;
	else if ((dn = d/xc) > xdmax) dn = xdmax;
	else if (dn < -xdmax) dn = -xdmax;
	xm += dn;
	xd += fabs(dn) - xd/xc;
	if (xd < 1.) xd = 1.;
	xdmax = 3.*xd/xc;
	r = d/xd;
	break;
	  case 2:
	d = x - xm;
	if (xc < 500) dn = d/++xc;
	else if ((dn = d/xc) > xdmax) dn = xdmax;
	else if (dn < -xdmax) dn = -xdmax;
	xm += dn;
	xd += fabs(dn) - xd/xc;
	if (xd < 1.) xd = 1.;
	xdmax = 3.*xd/xc;
	d = y - ym;
	if (yc < 500) dn = d/++yc;
	else if ((dn = d/yc) > ydmax) dn = ydmax;
	else if (dn < -ydmax) dn = -ydmax;
	ym += dn;
	yd += fabs(dn) - yd/yc;
	if (yd < 1.) yd = 1.;
	ydmax = 3.*yd/yc;
	theta = atan2(x, y);
	d = theta - tm;
	if (d > PI) d -= 2.*PI;
	else if (d < -PI) d += 2.*PI;
	if (thc < 500) dn = d/++thc;
	else if ((dn = d/thc) > tdmax) dn = tdmax;
	else if (dn < -tdmax) dn = -tdmax;
	if ((tm += dn) > PI) tm -= 2.*PI;
	else if (tm < -PI) tm += 2.*PI;
	td += fabs(dn) - td/thc;
	if (td < 0.001) td = 0.001;
	tdmax = 3.*td/thc;
	r = d/td;
	break;
	}
	return r*50.;
}
*/
