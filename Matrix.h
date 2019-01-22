#ifndef MATRIX_H
#define MATRIX_H

#include "RGBA.h"
#include <tuple>
#include <vector>
#include <string>

#ifdef _DEBUG
#include <iostream>
#endif

// Creates an m x n matrix of characters. Includes Color in RGBA
class Matrix
{
public:
	Matrix() {}
	Matrix(int width, int height) : width_{ width }, height_{ height },
		matrix_(height, std::vector<std::tuple<char, RGBA>>(width, std::make_tuple(' ', RGBA()))) {}
	Matrix(int width, int height, char default_fill_character) : width_{ width }, height_{ height },
		matrix_(height, std::vector<std::tuple<char, RGBA>>(width, std::make_tuple(default_fill_character, RGBA()))) {}

	class Proxy
	{
	public:
		Proxy(std::vector<std::tuple<char, RGBA>> &vector) : vector_(vector), index_{ 0 }{}

		class Deref
		{
		public:
			Deref(std::vector<std::tuple<char, RGBA>> &a, int index) : a(a), index_(index) {}

			operator char()
			{
				return std::get<0>(a[index_]);
			}
			char& operator=(const char& other)
			{
				return std::get<0>(a[index_]) = other;
			}

			void setColor(char red, char green, char blue);
			void setColor(RGBA rgba);
			bool fadeColor(int fade_delay, int multiplier);

			unsigned int getColor();
			RGBA getRGBA() { return std::get<1>(a[index_]); }
		private:
			std::vector<std::tuple<char, RGBA>>& a;
			int index_;
		};

		char operator[](int index) const
		{
			return std::get<0>(vector_[index]);
		}
		Deref operator[](int index)
		{
			if (index > vector_.size() - 1)
			{
#ifdef _DEBUG
				std::cout << "Width out of bounds!\n";

#endif
				index = 0;
			}
			return Deref(vector_, index);
		}

	private:
		int index_;
		std::vector<std::tuple<char, RGBA>> &vector_;
	};

	Proxy operator[](int index)
	{
		if (index > height_)
		{
#ifdef _DEBUG
			std::cout << "Height out of bounds!\n";
#endif
			index = 0;
		}
		return Proxy(matrix_[index]);
	}

	std::vector<std::tuple<char, RGBA>> &begin();
	std::vector<std::tuple<char, RGBA>> &end();

	int getHeight() { return height_; }
	int getWidth() { return width_; }

private:
	int width_, height_;
	std::vector<std::vector<std::tuple<char, RGBA>>> matrix_;
};

#endif // !MATRIX_H