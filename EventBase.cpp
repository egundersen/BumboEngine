#include "EventBase.h"

EventBase::EventBase(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, std::vector<std::vector<std::pair<int, int>>>& element_has_object)
	: unique_object_ID_{ unique_object_ID }, element_has_object_{ element_has_object }, center_position_x_{ center_position_x }, center_position_y_{ center_position_y }, collider_width_{ collider_width }, collider_height_{ collider_height },
	object_type_ID_(4), is_event_over_{ false }
{
}

void EventBase::createEvent()
{
	updateColliderCoordinates();
}

void EventBase::refreshEvent()
{
#ifdef _DEBUG
	//throw std::invalid_argument("EventBase cannot be called directly. Instead, call a subclass that inherits from EventBase. EX: Event_Tutorial");
#endif
	// display popup
	// wait 5 seconds
	// display another popup
	// make someone move somewhere
	// end event

	// WORLD:_______________________________________
	// constantly checks if player touches events
	// CallEvent
	// EventFinished->DestroyEvent
	
	// add above code to subclass
	// uncomment THROW and delete these comments
	// start event from character class (at end of battle)

}

void EventBase::updateColliderCoordinates()
{
	for (int i = 0; i < collider_height_; ++i)
		for (int j = 0; j < collider_width_; ++j)
		{
			element_has_object_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2 + j].first = object_type_ID_;
			element_has_object_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2 + j].second = unique_object_ID_;
		}
}
