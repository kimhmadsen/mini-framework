
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

/**
 * Moves the pointer to the next element of the annotations
 */
void DbAnnotations::Next()
{
	_done = (getann(0, &_annot) < 0);
}

/**
 * Checks if the pointer arrived at the end of the annotations
 * @return true if it is done; false otherwise
 */
bool DbAnnotations::IsDone()
{
	return _done;
}

/**
 * Gets the current element
 * @return an AnnotValue object which is the current element
 */
AnnotValue DbAnnotations::CurrentItem()
{
	AnnotValue value;
	value.sample = _annot.time;
	value.value = _annot.num;
	value.type = _annot.anntyp;
	return value;
}

/**
 * Checks if the current annotation is a pulse
 * @return true if it is a pulse
 */
bool DbAnnotations::CurrentIsPulse()
{
	return strcmp(annstr(_annot.anntyp),"N")== 0;
}

/**
 * Checks if the current annotation can be used for calculating EDR
 * @return true if it has EDR
 */
bool DbAnnotations::CurrentHasEdr()
{
	return isqrs(_annot.anntyp);
}
