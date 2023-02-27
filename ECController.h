#ifndef ECCONTROLLER_H
#define ECCONTROLLER_H

#include "ECGraphicViewImp.h"
#include "ECShape.h"
#include "ECHistory.h"
#include <vector>
#include <map>
#include <cmath>
//#include "ECCommand.h"


class ECGraphicDoc {
public:
	ECGraphicDoc() : curPos(-1) {}
	void DrawAll() const {
		for (int i = 0; i <= curPos; i++) {
			listShapes[i]->Execute();
		}
		for (auto shape : selectedShapes) {
			shape->Execute();
		}
	};
	void AddShape(ECShape* shapeIn) {
		curPos++;
		listShapes.push_back(shapeIn);
		hist.AddEvent(INSERTION, shapeIn);
	};
	void RemoveShape(ECShape* shapeToRemove) {
		remove(listShapes.begin(), listShapes.end(), shapeToRemove);
		curPos--;
	}
	void Undo() {
		hist.Undo();
		//curPos--;
		DrawAll();
	};
	void Redo() {
		hist.Redo();
		//curPos++;
		DrawAll();
	};
	bool SelectObject(int x, int y);
	//bool DeleteObject();
	void Unselect() {
		for (auto shape : selectedShapes) {
			shape->Select(false);
		}
		selectedShapes.clear();
	};
	void Delete();
	bool ClickSelected(int x, int y);
	void MovingSelected(int x, int y);
	void MoveSelected(int x, int y);
	void GroupSelected(ECGraphicViewImp& viewIn);
	void Ungroup();
private:
	ECHistory hist;
	std::vector<ECShape*> listShapes;
	std::vector<ECShape*> selectedShapes;
	int curPos;
};

class ECController {
public:
	ECController(ECGraphicDoc &docIn, ECGraphicViewImp& viewIn) : doc(docIn), view(viewIn), editMode(false), filled(false), ellipse(false) {}
	void DrawRectangle(int x, int y);
	void DrawEllipse(int x, int y);
	void CreateRectangle(int x, int y, int cx, int cy);
	void CreateEllipse(int x, int y, int cx, int cy);
	void CreateComposite(std::vector<ECShape*>);
	bool DrawingEllipse() {
		return ellipse;
	}
	void SwitchShape() {
		ellipse = !ellipse;
	}
	void DrawAll() const;
	void SwitchModes() {
		editMode = !editMode;
	}
	bool Editing() {
		return editMode;
	}
	bool ClickSelected(int x, int y);
	void MovingSelected(int x, int y);
	void MoveSelected(int x, int y);
	bool SelectObject(int x, int y);
	void UnselectObject() {
		doc.Unselect();
	};
	void GroupSelected() { doc.GroupSelected(view); }
	//void Save();
	void Undo() {
		doc.Undo();
	}
	void Redo() {
		doc.Redo();
	}
	void Delete() {
		doc.Delete();
	}
	void ToggleFilled() { filled = !filled; }

private:
	ECGraphicDoc& doc;
	ECGraphicViewImp& view;
	int cx, cy;
	bool editMode;
	bool filled;
	bool ellipse;
};
#endif // !1