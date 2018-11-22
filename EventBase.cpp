#include "EventBase.h"
#include <Windows.h>

EventBase::EventBase(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, std::vector<std::vector<std::pair<int, int>>>& element_has_object, std::vector<std::vector<std::string>> &matrix_display, std::vector<CharacterBase*> &characters, CharacterBase *attached_character)
	: unique_object_ID_{ unique_object_ID }, element_has_object_{ element_has_object }, center_position_x_{ center_position_x }, center_position_y_{ center_position_y }, collider_width_{ collider_width }, collider_height_{ collider_height }, characters_{ characters }, attached_character_{ attached_character },
	object_type_ID_(4), is_event_over_{ false }, matrix_display_{ matrix_display }, start_time_begin_event_(0), should_enter_battle_{ false }
{
}

void EventBase::onStartEvent()
{
	start_time_begin_event_ = GetTickCount();
}

void EventBase::createEvent()
{
	updateColliderCoordinates();
}

// Adds colliders to world so they can be seen
void EventBase::DEBUG_viewCollider(std::vector<std::vector<char>> &world_matrix)
{
	drawSolidRectangle(center_position_x_ - collider_width_ / 2, center_position_y_ - collider_height_ / 2, collider_width_, collider_height_, 'C', world_matrix);
}

// Removes colliders from the world so they can't be seen
void EventBase::DEBUG_hideCollider(std::vector<std::vector<char>> &world_matrix)
{
	drawSolidRectangle(center_position_x_ - collider_width_ / 2, center_position_y_ - collider_height_ / 2, collider_width_, collider_height_, ' ', world_matrix);
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

// Called when the event ends
void EventBase::onEventOver()
{
	for (int i = 0; i < collider_height_; ++i)
		for (int j = 0; j < collider_width_; ++j)
		{
			element_has_object_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2 + j].first = 0;
			element_has_object_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2 + j].second = 0;
		}
	is_event_over_ = true;
}
