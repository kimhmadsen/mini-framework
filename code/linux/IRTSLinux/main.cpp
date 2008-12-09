#include <stdio.h>
#include <iostream>
#include <list>

#include "PatientDb.h"
#include "Patient.h"
#include "PatientHandler.h"
#include "LCDView.hpp"

class Observers;

int main()
{
/*	cout<<"creating a DbPatient"<<endl;
	DbPatient dbPatient("100s");
	Patient patient(&dbPatient);
	cout<<"info:\n" << patient.getInfo() << endl;
*/
	cout<<"creating PatientDB" <<endl;
	Patient* patient2 = PatientDb::Instance()->GetPatient("0");
	cout<<"info:\n" << patient2->getInfo() << endl;

/*	PatientHandler* handler = new PatientHandler(&patient);
	LCDView view(handler);
	handler->start();
*/
	//sleep(1000);

	//handler->stop();

	//cout << "I'm stopped" << endl;
	//TODO: fix PatientDb !!!

/*	cout<<"creating PatientDB" <<endl;
	Patient* patient2 = PatientDb::Instance()->GetPatient("0");
	cout<<"info:\n" << patient2->getInfo() << endl;

	SignalIterator* signal = patient.getECG();
	AnnotIterator* annot = patient.getAnn();

	cout << "Signals" << endl << endl;
	while(!signal->IsDone())
	{
		SignalValue value = signal->CurrentItem();
		cout << value.time << "  " << value.value << "  " << value.value2 << endl;
		signal->Next();
	}

	cout << "Annotations" << endl << endl;
	while(!annot->IsDone())
	{
		AnnotValue value = annot->CurrentItem();
		cout << value.sample << "  " << value.value <<  endl;
		annot->Next();
	}

	cout << "DONE!" << endl;
*/
	while(true){}
	return 0;

}
