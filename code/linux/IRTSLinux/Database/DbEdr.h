/*
 * DbEdr.h
 *
 *  Created on: 9-Dec-08
 *      Author: maria
 */

#ifndef DBEDR_H_
#define DBEDR_H_

#include <string>
#include <math.h>
#include <wfdb/wfdb.h>
#include <wfdb/ecgmap.h>

using namespace std;

#define VBL	2048	/* VBL must be a power of 2 */

#ifdef M_PI
#define PI M_PI	/* pi to machine precision */
#else
#define PI 3.141592653589793238462643383279502884197169399375105820974944
			/* quite a few more digits than we need :-) */
#endif

class DbEdr
{
public:
	DbEdr(char* record);
	virtual ~DbEdr();
	int 		GetEdr(long time);
private:
	char* 		_record;
	int 		baseline(int s, WFDB_Time t);
	void 		getxy(WFDB_Time t0, WFDB_Time t1);
	int 		edr();
	double 		x, y;
	int 		blen, nsig, *sig;
	WFDB_Sample dt1, dt2;


};
#endif /* DBEDR_H_ */
