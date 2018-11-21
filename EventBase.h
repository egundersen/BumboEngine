#include "MatrixBase.h"

#ifndef EVENTBASE_H
#define EVENTBASE_H

class EventBase: public MatrixBase
{
public:
	explicit EventBase(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, 
		std::vector<std::vector<std::pair<int, int>>> &element_has_object);
	~EventBase() {}

	// Setters
	void createEvent();
	virtual void refreshEvent() {}

	// Getters
	bool isComplete() { return is_event_over_; }
	int getUniqueObjectID() { return unique_object_ID_; }
protected:
	// Setters
	virtual void updateColliderCoordinates();
	void onEventOver();

	bool is_event_over_;
	int object_type_ID_, unique_object_ID_, center_position_x_, center_position_y_, collider_width_, collider_height_;
	std::vector<std::vector<std::pair<int, int>>> &element_has_object_;
};

#endif // !EVENTBASE_H
