/*
 * PatientSignalIterator.h
 *
 *  Created on: mar 31, 2008
 *      Author: MSO
 */

#ifndef PATIENTSIGNALITERATOR_H
#define PATIENTSIGNALITERATOR_H

#include "SignalValue.h"
#include "Database/DbSignals.h"
#include "Database/DbAnnotations.h"
#include <vector>

using namespace std;



class SignalIterator
{
public:
	SignalIterator(DbSignals* signalValues);
	virtual void First();
	virtual void Next();
	virtual bool IsDone();
	virtual SignalValue CurrentItem();
private:
	DbSignals* _signal;
	SignalValue _current;
};

class AnnotIterator
{
public:
	AnnotIterator(DbAnnotations* annotValues);
	virtual void First();
	virtual void Next();
	virtual bool IsDone();
	virtual AnnotValue CurrentItem();
	virtual bool CurrentIsPulse();
	virtual bool CurrentHasEdr();
private:
	DbAnnotations* _annot;
	AnnotValue _current;
};

#endif /* PATIENTSIGNALITERATOR_H*/
