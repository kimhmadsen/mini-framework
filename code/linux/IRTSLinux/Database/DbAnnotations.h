
/**
 * @file
 * Implements the DbAnnotations class
 */
#ifndef DBANNOTATIONS_H_
#define DBANNOTATIONS_H_

#include <string>
#include <iostream>
#include "../SignalValue.h"
#include <wfdb/wfdb.h>
#include <wfdb/ecgmap.h>

using namespace std;

/**
 * Database Annotations
 */
class DbAnnotations
{
public:
	DbAnnotations(char* record);
	virtual ~DbAnnotations();
	virtual void First();
	virtual void Next();
	virtual bool IsDone();
	virtual AnnotValue CurrentItem();
	virtual bool CurrentIsPulse();
	virtual bool CurrentHasEdr();
private:
	WFDB_Annotation	_annot;
	bool			_done;
	char*			_record;
};

#endif /*DBANNOTATIONS_H_*/
