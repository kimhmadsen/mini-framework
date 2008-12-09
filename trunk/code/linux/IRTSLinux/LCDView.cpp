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

    //if one elemement in a array initialised, the rest is initialised to default 0 in c++
    for (int i = 0; i < rows; i++)
        _signals[i][i] = 0;
    for (int i = 0; i < 3; i++)
        fillcount[i] = 0;
    isActive = true;
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
        _signals[1][fillcount[EDR]]=_dm->getEDR();
        (fillcount[EDR])++;
        if ((fillcount[EDR]) == 39)
        {
            // do magic
            //delete [] _signals[0];
            //Draw();
            for (int i = 0; i < 40; i++)
                _signals[0][i] = _signals[1][i];
            (fillcount[EDR]) =0;
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
        pulse = (int)_dm->getPulse();
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

        for (int i = 0; i < 30; i++)
            std::cout << std::endl;
        std::cout << "LCD VIEW" << std::endl;
        std::cout << "PULSE: " << pulse << std::endl << std::endl;
        std::cout << "EDR values: " << std::endl;
        for (int d = 0; d < 2; d++)
        {
            int untill = 40;
            for (int i = 0; i< untill; i++)
            {
                std::cout << _signals[d][i] << " , ";
            }
            untill = fillcount[EDR];

        }

        std::cout << std::endl << "ECG values: " << std::endl;
        for (int d = 2; d < 4; d++)
        {
            int untill = 40;
            for (int i = 0; i< untill; i++)
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
    case ECG:
        IsType(ECG) ? isECG = false : isECG = true;
    case PULSE:
        IsType(PULSE) ? isPULSE = false : isPULSE = true;
    default:
        break;
    }
}

void LCDView::SetActive(bool ac)
{
    isActive = ac;
}
