#pragma once
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include "eventhandler.h"
#include "reactor.h"
#include "sockacceptor.h"
#include "ClientList.h"

class ClientEventHandler :
	public EventHandler
{
public:
	ClientEventHandler( const SockStream &stream, Reactor *reactor);
	~ClientEventHandler(void);

	virtual void HandleEvent ( HANDLE handle, Event_Type event_type );
	virtual HANDLE GetHandle();
	bool IsRunning();
	std::string GetCurrentPatient();
	
	std::vector <std::string> GetPatientList();
	void SetRunning(bool);
	void SelectPatient(std::string);
	bool IsNewPatientList();
	void RequestPatientList();
private:
	// Receives logging records from a connected client
	void SetPatientList(char *data,int res);
	SockStream peerStream;
		// Cached <Reactor>.
	Reactor *reactor;
	bool status;
	std::string currentPatient;
	std::vector <std::string> patientList;
	bool isPatientListNew;

};

