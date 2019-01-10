#include "Event_LostDevice.h"

void Event_LostDevice::createEvent()
{
	updateColliderCoordinates();

	Popup popup_1(25, 9, "! ! !", screen_matrix_, 'O');

	Popup popup_2(25, 9, "Hello, you must be {player}", screen_matrix_, 'O');
	Popup popup_3(25, 9, "My name is Aki~", screen_matrix_, 'O');
	Popup popup_4(25, 9, "I trust you received your father's package?", screen_matrix_, 'O');
	Popup popup_5(25, 9, "Please let me see it~", screen_matrix_, 'O');
	Popup popup_6(25, 9, "...", screen_matrix_, 'O');
	Popup popup_7(25, 9, "?", screen_matrix_, 'O');
	Popup popup_8(25, 9, "Oh what's that? You can't show it to me?", screen_matrix_, 'O');
	Popup popup_9(25, 9, "What ever could be wrong?", screen_matrix_, 'O');
	Popup popup_10(25, 9, "! ! !", screen_matrix_, 'O');
	Popup popup_11(25, 9, "You say you no longer have it?", screen_matrix_, 'O');
	Popup popup_12(25, 9, "You lost it!?", screen_matrix_, 'O');
	Popup popup_13(25, 9, "That's hilari-huh...", screen_matrix_, 'O');
	Popup popup_14(25, 9, "Just Te-e-e-errible news!!!", screen_matrix_, 'O');
	Popup popup_15(25, 9, "Heh heh hah hah ha ha ha ha hee~", screen_matrix_, 'O');
	Popup popup_16(25, 9, "I'm really sorry.", screen_matrix_, 'O');
	Popup popup_17(25, 9, "It's just... you don't seem to get it.", screen_matrix_, 'O');
	Popup popup_18(25, 9, "That package was VERY important to your father.", screen_matrix_, 'O');
	Popup popup_19(25, 9, "You could say the fate of the world hangs in balance.", screen_matrix_, 'O');
	Popup popup_20(25, 9, "And to think you'd just... LOSE IT. Wow...", screen_matrix_, 'O');
	Popup popup_21(25, 9, "Sorry, but I can't help but laugh!", screen_matrix_, 'O');
	Popup popup_22(25, 9, "To think the hero would be so clumsy!", screen_matrix_, 'O');
	Popup popup_23(25, 9, "He heh ha ha hah~", screen_matrix_, 'O');

	Popup popup_24(25, 9, "Er-what?", screen_matrix_, 'O');
	Popup popup_25(25, 9, "You say you didn't lose it?", screen_matrix_, 'O');
	Popup popup_26(25, 9, "Hmmm... perhaps someone stolen it.", screen_matrix_, 'O');
	Popup popup_27(25, 9, "I wonder who...", screen_matrix_, 'O');
	Popup popup_28(25, 9, "Did anything... \"weird\" happen to you in the last few minutes?", screen_matrix_, 'O');
	Popup popup_29(25, 9, "... because a group of thugs ran through here earlier, perhaps it could of been one of them?", screen_matrix_, 'O');
	Popup popup_30(25, 9, "Listen, I know I have no right to ask this of you...", screen_matrix_, 'O');
	Popup popup_31(25, 9, "But you've got to get your father's package back.", screen_matrix_, 'O');
	Popup popup_32(25, 9, "Through ANY MEANS NECESSARY", screen_matrix_, 'O');
	Popup popup_33(25, 9, "UNDERSTAND?", screen_matrix_, 'O');
	Popup popup_34(25, 9, "I'll stay here conducting... \"Research\" If you need my help, just ask~", screen_matrix_, 'O');

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
	popup_30.createPopupText();
	popup_31.createPopupText();
	popup_32.createPopupText();
	popup_33.createPopupText();
	popup_34.createPopupText();

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
	popups_.push_back(popup_30);
	popups_.push_back(popup_31);
	popups_.push_back(popup_32);
	popups_.push_back(popup_33);
	popups_.push_back(popup_34);
}

void Event_LostDevice::refreshEvent()
{
	switch (getEventIndex())
	{
	case 0:
		alignToPlayer();
		break;
	case 1:
		lookAround();
		break;
	case 2:
		moveToPlayer();
		break;
	case 3:
		freakOut();
		break;
	case 4:
		spin();
		break;
	case 5:
		giveInstructions();
		break;
	case 6:
		leave();
		break;
	case 7:
		onEventOver();
		break;
	default:
		break;
	}
}

void Event_LostDevice::alignToPlayer()
{
	switch (getCharacterByID(22)->getMovementIndex())
	{
	case 0:
		getCharacterByID(22)->move(screen_position_.x + screen_width_ / 2, 'x', 20);
		break;
	case 1:
		progressEvent(22);
		break;
	}
}

