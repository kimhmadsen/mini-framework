#include "DbSignals.h"

DbSignals::DbSignals(char* record)
{
	_record = record;
	_time = 0;
}
DbSignals::~DbSignals()
{

}

void DbSignals::First()
{
	WFDB_Siginfo sigInfo[2];
	isigopen(_record, sigInfo, 2);
	Next();
	_time = 0;
}
void DbSignals::Next()
{
	_done = (getvec(_sample) < 0);
	_time ++;
}
bool DbSignals::IsDone()
{
	return _done;
}
SignalValue DbSignals::CurrentItem()
{
	SignalValue value;
	value.time = _time;
	value.value = _sample[0];
	value.value2 = _sample[1];
	return value;
}
