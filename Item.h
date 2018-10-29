#include "Image.h";

#ifndef ITEM_H
#define ITEM_H

class Item
{
public:
	Item() {}
	Item(std::string item_name) : item_name_{ item_name } {}

	// Setters
	void useItem() { use_item_ = true; }

	// Getters
	bool shouldUseItem() { return use_item_; }
	std::string getName() { return item_name_; }
	std::string getDescription() { return description_; }
private:
	bool use_item_;
	std::string item_name_;
	std::string description_ = "No description";
};

#endif // !ITEM_H
