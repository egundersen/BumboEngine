#include "Event_BorderIncident.h"
#include <Windows.h>

void Event_BorderIncident::createEvent()
{
	updateColliderCoordinates();

	//Popup popup_4(25, 9, "I am very sorry,Zbut he wasn't able toZreach the checkpointZin time...Z", matrix_display_, 'X');
	
	// Guard #1 Dialog
	Popup popup_1(25, 9, "*cough*", matrix_display_, 'X');
	Popup popup_2(25, 9, "*cough* *cough*", matrix_display_, 'X');
	Popup popup_3(25, 9, "*clears throat*", matrix_display_, 'X');
	Popup popup_4(25, 9, "Attention!", matrix_display_, 'X');
	Popup popup_5(25, 9, "Do to deterioratingZair quality, weZwon't be allowingZanyone elseZinto the mazeZ", matrix_display_, 'X');
	Popup popup_6(25, 9, "We're truly sorry,Zwe know you walkingZall the way hereZ", matrix_display_, 'X');
	Popup popup_7(25, 9, "Some of you lostZfamily members alongZthe wayZ", matrix_display_, 'X');
	Popup popup_8(25, 9, "and WE-DID-SAY thatZthe checkpointZWOULD-REMAIN-OPENZ", matrix_display_, 'X');
	Popup popup_9(25, 9, "But we'll beZshutting downZimmediatly withZno warning orZheads-upZ", matrix_display_, 'X');
	Popup popup_10(25, 9, "Sorry ya walked allZthe way here, butZwe're closed nowZ", matrix_display_, 'X');
	Popup popup_11(25, 9, "So get fuckedZ", matrix_display_, 'X');

	// Crowd
	Popup popup_12(25, 9, "This is an outrage!", matrix_display_, 'X');
	Popup popup_13(25, 9, "You shouldn't haveZwaited for usZall to arriveZbefore shutting down,Zthis is madness!", matrix_display_, 'X');
	
	// Guard #2 Dialog
	Popup popup_14(25, 9, "We're sorry, but IZbelieve my associateZwas very clearZin his message:Z", matrix_display_, 'X');
	Popup popup_15(25, 9, "*ehem*!", matrix_display_, 'X');
	Popup popup_16(25, 9, "*clears throat*", matrix_display_, 'X');
	Popup popup_17(25, 9, "get fucked", matrix_display_, 'X');

	// Guard #1's Response to checkpoint attack
	Popup popup_18(25, 9, "You think you canZbreak through <MY>ZCHECKPOINT!!!???Z", matrix_display_, 'X');
	Popup popup_19(25, 9, "DO YOU EVENZKNOW WHO I AM?Z", matrix_display_, 'X');

	// Player thoughts
	Popup popup_20(25, 9, "You think toZyourself: *The guardsZaren't blockingZthe checkpointZanymore, perhapsZI could slipZthrough ...*Z", matrix_display_, 'X');

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
	switch (event_index_)
	{
	case 0:
		// guards talk
		guardTalks(4000);
		//approachCheckpoint();
		break;
	case 1:
		// audience looks around
		crowdLooksAround();
		//resetMovementIndexes();
		//event_index_++;
		break;
	case 2:
		// audience replies and guard responds
		guardReplies(4000);
		//runsThroughCheckpoint();
		break;
	case 3:
		// audience looks around (again)
		crowdLooksAround();
		break;
	case 4:
		// guchi gang approaches checkpoint
		approachCheckpoint();
		break;
	case 5:
		resetMovementIndexes();
		event_index_++;
		break;
	case 6:
		// guchi gang runs through checkpoint
		runsThroughCheckpoint();
		break;
	case 7:
		// guards yells after them
		guardStopThem(5000);
		break;
	case 8:
		// guards follow them & person in line walks next to you
		guardExits();
		break;
	case 9:
		// person says you dropped something, you check item, you realize they stole your item
		playerThinks(5000);
		break;
	case 10:
		onEventOver();
		break;
	default:
		break;
	}
}

