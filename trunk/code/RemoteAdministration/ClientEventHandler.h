#pragma once
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include "eventhandler.h"
#include "reactor.h"
#include "sockacceptor.h"
#include "ClientList.h"

/**
Responsible for handling all event related to a client

 */
class ClientEventHandler :
	public EventHandler
{
public:
	ClientEventHandler(); //Just for local testing
	ClientEventHandler( const SockStream &stream );
	~ClientEventHandler(void);

	virtual void HandleEvent ( HANDLE handle, Event_Type event_type );
	virtual HANDLE GetHandle();
	bool IsRunning();
	std::string GetCurrentPatient();
	
	std::vector <std::string> GetPatientList();
	void SetRunning(bool);
	void SetRunning();
	void SelectPatient(std::string);
	bool IsNewPatientList();
	void RequestPatientList();
	std::vector <std::string> patientList; //public for local testing
private:
	// Receives logging records from a connected client
	void SetPatientList(char *data,int res);
	SockStream peerStream;
		// Cached <Reactor>.
	Reactor *reactor;
	bool status;
	std::string currentPatient;
//	std::vector <std::string> patientList;
	bool isPatientListNew;

};

