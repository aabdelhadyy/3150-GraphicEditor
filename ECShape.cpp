#include "ECShape.h"
#include <iostream>
using namespace std;
void ECRectangle :: Execute() const {
	if (!moving && !deleted) {
		if (!filled) {
			view.DrawRectangle(_x, _y, _cx, _cy, 3, color);
		}
		if (filled) {
			view.DrawFilledRectangle(_x, _y, _cx, _cy, color);
		}
	}
};
void ECRectangle::Select(bool input) {
	selected = input;
	if (selected) {
		color = ECGV_BLUE;
	}
	else if (!selected) {
		color = ECGV_BLACK;
	}
}

bool ECRectangle::IsPointInside(int x, int y) const {
	if ((std::min(_x, _cx) <= x && x <= std::max(_x, _cx)) &&
		(std::min(_y, _cy) <= y && y <= std::max(_y, _cy))) {
		return true;
	}
	else return false;
}

void ECRectangle::UndoMove() {
	if (lastMove > -1) {
		//moving = false;
		int deltax = changesX[lastMove];
		int deltay = changesY[lastMove];
		_x -= deltax;
		_y -= deltay;
		_cx -= deltax;
		_cy -= deltay;
		lastMove--;
	}
}

void ECRectangle::RedoMove() {
	lastMove++;
	int deltax = changesX[lastMove];
	int deltay = changesY[lastMove];
	_x += deltax;
	_y += deltay;
	_cx += deltax;
	_cy += deltay;
}

void ECRectangle::Move(int deltax, int deltay) {
	_x += deltax;
	_y += deltay;
	_cx += deltax;
	_cy += deltay;
	changesX.push_back(deltax);
	changesY.push_back(deltay);
	lastMove++;
	moving = false;
}
void ECRectangle::Moving(int deltax, int deltay) {
	moving = true;
	view.DrawRectangle(_x + deltax, _y + deltay, _cx + deltax, _cy + deltay, 3, color);
}


ECEllipse::ECEllipse(ECGraphicViewImp& viewIn, int centerxIn, int centeryIn, int radiusxIn, int radiusyIn, bool filledIn) : ECShape(viewIn){
	centerx = centerxIn;
	centery = centeryIn;
	radiusx = radiusxIn;
	radiusy = radiusyIn;
	filled = filledIn;
}

void ECEllipse::Execute() const {
	if (!moving && !deleted) {
		if (!filled) {
			view.DrawEllipse(centerx, centery, radiusx, radiusy, 3, color);
		}
		if (filled) {
			view.DrawFilledEllipse(centerx, centery, radiusx, radiusy, color);
		}
	}
}


bool ECEllipse::IsPointInside(int x, int y) const {
	if (((centerx - radiusx <= x) && (x <= centerx + radiusx)) &&
		((centery - radiusy <= y) && (y <= centery + radiusy))) {
		return true;
	}
	else return false;
}
void ECEllipse::Moving(int deltax, int deltay) {
	moving = true;
	view.DrawEllipse(centerx + deltax, centery + deltay, radiusx, radiusy, 3, color);
}

void ECEllipse::Move(int deltax, int deltay) {
	centerx += deltax;
	centery += deltay;
	changesX.push_back(deltax);
	changesY.push_back(deltay);
	lastMove++;
	moving = false;
}

void ECEllipse::UndoMove() {
	if (lastMove > -1) {
		//moving = false;
		int deltax = changesX[lastMove];
		int deltay = changesY[lastMove];
		centerx -= deltax;
		centery -= deltay;
		lastMove--;
	}
}

void ECEllipse::RedoMove() {
	lastMove++;
	int deltax = changesX[lastMove];
	int deltay = changesY[lastMove];
	centerx += deltax;
	centery += deltay;
}




void ECComposite::Execute() const {
	if (grouped)
	{
		if (!moving && !deleted) {
			for (auto x : listChildren) {
				x->Execute();
			}
		}
	}
}

void ECComposite::Select(bool input) {
	if (grouped)
	{
		selected = input;
		for (auto x : listChildren) {
			x->Select(selected);
		}
	}
}

bool ECComposite::IsPointInside(int x, int y) const{
	if (grouped)
	{
		for (auto shape : listChildren) {
			if (shape->IsPointInside(x, y)) {
				return true;
			}
		}
		return false;
	}
}

void ECComposite::UndoMove() {
	if (grouped)
	{
		if (lastMove > -1) {
			for (auto shape : listChildren) {
				shape->UndoMove();
			}
		}
		lastMove--;
	}
}

void ECComposite::RedoMove() {
	if (grouped)
	{
		lastMove++;
		for (auto shape : listChildren) {
			shape->RedoMove();
		}
	}
}

void ECComposite::Moving(int x, int y) {
	if (grouped)
	{
		moving = true;
		for (auto shape : listChildren) {
			shape->Moving(x, y);
		}
	}
}

void ECComposite::Move(int deltax, int deltay) {
	if (grouped)
	{
		for (auto shape : listChildren) {
			shape->Move(deltax, deltay);
		}
		changesX.push_back(deltax);
		changesY.push_back(deltay);
		lastMove++;
		moving = false;
	}
}
