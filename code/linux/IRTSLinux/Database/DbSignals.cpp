#include "DbSignals.h"

DbSignals::DbSignals(char* record)
{
	_record = record;
	_sampleNum = 0;

	WFDB_Siginfo sigInfo[2];
	isigopen(_record, sigInfo, 2);
	_size = sigInfo[0].nsamp;
}
DbSignals::~DbSignals()
{

}

void DbSignals::First()
{
	WFDB_Siginfo sigInfo[2];
	isigopen(_record, sigInfo, 2);
	_size = sigInfo[0].nsamp;
	Next();
	_sampleNum = 0;
}
void DbSignals::Next()
{
	_done = (getvec(_sample) < 0);
	_sampleNum ++;
}
bool DbSignals::IsDone()
{
	return _done;
}
SignalValue DbSignals::CurrentItem()
{
	SignalValue value;
	value.sample = _sampleNum;
	value.value = _sample[0];
	value.value2 = _sample[1];
	return value;
}
long DbSignals::Size()
{
	return _size;
}

