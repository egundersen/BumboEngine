#include "Event_ThotPatrol.h"

Event_ThotPatrol::Event_ThotPatrol(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, CharacterBase * &selected_character, bool repeatable, std::vector<std::vector<std::pair<int, int>>>& element_has_object, Matrix & screen_matrix, std::vector<CharacterBase*>& characters, ScreenPosition & screen_position, int screen_width, int screen_height)
	: EventBase(unique_object_ID, center_position_x, center_position_y, collider_width, collider_height, 0, repeatable, element_has_object, screen_matrix, characters, screen_position, screen_width, screen_height), selected_character_{ selected_character }
{
}

void Event_ThotPatrol::createEvent()
{
	updateColliderCoordinates();

	Popup popup_0(25, 9, "Wooo! Wooo! Wooo!", screen_matrix_, '#');
	Popup popup_1(25, 9, "(Insert Police Siren Sound Effect Here)", screen_matrix_, '#');
	Popup popup_2(25, 9, "We came as as soon as we could.", screen_matrix_, '#');
	Popup popup_3(25, 9, "And it's been a while.", screen_matrix_, '#');
	Popup popup_4(25, 9, "Since October, actually.", screen_matrix_, '#');
	Popup popup_5(25, 9, "Thot patrol reportin'!", screen_matrix_, '#');
	Popup popup_6(25, 9, "What do we have here, Jenkins?", screen_matrix_, '#');
	Popup popup_7(25, 9, "Excuse me. My name's not \"Jenkins\"! I am Kayden motherF*****g Karper!", screen_matrix_, '#');
	Popup popup_8(25, 9, "Errr... WELL WHAT DO YOU HAVE HERE, HARPER?", screen_matrix_, '#');
	Popup popup_9(25, 9, "Two people alone...", screen_matrix_, '#');
	Popup popup_10(25, 9, "All I see is a THOT that needs to BEGONE!", screen_matrix_, '#');
	Popup popup_11(25, 9, "I can't get to sleep!", screen_matrix_, '#');
	Popup popup_12(25, 9, "Just think of the implications!", screen_matrix_, '#');
	Popup popup_13(25, 9, "What if he dove in too deep!", screen_matrix_, '#');
	Popup popup_14(25, 9, "That'd cause some complications!", screen_matrix_, '#');
	Popup popup_15(25, 9, "Wait! We have to give him a chance to explain himself!", screen_matrix_, '#');
	Popup popup_16(25, 9, "Are you saying it's my imagination?", screen_matrix_, '#');
	Popup popup_17(25, 9, "We can't just let them walk the streets, just smell the desperation!", screen_matrix_, '#');
	Popup popup_18(25, 9, "At least there's pretty lights!", screen_matrix_, '#');
	Popup popup_19(25, 9, "Though there's little variation...", screen_matrix_, '#');
	Popup popup_20(25, 9, "It nullifies the night.", screen_matrix_, '#');
	Popup popup_21(25, 9, "From OVERKILL", screen_matrix_, '#');
	Popup popup_22(25, 9, "Are you two done?", screen_matrix_, 'O');
	Popup popup_23(25, 9, "BEGONE THOT!", screen_matrix_, '#');
	Popup popup_24(25, 9, "The French Revolution is here!", screen_matrix_, '#');
	Popup popup_25(25, 9, "Wait! I can understand what I did was wrong... and I deserve to be punished...", screen_matrix_, 'O');
	Popup popup_26(25, 9, "...but {player} is innocent! Can't you let him go?", screen_matrix_, 'O');
	Popup popup_27(25, 9, "You still don't get it, do you?", screen_matrix_, '#');
	Popup popup_28(25, 9, "WENLIFE(tm) gives you lemons...", screen_matrix_, '#');
	Popup popup_29(25, 9, "You don't make lemonade.", screen_matrix_, '#');
	Popup popup_30(25, 9, "YOU DIE!", screen_matrix_, '#');

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
	popup_30.createPopupText();

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
	popups_.push_back(popup_30);
}

void Event_ThotPatrol::refreshEvent()
{
	switch (getEventIndex())
	{
	case 0:
		getCharacterByID(36)->teleportNPC(1088, 56);
		getCharacterByID(37)->teleportNPC(1075, 56);
		progressEvent();
		break;
	case 1:
		moveToPlayer();
		break;
	case 2:
		speak();
		break;
	case 3:
		moveToPlayer();
		break;
	case 4:
		battle();
		break;
	case 5:
		onEventOver();
		break;
	default:
		break;
	}
}

