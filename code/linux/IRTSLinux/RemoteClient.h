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

class RemoteClient
{
	SockStream patientStream;
	SOCK_Connector patientConnector;

public:
	RemoteClient( short serverPort, char* serverIp );
	virtual ~RemoteClient();
	int Run(void);
};

#endif /* REMOTECLIENT_H_ */
