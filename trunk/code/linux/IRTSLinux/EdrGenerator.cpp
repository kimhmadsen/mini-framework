/**
 * @file
 * DbEdr.cpp
 *
 *  Created on: 9-Dec-08
 *      Author: maria
 */

#include "EdrGenerator.h"

EdrGenerator::EdrGenerator(DbEdr* dbEdr)
{
	_dbEdr = dbEdr;

}
EdrGenerator::~EdrGenerator()
{

}
int EdrGenerator::GetEdr(long time)
{
    return _dbEdr->GetEdr(time);

}
