#include "Event_TeleportPlayer.h"

void Event_TeleportPlayer::createEvent()
{
	updateColliderCoordinates();
}

void Event_TeleportPlayer::refreshEvent()
{
	teleportPlayer(212, 61);
	onEventOver();
}
