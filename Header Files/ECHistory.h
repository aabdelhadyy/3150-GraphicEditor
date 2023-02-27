#ifndef ECHISTORY_H
#define ECHISTORY_H

#include <vector>
#include <iostream>
#include "ECShape.h"
enum ActionType {
	INSERTION = 0,
	DELETION = 1,
	MOVING = 2,
	GROUPING = 3,
	UNGROUPING = 4
};
class ECHistory {
public:
	ECHistory() : curEvent(-1) {}
	void Undo();
	void Redo();
	void AddEvent(ActionType event, ECShape* shape);
private:
	//ECGraphicDoc& doc;
	std::vector<ActionType> listEvents;
	std::vector<ECShape*> listShapes;
	int curEvent;
};

#endif // !ECHISTORY_H
