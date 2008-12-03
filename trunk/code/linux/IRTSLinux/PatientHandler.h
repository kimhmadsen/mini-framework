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
#include "Patient.h"

#include "Subject.hpp"

class PatientHandler : public Subject
{
public:
	PatientHandler(Patient*);
	~PatientHandler();
	void stop(void);
	void start(void);
	float getECG();

private:
	Patient* _patient;
	int _taskDiscrete_id;
	pthread_t _continuousThread;

	static void* tcontinuous_wrapper(void* thisObject);
	void task_continuous();
	static void tdiscrete_wrapper(void* thisObject);
	void task_discrete();
	int edr(long , long );
	unsigned sleep(double);
	float _lastECG;

};

#endif /* PATIENTHANDLER_H */
