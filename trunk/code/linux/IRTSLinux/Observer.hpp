/**
 * @file
 * Defines the Observer class
 */
#ifndef Observer_HPP
#define Observer_HPP

class Subject;

/**
 * Interface/abstract class for classes implementing the Observer role in the Observer pattern.
 */
class Observer
{

private:

protected:

	bool isECG;
	bool isEDR;
	bool isPULSE;
	bool isSTATE_CHANGE;
	bool isPATIENT_CHANGE;
	static const int numOfSignaltypes = 3;

public:
	enum Signaltypes
	{
		ECG, EDR, PULSE, STATE_CHANGE, PATIENT_CHANGE
	};
	~Observer()
	{
	}
	;

	virtual void Update(Subject* theModel, Signaltypes signaltype)= 0;
	//virtual bool IsType(Signaltypes) = 0;

	void SetType(Signaltypes signaltypes)
	{
		switch (signaltypes)
		{
		case EDR:
			isEDR = !isEDR;
			break;
		case ECG:
			isECG = !isECG;
			break;
		case PULSE:
			isPULSE = !isPULSE;
			break;
		case STATE_CHANGE:
			isSTATE_CHANGE = !isSTATE_CHANGE;
			break;
		case PATIENT_CHANGE:
			isPATIENT_CHANGE = !isPATIENT_CHANGE;
			break;
		default:
			break;
		}

	}

	bool IsType(Signaltypes signaltypes)
	{
		switch (signaltypes)
		{
		case EDR:
			return isEDR;
		case ECG:
			return isECG;
		case PULSE:
			return isPULSE;
		case STATE_CHANGE:
			return isSTATE_CHANGE;
		case PATIENT_CHANGE:
			return isPATIENT_CHANGE;
		default:
			return false;
		}
	}

	//protected:
	Observer()
	{
	}
	;

};

#endif
