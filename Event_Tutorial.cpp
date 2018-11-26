#include "Event_Tutorial.h"
#include <Windows.h>
#include <iostream>

void Event_Tutorial::createEvent()
{
	updateColliderCoordinates();

	Popup popup_1(25, 9, "Pardon me, butZCould I getZyour name?Z", matrix_display_, 'X');
	Popup popup_2(25, 9, "! ! ! ! !", matrix_display_, 'X');
	Popup popup_3(25, 9, "Very good, I wasZlooking for you.ZIt's about yourZfather...Z", matrix_display_, 'X');
	Popup popup_4(25, 9, "I am very sorry,Zbut he wasn't able toZreach the checkpointZin time...Z", matrix_display_, 'X');
	Popup popup_5(25, 9, "You have myZcondolences, heZwas my friendZas wellZ", matrix_display_, 'X');
	Popup popup_6(25, 9, "Bay-si-call-e,Zhe left me thisZpackage for youZ", matrix_display_, 'X');
	Popup popup_7(25, 9, "I've not seenZwhats inside, butZhe made sayZit was importantZ", matrix_display_, 'X');
	Popup popup_8(25, 9, "OBTAINED THEZZMYSTERIOUSZDevice !!Z", matrix_display_, 'X');
	Popup popup_9(25, 9, "Oh I forgot toZintroduce myselfZ", matrix_display_, 'X');
	Popup popup_10(25, 9, "I am theZtutorial NPCZ", matrix_display_, 'X');
	Popup popup_11(25, 9, "But everyone callsZme tutorial NPCZ", matrix_display_, 'X');
	Popup popup_12(25, 9, "Tutorial isZokay, right?Z", matrix_display_, 'X');

	Popup popup_13(25, 9, "Yeah so here isZtalking about thisZplaceZ", matrix_display_, 'X');
	Popup popup_14(25, 9, "Welcome to NakinomZborder checkpoint,Zthe last open roadZto safetyZ", matrix_display_, 'X');
	Popup popup_15(25, 9, "Must of been longZjourney, yes?ZHow about a refresh?Z", matrix_display_, 'X');
	Popup popup_16(25, 9, "Look upon.ZSee this sign?Z", matrix_display_, 'X');
	Popup popup_17(25, 9, "You can walkZup to signZand press EZ", matrix_display_, 'X');
	Popup popup_18(25, 9, "Make sense right?ZWalk to signZand press EZ", matrix_display_, 'X');
	Popup popup_19(25, 9, "You can press EZon people tooZ", matrix_display_, 'X');
	Popup popup_20(25, 9, "Okay, right?", matrix_display_, 'X');
	Popup popup_21(25, 9, "Press EZPress EZ", matrix_display_, 'X');
	Popup popup_22(25, 9, "Press EZtalk to thingsZ", matrix_display_, 'X');
	Popup popup_23(25, 9, "Pick up items", matrix_display_, 'X');
	Popup popup_24(25, 9, "Talk to people", matrix_display_, 'X');
	Popup popup_25(25, 9, "Look at,Zpress EZ", matrix_display_, 'X');
	Popup popup_26(25, 9, "Okay,Zmake sense?Z", matrix_display_, 'X');
	Popup popup_27(25, 9, "You understandZpress E talk to?Z", matrix_display_, 'X');
	Popup popup_28(25, 9, "Very good, youZknow this gameZdoes not comeZwith easy controlsZ", matrix_display_, 'X');
	Popup popup_29(25, 9, "No way for you toZknow... to press E.ZNo instructionZ", matrix_display_, 'X');
	Popup popup_30(25, 9, "I just thoughtZyou needed helpZ", matrix_display_, 'X');
	Popup popup_31(25, 9, "You know,ZI am very humbleZ", matrix_display_, 'X');
	Popup popup_32(25, 9, "I just wantZto help youZ", matrix_display_, 'X');
	Popup popup_33(25, 9, "Very good.ZSo, moving on...Z", matrix_display_, 'X');
	Popup popup_34(25, 9, "Press 'i' toZopen your inventr-yZ", matrix_display_, 'X');
	Popup popup_35(25, 9, "You know, you press EZon item you wonderZwhere it go.ZYou freak out!Z", matrix_display_, 'X');
	Popup popup_36(25, 9, "Don't worry", matrix_display_, 'X');
	Popup popup_37(25, 9, "I am here to help you", matrix_display_, 'X');
	Popup popup_38(25, 9, "I am here for you", matrix_display_, 'X');
	Popup popup_39(25, 9, "You know,ZI am very humbleZ", matrix_display_, 'X');
	Popup popup_40(25, 9, "I give you whatZinstruction you needZ", matrix_display_, 'X');
	Popup popup_41(25, 9, "Press E to interactZand Press I toZopen inventr-yZ", matrix_display_, 'X');
	Popup popup_42(25, 9, "If you confuse,Zyou can look itZup on the go0gleZ", matrix_display_, 'X');
	Popup popup_43(25, 9, "Look upon", matrix_display_, 'X');
	Popup popup_44(25, 9, "So yeah hereZis talking about thisZ", matrix_display_, 'X');
	Popup popup_45(25, 9, "Most people, theyZenter checkpoint,Zthey think 'Oh,Zmy troubles over'Z", matrix_display_, 'X');
	Popup popup_46(25, 9, "But no", matrix_display_, 'X');
	Popup popup_47(25, 9, "What lies on otherZside of checkpoint,Zis called the mazeZ", matrix_display_, 'X');
	Popup popup_48(25, 9, "Maze is veryZdangerous place,Zyou don't knowZwhat you doing,Zand you needZadviseZ", matrix_display_, 'X');
	Popup popup_49(25, 9, "But don't worry,Zyou know,ZI am here to helpZ", matrix_display_, 'X');
	Popup popup_50(25, 9, "You knowZI am very humbleZ", matrix_display_, 'X');
	Popup popup_51(25, 9, "And I am hereZto help youZ", matrix_display_, 'X');
	Popup popup_52(25, 9, "So you areZprepared when youZcross the checkpointZand enter the mazeZ", matrix_display_, 'X');
	Popup popup_53(25, 9, "So I will show youZhow combat works,Zit's very easyZ", matrix_display_, 'X');
	Popup popup_54(25, 9, "Here we go", matrix_display_, 'X');

	Popup popup_tutorial_choice(25, 9, "Do you LIKE TUTORIAL?ZZ YES             NOZZ", matrix_display_, 'X');

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
	popup_35.createPopupText();
	popup_36.createPopupText();
	popup_37.createPopupText();
	popup_38.createPopupText();
	popup_39.createPopupText();
	popup_40.createPopupText();
	popup_41.createPopupText();
	popup_42.createPopupText();
	popup_43.createPopupText();
	popup_44.createPopupText();
	popup_45.createPopupText();
	popup_46.createPopupText();
	popup_47.createPopupText();
	popup_48.createPopupText();
	popup_49.createPopupText();
	popup_50.createPopupText();
	popup_51.createPopupText();
	popup_52.createPopupText();
	popup_53.createPopupText();
	popup_54.createPopupText();
	popup_tutorial_choice.createPopupText();

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
	popups_.push_back(popup_35);
	popups_.push_back(popup_36);
	popups_.push_back(popup_37);
	popups_.push_back(popup_38);
	popups_.push_back(popup_39);
	popups_.push_back(popup_40);
	popups_.push_back(popup_41);
	popups_.push_back(popup_42);
	popups_.push_back(popup_43);
	popups_.push_back(popup_44);
	popups_.push_back(popup_45);
	popups_.push_back(popup_46);
	popups_.push_back(popup_47);
	popups_.push_back(popup_48);
	popups_.push_back(popup_49);
	popups_.push_back(popup_50);
	popups_.push_back(popup_51);
	popups_.push_back(popup_52);
	popups_.push_back(popup_53);
	popups_.push_back(popup_54);
	popups_.push_back(popup_tutorial_choice);

	/* NOTE: Instead of calling every index, the below should of been a loop, constantly "popping" the vector */
}

