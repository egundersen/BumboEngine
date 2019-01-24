#ifndef BITMAPDEFINITION_H
#define BITMAPDEFINITION_H

#include "RGBA.h"
#include <string>

// Container for bitmap image. Chooses what to show, hide and manage loaded image from resources.
class BitmapDefinition
{
public:
	BitmapDefinition()
		: resource_ID_{ 0 }, x_offset_{ 160 }, y_offset_{ 0 }, rgba_(), 
		should_show_bitmap_{ false }, uses_original_colors_{ false } {}
	BitmapDefinition(int resource_ID, int x_offset, int y_offset)
		: resource_ID_{ resource_ID }, x_offset_{ x_offset }, y_offset_{ y_offset }, rgba_(),
		should_show_bitmap_{ false }, uses_original_colors_{ false } {}
	BitmapDefinition(int resource_ID, int x_offset, int y_offset, RGBA rgba)
		: resource_ID_{ resource_ID }, x_offset_{ x_offset }, y_offset_{ y_offset }, rgba_{ rgba },
		should_show_bitmap_{ false }, uses_original_colors_{ false } {}

	// Setters
	void setXOffset(int x_offset) { x_offset_ = x_offset; }
	void setYOffset(int y_offset) { y_offset_ = y_offset; }
	void showBitmap() { should_show_bitmap_ = true; }
	void hideBitmap() { should_show_bitmap_ = false; }
	void setResourceID(int resource_ID) { resource_ID_ = resource_ID; }
	void setRGBA(RGBA rgba) { rgba_ = rgba; }
	void useOriginalColors() { uses_original_colors_ = true; }
		
	// Getters
	int getXOffset() { return x_offset_; }
	int getYOffset() { return y_offset_; }
	bool shouldShowBitmap() { return should_show_bitmap_; }
	bool usesOriginalColors() { return uses_original_colors_; }
	int getResourceID() { return resource_ID_; }
	RGBA &getRGBA() { return rgba_; }
private:
	int x_offset_, y_offset_;
	bool should_show_bitmap_, uses_original_colors_;
	int resource_ID_;
	RGBA rgba_;
};

#endif // !BITMAPDEFINITION_H
