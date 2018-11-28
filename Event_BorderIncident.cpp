#include "Event_BorderIncident.h"
#include <Windows.h>

void Event_BorderIncident::createEvent()
{
	updateColliderCoordinates();
}

void Event_BorderIncident::refreshEvent()
{
	switch (event_index_)
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
		// guchi gang runs through checkpoint
		runsThroughCheckpoint();
		break;
	case 5:
		// guards yells after them
		guardStopThem();
		break;
	case 6:
		// guards follow them & person in line walks next to you
		guardExits();
		break;
	case 7:
		// person says you dropped something, you check item, you realize they stole your item
		playerDroppedSomething();
	case 8:
		onEventOver();
		break;
	default:
		break;
	}
}

void Event_BorderIncident::guardTalks()
{
	event_index_++;
}

void Event_BorderIncident::crowdLooksAround()
{
	double current_time_begin_event_ = GetTickCount() - start_time_begin_event_;
	if (current_time_begin_event_ > 600)
	{
		event_index_++;
	}
	else if (current_time_begin_event_ > 500)
	{
		crowdLook2();
	}
	else if (current_time_begin_event_ > 400)
	{
		crowdLook1();
	}
	else if (current_time_begin_event_ > 300)
	{
		crowdLook2();
	}
	else if (current_time_begin_event_ > 200)
	{
		crowdLook1();
	}
	else if (current_time_begin_event_ > 100)
	{
		crowdLook2();
	}
	else if (current_time_begin_event_ <= 100)
	{
		crowdLook1();
	}
}

void Event_BorderIncident::guardReplies()
{
	event_index_++;
}

void Event_BorderIncident::runsThroughCheckpoint()
{
}

void Event_BorderIncident::guardStopThem()
{
	event_index_++;
}

void Event_BorderIncident::guardExits()
{
}

void Event_BorderIncident::playerDroppedSomething()
{
	event_index_++;
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
