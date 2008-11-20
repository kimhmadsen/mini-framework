#ifndef DBANNOTATIONS_H_
#define DBANNOTATIONS_H_

#include <string>
#include "../SignalValue.h"
using namespace std;


class DbAnnotations
{
public:
	DbAnnotations();
	virtual ~DbAnnotations();
	virtual void First();
	virtual void Next();
	virtual bool IsDone();
	virtual AnnotValue CurrentItem();

};

#endif /*DBANNOTATIONS_H_*/
