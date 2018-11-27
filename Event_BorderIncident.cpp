#include "Event_BorderIncident.h"

void Event_BorderIncident::createEvent()
{
	updateColliderCoordinates();
}

void Event_BorderIncident::refreshEvent()
{
	onEventOver();
}
