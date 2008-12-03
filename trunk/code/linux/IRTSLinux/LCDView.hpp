#ifndef LCDView_hpp
#define LCDView_hpp


#include "Observer.hpp"
#include "PatientHandler.h"

class LCDView : protected Observer
{
	public:
	LCDView(PatientHandler *);
	~LCDView();
	void Update(Subject* theModel, Signaltypes signaltype);
	void SetType(Signaltypes signals);
	bool IsType(Signaltypes signals);
	void Draw();
	private:
	PatientHandler *_dm;
	float _signals[6*numOfSignaltypes][100];
	int fillcount[3];
}; 

#endif