#include "Event_BridgeRally2.h"

void Event_BridgeRally2::createEvent()
{
	updateColliderCoordinates();

	Popup popup_1(25, 9, "Wha' are ye waitin' fer?", screen_matrix_, 'X');
	Popup popup_2(25, 9, "'tis our chance!", screen_matrix_, 'X');
	Popup popup_3(25, 9, "Thar's one o' them weebs... standin' on th' bridge...", screen_matrix_, 'X');
	Popup popup_4(25, 9, "JUST FARRDIN' ONE!?", screen_matrix_, 'X');
	Popup popup_5(25, 9, "WHA' KIND O' JOKES DO THEY TAKE US FER!?", screen_matrix_, 'X');
	Popup popup_6(25, 9, "But Captain, this scallywag looks pretty serious... maybe we should...", screen_matrix_, 'X');
	Popup popup_7(25, 9, "We literally outnumber 'im 17 t' 1.", screen_matrix_, 'X');
	Popup popup_8(25, 9, "Now shut yer traps 'n KILL HIM!", screen_matrix_, 'X');
	Popup popup_9(25, 9, "C-H-A-R-G-E ! ! ! !", screen_matrix_, 'X');

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

void Event_BridgeRally2::refreshEvent()
{
	switch (getEventIndex())
	{
	case 0:
		speak();
		break;
	case 1:
		leave();
		break;
	case 2:
		onEventOver();
		break;
	default:
		break;
	}
}

void Event_BridgeRally2::speak()
{
	switch (getPopupIndex())
	{
	case 0:
		popups_[0].displayPopup(10, 0);
		break;
	case 1:
		popups_[1].displayPopup(10, 0);
		break;
	case 2:
		popups_[2].displayPopup(-20, 12);
		getCharacterByID(41)->faceDirection('r');
		break;
	case 3:
		popups_[3].displayPopup(10, 0);
		break;
	case 4:
		popups_[4].displayPopup(10, 0);
		break;
	case 5:
		popups_[5].displayPopup(-20, 12);
		break;
	case 6:
		popups_[6].displayPopup(10, 0);
		break;
	case 7:
		popups_[7].displayPopup(10, 0);
		break;
	case 8:
		popups_[8].displayPopup(10, 0);
		getCharacterByID(41)->faceDirection('l');
		break;
	case 9:
		progressEvent();
		break;
	}
}

void Event_BridgeRally2::leave()
{
	switch (getCharacterByID(43)->getMovementIndex())
	{
	case 0:
		getCharacterByID(43)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	}
	switch (getCharacterByID(44)->getMovementIndex())
	{
	case 0:
		getCharacterByID(44)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	}
	switch (getCharacterByID(39)->getMovementIndex())
	{
	case 0:
		getCharacterByID(39)->move(85, 'y', 20);
		break;
	case 1:
		getCharacterByID(39)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	}
	switch (getCharacterByID(25)->getMovementIndex())
	{
	case 0:
		getCharacterByID(25)->move(85, 'y', 20);
		break;
	case 1:
		getCharacterByID(25)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	}
	switch (getCharacterByID(27)->getMovementIndex())
	{
	case 0:
		getCharacterByID(27)->move(85, 'y', 20);
		break;
	case 1:
		getCharacterByID(27)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	}
	// LEADER
	switch (getCharacterByID(24)->getMovementIndex())
	{
	case 0:
		getCharacterByID(24)->move(85, 'y', 20);
		break;
	case 1:
		getCharacterByID(24)->moveAndTeleport(240, 'x', 20, 'l', 210, 85);
		break;
	}
	switch (getCharacterByID(28)->getMovementIndex())
	{
	case 0:
		getCharacterByID(28)->move(301, 'x', 20);
		break;
	case 1:
		getCharacterByID(28)->move(85, 'y', 20);
		break;
	case 2:
		getCharacterByID(28)->resetDestination();
		getCharacterByID(28)->incrementMovementIndex();
		break;
	case 3:
		getCharacterByID(28)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	}
	switch (getCharacterByID(45)->getMovementIndex())
	{
	case 0:
		getCharacterByID(45)->move(85, 'y', 20);
		break;
	case 1:
		getCharacterByID(45)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	}
	switch (getCharacterByID(29)->getMovementIndex())
	{
	case 0:
		getCharacterByID(29)->move(85, 'y', 20);
		break;
	case 1:
		getCharacterByID(29)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	}
	switch (getCharacterByID(49)->getMovementIndex())
	{
	case 0:
		getCharacterByID(49)->move(85, 'y', 20);
		break;
	case 1:
		getCharacterByID(49)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	}
	switch (getCharacterByID(46)->getMovementIndex())
	{
	case 0:
		getCharacterByID(46)->move(85, 'y', 20);
		break;
	case 1:
		getCharacterByID(46)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	}
	switch (getCharacterByID(48)->getMovementIndex())
	{
	case 0:
		getCharacterByID(48)->move(85, 'y', 20);
		break;
	case 1:
		getCharacterByID(48)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	}
	switch (getCharacterByID(47)->getMovementIndex())
	{
	case 0:
		getCharacterByID(47)->move(85, 'y', 20);
		break;
	case 1:
		getCharacterByID(47)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	}
	// Progresses Event:
	switch (getCharacterByID(41)->getMovementIndex())
	{
	case 0:
		getCharacterByID(41)->move(301, 'x', 20);
		break;
	case 1:
		getCharacterByID(41)->move(85, 'y', 20);
		break;
	case 2:
		getCharacterByID(41)->resetDestination();
		getCharacterByID(41)->incrementMovementIndex();
		break;
	case 3:
		getCharacterByID(41)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	case 4:
		progressEvent();
		break;
	}
	switch (getCharacterByID(42)->getMovementIndex())
	{
	case 0:
		getCharacterByID(42)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	}
	switch (getCharacterByID(40)->getMovementIndex())
	{
	case 0:
		getCharacterByID(40)->move(301, 'x', 20);
		break;
	case 1:
		getCharacterByID(40)->move(85, 'y', 20);
		break;
	case 2:
		getCharacterByID(40)->resetDestination();
		getCharacterByID(40)->incrementMovementIndex();
		break;
	case 3:
		getCharacterByID(40)->moveAndTeleport(240, 'x', 20, 'u', 272, 192);
		break;
	}
}
