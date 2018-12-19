#include "Image.h";

#ifndef ITEM_H
#define ITEM_H

class Item
{
public:
	Item() : item_name_{ "" }, description_{ "" }, image_{ "" }, modifier_{ 0 }, item_type_{ "HEAL" }, use_item_{ false } {}
	Item(std::string item_name, int modifier, std::string description = "") : item_name_{ item_name }, description_{ description }, image_{ "/  \\Z|O |Z\\_ /Z", "/  \\Z|O |Z\\_ /Z" }, modifier_{ modifier }, item_type_{ "HEAL" }, use_item_{ false } {}
	Item(std::string item_name, int modifier, Image image, std::string description = "") : item_name_{ item_name }, description_{ description }, image_{ image }, modifier_{ modifier }, item_type_{ "HEAL" }, use_item_{ false } {}
	
	// This constructor is for any item that DOESN'T increase health
	Item(std::string item_name, std::string item_type, int modifier, Image image, std::string description = "") : item_name_{ item_name }, description_{ description }, image_ { image }, modifier_{ modifier }, item_type_{ item_type }, use_item_{ false } {}
	Item(std::string item_name, std::string item_type, int modifier, std::string description = "") : item_name_{ item_name }, description_{ description }, image_{ "/  \\Z|O |Z\\_ /Z", "/  \\Z|O |Z\\_ /Z" }, modifier_{ modifier }, item_type_{ item_type }, use_item_{ false } {}

	// Setters
	void useItem() { use_item_ = true; }

	// Getters
	int getModifier() { return modifier_; }
	bool shouldUseItem() { return use_item_; }
	Image getImage() { return image_; }
	std::string getName() { return item_name_; }
	std::string getType() { return item_type_; }
	std::string getDescription() { return description_; }
private:
	bool use_item_;
	int modifier_;
	std::string item_name_, description_, item_type_;
	Image image_;
};

#endif // !ITEM_H