void Event_Tutorial::refreshEvent()
{
	switch (event_index_)
	{
	case 0:
		moveManny(4000);
		break;
	case 1:
		getPlayerName();
		break;
	case 2:
		beforeTutorial(4000);
		break;
	case 3:
		skipTutorial();
		break;
	case 4:
		tutorial();
		break;
	case 5:
		attached_character_->teleportNPC(251, 634);
		attached_character_->faceDirection('d');
		should_enter_battle_ = true;
		event_index_++;
		break;
	case 6:
		onEventOver();
		break;
	default:
		break;
	}
}

void Event_Tutorial::moveManny(int time_interval)
{
	double current_time_begin_event_ = GetTickCount() - start_time_begin_event_;
	if (current_time_begin_event_ > time_interval * 2)
	{
		event_index_++;
		start_time_begin_event_ = GetTickCount();
	}
	else if (current_time_begin_event_ > time_interval)
		popups_[0].displayPopup(10, 0);
	else if (current_time_begin_event_ <= time_interval)
	{
		// Will automatically increase movement index
		switch (attached_character_->getMovementIndex())
		{
		case 0:
			attached_character_->move(216, 'x', 20);
			break;
		case 1:
			attached_character_->move(640, 'y', 35);
			break;
		case 2:
			attached_character_->move(211, 'x', 20);
			break;
		case 3:
			attached_character_->move(642, 'y', 35);
			break;
		case 4:
			attached_character_->move(201, 'x', 20);
			break;
		case 5:
			attached_character_->move(screen_position_.y + screen_height_ / 2 + 1, 'y', 35);
			break;
		case 6:
			attached_character_->move(screen_position_.x + screen_width_ / 2 + 9, 'x', 20);
			break;
		default:
			break;
		}
	}
}

