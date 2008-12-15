
/**
 * @file
 * Edr.h
 *
 *  Created on: 9-Dec-08
 *      Author: maria
 */

#ifndef EDRGENERATOR_H_
#define EDRGENERATOR_H_

#include "Database/DbEdr.h"

using namespace std;

/**
 * Calculates the EDR
 *
 */
class EdrGenerator
{
public:
	EdrGenerator(DbEdr* _dbEdr);
	virtual ~EdrGenerator();
	int 		GetEdr(long time);
private:
	DbEdr* _dbEdr;

};
#endif /* EDRGENERATOR_H_ */
