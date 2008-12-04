/*
 * PatientSignalIterator.cpp
 *
 *  Created on: mar 31, 2008
 *      Author: MSO
 */

#include "PatientSignalIterator.h"
using namespace std;



SignalIterator::SignalIterator(DbSignals* signalValues):_signal(signalValues)
{
	First();
}

void SignalIterator::First()
{
	_signal->First();
}

//
// It is a circular iterator.
// It will start from the beginning again when it is done.
//
void SignalIterator::Next()
{
	if(IsDone())
		First();
	else
		_signal->Next();
}

bool SignalIterator::IsDone()
{
	return _signal->IsDone();
}

SignalValue SignalIterator::CurrentItem()
{
	return _signal->CurrentItem();
}


AnnotIterator::AnnotIterator(DbAnnotations* annotValues):_annot(annotValues)
{
	First();
}

void AnnotIterator::First()
{
	_annot->First();
}

//
// It is a circular iterator.
// It will start from the beginning again when it is done.
//
void AnnotIterator::Next()
{
	if(IsDone())
		First();
	else
		_annot->Next();
}
bool AnnotIterator::IsDone()
{
	return _annot->IsDone();
}

AnnotValue AnnotIterator::CurrentItem()
{
	return _annot->CurrentItem();
}
