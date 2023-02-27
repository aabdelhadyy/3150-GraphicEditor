#include "ECController.h"
#include <iostream>
using namespace std;

bool ECGraphicDoc::SelectObject(int x, int y) {

	for (auto shape : listShapes) {
		if (shape->IsPointInside(x, y) && !shape->Selected()) {
			shape->Select(true);
			selectedShapes.push_back(shape);
			return true;
		}
	}
	return false;
	//cout << "SelectObject returned NULL" << endl;
}

bool ECGraphicDoc::ClickSelected(int x, int y) {
	for (auto shape : selectedShapes) {
		if (shape->IsPointInside(x, y)) {
			return true;
		}
	}
	return false;
}

void ECGraphicDoc::MovingSelected(int deltax, int deltay) {
	for (auto shape : selectedShapes) {
		shape->Moving(deltax, deltay);
	}
	DrawAll();
}

void ECGraphicDoc::MoveSelected(int deltax, int deltay) {
	for (auto shape : selectedShapes) {
		shape->Move(deltax, deltay);
		hist.AddEvent(MOVING, shape);
	}
	DrawAll();
}

void ECGraphicDoc::GroupSelected(ECGraphicViewImp& viewIn) {
	if (selectedShapes.size() > 1) {
		ECShape* newComp = new ECComposite(viewIn, selectedShapes);
		selectedShapes.clear();
		AddShape(newComp);
		cout << "Grouped." << endl;
		DrawAll();
	}
	else Ungroup();
}
void ECGraphicDoc::Ungroup() {

}

void ECGraphicDoc::Delete() {
	for (auto shape : selectedShapes) {
		shape->Delete(true);
		hist.AddEvent(DELETION, shape);
	}
	Unselect();
	DrawAll();
}

void ECController::DrawRectangle(int x, int y) {
	view.GetCursorPosition(cx, cy);
	doc.DrawAll();
	view.DrawRectangle(x, y, cx, cy);
	view.SetRedraw(true);
}

void ECController::DrawEllipse(int x, int y) {
	view.GetCursorPosition(cx, cy);
	int centerx = (x + cx) / 2;
	int centery = (y + cy) / 2;
	doc.DrawAll();
	view.DrawEllipse(centerx, centery, abs(cx-centerx), abs(cy-centery));
	view.SetRedraw(true);
}

void ECController::CreateRectangle(int x, int y, int cx, int cy) {

	ECShape* newRect = new ECRectangle(view, x, y, cx, cy, filled);
	//listShapes.push_back(newRect);
	//DrawAll();
	doc.AddShape(newRect);
	cout << "Rectangle added." << endl;
	doc.DrawAll();
}

void ECController::CreateEllipse(int x, int y, int cx, int cy) {
	int centerx = (x + cx) / 2;
	int centery = (y + cy) / 2;
	ECShape* newElip = new ECEllipse(view, centerx, centery, abs(cx- centerx), abs(cy-centery), filled);
	doc.AddShape(newElip); 
	cout << "Ellipse added." << endl;
	doc.DrawAll();
}

void ECController::CreateComposite(vector<ECShape*> listShapes) {
	ECShape* newComp = new ECComposite(view, listShapes);
	doc.AddShape(newComp);
	cout << "Composite added." << endl;
	doc.DrawAll();
}

bool ECController::SelectObject(int x, int y) {
	if (doc.SelectObject(x, y) != false) {
		//selectedShapes.push_back(doc.SelectObject(x, y));
		cout << "Shape added to vector." << endl;
		//view.SetRedraw(true);
		doc.DrawAll();
		
		return true;
	}
	return false;
}

bool ECController::ClickSelected(int x, int y) {
	//cout << "ClickSelected called." << endl;
	return doc.ClickSelected(x, y);
}

void ECController::MoveSelected(int x, int y) {
	doc.MoveSelected(x,y);
	//doc.Unselect();
}

void ECController::MovingSelected(int x, int y) {
	view.GetCursorPosition(cx, cy);
	int deltax = cx - x;
	int deltay = cy - y;
	doc.MovingSelected(deltax, deltay);
	doc.DrawAll();
}

void ECController::DrawAll() const {
	doc.DrawAll();
	view.SetRedraw(true);
}
