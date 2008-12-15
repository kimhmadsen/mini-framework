#ifndef DBANNOTATIONS_H_
#define DBANNOTATIONS_H_

#include <string>
#include <iostream>
#include "../SignalValue.h"
#include <wfdb/wfdb.h>
using namespace std;


class DbAnnotations
{
public:
	DbAnnotations(char* record);
	virtual ~DbAnnotations();
	virtual void First();
	virtual void Next();
	virtual bool IsDone();
	virtual AnnotValue CurrentItem();
private:
	WFDB_Annotation	_annot;
	bool			_done;
	char*			_record;
};

#endif /*DBANNOTATIONS_H_*/