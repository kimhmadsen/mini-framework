/**
 * @file
 * Implements the RemoteClient class
 */
#include <iostream>
#include <string.h>
#include "RemoteClient.h"
#include "PatientDb.h"

using namespace std;

RemoteClient::RemoteClient(short serverPort, char* serverIp,
		PatientHandler* patientHandler)
{
	this->serverIp = serverIp;
	this->serverPort = serverPort;
	this->patientHandler = patientHandler;

	patientHandler->Attach(this);
	this->isSTATE_CHANGE = true; // get notified about state changes.
	this->isPATIENT_CHANGE = true; // get notified about patient change.
}

RemoteClient::~RemoteClient()
{
	patientHandler->Detach(this);
}

int RemoteClient::Connect(void)
{
	InetAddr patientAddr(serverPort, serverIp);

	remoteAdminConnector.connect(remoteAdminStream, patientAddr);
	std::cout << "Patient value stream connected on port " << serverPort
			<< " \n";

	return 0;
}

int RemoteClient::Disconnect(void)
{
	remoteAdminConnector.close(remoteAdminStream);
	return 0;
}

void RemoteClient::Run(void)
{

	while (true)
	{
		string command;
		char buf[256];
		memset(buf, 0, sizeof(buf));
		int count;

		count = remoteAdminStream.recv(buf, sizeof(buf), 0);
		if (count > 0)
		{
			command.assign(buf);

			switch (command[0])
			{
			case 'G': // get patient list
			{
				string patientList;
				std::cout << "\nRemoteClient: command G" << std::endl;
				patientList = PatientDb::Instance()->GetPatientList();
				patientList.copy(buf, sizeof(&buf[2]), 0);
				count = patientList.size();
				break;
			}
			case 'P': // set current patient
			{
				string patientName;
				std::cout << "\nRemoteClient: command P" << std::endl;
				patientName = command.substr(2);
				char* name;
				strcpy(name, patientName.c_str());
				Patient* pat = PatientDb::Instance()->GetPatient(name );
				patientHandler->setPatient( pat );
				break;
			}
			case 'S': // start or stop the simulation.
			{
				std::cout << "\nRemoteClient: command S" << std::endl;
				int pos;
				pos = command.find("start", 1);
				if (pos != -1)
				{
					//const char startedStr[] = "G started\n";
					//count = sizeof(startedStr);
					patientHandler->start();
					//strncpy(buf, startedStr, count);
				}
				pos = command.find("stop", 1);
				if (pos != -1) // is -1 the right to look for?
				{
					//const char stoppedStr[] = "G stopped\n";
					//count = sizeof(stoppedStr);
					patientHandler->stop();
					//strncpy(buf, stoppedStr, count);
				}

				break;
			}
			default:
				std::cerr << "\n" << "RemoteClient: unknown command: " << buf
						<< std::endl;
				break;

			}

			remoteAdminStream.send_n(buf, count, 0);
		}
	}

	return;
}

void RemoteClient::Update(Subject *_sbj, Signaltypes signaltypes)
{
	char buf[256];
	memset(buf, 0, sizeof(buf));
	int count;

	switch (signaltypes)
	{
	case EDR:
		break;
	case ECG:
		break;
	case PULSE:
		break;
	case STATE_CHANGE:
	{
		bool running = patientHandler->getState();
		if(running)
		{
			const char startedStr[] = "G started\n";
			count = sizeof(startedStr);
			patientHandler->start();
			strncpy(buf, startedStr, count);
		}
		else
		{
			const char stoppedStr[] = "G stopped\n";
			count = sizeof(stoppedStr);
			patientHandler->stop();
			strncpy(buf, stoppedStr, count);
		}
		break;
	}
	case PATIENT_CHANGE:
	{	string response = "P ";
		response.append(patientHandler->getName());
		count = response.length();
		strncpy(buf, response.c_str(), count);
		break;
	}
	default:
		break;
	}
	remoteAdminStream.send_n(buf, count, 0);
}