void Event_BorderIncident::guardTalks(int time_interval)
{
	double current_time_begin_event_ = GetTickCount() - start_time_begin_event_;
	if (current_time_begin_event_ > time_interval * 12)
	{
		event_index_++;
		start_time_begin_event_ = GetTickCount();
	}
	else if (current_time_begin_event_ > time_interval * 11)
		popups_[10].displayPopup(20, -3);
	else if (current_time_begin_event_ > time_interval * 10)
		popups_[9].displayPopup(20, -3);
	else if (current_time_begin_event_ > time_interval * 9)
		popups_[8].displayPopup(20, -3);
	else if (current_time_begin_event_ > time_interval * 8)
		popups_[7].displayPopup(20, -3);
	else if (current_time_begin_event_ > time_interval * 7)
		popups_[6].displayPopup(20, -3);
	else if (current_time_begin_event_ > time_interval * 6) // skip 1 so dialogue lasts longer
		popups_[5].displayPopup(20, -3);
	else if (current_time_begin_event_ > time_interval * 4)
		popups_[4].displayPopup(20, -3);
	else if (current_time_begin_event_ > time_interval * 3)
		popups_[3].displayPopup(20, -3);
	else if (current_time_begin_event_ > time_interval * 2)
		popups_[2].displayPopup(20, -3);
	else if (current_time_begin_event_ > time_interval)
		popups_[1].displayPopup(20, -3);
	else if (current_time_begin_event_ <= time_interval)
		popups_[0].displayPopup(20, -3);
}

