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

	cout << "patient list: \n" << PatientDb::Instance()->GetPatientList()<< endl;

	Patient* patient = PatientDb::Instance()->GetPatient("100s");
	cout<< "selected patient:\n" << patient->getName() << patient->getInfo() << endl;


	PatientHandler* handler = new PatientHandler(patient);
	LCDView view(handler);
//	pthread_create(&threadRemoteClient, NULL, RemoteClientThread,
//			(void*) handler);

	handler->start();

	while (true)
	{
	}
	return 0;

}
