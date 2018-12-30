#include "Event_BridgeRally3.h"

void Event_BridgeRally3::createEvent()
{
	updateColliderCoordinates();

	Popup popup_1(25, 9, "Ok, so we no longer outnumber ye...", screen_matrix_, 'X');
	Popup popup_2(25, 9, "This is fine...", screen_matrix_, 'X');
	Popup popup_3(25, 9, "'cause if ye reckon I came here without some form o' TRUMP card, ye'd be sorely mistaken!", screen_matrix_, 'X');
	Popup popup_4(25, 9, "'tis naught too dangerous, but I can assure ye that when its o'er...", screen_matrix_, 'X');
	Popup popup_5(25, 9, "ye'll WANNA CRY!", screen_matrix_, 'X');
	Popup popup_6(25, 9, ".", screen_matrix_, 'X');
	Popup popup_7(25, 9, ". . .", screen_matrix_, 'X');
	Popup popup_8(25, 9, ". . . . .", screen_matrix_, 'X');
	Popup popup_9(25, 9, "Wha'?", screen_matrix_, 'X');
	Popup popup_10(25, 9, "Nothin'?", screen_matrix_, 'X');
	Popup popup_11(25, 9, "No...", screen_matrix_, 'X');
	Popup popup_12(25, 9, "It failed...", screen_matrix_, 'X');
	Popup popup_13(25, 9, "I ALWAYS FAIL!", screen_matrix_, 'X');
	Popup popup_14(25, 9, "Ye... Ye reckon ye're better than us!?", screen_matrix_, 'X');
	Popup popup_15(25, 9, "Yes, because I don't break the law.", screen_matrix_, 'O');
	Popup popup_16(25, 9, "HYPOCRISY! ! ! ! !", screen_matrix_, 'X');
	Popup popup_17(25, 9, "Ye're nah payin' t' watch anime! Do ye Know wha' thats called? PIRACY! YE BE NO DIFFERENT!", screen_matrix_, 'X');

	popup_1.createPopupText();
	popup_2.createPopupText();
	popup_3.createPopupText();
	popup_4.createPopupText();
	popup_5.createPopupText();
	popup_6.createPopupText();
	popup_7.createPopupText();
	popup_8.createPopupText();
	popup_9.createPopupText();
	popup_10.createPopupText();
	popup_11.createPopupText();
	popup_12.createPopupText();
	popup_13.createPopupText();
	popup_14.createPopupText();
	popup_15.createPopupText();
	popup_16.createPopupText();
	popup_17.createPopupText();

	popups_.push_back(popup_1);
	popups_.push_back(popup_2);
	popups_.push_back(popup_3);
	popups_.push_back(popup_4);
	popups_.push_back(popup_5);
	popups_.push_back(popup_6);
	popups_.push_back(popup_7);
	popups_.push_back(popup_8);
	popups_.push_back(popup_9);
	popups_.push_back(popup_10);
	popups_.push_back(popup_11);
	popups_.push_back(popup_12);
	popups_.push_back(popup_13);
	popups_.push_back(popup_14);
	popups_.push_back(popup_15);
	popups_.push_back(popup_16);
	popups_.push_back(popup_17);
}

void Event_BridgeRally3::refreshEvent()
{
	switch (getEventIndex())
	{
	case 0:
		speak();
		break;
	case 1:
		killPirate();
		break;
	case 2:
		onEventOver();
		break;
	default:
		break;
	}
}

void Event_BridgeRally3::speak()
{
	switch (getPopupIndex())
	{
	case 0:
		popups_[0].displayPopup(-8, 0);
		break;
	case 1:
		popups_[1].displayPopup(-8, 0);
		break;
	case 2:
		popups_[2].displayPopup(-8, 0);
		break;
	case 3:
		popups_[3].displayPopup(-8, 0);
		break;
	case 4:
		popups_[4].displayPopup(-8, 0);
		getCharacterByID(24)->faceDirection('d');
		break;
	case 5:
		popups_[5].displayPopup(-8, 0);
		getCharacterByID(24)->faceDirection('l');
		break;
	case 6:
		popups_[6].displayPopup(-8, 0);
		break;
	case 7:
		popups_[7].displayPopup(-8, 0);
		break;
	case 8:
		popups_[8].displayPopup(-8, 0);
		break;
	case 9:
		popups_[9].displayPopup(-8, 0);
		break;
	case 10:
		popups_[10].displayPopup(-8, 0);
		break;
	case 11:
		popups_[11].displayPopup(-8, 0);
		break;
	case 12:
		popups_[12].displayPopup(-8, 0);
		getCharacterByID(24)->faceDirection('d');
		break;
	case 13:
		popups_[13].displayPopup(-8, 0);
		getCharacterByID(24)->faceDirection('l');
		break;
	case 14:
		popups_[14].displayPopup(-25, 0);
		break;
	case 15:
		popups_[15].displayPopup(-8, 0);
		break;
	case 16:
		popups_[16].displayPopup(-8, 0);
		break;
	case 17:
		progressEvent();
		break;
	}
}

void Event_BridgeRally3::killPirate()
{
	switch (getCharacterByID(11)->getMovementIndex())
	{
	case 0:
		getCharacterByID(11)->move(212, 'x', 30);
		break;
	case 1:
		getCharacterByID(24)->teleportNPC(198, 165);
		getCharacterByID(11)->incrementMovementIndex();
		getCharacterByID(11)->faceDirection('l');
		break;
	case 2:
		getCharacterByID(11)->moveAndTeleport(180, 'x', 30, 'd', 123, 97);
		break;
	case 3:
		progressEvent();
		break;
	}
}
