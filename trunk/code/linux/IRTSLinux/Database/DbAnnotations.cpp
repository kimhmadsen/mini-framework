
/**
 * @file
 * Implements the DbAnnotations class
 */
#include "DbAnnotations.h"

/**
 * Constructor for DbAnnotations
 * @param record record name of the annotations file
 */
DbAnnotations::DbAnnotations(char* record)
{
	_record = record;
}

/**
 * Default destructor for DbAnnotations
 */
DbAnnotations::~DbAnnotations()
{

}

/**
 * Sets the pointer into the first element of the annotations
 */
void DbAnnotations::First()
{
	WFDB_Anninfo a;
	a.name = "atr";
	a.stat = WFDB_READ;
	annopen(_record, &a, 1);
	Next();
}
void DbAnnotations::Next()
{
	_done = (getann(0, &_annot) < 0);
//	while(strcmp(annstr(_annot.anntyp),"N")!= 0)
//		_done = (getann(0, &_annot) < 0);

}
bool DbAnnotations::IsDone()
{
	return _done;
}
AnnotValue DbAnnotations::CurrentItem()
{
	AnnotValue value;
	value.sample = _annot.time;
	value.value = _annot.num;
	value.type = _annot.anntyp;
	return value;
}
bool DbAnnotations::CurrentIsPulse()
{
	return strcmp(annstr(_annot.anntyp),"N")== 0;
}

bool DbAnnotations::CurrentHasEdr()
{
	return isqrs(_annot.anntyp);
}
