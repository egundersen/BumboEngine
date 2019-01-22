#include "Event_ThrowOffCliff.h"

Event_ThrowOffCliff::Event_ThrowOffCliff(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, int character_ID, std::string directory, bool repeatable, std::vector<std::vector<std::pair<int, int>>>& element_has_object, Matrix & screen_matrix, std::vector<CharacterBase*>& characters, ScreenPosition & screen_position, int screen_width, int screen_height)
	: EventBase(unique_object_ID, center_position_x, center_position_y, collider_width, collider_height, character_ID, repeatable, element_has_object, screen_matrix, characters, screen_position, screen_width, screen_height), directory_{ directory }
{
}

void Event_ThrowOffCliff::createEvent()
{
	updateColliderCoordinates();

	Popup popup_1(25, 9, "Well, well, well, WHO DO <WE> HAVE HERE?", screen_matrix_, '#');
	Popup popup_2(25, 9, "Someones been asking for some corporal punishment, huh?", screen_matrix_, '#');
	Popup popup_3(25, 9, "But, I'm only 7!", screen_matrix_, 'X');
	Popup popup_4(25, 9, "And if you don't tell me where you got this PC game-", screen_matrix_, '#');
	Popup popup_5(25, 9, "...it'll only take me 7 seconds to THROW YOU OFF THIS CLIFF!", screen_matrix_, '#');
	Popup popup_6(25, 9, "Gamest0p!", screen_matrix_, 'X');
	Popup popup_7(25, 9, "Nobody uses Gamest0p anymore! What is this 2016?", screen_matrix_, '#');
	Popup popup_8(25, 9, "You think you can make a fool out of <ME>?", screen_matrix_, '#');
	Popup popup_9(25, 9, "DO YOU EVEN KNOW WHO I AM?", screen_matrix_, '#');

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

void Event_ThrowOffCliff::refreshEvent()
{
	switch (getEventIndex())
	{
	case 0:
		speak1();
		break;
	case 1:
		move();
		break;
	case 2:
		speak2();
		break;
	case 3:
		throwOffCliff();
		break;
	case 4:
		onEventOver();
		break;
	default:
		break;
	}
}

void Event_ThrowOffCliff::speak1()
{
	switch (getPopupIndex())
	{
	case 0:
		popups_[0].displayPopup(-24, 21);
		break;
	case 1:
		progressEvent();
		break;
	}
}

void Event_ThrowOffCliff::move()
{
	switch (getCharacterByID(19)->getMovementIndex())
	{
	case 0:
		getCharacterByID(19)->move(515, 'x', 30);
		break;
	case 1:
		progressEvent();
		break;
	}
}

void Event_ThrowOffCliff::speak2()
{
	switch (getPopupIndex())
	{
	case 0:
		popups_[1].displayPopup(-1, 21);
		break;
	case 1:
		popups_[2].displayPopup(25, 8);
		break;
	case 2:
		popups_[3].displayPopup(-1, 21);
		break;
	case 3:
		popups_[4].displayPopup(-1, 21);
		break;
	case 4:
		popups_[5].displayPopup(25, 8);
		break;
	case 5:
		popups_[6].displayPopup(-1, 21);
		break;
	case 6:
		popups_[7].displayPopup(-1, 21);
		break;
	case 7:
		popups_[8].displayPopup(-1, 21);
		break;
	case 8:
		go_down_iterator_ = 0;
		fall_speed_ = 125;
		playMP3("falling.mp3", directory_, "falling", 35);
		progressEvent(19);
		break;
	}
}

void Event_ThrowOffCliff::throwOffCliff()
{
	double current_time_begin_event_ = GetTickCount64() - start_time_begin_event_;
	if (current_time_begin_event_ > fall_speed_)
	{
		if (go_down_iterator_ > 15)
		{
			getCharacterByID(19)->faceDirection('d');
			onEventOver();
		}
		else if (go_down_iterator_ > 15)
		{
			fall_speed_ = 5000; // currently does nothing
		}
		else if (go_down_iterator_ > 5)
		{
			fall_speed_ = 5;
			// TODO Audio Play Crash sound
		}
		else if (go_down_iterator_ == 0) {
			getCharacterByID(35)->teleportNPC(198, 165);
		}
		go_down_iterator_++;
		start_time_begin_event_ = GetTickCount64();
	}
	getCharacterByID(35)->displayGhostSprite(
		500 - (screen_position_.x + screen_width_ / 2) + (screen_width_ - 23), go_down_iterator_ + 22, 'd');
}