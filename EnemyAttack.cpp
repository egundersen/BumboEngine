#include "MatrixBase.h"
#include "EnemyAttack.h"
#include "Image.h"
#include <windows.h>
#include <thread>
#include <chrono>
#include <future>
#include <iostream>
#include <algorithm>

EnemyAttack::EnemyAttack(int width, int height, int player_health, std::string attack_name, int number_of_minor_attacks) : width_{ width }, height_{ height }, matrix_(height, std::vector<char>(width, ' ')), empty_vector_(width, ' '), player_health_{ player_health }, attack_name_{ attack_name }, number_of_minor_attacks_{ number_of_minor_attacks }
{
	element_is_occupied_ = new std::string*[height_];
	for (int i = 0; i < height_; ++i)
		element_is_occupied_[i] = new std::string[width_];
	for (int i = 0; i < height_; ++i)
		for (int j = 0; j < width_; ++j)
			element_is_occupied_[i][j] = "false";
	should_use_minor_attack = new bool[number_of_minor_attacks];
	for (int i = 0; i < number_of_minor_attacks; ++i)
		should_use_minor_attack[i] = true;
	movePlayerPosition(width_ / 2, height_ / 2, true);
	should_use_attack = true;
	is_attack_pattern_in_progress = true;
	call_once_threads = true;
}

// A cool attack pattern that shoots a line towards the player every 3-7 seconds
void EnemyAttack::shootHorizontalAttack(int time_in_seconds_between_attacks)
{
	double totalTime;
	while (should_use_attack) // Void Start
	{
		should_use_attack = false;
		totalTime = GetTickCount();
		number_of_remaining_attacks = number_of_minor_attacks_;
		attack_start_time = GetTickCount();
		//shootHorizontalAttack_Minor(GetTickCount(), 50, 60, 0, width_, 25, 1, "");
		//std::thread minor_attack1(&EnemyAttack::shootHorizontalAttack_Minor, this, GetTickCount(), 50, 60, 0, width_, 25, 1, "horizontal attack 1");
		//std::thread minor_attack2(&EnemyAttack::shootHorizontalAttack_Minor, this, GetTickCount(), 50, 60, 0, width_, 15, 2, "horizontal attack 2");
		//minor_attack1.join();
		//minor_attack2.join();
	}

	while (is_attack_pattern_in_progress)
	{
		double currentTime = GetTickCount() - attack_start_time;

		if (currentTime >= 2000) // 1000 = 1 second
		{
			minor_attacks.push_back(std::thread(&EnemyAttack::shootHorizontalAttack_Minor, this, GetTickCount(), 50, 60, 0, width_, rand() % (height_ - 1 - 0 + 1) + 0, 2, "horizontal attack 3"));
			number_of_remaining_attacks--;
			attack_start_time = GetTickCount(); // reset time
		}
		if (GetTickCount() - totalTime >= 25000)
		{
			for (auto& minor_attack : minor_attacks)
				minor_attack.join();
			// ATTACK COMPLETED
			std::cout << "ATTACK COMPLETED@!\n";
			is_attack_pattern_in_progress = false;
		}
	}
	std::cout << "ATTACK_OVER: " << totalTime;
}

void EnemyAttack::shootHorizontalAttack_Minor(int minor_attack_start_time, int speed, int trail_length, int min, int max, int height, int attack_index, std::string minor_attack_name)
{
	if (max > width_)
		throw std::invalid_argument("max position must not be greater than the screen width_");

	int original_start_time = minor_attack_start_time;
	remaining_attacks_.push_back(minor_attack_name);

	while (should_use_minor_attack[attack_index])
	{
		double currentTime = GetTickCount() - minor_attack_start_time;
		double totalTime = GetTickCount() - original_start_time;

		if (min - trail_length >= max)
		{
			should_use_minor_attack[attack_index] = false;
		}
		else if (currentTime >= speed)
		{
			if (min < max)
			{
				matrix_[height][min] = '>';
				element_is_occupied_[height][min] = minor_attack_name;
			}
			if (min - trail_length >= 0)
			{
				matrix_[height][min - trail_length] = ' ';
				element_is_occupied_[height][min - trail_length] = "false";
			}
			if (min - trail_length * 3 / 4 >= 0 && min - trail_length * 3 / 4 < max)
			{
				if ((min - trail_length * 3 / 4) % 2 == 0)
					matrix_[height][min - trail_length * 3 / 4] = '-';
				else
					matrix_[height][min - trail_length * 3 / 4] = ' ';
			}
			if (min - trail_length / 2 >= 0 && min - trail_length / 2 < max)
			{
				matrix_[height][min - trail_length / 2] = '-';
			}
			if (min - 1 >= 0 && min - 1 < max)
			{
				matrix_[height][min - 1] = '=';
			}
			minor_attack_start_time = GetTickCount(); // reset time
			min++;
		}
	}
}