void Event_Tutorial::beforeTutorial(int time_interval)
{
	double current_time_begin_event_ = GetTickCount() - start_time_begin_event_;
	if (current_time_begin_event_ > time_interval * 12)
	{
		event_index_++;
		start_time_begin_event_ = GetTickCount();
	}
	else if (current_time_begin_event_ > time_interval * 11)
		popups_[11].displayPopup(10, 0);
	else if (current_time_begin_event_ > time_interval * 10)
		popups_[10].displayPopup(10, 0);
	else if (current_time_begin_event_ > time_interval * 9)
		popups_[9].displayPopup(10, 0);
	else if (current_time_begin_event_ > time_interval * 8)
	{
		popups_[8].displayPopup(10, 0);
		popups_[7].displayPopup(-17, 9);
	}
	else if (current_time_begin_event_ > time_interval * 7) // FAKE ITEM
		popups_[7].displayPopup(-17, 9);
	else if (current_time_begin_event_ > time_interval * 6)
		popups_[6].displayPopup(10, 0);
	else if (current_time_begin_event_ > time_interval * 5)
		popups_[5].displayPopup(10, 0);
	else if (current_time_begin_event_ > time_interval * 4)
		popups_[4].displayPopup(10, 0);
	else if (current_time_begin_event_ > time_interval * 3)
		popups_[3].displayPopup(10, 0);
	else if (current_time_begin_event_ > time_interval * 2)
		popups_[2].displayPopup(10, 0);
	else if (current_time_begin_event_ > time_interval)
		popups_[1].displayPopup(10, 0);
}

void Event_Tutorial::tutorial()
{
	double current_time_begin_event_ = GetTickCount() - start_time_begin_event_;
	if (current_time_begin_event_ > 73000)
	{
		event_index_++;
		start_time_begin_event_ = GetTickCount();
	}
	else if (current_time_begin_event_ > 71000)
		popups_[53].displayPopup(10, 0);
	else if (current_time_begin_event_ > 69000)
		popups_[52].displayPopup(10, 0);
	else if (current_time_begin_event_ > 64000)
		popups_[51].displayPopup(10, 0);
	else if (current_time_begin_event_ > 63000)
		popups_[50].displayPopup(10, 0);
	else if (current_time_begin_event_ > 62000)
		popups_[49].displayPopup(10, 0);
	else if (current_time_begin_event_ > 61000)
		popups_[48].displayPopup(10, 0);
	else if (current_time_begin_event_ > 60000)
		popups_[47].displayPopup(10, 0);
	else if (current_time_begin_event_ > 59000)
		popups_[46].displayPopup(10, 0);
	else if (current_time_begin_event_ > 58000)
		popups_[45].displayPopup(10, 0);
	else if (current_time_begin_event_ > 57000)
		popups_[44].displayPopup(10, 0);
	else if (current_time_begin_event_ > 56000)
		popups_[43].displayPopup(10, 0);
	else if (current_time_begin_event_ > 55000)
		popups_[42].displayPopup(10, 0);
	else if (current_time_begin_event_ > 54000)
		popups_[41].displayPopup(10, 0);
	else if (current_time_begin_event_ > 53000)
		popups_[40].displayPopup(10, 0);
	else if (current_time_begin_event_ > 52000)
		popups_[39].displayPopup(10, 0);
	else if (current_time_begin_event_ > 51000)
		popups_[38].displayPopup(10, 0);
	else if (current_time_begin_event_ > 50000)
		popups_[37].displayPopup(10, 0);
	else if (current_time_begin_event_ > 49000)
		popups_[36].displayPopup(10, 0);
	else if (current_time_begin_event_ > 48000)
		popups_[35].displayPopup(10, 0);
	else if (current_time_begin_event_ > 45500)
		popups_[34].displayPopup(10, 0);
	else if (current_time_begin_event_ > 44000)
		popups_[33].displayPopup(10, 0);
	else if (current_time_begin_event_ > 43000)
		popups_[32].displayPopup(10, 0);
	else if (current_time_begin_event_ > 40000)
		popups_[31].displayPopup(10, 0);
	else if (current_time_begin_event_ > 37000)
		popups_[30].displayPopup(10, 0);
	else if (current_time_begin_event_ > 35000)
		popups_[29].displayPopup(10, 0);
	else if (current_time_begin_event_ > 32000)
		popups_[28].displayPopup(10, 0);
	else if (current_time_begin_event_ > 29000)
		popups_[27].displayPopup(10, 0);
	else if (current_time_begin_event_ > 26000)
		popups_[26].displayPopup(10, 0);
	else if (current_time_begin_event_ > 24000)
		popups_[25].displayPopup(10, 0);
	else if (current_time_begin_event_ > 23000)
		popups_[24].displayPopup(10, 0);
	else if (current_time_begin_event_ > 22000)
		popups_[23].displayPopup(10, 0);
	else if (current_time_begin_event_ > 21000)
		popups_[22].displayPopup(10, 0);
	else if (current_time_begin_event_ > 19000)
		popups_[21].displayPopup(10, 0);
	else if (current_time_begin_event_ > 18000)
		popups_[20].displayPopup(10, 0);
	else if (current_time_begin_event_ > 17000)
		popups_[19].displayPopup(10, 0);
	else if (current_time_begin_event_ > 16000)
	{
		popups_[18].displayPopup(10, 0);
		attached_character_->faceDirection('l');
	}
	else if (current_time_begin_event_ > 14000)
	{
		popups_[17].displayPopup(10, 0);
		attached_character_->faceDirection('d');
	}
	else if (current_time_begin_event_ > 11500)
	{
		popups_[16].displayPopup(10, 0);
		attached_character_->faceDirection('r');
	}
	else if (current_time_begin_event_ > 10000)
	{
		popups_[15].displayPopup(10, 0);
		attached_character_->faceDirection('u');
	}
	else if (current_time_begin_event_ > 7000)
		popups_[14].displayPopup(10, 0);
	else if (current_time_begin_event_ > 4000)
		popups_[13].displayPopup(10, 0);
	else if (current_time_begin_event_ <= 4000)
		popups_[12].displayPopup(10, 0);
}

