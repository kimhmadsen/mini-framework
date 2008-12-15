	// PatientServer.cpp : Defines the entry point for the console application.
//

/**
 * @mainpage
 * The server application shall handle the following events:
 * - an alarm event (carrying a priority field and a text string)
 * - a patient value event (carrying a type field and a value field)
 * - a log event (carrying a text string)
 *
 * 
 * Each time an alarm is received the application shall display the last 10 alarms on the screen in priority order with a time stamp.
 * The received patient values are displayed as they are received.
 * Received log events are displayed as the are received (in real life: should be stored on a log file).
 *
 */

#include "stdafx.h"
#include "minifw.h"
#include "inetaddr.h"
#include "reactor.h"
#include "selectreactor.h"
#include "acceptortemplate.h"
#include "patientinfoeventhandler.h"
#include "ClientEventHandler.h"
#include "ClientList.h"
#include "LFThreadPool.h"
#include "threadmanager.h"
#include <cstdlib>
#include <conio.h>
#include <windows.h>

#define TRACE(x) 

const short CLIENT_PORT = 10000;
std::vector <std::string> patientList;
void *worker_thread(void *);
void DoTheUI();

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Remote Administration starting power-up sequence.\n";

	InetAddr client_addr( CLIENT_PORT );
	MiniFwInit(); 
	AcceptorTemplate<ClientEventHandler> ClientAcceptor( client_addr, SelectReactor::instance() );
	std::cout << "Waiting for Client on port " << client_addr.GetPort() << "\n";

	//ClientEventHandler *ceh = new ClientEventHandler();
	//ceh->SelectPatient("HANS WIGGO");
	//ceh->patientList.push_back("KYLE");
	//ceh->patientList.push_back("STAN");
	//ceh->patientList.push_back("CARTMAN");
	//ceh->patientList.push_back("BUTTERS");

	//ClientEventHandler *cehw = new ClientEventHandler();
	//cehw->SelectPatient("HANS OLE");
	//cehw->SetRunning(true);
	LFThreadPool lftp(SelectReactor::instance());

	for(int i = 0; i < 5; ++i)
		ThreadManager::Instance()->Spawn(worker_thread, &lftp);

	//lftp.JoinPool();

	DoTheUI();
	for(;;)
	{

		TIMEVAL tv;
		tv.tv_sec  = 10;
		tv.tv_usec = 100000;
		SelectReactor::instance()->HandleEvents( &tv );
		// do timeout things 
		TRACE( printf( "." ) );
	}

	return 0;
}

void DrawLine(){

	for(int i =0; i < 5; i++)
		std::cout << " ";
	for(int i =0; i < 50; i++)
		std::cout << "#";
	std::cout << std::endl;

}

void DrawGeneralHeading(){

	for(int i =0; i < 5; i++)
		std::cout << " ";

	for(int i= 0; i < 3; i++)
		std::cout << "#";
	std::cout << "ID";
	for(int i= 0; i < 3; i++)
		std::cout << "#";
	std::cout << "NAME";
	
	for(int i = 0; i < 15; i++)
		std::cout << "#";

	std::cout << "STATUS";
	for(int i = 0; i <17; i++)
		std::cout << "#";
	std::cout << std::endl;
}
void DrawPatients(){
	
	ClientList *cl = ClientList::Instance();
	for(int loop = 0; loop < cl->Size(); loop++){
		for(int i =0; i < 5; i++)
			std::cout << " ";
		std::cout << "#";

		for(int i =0; i < 2; i++)
			std::cout << " ";
		
		std::cout << "0" << loop << "  " << (cl->At(loop))->GetCurrentPatient() << "   ";
		if(cl->At(loop)->IsRunning())
			std::cout << "Running";
		else
			std::cout << "Stopped";

		for(int i = 0; i < 32 - cl->At(loop)->GetCurrentPatient().size(); i++)
			std::cout << " ";
		std::cout << "#" << std::endl;

	}
}

