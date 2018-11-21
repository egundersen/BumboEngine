#include "Event_Test.h"
#include <iostream>
#include <Windows.h>

void Event_Test::createEvent()
{
	updateColliderCoordinates();

	Popup popup_1(23, 9, "what is yourZ NAME!!!???Z", matrix_display_, 'X');
	popup_1.createPopupText();
	Popup popup_2(23, 9, "hello my nameZis MANNY kanEZ", matrix_display_, 'X');
	popup_2.createPopupText();

	popups_.push_back(popup_1);
	popups_.push_back(popup_2);
}

void Event_Test::refreshEvent()
{
	double current_time_begin_event_ = GetTickCount() - start_time_begin_event_;
	if (current_time_begin_event_ > 7000)
	{
		onEventOver();
	}
	else if (current_time_begin_event_ > 5000)
	{
		popups_[1].displayPopup(-20, 10);
	}
	else if (current_time_begin_event_ > 2000)
	{
		popups_[0].displayPopup(20, 0);

		// move [Example]
		if (!characters_[0]->hasReachDestination())
			characters_[0]->move(2382, 'x', 250);
	}

	// delete these comments
	// ability to start event from character class (at end of battle)

	// teleport [example]
	//characters_[0]->teleportNPC(2382, characters_[0]->getCenterPositionY());
}
