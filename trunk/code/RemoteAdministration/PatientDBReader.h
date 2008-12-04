#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class PatientDBReader
{
public:
	PatientDBReader();
	PatientDBReader(char*);
	~PatientDBReader(void);
	string getPatient(char*);
	void setDBFile(char*);

private:
	char* dbFile;
	string getRightCpr(char*);
	string getPatientInfo(ifstream*, string);
};