// decides which attack to use based on the initialization of the EnemyAttack class
void EnemyAttack::useAttack()
{
	if (attack_name_ == "Shoot Horizontal Attack")
		shootHorizontalAttack(10);
	else
		throw std::invalid_argument("Invalid attack! Make sure that attack was spelled right. Ex: Shoot Horizontal Attack");
}

// Refreshes screen to show player/enemy positions
void EnemyAttack::refreshScreen()
{
	if (call_once_threads == true)
	{
		std::thread evaluate_player_input(&EnemyAttack::evaluatePlayerInput, this);
		useAttack();
		//std::thread use_attack(&EnemyAttack::useAttack, this);
		//use_attack.join();
		evaluate_player_input.join();
		call_once_threads = false;
	}
}

void EnemyAttack::OnBeginAttack()
{
	refreshScreen();
}

void EnemyAttack::setPlayerLocation()
{
	for (int i = 0; i < height_; ++i)
	{
		for (int j = 0; j < width_; ++j)
		{
			if (i == player_position_.y && j == player_position_.x) // Player Position
			{
				if (element_is_occupied_[i][j] != "false") // Detect Collision with player
				{
					// Check if the attack name is in the remaining attacks vector
					if (std::find(remaining_attacks_.begin(), remaining_attacks_.end(), element_is_occupied_[i][j]) != remaining_attacks_.end())
					{
						displayCollision(j, i);
						hurtPlayer();
						remaining_attacks_.erase(std::remove(remaining_attacks_.begin(), remaining_attacks_.end(), element_is_occupied_[i][j]), remaining_attacks_.end());
					}
				}
				matrix_[i][j] = 'O';
			}
			else if (element_is_occupied_[i][j] == "false" && matrix_[i][j] != ' ')
			{
				matrix_[i][j] = ' ';
			}
		}
	}
	displayScreen();
}

// Sets the player's position coordinates
void EnemyAttack::movePlayerPosition(int x_position, int y_position, bool should_round_position)
{
	if (should_round_position)
	{
		player_position_.x = round(x_position);
		player_position_.y = round(y_position);
	}
	else
	{
		player_position_.x = x_position;
		player_position_.y = y_position;
	}
}

void EnemyAttack::evaluatePlayerInput()
{
	double start_time = GetTickCount();

	while (is_attack_pattern_in_progress)
	{
		double currentTime = GetTickCount() - start_time;

		if (currentTime >= 50) // 1000 = 1 second
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				if (player_position_.y > 0)
					--player_position_.y;
			}
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				if (player_position_.y < height_ - 1)
					++player_position_.y;
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				//std::cout << "PRESSED RIGHT";
				if (player_position_.x < width_ - 1)
					++player_position_.x;
			}
			else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				//std::cout << "PRESSED LEFT";
				if (player_position_.x > 0)
					--player_position_.x;
			}
			setPlayerLocation();
			start_time = GetTickCount(); // reset time
		}
	}
}

void EnemyAttack::hurtPlayer()
{
	player_health_--;
	playPlayerHurtSound();
}

void EnemyAttack::playPlayerHurtSound()
{
	Beep(600, 50);
	Beep(600, 500);
}

// displays matrix for fight on screen
void EnemyAttack::displayScreen()
{
	int newLineCounter = 0;
	for (auto line : matrix_)
	{
		if (line == empty_vector_)
		{
			newLineCounter++;
		}
		else
		{
			if (newLineCounter != 0)
			{
				std::cout << std::string(newLineCounter, '\n');
				newLineCounter = 0;
			}
			for (auto x : line)
				std::cout << x;
		}
	}
	std::cout << std::string(newLineCounter, '\n');
}

void EnemyAttack::displayCollision(int x_position, int y_position)
{
	for (int i = 0; i < height_; ++i)
	{
		for (int j = 0; j < width_; ++j)
		{
			if (i == y_position && j == x_position)
				std::cout << 'O';
			else if (matrix_[i][j] == 'O')
				std::cout << ' ';
			else
				std::cout << matrix_[i][j];
		}
	}
}

// Displays the matrix on the screen. [FOR DEBUG ONLY!]
void EnemyAttack::DEBUG_displayMatrix(std::vector<std::vector<char>> matrix)
{
	for (auto line : matrix)
	{
		for (auto x : line)
			std::cout << x;
		std::cout << "\n";
	}
}

// Displays the image on the screen. [FOR DEBUG ONLY!]
void EnemyAttack::DEBUG_displayImage(int center_x, int center_y, std::string image_in_ASCII)
{
	Image image(image_in_ASCII);
	//addImageToMatrix(center_x, center_y, image, matrix_, element_is_occupied_);
	//DEBUG_displayMatrix(image.image_matrix);
	// display image over grid vector
	displayScreen();
}
