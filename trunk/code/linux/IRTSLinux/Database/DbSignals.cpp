
/**
 * @file
 * Implements the DbSignals class
 */
#include "DbSignals.h"

/**
 * Constructor for DbSignals
 * @param record record name of the signals file
 */
DbSignals::DbSignals(char* record)
{
	_record = record;
	_sampleNum = 0;

	WFDB_Siginfo sigInfo[2];
	isigopen(_record, sigInfo, 2);
	_size = sigInfo[0].nsamp;
}

/**
 * Default destructor for DbSignals
 */
DbSignals::~DbSignals()
{

}

/**
 * Sets the pointer into the first element of the signals
 */
void DbSignals::First()
{
	WFDB_Siginfo sigInfo[2];
	isigopen(_record, sigInfo, 2);
	_size = sigInfo[0].nsamp;
	Next();
	_sampleNum = 0;
}


/**
 * Moves the pointer to the next element of the signals
 */
void DbSignals::Next()
{
	_done = (getvec(_sample) < 0);
	_sampleNum ++;
}


/**
 * Checks if the pointer arrived at the end of the signals
 * @return true if it is done; false otherwise
 */
bool DbSignals::IsDone()
{
	return _done;
}


/**
 * Gets the current element
 * @return an SignalValue object which is the current element
 */
SignalValue DbSignals::CurrentItem()
{
	SignalValue value;
	value.sample = _sampleNum;
	value.value = _sample[0];
	value.value2 = _sample[1];
	return value;
}

/**
 * Gets the number of samples in the signals file
 * @return number of samples
 */
long DbSignals::Size()
{
	return _size;
}

