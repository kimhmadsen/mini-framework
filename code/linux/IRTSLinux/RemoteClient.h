/*
 * RemoteClient.h
 *
 *  Created on: 14-12-2008
 *      Author: kim
 */

#ifndef REMOTECLIENT_H_
#define REMOTECLIENT_H_

#include "sockstream.h"
#include "sockconnector.h"
#include "PatientHandler.h"
#include "Observer.hpp"

class RemoteClient: protected Observer
{
	short serverPort;
	char* serverIp;
	PatientHandler* patientHandler;
	SockStream remoteAdminStream;
	SOCK_Connector remoteAdminConnector;

public:
	RemoteClient(short serverPort, char* serverIp,
			PatientHandler* patientHandler);
	virtual ~RemoteClient();
	// obsever functions
	void Update(Subject* theModel, Signaltypes signaltype);


	int Connect(void);
	int Disconnect(void);
	void Run(void);
};

#endif /* REMOTECLIENT_H_ */
