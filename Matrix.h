#include "RGBA.h"
#include <tuple>
#include <vector>
#include <string>

#ifndef MATRIX_H
#define MATRIX_H

// Creates an m x n matrix of characters. Includes Color in RGBA
class Matrix
{
public:
	Matrix() {}
	Matrix(int width, int height) : width_{ width }, height_{ height },
		matrix_(height, std::vector<std::tuple<char, RGBA>>(width, std::make_tuple(' ', RGBA()))) {}

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
			unsigned int getColor();
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
				throw std::invalid_argument("Index must not be greater than width");
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
			throw std::invalid_argument("Index must not be greater than height");
#endif
			index = 0;
		}
		return Proxy(matrix_[index]);
	}

	int getHeight() { return height_; }
	int getWidth() { return width_; }

private:
	int width_, height_;
	std::vector<std::vector<std::tuple<char, RGBA>>> matrix_;
};

#endif // !MATRIX_H