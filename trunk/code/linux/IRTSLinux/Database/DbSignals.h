#ifndef DBSIGNALS_H_
#define DBSIGNALS_H_

#include <string>
#include "../SignalValue.h"
using namespace std;

class DbSignals
{
public:
	DbSignals();
	virtual ~DbSignals();
	virtual void First();
	virtual void Next();
	virtual bool IsDone();
	virtual SignalValue CurrentItem();
};

#endif /*DBSIGNALS_H_*/
