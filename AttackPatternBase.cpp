#include "AttackPatternBase.h"

AttackPatternBase::AttackPatternBase(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_attacks)
	: width_{ width }, height_{ height }, attack_matrix_(width, height), player_{ player }, attacks_to_create_{ number_of_attacks }, screen_matrix_{ screen_matrix }, border_was_destroyed_{ false },
	is_playing_animation_{ false }, start_time_hurt_animation_(0), animation_counter_(0)
{
	border_ = new Attack_Border(width, height, player_position_, attack_matrix_, element_is_occupied_);
	element_is_occupied_ = new bool*[height_];
	for (int i = 0; i < height_; ++i)
		element_is_occupied_[i] = new bool[width_];
	for (int i = 0; i < height_; ++i)
		for (int j = 0; j < width_; ++j)
			element_is_occupied_[i][j] = false;

	created_attacks_ = 0;
	slow_player_ = 0; // Lower is faster
	movePlayerToPosition(width_ / 2, height_ / 2, true);
	has_completed_initialization_ = false;
}

AttackPatternBase::~AttackPatternBase()
{
	for (int i = 0; i < height_; ++i)
		delete[] element_is_occupied_[i];
	delete[] element_is_occupied_;
}

// Calls once when the entire attack starts
void AttackPatternBase::OnBeginAttack()
{
	start_time_new_attack_ = GetTickCount64();
	start_time_slow_player_ = GetTickCount64();
	has_completed_initialization_ = true;
}

// Refreshes the Screen as well as Animations
void AttackPatternBase::refreshBackend()
{
	is_playing_animation_ ? playPlayerDeathAnimation() : refreshScreen();
}

// Runs when border should appear (Like on beginning of attack pattern)
void AttackPatternBase::createBorder()
{
	border_->onBeginAttack();
}

// Sets the players location
void AttackPatternBase::refreshPlayerLocation()
{
	for (int i = 0; i < height_; ++i)
	{
		for (int j = 0; j < width_; ++j)
		{
			if (i == player_position_.y && j == player_position_.x) // Player Position
			{
				attack_matrix_[i][j] = player_.getHealthText();
			}
			else if (!element_is_occupied_[i][j] && attack_matrix_[i][j] != ' ')
			{
				attack_matrix_[i][j] = ' ';
			}
		}
	}
}

// Takes input and decides whether to move player
void AttackPatternBase::evaluatePlayerInput()
{
	double current_time_move_player = GetTickCount64() - start_time_slow_player_;

	// Slow player if they are pressing SHIFT key
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		slow_player_ = 60;
	else
		slow_player_ = 10;
	if (current_time_move_player >= slow_player_)
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
			if (player_position_.x < width_ - 1)
				++player_position_.x;
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			if (player_position_.x > 0)
				--player_position_.x;
		}
		start_time_slow_player_ = GetTickCount64();
	}
}

// Hurts the player
void AttackPatternBase::hurtPlayer()
{
	if (player_.hasShield()) { player_.useShield(); }
	else { player_.subtractHealth(1); }

	if (player_.getHealth() <= 0) // Animation ONLY
	{
		is_playing_animation_ = true;
		animation_counter_ = 0;
		start_time_hurt_animation_ = GetTickCount64();
		playPlayerDeathAnimation();
		player_.setHealth(1); // Allows animation to finish
	}
	playPlayerHurtSound();
}

// Plays a sound
void AttackPatternBase::playPlayerHurtSound()
{
	Beep(600, 50);
	Beep(600, 500);
}

// Plays player death animation
void AttackPatternBase::playPlayerDeathAnimation()
{
	int current_time_hurt_animation = GetTickCount64() - start_time_hurt_animation_, speed = 2;
	bool completed_right = false, completed_left = false, completed_up = false, completed_down = false;
	if (current_time_hurt_animation > 10)
	{
		player_position_.x + animation_counter_ < width_ ? screen_matrix_[player_position_.y][player_position_.x + animation_counter_] = 'O' : completed_right = true;
		player_position_.x - animation_counter_ >= 0 ? screen_matrix_[player_position_.y][player_position_.x - animation_counter_] = 'O' : completed_left = true;
		player_position_.y - animation_counter_ >= 0 ? screen_matrix_[player_position_.y - animation_counter_][player_position_.x] = 'O' : completed_up = true;
		player_position_.y + animation_counter_ < height_ ? screen_matrix_[player_position_.y + animation_counter_][player_position_.x] = 'O' : completed_down = true;
		
		if (player_position_.x + animation_counter_ - speed < width_) { screen_matrix_[player_position_.y][player_position_.x + animation_counter_ - speed] = ' '; }
		if (player_position_.x - animation_counter_ + speed >= 0) { screen_matrix_[player_position_.y][player_position_.x - animation_counter_ + speed] = ' '; }
		if (player_position_.y - animation_counter_ + speed >= 0) { screen_matrix_[player_position_.y - animation_counter_ + speed][player_position_.x] = ' '; }
		if (player_position_.y + animation_counter_ - speed < height_) { screen_matrix_[player_position_.y + animation_counter_ - speed][player_position_.x] = ' '; }
		
		animation_counter_+=speed;
		start_time_hurt_animation_ = GetTickCount64();
	}
	if (completed_right && completed_left && completed_up && completed_down) { is_playing_animation_ = false; player_.setHealth(0); }
}

// Sets the player's position coordinates
void AttackPatternBase::movePlayerToPosition(int x_position, int y_position, bool should_round_position)
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

void AttackPatternBase::moveAttack()
{
	for (auto it = attacks_list_.begin(); it != attacks_list_.end(); )
	{
		(*it)->move();
		++it;
	}
}

void AttackPatternBase::checkBorderCollision()
{
	if (!border_was_destroyed_)
	{
		border_->detectCollision();
		if (border_->hasHitPlayer())
		{
			hurtPlayer();
			delete(border_);
			border_was_destroyed_ = true;
		}
	}
}

void AttackPatternBase::attacksCheckCollision()
{
	for (auto it = attacks_list_.begin(); it != attacks_list_.end(); )
	{
		if ((*it)->hasHitPlayer())
		{
			hurtPlayer();
			delete(*it);
			it = attacks_list_.erase(it);
		}
		else if ((*it)->hasAttackFinished())
		{
			delete(*it);
			it = attacks_list_.erase(it);
		}
		else
			++it;
	}
}

// displays matrix for fight on screen
void AttackPatternBase::displayScreen()
{
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			char temp = attack_matrix_[i][j];
			screen_matrix_[i][j] = temp;
			screen_matrix_[i][j].setColor(attack_matrix_[i][j].getRGBA());
		}
	}
	screen_matrix_[player_position_.y][player_position_.x].setColor(255, 255, 0);
}