#ifndef DBSIGNALS_H_
#define DBSIGNALS_H_

#include <string>
#include "../SignalValue.h"
#include <wfdb/wfdb.h>

using namespace std;

class DbSignals
{
public:
	DbSignals(char* record);
	virtual ~DbSignals();
	virtual void First();
	virtual void Next();
	virtual bool IsDone();
	virtual SignalValue CurrentItem();
private:
	char* 			_record;
	WFDB_Sample 	_sample[2];
	bool 			_done;
	long			_time; //units are sample intervals

};

#endif /*DBSIGNALS_H_*/
