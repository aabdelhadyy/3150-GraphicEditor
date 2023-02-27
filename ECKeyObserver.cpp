#include "ECKeyObserver.h"
#include <iostream>

//************************************************************
using namespace std;
ECKeyObserver::ECKeyObserver(ECGraphicViewImp& viewIn, ECController& ctrlIn) : view(viewIn), ctrl(ctrlIn), editMode(false)
{
    //ctrlPressed = false;
    int cx1, cy1, cx2, cy2 = 0;
    cout << "Initialized." << endl;
}

void ECKeyObserver::Update()
{
    ECGVEventType evt = view.GetCurrEvent();
    // is this space bar key released?
    if (evt == ECGV_EV_KEY_DOWN_SPACE)
    {
        ctrl.SwitchModes();
        cout << "Editing: " << ctrl.Editing() << endl;
        if (!ctrl.Editing()) {
            ctrl.UnselectObject();
        }
        //ctrl.DrawAll();
        //view.SetRedraw(true);
        // set the view to redraw
        // Note: call SetRedraw(true) once there is something changed in the view
        //view.SetRedraw(true);
    }
    if (evt == ECGV_EV_KEY_UP_G) {
        if (!ctrl.Editing()) {
            ctrl.SwitchShape();
            cout << "Ellipse: " << ctrl.DrawingEllipse() << endl;
        }
        if (ctrl.Editing()) {
            ctrl.GroupSelected();
        }
    }
    if (evt == ECGV_EV_KEY_DOWN_F) {
        ctrl.ToggleFilled();
    }

    if (evt == ECGV_EV_KEY_DOWN_Z) {
        ctrl.Undo();
    }
    if (evt == ECGV_EV_KEY_DOWN_Y) {
        ctrl.Redo();
    }
    if (evt == ECGV_EV_KEY_DOWN_D) {
        ctrl.Delete();
    }
    if (evt == ECGV_EV_KEY_DOWN_UP) {
        if (ctrl.Editing()) {
            ctrl.MoveSelected(0, -10);
        }
    }
    if (evt == ECGV_EV_KEY_DOWN_DOWN) {
        if (ctrl.Editing()) {
            ctrl.MoveSelected(0, 10);
        }
    }
    if (evt == ECGV_EV_KEY_DOWN_LEFT) {
        if (ctrl.Editing()) {
            ctrl.MoveSelected(-10, 0);
        }
    }
    if (evt == ECGV_EV_KEY_DOWN_RIGHT) {
        if (ctrl.Editing()) {
            ctrl.MoveSelected(10, 0);
        }
    }
    if (evt == ECGV_EV_KEY_DOWN_CTRL) {
        //ctrlPressed = true;
    }
    // if this is the timer event
    if (evt == ECGV_EV_TIMER)
    {
        // if space bar already pressed, draw a winidow
        // Note: you need to draw this in the timer event; otherwise you won't see the rectangle
        
    }
}