void Event_Tutorial::getPlayerName()
{
	if (!has_entered_name_)
	{
		// display form popup

		double current_time_begin_event_ = GetTickCount() - start_time_begin_event_;
		if (current_time_begin_event_ > 200)
		{
			// get key pressed
		}
		// display form text

		event_index_++; // REMOVE THIS LINE
	}
	else
	{
		event_index_++;
	}
}

void Event_Tutorial::skipTutorial()
{
	if (!should_go_down_)
	{
		popups_[54].displayPopup(10, 0);

		double current_time_begin_event_ = GetTickCount() - start_time_begin_event_;
		if (current_time_begin_event_ > 200)
		{
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				dialog_choice_index_ = 1;
				start_time_begin_event_ = GetTickCount();
			}
			else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				dialog_choice_index_ = 0;
				start_time_begin_event_ = GetTickCount();
			}
			else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				start_time_begin_event_ = GetTickCount();
				confirmSelection();
			}
		}

		displayDialogChoice(40, 10);
	}
	else
	{
		double current_time_begin_event_ = GetTickCount() - start_time_begin_event_;
		if (current_time_begin_event_ > fall_speed)
		{
			if (go_down_iterator_ > 15)
			{
				onEventOver();
			}
			else if (go_down_iterator_ > 15)
			{
				fall_speed = 5000; // currently does nothing
			}
			else if (go_down_iterator_ > 5)
			{
				fall_speed = 5;
				// TODO Play Crash sound
			}
			go_down_iterator_++;
			start_time_begin_event_ = GetTickCount();
		}
		if (attached_character_ != nullptr)
			attached_character_->getSprite()->displayGhostAtPosition(43, go_down_iterator_ + 14);
	}
}

void Event_Tutorial::displayDialogChoice(int position_x, int position_y)
{
	if (dialog_choice_index_ == 0)
	{
		matrix_display_[position_y][position_x] = '^';
		matrix_display_[position_y][position_x + 1] = '^';
		matrix_display_[position_y][position_x - 1] = '^';
	}
	else
	{
		matrix_display_[position_y][position_x + 15] = '^';
		matrix_display_[position_y][position_x + 16] = '^';
		matrix_display_[position_y][position_x + 17] = '^';
		matrix_display_[position_y][position_x + 14] = '^';
	}
}

void Event_Tutorial::confirmSelection()
{
	if (dialog_choice_index_ == 0) // YES, do tutorial
	{
		event_index_++;
	}
	else // NO
	{
		should_go_down_ = true;
		attached_character_->teleportNPC(163, 680);
	}
}
