
#ifndef KeyObserver_h
#define KeyObserver_h

#include "ECObserver.h"
#include "ECGraphicViewImp.h"
#include "ECController.h"
#include <iostream>

//************************************************************
class ECKeyObserver : public ECObserver
{
public:
    ECKeyObserver(ECGraphicViewImp& viewIn, ECController& ctrlIn);
    virtual void Update();

private:
    ECController& ctrl;
    ECGraphicViewImp& view;
    bool editMode;
    //bool ctrlPressed;
    //bool KeyMoving;
    int cx1, cy1, cx2, cy2;
};

#endif /* KeyObserver_h */
