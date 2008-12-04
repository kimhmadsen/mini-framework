
#include "Subject.hpp"

void Subject::Attach(Observer *o)
{
  _observers->push_back(o);
}


void Subject::Detach(Observer *o)
{
  _observers->remove(o);
}

void Subject::Notify(Observer::Signaltypes signaltypes)
{
  std::list<Observer *>::iterator i;

  for(i = _observers->begin(); i != _observers->end(); i++) {
	if((*i)->IsType(signaltypes))
	{
	  (*i)->Update(this, signaltypes);
	  //std::cout << "DONKIFY" << std::endl;
	}

  }
}
