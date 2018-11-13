#include "Image.h";

#ifndef ITEM_H
#define ITEM_H

class Item
{
public:
	Item() {}
	Item(std::string item_name, std::string description = "") : item_name_{ item_name }, description_{ description }, image_{ "/  \\Z|O |Z\\_ /Z" }{}
	Item(std::string item_name, Image image, std::string description = "") : item_name_{ item_name }, description_{ description }, image_{ image }{}

	// Setters
	void useItem() { use_item_ = true; }

	// Getters
	bool shouldUseItem() { return use_item_; }
	Image getImage() { return image_; }
	std::string getName() { return item_name_; }
	std::string getDescription() { return description_; }
private:
	bool use_item_;
	std::string item_name_, description_;
	Image image_;
};

#endif // !ITEM_H
