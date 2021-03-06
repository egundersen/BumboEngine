#include "Event_Test.h"

void Event_Test::createEvent()
{
	updateColliderCoordinates();

	Popup popup_1(23, 9, "what is your  NAME!!!??? ", screen_matrix_, 'X');
	popup_1.createPopupText();
	Popup popup_2(23, 9, "hello my name is MANNY kanE ", screen_matrix_, 'X');
	popup_2.createPopupText();

	popups_.push_back(popup_1);
	popups_.push_back(popup_2);
}

void Event_Test::refreshEvent()
{
	double current_time_begin_event_ = GetTickCount64() - start_time_begin_event_;
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

		// move [Example] | In this case, I already know characters_[0] is All Might
		//if (!attached_character_->hasReachDestination())
		//	attached_character_->move(2382, 'x', 250);

		// teleport [example]
		//characters_[0]->teleportNPC(2382, characters_[0]->getCenterPositionY());

		/* battle [example]
		*  PLEASE READ BEFORE TRYING TO START AN ATTACK WITH AN EVENT!!! 
		*  This only works if this event is provided a character to start the battle with.
		*  Do this in the event constructor. If no character is provided, THIS WILL FAIL.
		*  This class (The test event) WILL FAIL BECAUSE IT IS NOT BEING PASSED A
		*  CHARACTER IN THE CONSTRUCTOR (In Worldbase.cpp).

		*  As such, an event can only start ONE BATTLE.
		*  This should be fine for the purposes of Wenlife, but if you find this mechanic
		*  limiting, feel free to change the code so a vector of characters is passed
		*  to events. Thank you for reading this far.
		*/
		// should_enter_battle_ = true;
	}
}
