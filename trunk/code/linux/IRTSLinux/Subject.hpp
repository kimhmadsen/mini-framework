#ifndef Subject_HPP
#define Subject_HPP

#include <list>
#include <iostream>
//class Observer;
#include "Observer.hpp"

class Subject {

 protected:
  //enum Signaltypes{ ECG, EDR, PULSE };
  std::list<Observer *> *_observers;

 public:
  ~Subject(){}
  virtual void Attach(Observer *);
  virtual void Detach(Observer *);
  virtual void Notify(Observer::Signaltypes signaltypes);
  Subject(){
	_observers = new std::list<Observer *>;
	}
};

#endif

