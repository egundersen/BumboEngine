#include "Event_BorderIncident.h"
#include <Windows.h>

void Event_BorderIncident::createEvent()
{
	updateColliderCoordinates();

	//Popup popup_4(25, 9, "I am very sorry,Zbut he wasn't able toZreach the checkpointZin time...Z", screen_matrix_, 'X');
	
	// Guard #1 Dialog
	Popup popup_1(25, 9, "*cough*", screen_matrix_, 'X');
	Popup popup_2(25, 9, "*cough* *cough*", screen_matrix_, 'X');
	Popup popup_3(25, 9, "*clears throat*", screen_matrix_, 'X');
	Popup popup_4(25, 9, "Attention!", screen_matrix_, 'X');
	Popup popup_5(25, 9, "Do to deteriorating air quality, we won't be allowing anyone else into the maze ", screen_matrix_, 'X');
	Popup popup_6(25, 9, "We're truly sorry, we know you walking all the way here ", screen_matrix_, 'X');
	Popup popup_7(25, 9, "Some of you lost family members along the way ", screen_matrix_, 'X');
	Popup popup_8(25, 9, "and WE-DID-SAY that the checkpoint WOULD-REMAIN-OPEN ", screen_matrix_, 'X');
	Popup popup_9(25, 9, "But we'll be shutting down immediatly with no warning or heads-up ", screen_matrix_, 'X');
	Popup popup_10(25, 9, "Sorry ya walked all the way here, but we're closed now ", screen_matrix_, 'X');
	Popup popup_11(25, 9, "So get fucked ", screen_matrix_, 'X');

	// Crowd
	Popup popup_12(25, 9, "This is an outrage!", screen_matrix_, 'X');
	Popup popup_13(25, 9, "You shouldn't have waited for us all to arrive before shutting down, this is madness!", screen_matrix_, 'X');
	
	// Guard #2 Dialog
	Popup popup_14(25, 9, "We're sorry, but I believe my associate was very clear in his message: ", screen_matrix_, 'X');
	Popup popup_15(25, 9, "*ehem*!", screen_matrix_, 'X');
	Popup popup_16(25, 9, "*clears throat*", screen_matrix_, 'X');
	Popup popup_17(25, 9, "get fucked", screen_matrix_, 'X');

	// Guard #1's Response to checkpoint attack
	Popup popup_18(25, 9, "You think you can break through <MY> CHECKPOINT!!!??? ", screen_matrix_, 'X');
	Popup popup_19(25, 9, "DO YOU EVEN KNOW WHO I AM? ", screen_matrix_, 'X');

	// Player thoughts
	Popup popup_20(31, 9, "You think to yourself: *The guards aren't blocking the checkpoint anymore, perhaps I could slip through ...* ", screen_matrix_, 'X');

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
}

void Event_BorderIncident::refreshEvent()
{
	switch (getEventIndex())
	{
	case 0:
		// guards talk
		guardTalks();
		break;
	case 1:
		// audience looks around
		crowdLooksAround();
		break;
	case 2:
		// audience replies and guard responds
		guardReplies();
		break;
	case 3:
		// audience looks around (again)
		crowdLooksAround();
		break;
	case 4:
		// guchi gang approaches checkpoint
		approachCheckpoint(600, -412);
		break;
	case 5:
		resetMovementIndexes();
		progressEvent();
		break;
	case 6:
		// guchi gang runs through checkpoint
		runsThroughCheckpoint(600, -412);
		break;
	case 7:
		// guards yells after them
		guardStopThem();
		break;
	case 8:
		// guards follow them & person in line walks next to you
		guardExits();
		break;
	case 9:
		// person says you dropped something, you check item, you realize they stole your item
		playerThinks();
		break;
	case 10:
		onEventOver();
		break;
	default:
		break;
	}
}

