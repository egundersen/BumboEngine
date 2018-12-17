#include "EventBase.h"
#include <Windows.h>

EventBase::EventBase(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, int character_ID, bool repeatable, std::vector<std::vector<std::pair<int, int>>>& element_has_object, Matrix &screen_matrix, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height)
	: unique_object_ID_{ unique_object_ID }, element_has_object_{ element_has_object }, center_position_x_{ center_position_x }, center_position_y_{ center_position_y }, collider_width_{ collider_width }, collider_height_{ collider_height }, characters_{ characters }, character_ID_{ character_ID }, screen_position_{ screen_position }, repeatable_{ repeatable },
	object_type_ID_(4), is_event_over_{ false }, screen_matrix_{ screen_matrix }, start_time_begin_event_(0), should_enter_battle_{ false }, screen_width_{ screen_width }, screen_height_{ screen_height }, event_index_(0)
{
	setAttachedCharacterIndex();
}

// Called when the event begins
void EventBase::onStartEvent()
{
	start_time_begin_event_ = GetTickCount64();
}

// Resets all attributes of the event and changes it's completion state
void EventBase::reset()
{
	is_event_over_ = false;
	updateColliderCoordinates();
}

// Teleports the player to a specified coordinate
void EventBase::teleportPlayer(int position_x, int position_y)
{
	screen_position_.x = position_x - screen_width_ / 2;
	screen_position_.y = position_y - screen_height_ / 2;
}

// Called when the event is created
void EventBase::createEvent()
{
	updateColliderCoordinates();
}

// Adds colliders to world so they can be seen
void EventBase::DEBUG_viewCollider(Matrix &world_matrix)
{
	drawSolidRectangle(center_position_x_ - collider_width_ / 2, center_position_y_ - collider_height_ / 2, collider_width_, collider_height_, 'C', world_matrix);
}

// Removes colliders from the world so they can't be seen
void EventBase::DEBUG_hideCollider(Matrix &world_matrix)
{
	drawSolidRectangle(center_position_x_ - collider_width_ / 2, center_position_y_ - collider_height_ / 2, collider_width_, collider_height_, ' ', world_matrix);
}

// Returns address to character with the provided ID
CharacterBase * EventBase::getCharacterByID(int character_ID)
{
	for (std::vector< CharacterBase* >::iterator it = characters_.begin(); it != characters_.end(); ++it)
	{
		if ((*it)->getUniqueObjectID() == character_ID)
		{
			return *it;
		}
	}
#ifdef _DEBUG
	throw std::invalid_argument("Invalid ID : No character exists with the given ID");
#endif
	return nullptr;
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

// Sets the attached character based on the provided character ID
void EventBase::setAttachedCharacterIndex()
{
	for (std::vector< CharacterBase* >::iterator it = characters_.begin(); it != characters_.end(); ++it)
	{
		if ((*it)->getUniqueObjectID() == character_ID_)
		{
			attached_character_ = *it;
			return;
		}
	}
}