void DrawPatient(int patient){

	
	ClientList *cl = ClientList::Instance();
	for(int i =0; i < 5; i++)
		std::cout << " ";
	std::cout << "#";
	for(int i = 0; i < 48; i++)
		std::cout << " ";
	std::cout << "#" << std::endl;
	for(int i =0; i < 5; i++)
		std::cout << " ";
	std::cout << "#";
	for(int i = 0; i < 48; i++)
		std::cout << " ";
	std::cout << "#" << std::endl;

	for(int i =0; i < 5; i++)
		std::cout << " ";
	std::cout << "#";
	for(int i = 0; i < 2; i++)
		std::cout << " ";
	std::cout << "ID :" << patient;
	for(int i = 0; i < 41; i++)
		std::cout << " ";
	std::cout << "#" << std::endl;

	cl->At(patient)->RequestPatientList();
	while(!(cl->At(patient)->IsNewPatientList()))
	{
		Sleep(500);
	}

	patientList = cl->At(patient)->GetPatientList();

	for(int loop = 0; loop < patientList.size(); loop++)
	{

		for(int i =0; i < 5; i++)
			std::cout << " ";
		std::cout << "#";
		for(int i = 0; i < 2; i++)
			std::cout << " ";
		std::cout << loop << "  " << patientList.at(loop);

		for(int i = 0; i < 43 - patientList.at(loop).size(); i++)
			std::cout << " ";
		std::cout << "#" << std::endl;

	}

}
void DrawMenu(int type) {

	switch(type)
	{
	case 1:
		for(int i = 0 ; i < 10; i++)
			std::cout << " ";
		std::cout << "Press S to toggle client STATUS" << std::endl;
		for(int i = 0 ; i < 10; i++)
			std::cout << " ";
		std::cout << "Press the ID to selection configuration" << std::endl;
		for(int i = 0 ; i < 10; i++)
			std::cout << " ";
		std::cout << "Press m for update display" << std::endl;


		break;
	case 2:
		for(int i = 0 ; i < 10; i++)
			std::cout << " ";
		std::cout << "Press the ID of the client to toggle STATUS on" << std::endl;
		for(int i = 0 ; i < 10; i++)
			std::cout << " ";
		std::cout << "Press m for main menu" << std::endl;
		break;
	case 3:
		for(int i = 0 ; i < 10; i++)
			std::cout << " ";
		std::cout << "Press the # of the patient to use" << std::endl;
		for(int i = 0 ; i < 10; i++)
			std::cout << " ";
		std::cout << "Press m for main menu" << std::endl;
		break;
	default:
		for(int i = 0 ; i < 10; i++)
			std::cout << " ";
		std::cout << "Press S to toggle client STATUS\nPress the ID to selection configuration" << std::endl;
		break;
	}

}

void ShowAll(){

	DrawGeneralHeading();
	DrawPatients();
	DrawLine();

}


void ShowPatient(int i){

	DrawLine();
	DrawPatient(i);
	DrawLine();

}

void DoTheUI(){

	char prevselection = 'm';
	char selection = 'm';
	for(;;){
		
		if(selection != 's' && selection > 64 && selection != 'p') {
			system("cls");
			std::cout << std::endl << std::endl;
			ShowAll();
			DrawMenu(1);
			selection = 'b';
			while(selection != 'm' && selection != 's' && (selection > 64 || selection < 48)){
				std::cin >> selection;
			}
		}
		if(selection == 's')
		{
			system("cls");
			std::cout << std::endl << std::endl;
			ShowAll();
			DrawMenu(2);

			ClientList *cl = ClientList::Instance();
			while(selection != 'm' && (selection-48 < 0 || selection - 48 >cl->Size())){	
				std::cin >> selection;
			}
			
			if(selection > 64 || selection < 48)
			{
				selection = 'm';
			}
			else
				cl->At(selection-48)->SetRunning();
		
			selection = 'm';
		}

		if(selection <= 64 && selection >= 48)
		{
			//Select the patient on client
			system("cls");
			std::cout << std::endl << std::endl;
			int patient = selection - 48;
			ShowPatient(patient);
			DrawMenu(3);
			selection = 'b';
			ClientList *cl = ClientList::Instance();
			while(selection != 'm' && (selection-48 < 0 || selection - 48 >patientList.size())){	
				std::cin >> selection;
			}

			cl->At(patient)->SelectPatient(patientList.at(selection-48));
			selection = 'm';
		}

	}

}

void *worker_thread(void *arg)
{

	LFThreadPool *threadpool = static_cast<LFThreadPool *> (arg);
	threadpool->JoinPool();

	return 0;
}