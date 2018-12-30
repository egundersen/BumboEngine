#include "Event_AkiClearCave.h"
#include <Windows.h>

void Event_AkiClearCave::createEvent()
{
	updateColliderCoordinates();

	Popup popup_1(25, 9, "Oh, {player}, I was just looking for you.", screen_matrix_, 'O');
	Popup popup_2(25, 9, "I think the perpetrator is hiding in the CLEAR cave.", screen_matrix_, 'O');
	Popup popup_3(25, 9, "It's just... due north of here...", screen_matrix_, 'O');
	Popup popup_4(25, 9, "...not that you would want to come along or anything.", screen_matrix_, 'O');
	Popup popup_5(25, 9, "...", screen_matrix_, 'O');
	Popup popup_6(25, 9, "Nevermind!!!", screen_matrix_, 'O');
	Popup popup_7(25, 9, "Forget I said anything!!!", screen_matrix_, 'O');
	Popup popup_8(25, 9, "I guess...", screen_matrix_, 'O');
	Popup popup_9(25, 9, "I guess I'll see you in the CLEAR cave :D", screen_matrix_, 'O');

	popup_1.createPopupText();
	popup_2.createPopupText();
	popup_3.createPopupText();
	popup_4.createPopupText();
	popup_5.createPopupText();
	popup_6.createPopupText();
	popup_7.createPopupText();
	popup_8.createPopupText();
	popup_9.createPopupText();

	popups_.push_back(popup_1);
	popups_.push_back(popup_2);
	popups_.push_back(popup_3);
	popups_.push_back(popup_4);
	popups_.push_back(popup_5);
	popups_.push_back(popup_6);
	popups_.push_back(popup_7);
	popups_.push_back(popup_8);
	popups_.push_back(popup_9);
}

void Event_AkiClearCave::refreshEvent()
{
	switch (getEventIndex())
	{
	case 0:
		lookAround();
		break;
	case 1:
		moveToPlayer();
		break;
	case 2:
		speak();
		break;
	case 3:
		leave();
		break;
	case 4:
		onEventOver();
		break;
	default:
		break;
	}
}

bool Event_AkiClearCave::isAvailable()
{
	return true;
	if (getCharacterByID(14) == nullptr || getCharacterByID(14)->isBattleOver())
		return true;
	else
		return false;
}

void Event_AkiClearCave::lookAround()
{
	double current_time_begin_event_ = GetTickCount64() - start_time_begin_event_;
	if (current_time_begin_event_ > 3500)
	{
		progressEvent();
	}
	else if (current_time_begin_event_ > 2000)
	{
		popups_[0].displayPopup(-25, 3);
	}
	else if (current_time_begin_event_ > 1500)
	{
		getCharacterByID(22)->faceDirection('u');
	}
	else if (current_time_begin_event_ > 1000)
	{
		getCharacterByID(22)->faceDirection('r');
	}
	else if (current_time_begin_event_ > 500)
	{
		getCharacterByID(22)->faceDirection('l');
	}
	else if (current_time_begin_event_ <= 500)
	{
		getCharacterByID(22)->faceDirection('r');
	}
}

void Event_AkiClearCave::moveToPlayer()
{
	switch (getCharacterByID(22)->getMovementIndex())
	{
	case 0:
		getCharacterByID(22)->move(screen_position_.y + screen_height_ / 2 + 8, 'y', 20);
		break;
	case 1:
		progressEvent(22);
		break;
	}
}

void Event_AkiClearCave::speak()
{
	switch (getPopupIndex())
	{
	case 0:
		popups_[1].displayPopup(-20, 0);
		break;
	case 1:
		popups_[2].displayPopup(-20, 0);
		break;
	case 2:
		popups_[3].displayPopup(-20, 0);
		getCharacterByID(22)->faceDirection('r');
		break;
	case 3:
		popups_[4].displayPopup(-20, 0);
		break;
	case 4:
		popups_[5].displayPopup(-20, 0);
		break;
	case 5:
		popups_[6].displayPopup(-20, 0);
		getCharacterByID(22)->faceDirection('u');
		break;
	case 6:
		popups_[7].displayPopup(-20, 0);
		break;
	case 7:
		popups_[8].displayPopup(-20, 0);
		break;
	case 8:
		progressEvent();
		break;
	}
}

void Event_AkiClearCave::leave()
{
	switch (getCharacterByID(22)->getMovementIndex())
	{
	case 0:
		getCharacterByID(22)->move(200, 'y', 30);
		break;
	case 1:
		getCharacterByID(22)->teleportNPC(198, 165);
		progressEvent(22);
		break;
	}
}