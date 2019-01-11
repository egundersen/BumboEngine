#include "Event_BridgeRally.h"

void Event_BridgeRally::createEvent()
{
	updateColliderCoordinates();

	Popup popup_0(25, 9, "Listen up!", screen_matrix_, 'X');
	Popup popup_1(25, 9, "What are we?", screen_matrix_, 'X');
	Popup popup_2(15, 5, "Pirates!", screen_matrix_, 'X');
	Popup popup_3(15, 5, "Scallywags!", screen_matrix_, 'X');

	Popup popup_4(25, 9, "Wha' type o' pirates?", screen_matrix_, 'X');
	Popup popup_5(22, 5, "Software Pirates", screen_matrix_, 'X');

	Popup popup_6(25, 9, "'n wha' are we after?", screen_matrix_, 'X');
	Popup popup_7(15, 5, "Doubloons", screen_matrix_, 'X');
	Popup popup_8(15, 5, "Loot", screen_matrix_, 'X');
	Popup popup_9(15, 5, "Riches", screen_matrix_, 'X');
	Popup popup_10(15, 5, "Rape", screen_matrix_, 'X');
	Popup popup_11(15, 5, "Wenches", screen_matrix_, 'X');
	Popup popup_12(15, 5, "Sprogs", screen_matrix_, 'X');

	Popup popup_13(25, 9, "Wha'? NO!", screen_matrix_, 'X');
	Popup popup_14(25, 9, "Remember, scallywags? We be fightin' against oppression.", screen_matrix_, 'X');
	Popup popup_15(25, 9, "Fer years we've been forced into livin' on th' bottom.", screen_matrix_, 'X');
	Popup popup_16(25, 9, "Forced into th' darkest reaches o' th' DEEP cave.", screen_matrix_, 'X');
	Popup popup_17(25, 9, "We've suffered th' worst conditions imaginable.", screen_matrix_, 'X');
	Popup popup_18(25, 9, "We've been persecuted 'n taken t' court! While they...", screen_matrix_, 'X');
	Popup popup_19(25, 9, "THEY've remained in th' CLEAR cave, spreadin' thar hippocratic oath 'n tarnishin' our reputations.", screen_matrix_, 'X');
	Popup popup_20(25, 9, "We've had t' live in fear o' them! Even Vice-Private-Nugent has failed t' keep us safe from thar TYRANNY!", screen_matrix_, 'X');
	Popup popup_21(25, 9, "But no more! While they've lived, thinkin' they be safe from us, we've only increased our numbers!", screen_matrix_, 'X');
	Popup popup_22(25, 9, "LET THIS DAY mark th' end o' a society rooted in bigotry.", screen_matrix_, 'X');
	Popup popup_23(25, 9, "Fer years th' weebs 'ave kept from us, whats rightfully ours!", screen_matrix_, 'X');
	Popup popup_24(25, 9, "Lads, if ye stand t' fight oppression, say I!", screen_matrix_, 'X');
	Popup popup_25(25, 9, "...", screen_matrix_, 'X');
	Popup popup_26(25, 9, "Er...", screen_matrix_, 'X');
	Popup popup_27(25, 9, "If ye stand against oppression AND fer loot, say I!", screen_matrix_, 'X');
	Popup popup_28(9, 5, "I", screen_matrix_, 'X');

	Popup popup_29(25, 9, "C-H-A-R-G-E ! ! ! !", screen_matrix_, 'X');

	popup_0.createPopupText();
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
	popup_18.createPopupText();
	popup_19.createPopupText();
	popup_20.createPopupText();
	popup_21.createPopupText();
	popup_22.createPopupText();
	popup_23.createPopupText();
	popup_24.createPopupText();
	popup_25.createPopupText();
	popup_26.createPopupText();
	popup_27.createPopupText();
	popup_28.createPopupText();
	popup_29.createPopupText();

	popups_.push_back(popup_0);
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
	popups_.push_back(popup_18);
	popups_.push_back(popup_19);
	popups_.push_back(popup_20);
	popups_.push_back(popup_21);
	popups_.push_back(popup_22);
	popups_.push_back(popup_23);
	popups_.push_back(popup_24);
	popups_.push_back(popup_25);
	popups_.push_back(popup_26);
	popups_.push_back(popup_27);
	popups_.push_back(popup_28);
	popups_.push_back(popup_29);
}

void Event_BridgeRally::refreshEvent()
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

