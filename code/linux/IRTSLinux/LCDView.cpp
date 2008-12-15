/**
 * @file
 * Implements the LCDView class
 */
#include "LCDView.hpp"
#include <iostream>
#include <stdlib.h>

LCDView::LCDView(PatientHandler *dm)
{
	_dm = dm;
	_dm->Attach(this);
	isEDR = true;
	isECG = true;
	isPULSE = true;

	pulse = 0;
	//if one element in a array initialised, the rest is initialised to default 0 in c++
	//actually.... it doesn't!
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < 40; j++)
			_signals[i][j] = 0;
	}
	for (int i = 0; i < 3; i++)
		fillcount[i] = 0;
	isActive = false;

}

LCDView::~LCDView()
{
	_dm->Detach(this);
}
void LCDView::Run(void)
{
	cout << "LCDView running" << endl;

	printMenu();
	while (true)
	{
		char input[256];
		cin.getline(input, 20);
		string command = input;
		if (command.length() > 0)
		{
			cout << "command to execute: " << command << endl;
			switch (command[0])
			{
			case 'G': // get patient list
			{
				string patientList;
				//std::cout << "\nRemoteClient: command G" << std::endl;
				patientList = PatientDb::Instance()->GetPatientList();
				cout << "response: " << endl << patientList << endl << endl;
				break;
			}
			case 'P': // set current patient
			{
				string patientName;
				patientName = command.substr(2);
				std::cout << "\nRequested Patient: " << patientName
						<< std::endl;
				char name[10];
				memset(name, 0, sizeof(name));
				strcpy(name, patientName.c_str());
				Patient* pat = PatientDb::Instance()->GetPatient(name);
				cout << "patient created: " << pat->getName() << endl;
				_dm->setPatient(pat);
				break;
			}
			case 'S': // start or stop the simulation.
			{
				int pos;
				pos = command.find("start", 1);
				if (pos != -1)
				{
					//const char startedStr[] = "G started\n";
					//count = sizeof(startedStr);
					cout << "starting simulator" << endl;
					_dm->start();

					//strncpy(buf, startedStr, count);
				}
				pos = command.find("stop", 1);
				if (pos != -1) // is -1 the right to look for?
				{
					//const char stoppedStr[] = "G stopped\n";
					//count = sizeof(stoppedStr);
					cout << "stopping simulator" << endl;
					_dm->stop();
					//strncpy(buf, stoppedStr, count);
				}
				break;
			}
			case 'E':
				isActive = true;
				break;
			case 'D':
			{
				isActive = false;
				printMenu();
				break;
			}
			default:
				cout << "Unknown option. Try again" << endl;
				printMenu();
				break;

			}
			sleep(1);
			command = "";
		}

	}

	return;
}
void LCDView::printMenu()
{
	cout << "Simulator options: " << endl;
	cout << "S start  - starts the simulator " << endl;
	cout << "S stop   - stops the simulator " << endl;
	cout << "G        - gets the list of patients  " << endl;
	cout << "P <name> - selects the patient " << endl;
	cout << "E        - enables output" << endl;
	cout << "D        - disables output" << endl;

}

void LCDView::Update(Subject *_sbj, Signaltypes signaltypes)
{
	//std::cout << "HEY - UPDATE" << std::endl;
	switch (signaltypes)
	{
	case EDR:
		_signals[1][fillcount[EDR]] = _dm->getEDR();
		(fillcount[EDR])++;
		if ((fillcount[EDR]) >= 10)
		{
			// do magic
			//delete [] _signals[0];
			//Draw();
			for (int i = 0; i < 10; i++)
				_signals[0][i] = _signals[1][i];
			(fillcount[EDR]) = 0;
			//Draw();
		}
		break;
	case ECG:
		_signals[3][fillcount[ECG]] = _dm->getECG();
		//std::cout << "ECG VALUE - " << _signals[5][fillcount[ECG]];
		(fillcount[ECG])++;
		if (fillcount[ECG] == 39)
		{
			// do magic
			//delete [] _signals[0];
			Draw();
			for (int i = 0; i < 40; i++)
				_signals[2][i] = _signals[3][i];
			(fillcount[ECG]) = 0;

		}
		break;
	case PULSE:
		pulse = (int) _dm->getPulse();
		//Draw();
		break;
	default:
		break;
	}

}

void LCDView::Draw()
{
	if (isActive)
	{

		for (int i = 0; i < 5; i++)
			std::cout << std::endl;
		std::cout << "LCD VIEW" << std::endl;
		std::cout << "PULSE: " << pulse << std::endl << std::endl;
		std::cout << "EDR values: " << std::endl;
		for (int d = 0; d < 2; d++)
		{
			int untill = 10;
			for (int i = 0; i < untill; i++)
			{
				std::cout << _signals[d][i] << " , ";
			}
			untill = fillcount[EDR];

		}

		std::cout << std::endl << "ECG values: " << std::endl;
		for (int d = 2; d < 4; d++)
		{
			int untill = 40;
			for (int i = 0; i < untill; i++)
			{
				std::cout << _signals[d][i] << " , ";
			}
			untill = fillcount[ECG];

		}
	}
}
bool LCDView::IsType(Signaltypes signaltypes)
{
	switch (signaltypes)
	{
	case EDR:
		return isEDR;
	case ECG:
		return isECG;
	case PULSE:
		return isPULSE;
	default:
		return false;
	}
}

void LCDView::SetType(Signaltypes signaltypes)
{
	switch (signaltypes)
	{
	case EDR:
		IsType(EDR) ? isEDR = false : isEDR = true;
		break;
	case ECG:
		IsType(ECG) ? isECG = false : isECG = true;
		break;
	case PULSE:
		IsType(PULSE) ? isPULSE = false : isPULSE = true;
		break;
	default:
		break;
	}
}

void LCDView::SetActive(bool ac)
{
	isActive = ac;
}
