
#ifndef MouseObserver_h
#define MouseObserver_h

#include "ECObserver.h"
#include "ECGraphicViewImp.h"
#include "ECController.h"
#include <iostream>

//************************************************************
class ECMouseObserver : public ECObserver
{
public:
    ECMouseObserver(ECGraphicViewImp& viewIn, ECController &ctrlIn);
    virtual void Update();

private:
    ECController& ctrl;
    ECGraphicViewImp& view;
    bool fIsMouseClicked;
    bool objectSelected;
    bool moving;
    int cx1, cy1, cx2, cy2;
};

#endif /* MouseObserver_h */

