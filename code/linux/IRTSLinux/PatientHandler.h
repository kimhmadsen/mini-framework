/*
 * PatientHandler.h
 *
 *  Created on: mar 31, 2008
 *      Author: MSO
 */

/*
 * Description:
 */
#ifndef PATIENTHANDLER_H
#define PATIENTHANDLER_H

#include <pthread.h>
#include <time.h>
#include <signal.h>
#include "Patient.h"

#include "Subject.hpp"

#define VBL	2048	/* VBL must be a power of 2 */
#ifdef M_PI
#define PI M_PI	/* pi to machine precision */
#else
#define PI 3.141592653589793238462643383279502884197169399375105820974944
/* quite a few more digits than we need :-) */
#endif

class PatientHandler : public Subject
{
public:
	PatientHandler(Patient*);
	~PatientHandler();
	void stop(void);
	void start(void);
	void setPatient( Patient* patient );
    float getECG();
    float getPulse();
    float getEDR();
    string getName();
    bool getState();

private:
	Patient* _patient;
	bool _running;

	static void handler_wrapper(int signo, siginfo_t *info, void *context);
    void handler();
	long _ticks;

    timer_t _timerid;
    struct itimerspec _value;
    struct sigevent _sig_spec;
    float _lastECG;
    float _lastPulse;
    float _lastEDR;

    SignalIterator* _iterator;
    AnnotIterator* _pulseIterator;
    EdrGenerator* _edrGenerator;


};

#endif /* PATIENTHANDLER_H */