void Event_BorderIncident::guardTalks()
{
	switch (getPopupIndex())
	{
	case 0:
		popups_[0].displayPopup(20, -3);
		break;
	case 1:
		popups_[1].displayPopup(20, -3);
		break;
	case 2:
		popups_[2].displayPopup(20, -3);
		break;
	case 3:
		popups_[3].displayPopup(20, -3);
		break;
	case 4:
		popups_[4].displayPopup(20, -3);
		break;
	case 5:
		popups_[5].displayPopup(20, -3);
		break;
	case 6:
		popups_[6].displayPopup(20, -3);
		break;
	case 7:
		popups_[7].displayPopup(20, -3);
		break;
	case 8:
		popups_[8].displayPopup(20, -3);
		break;
	case 9:
		popups_[9].displayPopup(20, -3);
		break;
	case 10:
		popups_[10].displayPopup(20, -3);
		break;
	case 11:
		progressEvent();
		break;
	}
}

void Event_BorderIncident::crowdLooksAround()
{
	double current_time_begin_event_ = GetTickCount64() - start_time_begin_event_;
	if (current_time_begin_event_ > 3000)
	{
		progressEvent();
	}
	else if (current_time_begin_event_ > 2500)
	{
		crowdLook2();
	}
	else if (current_time_begin_event_ > 2000)
	{
		crowdLook1();
	}
	else if (current_time_begin_event_ > 1500)
	{
		crowdLook2();
	}
	else if (current_time_begin_event_ > 1000)
	{
		crowdLook1();
	}
	else if (current_time_begin_event_ > 500)
	{
		crowdLook2();
	}
	else if (current_time_begin_event_ <= 500)
	{
		crowdLook1();
	}
}

void Event_BorderIncident::guardReplies()
{
	switch (getPopupIndex())
	{
	case 0:
		popups_[11].displayPopup(-25, -3);
		break;
	case 1:
		popups_[12].displayPopup(-25, -3);
		break;
	case 2:
		popups_[13].displayPopup(27, 16);
		attached_character_->move(1070, 'x', 20);
		break;
	case 3:
		popups_[14].displayPopup(27, 16);
		break;
	case 4:
		popups_[15].displayPopup(27, 16);
		break;
	case 5:
		popups_[16].displayPopup(27, 16);
		break;
	case 6:
		progressEvent();
		break;
	}
}

void Event_BorderIncident::approachCheckpoint(int position_x, int position_y)
{
	// Ryuuko
	switch (getCharacterByID(11)->getMovementIndex())
	{
	case 0:
		getCharacterByID(11)->teleportNPC(392 + position_x, 630 + position_y);
		getCharacterByID(11)->incrementMovementIndex();
		break;
	case 1:
		getCharacterByID(11)->move(433 + position_x, 'x', 30);
		break;
	case 2:
		getCharacterByID(11)->move(626 + position_y, 'y', 30);
		break;
	case 3:
		getCharacterByID(11)->move(454 + position_x, 'x', 30);
		break;
	default:
		break;
	}

	// Sharktooth (Changes Event Index)
	switch (getCharacterByID(14)->getMovementIndex())
	{
	case 0:
		getCharacterByID(14)->teleportNPC(382 + position_x, 634 + position_y);
		getCharacterByID(14)->incrementMovementIndex();
		break;
	case 1:
		getCharacterByID(14)->move(433 + position_x, 'x', 32);
		break;
	case 2:
		getCharacterByID(14)->move(629 + position_y, 'y', 32);
		break;
	case 3:
		getCharacterByID(14)->move(446 + position_x, 'x', 32);
		break;
	case 4:
		getCharacterByID(14)->move(623 + position_y, 'y', 32);
		break;
	case 5:
		getCharacterByID(14)->faceDirection('r');
		getCharacterByID(14)->incrementMovementIndex();
		break;
	case 6:
		progressEvent();
		break;
	default:
		break;
	}

	// Bonny
	switch (getCharacterByID(13)->getMovementIndex())
	{
	case 0:
		getCharacterByID(13)->teleportNPC(372 + position_x, 634 + position_y);
		getCharacterByID(13)->incrementMovementIndex();
		break;
	case 1:
		getCharacterByID(13)->move(428 + position_x, 'x', 40);
		break;
	case 2:
		getCharacterByID(13)->move(626 + position_y, 'y', 40);
		break;
	case 3:
		getCharacterByID(13)->move(438 + position_x, 'x', 40);
		break;
	default:
		break;
	}

	// Aki
	switch (getCharacterByID(12)->getMovementIndex())
	{
	case 0:
		getCharacterByID(12)->teleportNPC(362 + position_x, 633 + position_y);
		getCharacterByID(12)->incrementMovementIndex();
		break;
	case 1:
		getCharacterByID(12)->move(433 + position_x, 'x', 40);
		break;
	default:
		break;
	}
	
	// Mysterious Mr. X
	switch (getCharacterByID(15)->getMovementIndex())
	{
	case 0:
		getCharacterByID(15)->teleportNPC(356 + position_x, 628 + position_y);
		getCharacterByID(15)->incrementMovementIndex();
		break;
	case 1:
		getCharacterByID(15)->move(426 + position_x, 'x', 40);
		break;
	default:
		break;
	}
}

