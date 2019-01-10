#ifndef DIALOGNODE
#define DIALOGNODE

#include "Item.h"

class DialogNode
{
public:
	DialogNode() : player_dialog_{ "" }, response_{ "" }, action_{ "" } {}
	DialogNode(std::string player_dialog, std::string response, std::string action = "")
		: player_dialog_{ player_dialog }, response_{ response }, action_{ action }
	{
	}
	DialogNode(std::string player_dialog, std::string response, Item item)
		: player_dialog_{ player_dialog }, response_{ response }, action_{ "ITEM" }, item_{ item }
	{
	}

	// Setters
	void setChoice1(DialogNode *choice) { choice_1_ = choice; }
	void setChoice2(DialogNode *choice) { choice_2_ = choice; }
	void setChoice3(DialogNode *choice) { choice_3_ = choice; }

	// Getters
	std::string getPlayerDialog() { return player_dialog_; }
	std::string getResponse() { return response_; }
	std::string getAction() { return action_; }
	Item getItem() { return item_; }

	DialogNode *choice_1_;
	DialogNode *choice_2_;
	DialogNode *choice_3_;
private:
	std::string player_dialog_, response_, action_;
	Item item_;
};

#endif // !DIALOGNODE
