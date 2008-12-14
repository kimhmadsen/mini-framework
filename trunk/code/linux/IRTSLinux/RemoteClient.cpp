/*
 * RemoteClient.cpp
 *
 *  Created on: 14-12-2008
 *      Author: kim
 */

#include <iostream>
#include "RemoteClient.h"

RemoteClient::RemoteClient(short serverPort, char* serverIp)
{

	InetAddr patientAddr(serverPort, serverIp);

	patientConnector.connect(patientStream, patientAddr);
	std::cout << "Patient value stream connected on port " << serverPort
			<< " \n";

}

RemoteClient::~RemoteClient()
{

}

int RemoteClient::Run(void)
{

	//	int i = 0;
	//	while (running)
	//	{
	//		char buf[256];
	//		memset(buf, 0, sizeof buf);
	//		int count;
	//		cout << "request " << i << endl;
	//		if (run.compare("run") == 0)
	//		{
	//			std::cout
	//					<< "Type the cpr number of a patient to get the information: \n";
	//			std::cin.getline(buf, sizeof buf);
	//			count = std::cin.gcount();
	//		}
	//		else //testing...
	//		{
	//			char cpr[] = "090382-3542";
	//			strcpy(buf, cpr);
	//			count = strlen(buf);
	//		}
	//		patientStream.send_n(buf, count, 0);
	//		char buf_in[256];
	//		memset(buf_in, 0, sizeof buf_in);
	//		count = patientStream.recv(buf_in, sizeof buf_in, 0);
	//		std::cout << "\n" << buf_in << std::endl;
	//
	//		i++;
	//
	//		if(run.compare("run")!= 0 && i == numRemoteClient();berOfRequests) //run == "test1" or run == "test2"
	//		running = false;
	//
	//		if (run.compare("test2") == 0 && running)
	//		{
	//			patientConnector.close(patientStream);
	//			patientConnector.connect(patientStream, patientAddr);
	//			std::cout << "Patient value stream connected on port "
	//					<< PATIENT_PORT << " \n";
	//
	//			/*			SockStream patientStream;
	//			 SOCK_Connector patientConnector;
	//			 patientConnector.connect (patientStream, patientAddr);
	//			 std::cout << "Patient value stream connected on port " << PATIENT_PORT << " \n";
	//			 */
	//		}
	//	}

	return 0;
}
