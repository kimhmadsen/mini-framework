
/**
 * @file
 * DbEdr.cpp
 *
 *  Created on: 9-Dec-08
 *      Author: maria
 */

#include "EdrGenerator.h"

/**
 * Constructor for EdrGenerator
 * @param dbEdr DbEdr object that will do the database calls.
 */
EdrGenerator::EdrGenerator(DbEdr* dbEdr)
{
	_dbEdr = dbEdr;

}

/**
 * Default destructor for EdrGenerator
 */
EdrGenerator::~EdrGenerator()
{

}

/**
 * Calculates the EDR from a given sample number
 * @param time sample number
 * @return the EDR value
 */
int EdrGenerator::GetEdr(long time)
{
    return _dbEdr->GetEdr(time);

}
