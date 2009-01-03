
/**
 * @file
 * Implements the PatientHandler class
 * @date 2008-12-09
 * @author maria
 */
#include "DbEdr.h"

/**
 * Constructor for DbEdr
 * @param record record name of the annotations file
 */
DbEdr::DbEdr(char* record)
{
	_record = record;
	blen = strtim("1");	/* set half-length of baseline filter to 1 second */
	nsig = 2;
	dt1 = 0L;
}

/**
 * Default destructor for DbEdr
 */
DbEdr::~DbEdr()
{

}

/**
 * Calculates the EDR from a given sample number
 * @param time sample number
 * @return the EDR value
 */
int DbEdr::GetEdr(long time)
{
    if (dt1 == 0L) dt1 = -(dt2 = strtim("0.04"));
    getxy(time+dt1, time+dt2);
    return edr();

}

int DbEdr::baseline(int s, WFDB_Time t)
{

    int c, i;
    static WFDB_Time t0;
	static long bbuf[2][VBL];

    if (s < 0 || s >= nsig) return (0);
    if (t0 == 0L)
	for (c = 0, bbuf[c][0] = sample(c, 0L) * (2*blen+1); c < nsig; c++)
	    for (i = 1; i < VBL; i++)
		bbuf[c][i] = bbuf[c][0];
    while (t0 < t)
	for (c = 0; c < nsig; c++)
	    bbuf[c][++t0 & (VBL-1)] += sample(c, t+blen) - sample(c, t-blen);
    return ((int)(bbuf[s][t & (VBL-1)]/blen));
}

void DbEdr::getxy(WFDB_Time t0, WFDB_Time t1)
{
    for (x = y = 0.0; t0 <= t1; t0++) {
	x += sample(0, t0) - baseline(0, t0);
	if (nsig > 1) y += sample(1, t0) - baseline(1, t0);
    }
}

int DbEdr::edr()			/* calculate instantaneous EDR */
{
    double d, dn, r, theta;
    static int xc, yc, thc;
    static double xd, yd, td, xdmax, ydmax, tdmax, xm, ym, tm;

    if (x == 0 && y == 0) return (0);
    switch (nsig) {
      case 1:
	d = x - xm;
	if (xc < 500) dn = d/++xc;
	else if ((dn = d/xc) > xdmax) dn = xdmax;
	else if (dn < -xdmax) dn = -xdmax;
	xm += dn;
	xd += fabs(dn) - xd/xc;
	if (xd < 1.) xd = 1.;
	xdmax = 3.*xd/xc;
	r = d/xd;
	break;
      case 2:
	d = x - xm;
	if (xc < 500) dn = d/++xc;
	else if ((dn = d/xc) > xdmax) dn = xdmax;
	else if (dn < -xdmax) dn = -xdmax;
	xm += dn;
	xd += fabs(dn) - xd/xc;
	if (xd < 1.) xd = 1.;
	xdmax = 3.*xd/xc;
	d = y - ym;
	if (yc < 500) dn = d/++yc;
	else if ((dn = d/yc) > ydmax) dn = ydmax;
	else if (dn < -ydmax) dn = -ydmax;
	ym += dn;
	yd += fabs(dn) - yd/yc;
	if (yd < 1.) yd = 1.;
	ydmax = 3.*yd/yc;
	theta = atan2(x, y);
	d = theta - tm;
	if (d > PI) d -= 2.*PI;
	else if (d < -PI) d += 2.*PI;
	if (thc < 500) dn = d/++thc;
	else if ((dn = d/thc) > tdmax) dn = tdmax;
	else if (dn < -tdmax) dn = -tdmax;
	if ((tm += dn) > PI) tm -= 2.*PI;
	else if (tm < -PI) tm += 2.*PI;
	td += fabs(dn) - td/thc;
	if (td < 0.001) td = 0.001;
	tdmax = 3.*td/thc;
	r = d/td;
	break;
    }
    return ((int)(r*50.));
}