void Event_BridgeRally::speak()
{
	switch (getPopupIndex())
	{
	case 0:
		popups_[0].displayPopup(-20, 0);
		break;
	case 1:
		popups_[1].displayPopup(-20, 0);
		break;
	case 2: // RESPONSE
		popups_[2].displayPopup(40, -1);
		popups_[2].displayPopup(15, 18);
		popups_[3].displayPopup(1, 8);
		break;
	case 3:
		popups_[4].displayPopup(-20, 0);
		break;
	case 4: // RESPONSE
		popups_[5].displayPopup(32, 3);
		popups_[5].displayPopup(11, 18);
		popups_[5].displayPopup(-13, 8);
		break;
	case 5:
		popups_[6].displayPopup(-20, 0);
		break;
	case 6: // RESPONSE
		popups_[7].displayPopup(45, 3);
		popups_[8].displayPopup(15, 24);
		popups_[9].displayPopup(-13, 13);
		popups_[10].displayPopup(-5, 20);
		popups_[11].displayPopup(-10, 5);
		popups_[12].displayPopup(36, 11);
		break;
	case 7:
		popups_[13].displayPopup(-20, 0);
		break;
	case 8:
		popups_[14].displayPopup(-20, 0);
		break;
	case 9:
		popups_[15].displayPopup(-20, 0);
		break;
	case 10:
		popups_[16].displayPopup(-20, 0);
		break;
	case 11:
		popups_[17].displayPopup(-20, 0);
		break;
	case 12:
		popups_[18].displayPopup(-20, 0);
		break;
	case 13:
		popups_[19].displayPopup(-20, 0);
		break;
	case 14:
		popups_[20].displayPopup(-20, 0);
		break;
	case 15:
		popups_[21].displayPopup(-20, 0);
		break;
	case 16:
		popups_[22].displayPopup(-20, 0);
		break;
	case 17:
		popups_[23].displayPopup(-20, 0);
		break;
	case 18:
		popups_[24].displayPopup(-20, 0);
		break;
	case 19:
		popups_[25].displayPopup(-20, 0);
		break;
	case 20:
		popups_[26].displayPopup(-20, 0);
		break;
	case 21:
		popups_[27].displayPopup(-20, 0);
		break;
	case 22: // Response
		popups_[28].displayPopup(53, 3);
		popups_[28].displayPopup(15, 24);
		popups_[28].displayPopup(4, 16);
		popups_[28].displayPopup(-3, 5);
		popups_[28].displayPopup(36, 11);
		break;
	case 23:
		popups_[29].displayPopup(-20, 0);
		break;
	case 24:
		progressEvent();
		break;
	}
}

void Event_BridgeRally::leave()
{
	if (getCharacterByID(43)->getMovementIndex() == 0)
		getCharacterByID(43)->moveAndTeleport(93, 'y', 30, 'l', 322, 85);
	if (getCharacterByID(44)->getMovementIndex() == 0)
		getCharacterByID(44)->moveAndTeleport(93, 'y', 20, 'l', 332, 85);
	if (getCharacterByID(39)->getMovementIndex() == 0)
		getCharacterByID(39)->moveAndTeleport(93, 'y', 25, 'l', 344, 86);
	if (getCharacterByID(25)->getMovementIndex() == 0)
		getCharacterByID(25)->moveAndTeleport(93, 'y', 28, 'l', 310, 93);
	if (getCharacterByID(27)->getMovementIndex() == 0)
		getCharacterByID(27)->moveAndTeleport(93, 'y', 25, 'l', 310, 85);
	if (getCharacterByID(24)->getMovementIndex() == 0)
		getCharacterByID(24)->moveAndTeleport(93, 'y', 25, 'l', 275, 86); // LEADER
	if (getCharacterByID(28)->getMovementIndex() == 0)
		getCharacterByID(28)->moveAndTeleport(93, 'y', 28, 'u', 293, 109);
	if (getCharacterByID(45)->getMovementIndex() == 0)
		getCharacterByID(45)->moveAndTeleport(93, 'y', 20, 'l', 288, 82);
	if (getCharacterByID(29)->getMovementIndex() == 0)
		getCharacterByID(29)->moveAndTeleport(93, 'y', 25, 'u', 281, 100);
	if (getCharacterByID(49)->getMovementIndex() == 0)
		getCharacterByID(49)->moveAndTeleport(93, 'y', 20, 'l', 299, 87);
	if (getCharacterByID(46)->getMovementIndex() == 0)
		getCharacterByID(46)->moveAndTeleport(93, 'y', 25, 'u', 284, 117);
	if (getCharacterByID(48)->getMovementIndex() == 0)
		getCharacterByID(48)->moveAndTeleport(93, 'y', 20, 'u', 271, 110);
	if (getCharacterByID(47)->getMovementIndex() == 0)
		getCharacterByID(47)->moveAndTeleport(93, 'y', 25, 'd', 300, 79);
	if (getCharacterByID(41)->getMovementIndex() == 0)
		getCharacterByID(41)->moveAndTeleport(304, 'x', 20, 'u', 284, 117);
	if (getCharacterByID(40)->getMovementIndex() == 0)
		getCharacterByID(40)->moveAndTeleport(304, 'x', 20, 'u', 281, 107);
	if (getCharacterByID(42)->getMovementIndex() == 0)
		getCharacterByID(42)->moveAndTeleport(304, 'x', 20, 'l', 265, 85);

	switch (getCharacterByID(26)->getMovementIndex())
	{
	case 0:
		getCharacterByID(26)->move(107, 'y', 30);
		break;
	case 1:
		getCharacterByID(26)->moveAndTeleport(304, 'x', 20, 'u', 271, 99);
		break;
	case 2:
		getCharacterByID(43)->resetMovementIndex();
		getCharacterByID(44)->resetMovementIndex();
		getCharacterByID(39)->resetMovementIndex();
		getCharacterByID(25)->resetMovementIndex();
		getCharacterByID(27)->resetMovementIndex();
		getCharacterByID(24)->resetMovementIndex();
		getCharacterByID(28)->resetMovementIndex();
		getCharacterByID(45)->resetMovementIndex();
		getCharacterByID(29)->resetMovementIndex();
		getCharacterByID(49)->resetMovementIndex();
		getCharacterByID(46)->resetMovementIndex();
		getCharacterByID(48)->resetMovementIndex();
		getCharacterByID(47)->resetMovementIndex();
		getCharacterByID(41)->resetMovementIndex();
		getCharacterByID(40)->resetMovementIndex();
		getCharacterByID(42)->resetMovementIndex();
		getCharacterByID(26)->resetMovementIndex();
		progressEvent();
		break;
	}
}
