#include "ECHistory.h"
using namespace std;
void ECHistory::AddEvent(ActionType event, ECShape* shape) {
	if (curEvent >= -1) {
		int szlist = listEvents.size();
		for (int i = curEvent + 1; i < szlist; ++i) {
			listEvents.pop_back();
			listShapes.pop_back();
		}
	}
	std::cout << "Event added." << std::endl;
	listEvents.push_back(event);
	listShapes.push_back(shape);
	curEvent++;
}

void ECHistory::Undo() {
	cout << "Before " << curEvent << endl;
	if (curEvent > -1) {
		switch (listEvents[curEvent]) {
		case INSERTION:
			listShapes[curEvent]->Delete(true);
			break;
		case DELETION:
			listShapes[curEvent]->Delete(false);
			break;
		case MOVING:
			listShapes[curEvent]->UndoMove();
			break;
		case GROUPING:
			listShapes[curEvent]->Ungroup();
		case UNGROUPING:
			listShapes[curEvent]->Group();
		}
		curEvent--;

		cout << "After " << curEvent << endl;
	}
	else return;
}
void ECHistory::Redo() {

	cout << "Before " << curEvent << endl;
	if (curEvent < listEvents.size() - 1 || curEvent == -1) {
		curEvent++;
		switch (listEvents[curEvent]) {
		case INSERTION:
			listShapes[curEvent]->Delete(false);
			break;
		case DELETION:
			listShapes[curEvent]->Delete(true);
			break;
		case MOVING:
			listShapes[curEvent]->RedoMove();
			break;
		case GROUPING:
			listShapes[curEvent]->Group();
		case UNGROUPING:
			listShapes[curEvent]->Ungroup();
		}

		cout << "After " << curEvent << endl;
	}
	else return;
}