void Event_ThotPatrol::moveToPlayer()
{
	switch (getCharacterByID(36)->getMovementIndex())
	{
	case 0:
		getCharacterByID(36)->move(1098, 'x', 20);
		break;
	case 1:
		getCharacterByID(36)->move(65, 'y', 30);
		break;
	case 2:
		getCharacterByID(36)->move(1119, 'x', 20);
		break;
	case 3:
		getCharacterByID(36)->move(56, 'y', 30);
		break;
	case 4:
		getCharacterByID(36)->move(1128, 'x', 20);
		break;
	case 5:
		progressEvent();
		break;
	}

	switch (getCharacterByID(37)->getMovementIndex())
	{
	case 0:
		getCharacterByID(37)->move(1098, 'x', 20);
		break;
	case 1:
		getCharacterByID(37)->move(65, 'y', 30);
		break;
	case 2:
		getCharacterByID(37)->move(1121, 'x', 20);
		break;
	}
}

void Event_ThotPatrol::speak()
{
	switch (getPopupIndex())
	{
	case 0:
		popups_[0].displayPopup(-23, -3);
		break;
	case 1:
		popups_[1].displayPopup(-23, 21);
		break;
	case 2:
		popups_[2].displayPopup(-23, -3);
		break;
	case 3:
		popups_[3].displayPopup(-23, 21);
		break;
	case 4:
		popups_[4].displayPopup(-23, -3);
		break;
	case 5:
		popups_[5].displayPopup(-23, 21);
		break;
	case 6:
		popups_[6].displayPopup(-23, -3);
		break;
	case 7:
		getCharacterByID(37)->faceDirection('u');
		popups_[7].displayPopup(-23, 21);
		break;
	case 8:
		getCharacterByID(37)->faceDirection('r');
		popups_[8].displayPopup(-23, -3);
		break;
	case 9:
		popups_[9].displayPopup(-23, 21);
		break;
	case 10:
		popups_[10].displayPopup(-23, -3);
		break;
	case 11:
		getCharacterByID(37)->faceDirection('u');
		popups_[11].displayPopup(-23, 21);
		break;
	case 12:
		getCharacterByID(36)->faceDirection('d');
		popups_[12].displayPopup(-23, -3);
		break;
	case 13:
		popups_[13].displayPopup(-23, 21);
		break;
	case 14:
		popups_[14].displayPopup(-23, -3);
		break;
	case 15:
		getCharacterByID(37)->faceDirection('r');
		popups_[15].displayPopup(-23, 21);
		break;
	case 16:
		popups_[16].displayPopup(-23, -3);
		break;
	case 17:
		getCharacterByID(37)->faceDirection('u');
		popups_[17].displayPopup(-23, 21);
		break;
	case 18:
		popups_[18].displayPopup(-23, -3);
		break;
	case 19:
		popups_[19].displayPopup(-23, 21);
		break;
	case 20:
		getCharacterByID(36)->faceDirection('r');
		popups_[20].displayPopup(-23, -3);
		break;
	case 21:
		getCharacterByID(37)->faceDirection('r'); // FROM OVERKILL
		popups_[21].displayPopup(-23, 21);
		popups_[21].displayPopup(-23, -3);
		break;
	case 22:
		popups_[22].displayPopup(23, 1); // AKI
		break;
	case 23:
		popups_[23].displayPopup(-23, 21);
		break;
	case 24:
		popups_[24].displayPopup(-23, -3);
		break;
	case 25:
		popups_[25].displayPopup(23, 1); // AKI
		break;
	case 26:
		popups_[26].displayPopup(23, 1); // AKI
		break;
	case 27:
		popups_[27].displayPopup(-23, 21);
		break;
	case 28:
		popups_[28].displayPopup(-23, -3);
		break;
	case 29:
		popups_[29].displayPopup(-23, 21);
		break;
	case 30:
		popups_[30].displayPopup(-23, -3);
		break;
	case 31:
		progressEvent();
		break;
	}
}

void Event_ThotPatrol::battle()
{
	selected_character_ = getCharacterByID(36);
	selected_character_->enterBattle();
}
