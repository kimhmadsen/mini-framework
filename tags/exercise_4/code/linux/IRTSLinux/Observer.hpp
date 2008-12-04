#ifndef Observer_HPP
#define Observer_HPP

class Subject;

class Observer {

 private:
  
 protected:

 
  bool isECG;
  bool isEDR;
  bool isPULSE;
  static const int numOfSignaltypes = 3;

 public:
 enum Signaltypes{ ECG, EDR, PULSE };
  ~Observer(){};
  virtual void Update(Subject* theModel, Signaltypes signaltype)= 0;
  virtual void SetType(Signaltypes) = 0;
  virtual bool IsType(Signaltypes) = 0;
 //protected:
  Observer(){};


};

#endif
