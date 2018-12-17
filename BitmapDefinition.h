#include "RGBA.h"
#include <string>

#ifndef BITMAPDEFINITION_H
#define BITMAPDEFINITION_H

class BitmapDefinition
{
public:
	BitmapDefinition()
		: file_path_{ "" }, x_offset_{ 160 }, y_offset_{ 0 }, rgba_(), 
		should_show_bitmap_{ false } {}
	BitmapDefinition(std::string file_path, int x_offset, int y_offset)
		: file_path_{ file_path }, x_offset_{ x_offset }, y_offset_{ y_offset }, rgba_(),
		should_show_bitmap_{ false } {}
	BitmapDefinition(std::string file_path, int x_offset, int y_offset, RGBA rgba)
		: file_path_{ file_path }, x_offset_{ x_offset }, y_offset_{ y_offset }, rgba_{ rgba },
		should_show_bitmap_{ false } {}

	// Setters
	void setXOffset(int x_offset) { x_offset_ = x_offset; }
	void setYOffset(int y_offset) { y_offset_ = y_offset; }
	void showBitmap() { should_show_bitmap_ = true; }
	void hideBitmap() { should_show_bitmap_ = false; }
	void setFilePath(std::string file_path) { file_path_ = file_path; }
	void setRGBA(RGBA rgba) { rgba_ = rgba; }
		
	// Getters
	int getXOffset() { return x_offset_; }
	int getYOffset() { return y_offset_; }
	bool shouldShowBitmap() { return should_show_bitmap_; }
	std::string getFilePath() { return file_path_; }
	RGBA &getRGBA() { return rgba_; }
private:
	int x_offset_, y_offset_;
	bool should_show_bitmap_;
	std::string file_path_;
	RGBA rgba_;
};

#endif // !BITMAPDEFINITION_H
