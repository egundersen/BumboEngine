#ifndef EVENTBASE_H
#define EVENTBASE_H

#include "CharacterBase.h"
#include "ScreenPosition.h"
#include "Popup.h"

// Basic functionality for all events. Manages, starts, resets events
class EventBase : public MatrixBase
{
public:
	explicit EventBase(int unique_object_ID, int center_position_x, int center_position_y, int collider_width, int collider_height, int character_ID, bool repeatable,
		std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, std::vector<CharacterBase*> &characters, ScreenPosition &screen_position, int screen_width, int screen_height);
	~EventBase() {}

	// Setters
	void onStartEvent();
	void reset();
	virtual void createEvent();
	virtual void refreshEvent() {}
	void progressPopup();
	void DEBUG_viewCollider(Matrix &world_matrix);
	void DEBUG_hideCollider(Matrix &world_matrix);

	// Getters
	virtual bool isAvailable() { return true; }
	bool isComplete() { return is_event_over_; }
	bool isRepeatable() { return repeatable_; }
	bool shouldEnterBattle() { return should_enter_battle_; }
	int getUniqueObjectID() { return unique_object_ID_; }
	CharacterBase *getCharacterByID(int character_ID);
	CharacterBase *getAttachedCharacter() { return attached_character_; }
protected:
	// Setters
	virtual void updateColliderCoordinates();
	void removeColliders();
	void onEventOver();
	void progressEvent(int id = 0);
	void setAttachedCharacterIndex();
	void teleportPlayer(int position_x, int position_y);

	int getPopupIndex() { return popup_index_; }
	int getEventIndex() { return event_index_; }

	bool is_event_over_, should_enter_battle_, repeatable_;
	int object_type_ID_, unique_object_ID_, center_position_x_, center_position_y_, collider_width_, collider_height_,
		start_time_begin_event_, character_ID_, screen_width_, screen_height_;
	std::vector<std::vector<std::pair<int, int>>> &element_has_object_;
	Matrix &screen_matrix_;
	std::vector<CharacterBase*> &characters_;
	CharacterBase *attached_character_;
	ScreenPosition &screen_position_;
	std::vector<Popup> popups_;
private:
	int event_index_, popup_index_;
};

#endif // !EVENTBASE_H
