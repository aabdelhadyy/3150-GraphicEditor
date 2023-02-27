#include "ECMouseObserver.h"
#include <iostream>

//************************************************************
using namespace std;
ECMouseObserver::ECMouseObserver(ECGraphicViewImp& viewIn, ECController &ctrlIn) : view(viewIn), ctrl(ctrlIn), fIsMouseClicked(false), moving(false)
{
    int cx1, cy1, cx2, cy2 = 0;
    cout << "Initialized." << endl;
}

void ECMouseObserver::Update()
{
    ECGVEventType evt = view.GetCurrEvent();
    // is this space bar key released?
    if (evt == ECGV_EV_MOUSE_BUTTON_DOWN)
    {
        fIsMouseClicked = true;
        if (!ctrl.Editing()) {
            view.GetCursorPosition(cx1, cy1);
            cout << cx1 << " " << cy1 << endl;
            
        }
        if (ctrl.Editing()){
            view.GetCursorPosition(cx1, cy1);
            if (ctrl.ClickSelected(cx1, cy1)) {
                moving = true;
                cout << "Clicked on selected object." << endl;
            }
            else if (ctrl.SelectObject(cx1, cy1)) {
                objectSelected = true;
                cout << "Selected." << endl;
            }
        }
    }
    if (evt == ECGV_EV_MOUSE_BUTTON_UP)
    {
        fIsMouseClicked = false;
        view.GetCursorPosition(cx2, cy2);
        if (!ctrl.Editing()) {
            cout << cx2 << " " << cy2 << endl;
            if (ctrl.DrawingEllipse()) {
                ctrl.CreateEllipse(cx1, cy1, cx2, cy2);
            }
            else ctrl.CreateRectangle(cx1, cy1, cx2, cy2);
        }

        if (ctrl.Editing()) {
            if (moving) {
                int deltax = cx2 - cx1;
                int deltay = cy2 - cy1;
                ctrl.MoveSelected(deltax, deltay);
                moving = false;
            }
        }
        //ctrl.DrawAll();{
        // 
        //view.SetRedraw(true);
        // set the view to redraw
        // Note: call SetRedraw(true) once there is something changed in the view
        //view.SetRedraw(true);
    }
    // if this is the timer event
    if (evt == ECGV_EV_TIMER)
    {
        // if space bar already pressed, draw a winidow
        // Note: you need to draw this in the timer event; otherwise you won't see the rectangle
        
        if (fIsMouseClicked && !ctrl.Editing())
        {
            if (ctrl.DrawingEllipse()) {
                ctrl.DrawEllipse(cx1, cy1);
            }
            else ctrl.DrawRectangle(cx1, cy1);
            //view.DrawRectangle(cx1, cy1, cx2, cy2);
        }
        if (moving && ctrl.Editing()) {
            ctrl.MovingSelected(cx1, cy1);
        }
        ctrl.DrawAll();
    }
}

