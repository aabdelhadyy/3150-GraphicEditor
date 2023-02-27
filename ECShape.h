#ifndef ECSHAPE_H
#define ECSHAPE_H

//#include "ECLine"
#include "ECGraphicViewImp.h"
#include <algorithm>
#include <vector>

class ECShape {
public:
	ECShape(ECGraphicViewImp& viewIn) :view(viewIn) {
		deleted = selected = moving = false;
		grouped = true;
		lastMove = -1;
	};
	virtual ~ECShape() {}
	virtual void Execute() const = 0;
	virtual void Move(int x, int y) = 0;
	virtual void UndoMove() = 0;
	virtual void RedoMove() = 0;
	virtual void Moving(int x, int y) = 0;
	// virtual void Unmove() = 0;
	virtual void Select(bool input) {
		selected = input;
		if (selected) {
			color = ECGV_BLUE;
		}
		else if (!selected) {
			color = ECGV_BLACK;
		}
	};
	virtual bool Selected() {return selected;}
	virtual bool IsPointInside(int x, int y) const = 0;
	virtual void Delete(bool input) { deleted = input; }
	virtual void Group() { grouped = true; }
	virtual void Ungroup() { grouped = false; }
	//virtual void GetCenter(int& x, int& y) const = 0;
protected:
	ECGraphicViewImp& view;
	std::vector<int> changesX;
	std::vector<int> changesY;
	ECGVColor color;
	int lastMove;
	bool deleted;
	bool selected;
	bool moving;
	bool grouped;
};

class ECRectangle : public ECShape {
public:
	ECRectangle(ECGraphicViewImp& viewIn, int x, int y, int cx, int cy, bool filledIn) : ECShape(viewIn){
		_x = x;
		_y = y;
		_cx = cx;
		_cy = cy;
		filled = filledIn;
	}
	virtual void Execute() const;
	virtual void Select(bool input);

	virtual bool IsPointInside(int x, int y) const;
	virtual void UndoMove();
	virtual void RedoMove();
	virtual void Move(int deltax, int deltay);
	virtual void Moving(int deltax, int deltay);
private:
	int _x, _y, _cx, _cy;
	bool filled;
};

class ECEllipse : public ECShape {
public:
	ECEllipse(ECGraphicViewImp& viewIn, int x, int y, int cx, int cy, bool filledIn); 
	virtual void Execute() const;
	virtual bool IsPointInside(int x, int y) const;
	virtual void UndoMove();
	virtual void RedoMove();
	virtual void Move(int deltax, int deltay);
	virtual void Moving(int deltax, int deltay);
	//void GetCenter(int& cx, int& cy);
private:
	int centerx, centery, radiusx, radiusy;
	bool filled;
};



class ECComposite : public ECShape {
public:
	ECComposite(ECGraphicViewImp& viewIn, std::vector<ECShape*> listChildrenIn) : ECShape(viewIn), listChildren(listChildrenIn) {
		grouped = true;
	}
	virtual void Execute() const;
	virtual bool IsPointInside(int x, int y) const;
	virtual void Select(bool input) override;
	virtual void UndoMove();
	virtual void RedoMove();
	virtual void Move(int deltax, int deltay);
	virtual void Moving(int deltax, int deltay);
private:
	std::vector<ECShape*> listChildren;
};
#endif // !ECSHAPE_H