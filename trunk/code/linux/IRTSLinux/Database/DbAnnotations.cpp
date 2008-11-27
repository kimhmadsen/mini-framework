#include "DbAnnotations.h"

DbAnnotations::DbAnnotations(char* record)
{
	_record = record;
}
DbAnnotations::~DbAnnotations()
{

}

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
	while(strcmp(annstr(_annot.anntyp),"N")!= 0)
		_done = (getann(0, &_annot) < 0);

}
bool DbAnnotations::IsDone()
{
	return _done;
}
AnnotValue DbAnnotations::CurrentItem()
{
	AnnotValue value;
	value.sample = _annot.time;
	value.value = 1;
	return value;
}
