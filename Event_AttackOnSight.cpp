#include "Event_AttackOnSight.h"
#include <Windows.h>

void Event_AttackOnSight::createEvent()
{
	updateColliderCoordinates();

	Popup popup_1(23, 9, "Avast!Z", matrix_display_, 'X');
	popup_1.createPopupText();

	popups_.push_back(popup_1);
}

void Event_AttackOnSight::refreshEvent()
{
	double current_time_begin_event_ = GetTickCount() - start_time_begin_event_;
	if (current_time_begin_event_ > 2000)
	{
		should_enter_battle_ = true;
		onEventOver();
	}
	else if (current_time_begin_event_ <= 2000)
	{
		popups_[0].displayPopup(20, 0);
	}
}