void Event_LostDevice::lookAround()
{
	double current_time_begin_event_ = GetTickCount64() - start_time_begin_event_;
	if (current_time_begin_event_ > 3500)
	{
		progressEvent();
	}
	else if (current_time_begin_event_ > 2000)
	{
		popups_[0].displayPopup(-25, -3);
	}
	else if (current_time_begin_event_ > 1500)
	{
		getCharacterByID(22)->faceDirection('d');
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

void Event_LostDevice::moveToPlayer()
{
	switch (getCharacterByID(22)->getMovementIndex())
	{
	case 0:
		getCharacterByID(22)->move(screen_position_.y + screen_height_ / 2 - 6, 'y', 30);
		break;
	case 1:
		progressEvent(22);
		break;
	}
}

void Event_LostDevice::freakOut()
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
		break;
	case 3:
		popups_[4].displayPopup(-20, 0);
		break;
	case 4:
		popups_[5].displayPopup(-20, 0);
		break;
	case 5:
		popups_[6].displayPopup(-20, 0);
		break;
	case 6:
		popups_[7].displayPopup(-20, 0);
		break;
	case 7:
		popups_[8].displayPopup(-20, 0);
		break;
	case 8:
		popups_[9].displayPopup(-20, 0);
		break;
	case 9:
		popups_[10].displayPopup(-20, 0);
		break;
	case 10:
		popups_[11].displayPopup(-20, 0);
		break;
	case 11:
		popups_[12].displayPopup(-20, 0);
		break;
	case 12:
		popups_[13].displayPopup(-20, 0);
		break;
	case 13:
		popups_[14].displayPopup(-20, 0);
		break;
	case 14:
		popups_[15].displayPopup(-20, 0);
		getCharacterByID(22)->faceDirection('r');
		break;
	case 15:
		popups_[16].displayPopup(-20, 0);
		getCharacterByID(22)->faceDirection('d');
		break;
	case 16:
		popups_[17].displayPopup(-20, 0);
		break;
	case 17:
		popups_[18].displayPopup(-20, 0);
		break;
	case 18:
		popups_[19].displayPopup(-20, 0);
		break;
	case 19:
		popups_[20].displayPopup(-20, 0);
		break;
	case 20:
		popups_[21].displayPopup(-20, 0);
		break;
	case 21:
		popups_[22].displayPopup(-20, 0);
		break;
	case 22:
		progressEvent();
		break;
	}
}

void Event_LostDevice::spin()
{
	double current_time_begin_event_ = GetTickCount64() - start_time_begin_event_;
	if (current_time_begin_event_ > 2000)
	{
		progressEvent();
	}
	else if (current_time_begin_event_ > 1800)
	{
		getCharacterByID(22)->faceDirection('r');
	}
	else if (current_time_begin_event_ > 1600)
	{
		getCharacterByID(22)->faceDirection('d');
	}
	else if (current_time_begin_event_ > 1400)
	{
		getCharacterByID(22)->faceDirection('l');
	}
	else if (current_time_begin_event_ > 1200)
	{
		getCharacterByID(22)->faceDirection('u');
	}
	else if (current_time_begin_event_ > 1000)
	{
		getCharacterByID(22)->faceDirection('r');
	}
	else if (current_time_begin_event_ > 800)
	{
		getCharacterByID(22)->faceDirection('d');
	}
	else if (current_time_begin_event_ > 600)
	{
		getCharacterByID(22)->faceDirection('l');
	}
	else if (current_time_begin_event_ > 400)
	{
		getCharacterByID(22)->faceDirection('u');
	}
	else if (current_time_begin_event_ > 200)
	{
		getCharacterByID(22)->faceDirection('r');
	}
	else if (current_time_begin_event_ <= 200)
	{
		getCharacterByID(22)->faceDirection('d');
	}
}

void Event_LostDevice::giveInstructions()
{
	switch (getPopupIndex())
	{
	case 0:
		popups_[23].displayPopup(-20, 0);
		break;
	case 1:
		getCharacterByID(22)->faceDirection('d');
		popups_[24].displayPopup(-20, 0);
		break;
	case 2:
		popups_[25].displayPopup(-20, 0);
		break;
	case 3:
		popups_[26].displayPopup(-20, 0);
		getCharacterByID(22)->faceDirection('r');
		break;
	case 4:
		popups_[27].displayPopup(-20, 0);
		getCharacterByID(22)->faceDirection('d');
		break;
	case 5:
		popups_[28].displayPopup(-20, 0);
		break;
	case 6:
		popups_[29].displayPopup(-20, 0);
		break;
	case 7:
		popups_[30].displayPopup(-20, 0);
		break;
	case 8:
		popups_[31].displayPopup(-20, 0);
		break;
	case 9:
		popups_[32].displayPopup(-20, 0);
		break;
	case 10:
		popups_[33].displayPopup(-20, 0);
		break;
	case 11:
		progressEvent();
		break;
	}
}

void Event_LostDevice::leave()
{
	switch (getCharacterByID(22)->getMovementIndex())
	{
	case 0:
		getCharacterByID(22)->move(197, 'y', 30);
		break;
	case 1:
		getCharacterByID(22)->teleportNPC(275, 198);
		getCharacterByID(22)->faceDirection('l');
		progressEvent(22);
		break;
	}
}