
/**
 * @file
 * Defines the xx class
 */
#ifndef LCDView_hpp
#define LCDView_hpp


#include "Observer.hpp"
#include "PatientHandler.h"
#include "PatientDb.h"

/**
* @ingroup view
* The LCD view display ECG and EDR signals
*Implements the observer part of the observer pattern.
*/
class LCDView : protected Observer
{
public:
    /**
    * Constructor
    * @param dm reference the current patient handler.
    */
    LCDView(PatientHandler *dm);
    /**
    * Destructor
    */
    ~LCDView();
    /**
    * callback function part of the observer pattern. Called from the model when ever it changes.
    * @param theModel reference to the model
    * @param signaltype the signaltype which has changed.
    */
    void Update(Subject* theModel, Signaltypes signaltype);
    /**
    * set the signal type
    */
    void SetType(Signaltypes signals);
    /**
    * check the signal type
    */
    bool IsType(Signaltypes signals);
    /**
    * Draws the display
    */
    void Draw();
    /**
    * set and clear the active flag.
    */
    void SetActive(bool);

    /**
     * Controls the UI
     */
    void Run(void);
private:
    PatientHandler *_dm; ///< reference the pateint handler
    static const int rows = 4; ///< the number of rows
    float _signals[rows][40]; ///< the signal values
    int pulse; ///< the current pulse
    int fillcount[3]; ///< the fill count
    bool isActive; ///< holds the active flag
    void printMenu(void);
};

#endif
