/**
 * @file
 * Defines the Subject class
 */
#ifndef Subject_HPP
#define Subject_HPP

#include <list>
#include <iostream>
//class Observer;
#include "Observer.hpp"

/**
 * Subject is an interface for classes playing the 'subject' role in the observer pattern.
 *
 */
class Subject
{

protected:
	//enum Signaltypes{ ECG, EDR, PULSE };
	std::list<Observer *> *_observers; ///< List with all observers

public:
	~Subject()
	{
	}
	/**
	 * Attach an observer to the subject
	 * @param o Observer
	 */
	virtual void Attach(Observer *);

	/**
	 * Attach an observer to the subject
	 */
	virtual void Detach(Observer *);

	/**
	 * Notifies the changes in the subject to the different observers
	 */
	virtual void Notify(Observer::Signaltypes signaltypes);
	Subject()
	{
		_observers = new std::list<Observer *>;
	}
};

#endif