void Event_BorderIncident::runsThroughCheckpoint(int position_x, int position_y)
{
	// Ryuuko
	switch (getCharacterByID(11)->getMovementIndex())
	{
	case 0:
		getCharacterByID(11)->move(627 + position_y, 'y', 30);
		break;
	case 1:
		getCharacterByID(11)->move(screen_position_.x + screen_width_ / 2, 'x', 30);
		break;
	case 2:
		getCharacterByID(11)->faceDirection('u');
		getCharacterByID(11)->incrementMovementIndex();
		break;
	case 3:
		getCharacterByID(11)->waitForTime(2000);
		break;
	case 4:
		getCharacterByID(11)->move(471 + position_x, 'x', 30);
		break;
	case 5:
		getCharacterByID(9)->teleportNPC(483 + position_x, 671 + position_y); // Remove guard thats in the way
		getCharacterByID(11)->move(472 + position_x, 'x', 30);
		break;
	case 6:
		getCharacterByID(11)->move(518 + position_x, 'x', 10);
		break;
	case 7:
		getCharacterByID(11)->teleportNPC(192, 84); // Actual World Position
		getCharacterByID(11)->faceDirection('r');
		break;
	default:
		break;
	}

	// Sharktooth
	switch (getCharacterByID(14)->getMovementIndex())
	{
	case 0:
		getCharacterByID(14)->move(screen_position_.x + screen_width_ / 2 - 9, 'x', 32);
		break;
	case 1:
		getCharacterByID(14)->move(627 + position_y, 'y', 32);
		break;
	case 2:
		getCharacterByID(14)->waitForTime(2500);
		break;
	case 3:
		getCharacterByID(14)->move(518 + position_x, 'x', 10);
		break;
	case 4:
		getCharacterByID(14)->teleportNPC(104, 203);
		getCharacterByID(14)->faceDirection('u');
		break;
	default:
		break;
	}

	// Bonny
	switch (getCharacterByID(13)->getMovementIndex())
	{
	case 0:
		getCharacterByID(13)->waitForTime(2800);
		break;
	case 1:
		getCharacterByID(13)->move(screen_position_.x + screen_width_ / 2 - 9, 'x', 32);
		break;
	case 2:
		getCharacterByID(13)->move(627 + position_y, 'y', 32);
		break;
	case 3:
		getCharacterByID(13)->move(518 + position_x, 'x', 10);
		break;
	case 4:
		getCharacterByID(13)->teleportNPC(564, 163);
		getCharacterByID(13)->faceDirection('r');
		break;
	default:
		break;
	}

	// Aki
	switch (getCharacterByID(12)->getMovementIndex())
	{
	case 0:
		getCharacterByID(12)->waitForTime(2800);
		break;
	case 1:
		getCharacterByID(12)->move(623 + position_y, 'y', 32);
		break;
	case 2:
		getCharacterByID(12)->move(screen_position_.x + screen_width_ / 2 - 9, 'x', 32);
		break;
	case 3:
		getCharacterByID(12)->move(626 + position_y, 'y', 32);
		break;
	case 4:
		getCharacterByID(12)->move(518 + position_x, 'x', 10);
		break;
	case 5:
		getCharacterByID(12)->teleportNPC(664, 67);
		getCharacterByID(12)->faceDirection('d');
		break;
	default:
		break;
	}

	// Mysterious Mr. X (Changes Event Index)
	switch (getCharacterByID(15)->getMovementIndex())
	{
	case 0:
		getCharacterByID(15)->waitForTime(2800);
		break;
	case 1:
		getCharacterByID(15)->move(630 + position_y, 'y', 32);
		break;
	case 2:
		getCharacterByID(15)->waitForTime(1000);
		break;
	case 3:
		getCharacterByID(15)->move(screen_position_.x + screen_width_ / 2 - 9, 'x', 32);
		break;
	case 4:
		getCharacterByID(15)->move(627 + position_y, 'y', 32);
		break;
	case 5:
		getCharacterByID(15)->move(screen_position_.x + screen_width_ / 2 - 9 + 3, 'x', 10);
		break;
	case 6:
		getCharacterByID(15)->waitForTime(250);
		break;
	case 7:
		getCharacterByID(15)->move(479 + position_x, 'x', 1);
		break;
	case 8:
		getCharacterByID(15)->move(518 + position_x, 'x', 1);
		getCharacterByID(8)->faceDirection('r'); // face guard right
		break;
	case 9:
		getCharacterByID(7)->teleportNPC(493 + position_x, 671 + position_y);
		getCharacterByID(15)->teleportNPC(453 + position_x, 671 + position_y);
		progressEvent();
		break;
	default:
		break;
	}
}

