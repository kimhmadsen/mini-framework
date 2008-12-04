#include "PatientDBReader.h"

PatientDBReader::PatientDBReader(char* file)
{
	dbFile = file;
}
PatientDBReader::PatientDBReader()
{
	
}

PatientDBReader::~PatientDBReader(void)
{

}

string PatientDBReader::getPatient(char* cpr)
{
	ifstream fileStream (dbFile);
	if ( !fileStream.is_open() ) {
		cout<<"The file couldn't be opened\n";
		return "";
	}

	cout<<"The file is opened\n";
	string stringCpr = getRightCpr(cpr);
	cout<<"cpr: "<<stringCpr<<endl;
	char line[100];
	do{
		fileStream.getline(line, 100);
		if(line[0] == '#')
		{
			string stringLine(line, 1, sizeof(line));
			if (stringLine.compare(stringCpr) == 0)
			{
				return getPatientInfo(&fileStream, stringCpr);
				//cout<<info<<endl;
			}
		}
	}while(!fileStream.eof());

	return "";
}
string PatientDBReader::getRightCpr(char* charCpr)
{
	string cpr(charCpr);
	if(cpr.find('-')!=string::npos)
		cpr.erase(cpr.find('-'), 1);
	while(cpr.find(' ')!=string::npos)
		cpr.erase(cpr.find(' '), 1);
	
	return cpr;
}
string PatientDBReader::getPatientInfo(ifstream* fileStream, string cpr)
{
	string info = "cpr number: ";
	info.append(cpr);
	info.append("\n");
	char line[100];
	while(!fileStream->eof())
	{
		fileStream->getline(line, 100);
		if(line[0] == ' ' || line[0] == '#') break;
		info.append(line);
		info.append("\n");
	}


	return info;
}
void PatientDBReader::setDBFile(char* file)
{
	dbFile = file;
}