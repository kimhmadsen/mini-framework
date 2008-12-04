#include "LCDView.hpp"
#include <iostream>

LCDView::LCDView(PatientHandler *dm)
{
	_dm = dm;
	_dm->Attach(this);
	isEDR = false;
	isECG = true;
	isPULSE = false;
	/**
	 * ECG = arrays 0 - 5, where array 5 is the temporay filler.
	 * EDR = arrays 6 - 11, where array 11 is the temporay filler.
	 * PULSE = arrays 12 - 17, where array 17 is the temporay filler.
	 */
	//*_signals = new float[6*numOfSignaltypes];
	
	//if one elemement in a array initialised, the rest is initialised to default 0 in c++
	for(int i = 0; i < 6*numOfSignaltypes; i++)
		_signals[i][i] = 0;
	fillcount[0] = 0;
}

LCDView::~LCDView()
{
	_dm->Detach(this);
}

void LCDView::Update(Subject *_sbj, Signaltypes signaltypes)
{
	//std::cout << "HEY - UPDATE" << std::endl;
	switch (signaltypes)
	{
	case EDR:
		//_signals[11][fillcount[EDR]]=dm->getEDR();
		(fillcount[EDR])++;
		if(fillcount[EDR] == 99)
		{
			// do magic
			delete [] _signals[0];
			for(int i = 0; i < 5; i++)
				*_signals[i] = *_signals[i+1];
			fillcount[EDR] =0;
			Draw();
		}
		break;
	case ECG:
		_signals[5][fillcount[ECG]] = _dm->getECG();
		std::cout << "ECG VALUE - " << _signals[5][fillcount[ECG]];
		(fillcount[ECG])++;
		if(fillcount[ECG] == 99)
		{
			// do magic
			//delete [] _signals[6];
			for(int i = 0; i < 5; i++)
				for(int d = 0; d < 100; d++)
					_signals[i][d] = _signals[i+1][d];
			fillcount[ECG] = 0;
			Draw();
		}
		break;
	case PULSE:
		//_signals[17][fillcount[PULSE]] = dm->getPULSE();
		(fillcount[PULSE])++;
		if(fillcount[PULSE] == 99)
		{
			// do magic
			//delete [] _signals[12];
			for(int i = 12; i < 17; i++)
				*_signals[i] = *_signals[i+1];
			
			//*_signals[17] = new float[100];
			fillcount[PULSE] = 0;
			Draw();
		}	
		break;
	default:
		break;
	}
		
}

void LCDView::Draw()
{
	for(int d = 0; d < 5; d++)
		for(int i = 0; i< 100; i++)
			std::cout << "ECG " << _signals[5][i] << std::endl; 
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
	case ECG:
		IsType(ECG) ? isECG = false : isECG = true;
	case PULSE:
		IsType(PULSE) ? isPULSE = false : isPULSE = true;
	default:
		break;
	}
}