void Event_BorderIncident::crowdLooksAround()
{
	double current_time_begin_event_ = GetTickCount() - start_time_begin_event_;
	if (current_time_begin_event_ > 3000)
	{
		event_index_++;
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

void Event_BorderIncident::guardReplies(int time_interval)
{
	double current_time_begin_event_ = GetTickCount() - start_time_begin_event_;
	if (current_time_begin_event_ > time_interval * 7)
	{
		event_index_++;
		start_time_begin_event_ = GetTickCount();
	}
	else if (current_time_begin_event_ > time_interval * 6)
		popups_[16].displayPopup(27, 16);
	else if (current_time_begin_event_ > time_interval * 5)
		popups_[15].displayPopup(27, 16);
	else if (current_time_begin_event_ > time_interval * 4)
		popups_[14].displayPopup(27, 16);
	else if (current_time_begin_event_ > time_interval * 3) // Guard 2 speaks
	{
		popups_[13].displayPopup(27, 16);
		attached_character_->move(470, 'x', 20);
	}
	else if (current_time_begin_event_ > time_interval * 2)
		popups_[12].displayPopup(-25, -3);
	else if (current_time_begin_event_ <= time_interval * 2) // Crowd speaks
		popups_[11].displayPopup(-25, -3);
}

void Event_BorderIncident::approachCheckpoint()
{
	// Ryuuko
	switch (getCharacterByID(11)->getMovementIndex())
	{
	case 0:
		getCharacterByID(11)->teleportNPC(392, 630);
		getCharacterByID(11)->incrementMovementIndex();
		break;
	case 1:
		getCharacterByID(11)->move(433, 'x', 30);
		break;
	case 2:
		getCharacterByID(11)->move(626, 'y', 30);
		break;
	case 3:
		getCharacterByID(11)->move(454, 'x', 30);
		break;
	default:
		break;
	}

	// Sharktooth (Changes Event Index)
	switch (getCharacterByID(14)->getMovementIndex())
	{
	case 0:
		getCharacterByID(14)->teleportNPC(382, 634);
		getCharacterByID(14)->incrementMovementIndex();
		break;
	case 1:
		getCharacterByID(14)->move(433, 'x', 32);
		break;
	case 2:
		getCharacterByID(14)->move(629, 'y', 32);
		break;
	case 3:
		getCharacterByID(14)->move(446, 'x', 32);
		break;
	case 4:
		getCharacterByID(14)->move(623, 'y', 32);
		break;
	case 5:
		getCharacterByID(14)->faceDirection('r');
		getCharacterByID(14)->incrementMovementIndex();
		break;
	case 6:
		event_index_++;
		break;
	default:
		break;
	}

	// Bonny
	switch (getCharacterByID(13)->getMovementIndex())
	{
	case 0:
		getCharacterByID(13)->teleportNPC(372, 634);
		getCharacterByID(13)->incrementMovementIndex();
		break;
	case 1:
		getCharacterByID(13)->move(428, 'x', 40);
		break;
	case 2:
		getCharacterByID(13)->move(626, 'y', 40);
		break;
	case 3:
		getCharacterByID(13)->move(438, 'x', 40);
		break;
	default:
		break;
	}

	// Aki
	switch (getCharacterByID(12)->getMovementIndex())
	{
	case 0:
		getCharacterByID(12)->teleportNPC(362, 633);
		getCharacterByID(12)->incrementMovementIndex();
		break;
	case 1:
		getCharacterByID(12)->move(433, 'x', 40);
		break;
	default:
		break;
	}
	
	// Mysterious Mr. X
	switch (getCharacterByID(15)->getMovementIndex())
	{
	case 0:
		getCharacterByID(15)->teleportNPC(356, 628);
		getCharacterByID(15)->incrementMovementIndex();
		break;
	case 1:
		getCharacterByID(15)->move(426, 'x', 40);
		break;
	default:
		break;
	}
}

void Event_BorderIncident::runsThroughCheckpoint()
{
	// Ryuuko
	switch (getCharacterByID(11)->getMovementIndex())
	{
	case 0:
		getCharacterByID(11)->move(627, 'y', 30);
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
		getCharacterByID(11)->move(471, 'x', 30);
		break;
	case 5:
		getCharacterByID(9)->teleportNPC(483, 671); // Remove guard thats in the way
		getCharacterByID(11)->move(472, 'x', 30);
		break;
	case 6:
		getCharacterByID(11)->move(518, 'x', 10);
		break;
	case 7:
		getCharacterByID(11)->teleportNPC(307, 382); // Actual World Position
		getCharacterByID(11)->faceDirection('d');
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
		getCharacterByID(14)->move(627, 'y', 32);
		break;
	case 2:
		getCharacterByID(14)->waitForTime(2500);
		break;
	case 3:
		getCharacterByID(14)->move(518, 'x', 10);
		break;
	case 4:
		getCharacterByID(14)->teleportNPC(765, 254);
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
		getCharacterByID(13)->move(627, 'y', 32);
		break;
	case 3:
		getCharacterByID(13)->move(518, 'x', 10);
		break;
	case 4:
		getCharacterByID(13)->teleportNPC(633, 135);
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
		getCharacterByID(12)->move(623, 'y', 32);
		break;
	case 2:
		getCharacterByID(12)->move(screen_position_.x + screen_width_ / 2 - 9, 'x', 32);
		break;
	case 3:
		getCharacterByID(12)->move(626, 'y', 32);
		break;
	case 4:
		getCharacterByID(12)->move(518, 'x', 10);
		break;
	case 5:
		getCharacterByID(12)->teleportNPC(204, 516);
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
		getCharacterByID(15)->move(630, 'y', 32);
		break;
	case 2:
		getCharacterByID(15)->waitForTime(1000);
		break;
	case 3:
		getCharacterByID(15)->move(screen_position_.x + screen_width_ / 2 - 9, 'x', 32);
		break;
	case 4:
		getCharacterByID(15)->move(627, 'y', 32);
		break;
	case 5:
		getCharacterByID(15)->move(screen_position_.x + screen_width_ / 2 - 9 + 3, 'x', 10);
		break;
	case 6:
		getCharacterByID(15)->waitForTime(250);
		break;
	case 7:
		getCharacterByID(15)->move(479, 'x', 1);
		break;
	case 8:
		getCharacterByID(15)->move(518, 'x', 1);
		getCharacterByID(8)->faceDirection('r'); // face guard right
		break;
	case 9:
		getCharacterByID(7)->teleportNPC(493, 671);
		getCharacterByID(15)->teleportNPC(453, 671);
		start_time_begin_event_ = GetTickCount();
		event_index_++;
		break;
	default:
		break;
	}
}

void Event_BorderIncident::guardStopThem(int time_interval)
{
	double current_time_begin_event_ = GetTickCount() - start_time_begin_event_;
	if (current_time_begin_event_ > time_interval * 2)
	{
		event_index_++;
		start_time_begin_event_ = GetTickCount();
	}
	else if (current_time_begin_event_ > time_interval)
		popups_[18].displayPopup(20, -3);
	else if (current_time_begin_event_ <= time_interval)
	{
		popups_[17].displayPopup(20, -3);
	}
}

void Event_BorderIncident::guardExits()
{
	switch (getCharacterByID(8)->getMovementIndex())
	{
	case 0:
		getCharacterByID(8)->move(619, 'y', 20);
		//getCharacterByID(9)->move(512, 'x', 20);
		break;
	case 1:
		getCharacterByID(8)->move(512, 'x', 20);
		//getCharacterByID(9)->move(518, 'x', 20);
		break;
	case 2:
		getCharacterByID(8)->teleportNPC(473, 671);
		//getCharacterByID(9)->teleportNPC(483, 671);
		event_index_++;
		break;
	default:
		break;
	}
}

void Event_BorderIncident::playerThinks(int time_interval)
{
	double current_time_begin_event_ = GetTickCount() - start_time_begin_event_;
	if (current_time_begin_event_ > time_interval * 2)
	{
		event_index_++;
		start_time_begin_event_ = GetTickCount();
	}
	else if (current_time_begin_event_ <= time_interval * 2)
		popups_[19].displayPopup(0, -3);
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
