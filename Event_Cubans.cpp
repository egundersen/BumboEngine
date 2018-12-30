#include "Event_Cubans.h"

void Event_Cubans::createEvent()
{
	updateColliderCoordinates();

	Popup popup_1(25, 9, "Yer back! Do ye forgive me!?", screen_matrix_, 'X');
	Popup popup_2(25, 9, "¿Conoces a ese punto? Ese tipo no sirve.", screen_matrix_, 'X');
	Popup popup_3(25, 9, "Me has fallado por última vez.", screen_matrix_, 'X');

	popup_1.createPopupText();
	popup_2.createPopupText();
	popup_3.createPopupText();

	popups_.push_back(popup_1);
	popups_.push_back(popup_2);
	popups_.push_back(popup_3);
}

void Event_Cubans::refreshEvent()
{
	switch (getEventIndex())
	{
	case 0:
		moveCubans();
		break;
	case 1:
		speak();
		break;
	case 2:
		leave();
		break;
	case 3:
		onEventOver();
		break;
	default:
		break;
	}
}

void Event_Cubans::moveCubans()
{
	switch (getCharacterByID(33)->getMovementIndex())
	{
	case 0:
		getCharacterByID(33)->move(493, 'x', 30);
		getCharacterByID(34)->move(502, 'x', 30);
		break;
	case 1:
		getCharacterByID(33)->faceDirection('d');
		getCharacterByID(34)->faceDirection('d');
		progressEvent(33);
		break;
	}
}

void Event_Cubans::speak()
{
	switch (getPopupIndex())
	{
	case 0:
		popups_[0].displayPopup(-5, 0);
		break;
	case 1:
		popups_[1].displayPopup(27, 9);
		getCharacterByID(33)->faceDirection('r');
		getCharacterByID(34)->faceDirection('l');
		break;
	case 2:
		popups_[2].displayPopup(27, 9);
		getCharacterByID(33)->faceDirection('d');
		break;
	case 3:
		progressEvent();
		break;
	}
}

void Event_Cubans::leave()
{
	switch (getCharacterByID(33)->getMovementIndex())
	{
	case 0:
		getCharacterByID(33)->move(104, 'y', 30);
		break;
	case 1:
		getCharacterByID(33)->move(479, 'x', 30);
		break;
	case 2:
		getCharacterByID(18)->teleportNPC(197, 177);
		getCharacterByID(33)->incrementMovementIndex();
		break;
	case 3:
		getCharacterByID(33)->move(493, 'x', 30);
		break;
	case 4:
		getCharacterByID(33)->move(94, 'y', 30);
		break;
	case 5:
		getCharacterByID(33)->moveAndTeleport(519, 'x', 30, 'd', 197, 177);
		getCharacterByID(34)->moveAndTeleport(528, 'x', 30, 'd', 197, 177);
		break;
	case 6:
		progressEvent(33);
		break;
	}
}