void Event_BorderIncident::guardStopThem()
{
	switch (getPopupIndex())
	{
	case 0:
		popups_[17].displayPopup(20, -3);
		break;
	case 1:
		popups_[18].displayPopup(20, -3);
		break;
	case 2:
		progressEvent();
		break;
	}
}

void Event_BorderIncident::guardExits()
{
	switch (getCharacterByID(8)->getMovementIndex())
	{
	case 0:
		getCharacterByID(8)->move(207, 'y', 20);
		break;
	case 1:
		getCharacterByID(8)->move(1112, 'x', 20);
		break;
	case 2:
		getCharacterByID(8)->teleportNPC(1073, 259);
		progressEvent();
		break;
	default:
		break;
	}
}

void Event_BorderIncident::playerThinks()
{
	switch (getPopupIndex())
	{
	case 0:
		popups_[19].displayPopup(0, -3);
		break;
	case 1:
		progressEvent();
		break;
	}
}

void Event_BorderIncident::crowdLook1()
{
	getCharacterByID(3)->faceDirection('d');
	getCharacterByID(4)->faceDirection('r');
	getCharacterByID(5)->faceDirection('l');
	getCharacterByID(6)->faceDirection('r');
}

void Event_BorderIncident::crowdLook2()
{
	getCharacterByID(3)->faceDirection('r');
	getCharacterByID(4)->faceDirection('l');
	getCharacterByID(5)->faceDirection('r');
	getCharacterByID(6)->faceDirection('l');
}

void Event_BorderIncident::resetMovementIndexes()
{
	getCharacterByID(11)->resetMovementIndex();
	getCharacterByID(12)->resetMovementIndex();
	getCharacterByID(13)->resetMovementIndex();
	getCharacterByID(14)->resetMovementIndex();
	getCharacterByID(15)->resetMovementIndex();
}
