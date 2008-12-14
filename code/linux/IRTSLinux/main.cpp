#include <stdio.h>
#include <iostream>
#include <list>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>
#include "PatientDb.h"
#include "Patient.h"
#include "PatientHandler.h"
#include "LCDView.hpp"
#include "RemoteClient.h"

const short SERVER_PORT = 10000;
char *host;

RemoteClient* rc;

class Observers;

void* RemoteClientThread(void* patientHandler)
{

	rc = new RemoteClient(SERVER_PORT, host, (PatientHandler*) patientHandler);
	rc->Connect();
	rc->Run();

	return NULL;
}

int main(int argc, char* argv[])
{
	pthread_t threadRemoteClient;

	if (argc > 1)
	{
		host = (char *) argv[1];
	}
	else
	{
		hostent* localHost = gethostbyname("localhost");
		host = inet_ntoa(*(struct in_addr *) *localHost->h_addr_list);
	}

	cout << "creating a DbPatient" << endl;
	DbPatient dbPatient((char*)"100s");
	Patient patient(&dbPatient);
	cout << "info:\n" << patient.getInfo() << endl;

	//	cout << "creating PatientDB" << endl;
	//	Patient* patient2 = PatientDb::Instance()->GetPatient("0");
	//	cout << "info:\n" << patient2->getInfo() << endl;

	PatientHandler* handler = new PatientHandler(&patient);

	LCDView view(handler);
	pthread_create(&threadRemoteClient, NULL, RemoteClientThread,
			(void*) handler);

	handler->start();
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
	while (true)
	{
	}
	return 0;

}
