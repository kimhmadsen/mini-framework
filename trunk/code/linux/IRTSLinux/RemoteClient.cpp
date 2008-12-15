
/**
 * @file
 * Implements the RemoteClient class
 */
#include <iostream>
#include <string.h>
#include "RemoteClient.h"
#include "PatientDb.h"

using namespace std;

/**
 * Constructor for the RemoteClient
 * @param serverPort port in the server
 * @param serverIp IP of the server
 * @param patientHandler pointer to the patient handler we want to attach to
 */
RemoteClient::RemoteClient(short serverPort, char* serverIp,
		PatientHandler* patientHandler)
{
	this->serverIp = serverIp;
	this->serverPort = serverPort;
	this->patientHandler = patientHandler;


	this->isSTATE_CHANGE = true; // get notified about state changes.
	this->isPATIENT_CHANGE = true; // get notified about patient change.
}

/**
 * Destructor for RemoteClient
 */
RemoteClient::~RemoteClient()
{
	patientHandler->Detach(this);
}

/**
 * Connects to the server
 * @return status on the connect to the socket
 */
int RemoteClient::Connect(void)
{
	InetAddr patientAddr(serverPort, serverIp);

	std::cout << "Connecting to IP " << serverIp << " and port " << serverPort
			<< endl;
	int status = remoteAdminConnector.connect(remoteAdminStream, patientAddr);
	if (status == 0)
	{
		patientHandler->Attach(this);
		std::cout << "Patient value stream connected on port " << serverPort << endl;
		return 0;
	}
	patientHandler->Detach(this);
	return status;
}

/**
 * Closes the connection with the server
 */
int RemoteClient::Disconnect(void)
{
	remoteAdminConnector.close(remoteAdminStream);
	return 0;
}

/**
 * Listens to the socket for new commands and reacts to them
 */
void RemoteClient::Run(void)
{
	cout << "RemoteClient running" << endl;

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
			cout << "command received: " << command << endl;
			switch (command[0])
			{
			case 'G': // get patient list
			{
				string patientList = "G ";
				//std::cout << "\nRemoteClient: command G" << std::endl;
				patientList.append(PatientDb::Instance()->GetPatientList());
				strncpy(buf, patientList.c_str(), patientList.length());
				//patientList.copy(buf, sizeof(&buf[2]), 0);
				count = patientList.length();
				break;
			}
			case 'P': // set current patient
			{
				string patientName;
				std::cout << "\nRemoteClient: command P" << std::endl;
				patientName = command.substr(2);
				std::cout << "\nRequested Patient: " << patientName
						<< std::endl;

				char* name;
				strcpy(name, patientName.c_str());
				Patient* pat = PatientDb::Instance()->GetPatient(name);
				cout << "patient created: " << pat->getName() << endl;
				patientHandler->setPatient(pat);
				count = 0;
				break;
			}
			case 'S': // start or stop the simulation.
			{
				std::cout << "\nRemoteClient: command S" << std::endl;
				int pos;
				pos = command.find("start", 1);
				if (pos != -1)
				{
					cout << "starting simulator" << endl;
					patientHandler->start();
				}
				pos = command.find("stop", 1);
				if (pos != -1) // is -1 the right to look for?
				{
					cout << "stopping simulator" << endl;
					patientHandler->stop();
				}
				count = 0;
				break;
			}
			default:
				std::cerr << "\n" << "RemoteClient: unknown command: " << buf
						<< std::endl;
				count = 0;
				break;

			}

			if (count > 0)
			{
				remoteAdminStream.send_n(buf, count, 0);
				cout << "response: " << buf << endl;
			}

			sleep(1);
		}
	}

	return;
}

/**
* callback function part of the observer pattern. Called from the model when ever it changes.
* @param _sbj reference to the patient handler
* @param signaltype the signaltype which has changed.
*/
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
		if (running)
		{
			const char startedStr[] = "S started\n";
			count = sizeof(startedStr);
			//patientHandler->start();
			strncpy(buf, startedStr, count);
		}
		else
		{
			const char stoppedStr[] = "S stopped\n";
			count = sizeof(stoppedStr);
			//patientHandler->stop();
			strncpy(buf, stoppedStr, count);
		}
		break;
	}
	case PATIENT_CHANGE:
	{
		string response = "P ";
		response.append(patientHandler->getName());
		count = response.length();
		strncpy(buf, response.c_str(), count);
		break;
	}
	default:
		break;
	}
	if (count > 0)
	{
		remoteAdminStream.send(buf, count, 0);

		cout << "sending to server: " << buf << endl;

	}
}
