#ifndef PLAYERDEFINITION_H
#define PLAYERDEFINITION_H

#include <string>
#include <Lmcons.h>

class PlayerDefinition {
public:
	PlayerDefinition(int starting_health, int max_health)
		: health_{ starting_health }, damage_modifier_(1), shield_{ false },
		max_health_{ max_health }, health_text_(starting_health + '0') 
	{
		TCHAR username[UNLEN + 1];
		DWORD size = UNLEN + 1;
		GetUserName((TCHAR*)username, &size);
		std::wstring temp1 = username;
		std::string temp2(temp1.begin(), temp1.end());
		player_name_ = temp2;
	}

	// Setters
	void setHealth(int health) {
		health_ = health;
		setHealthText();
	}
	void addHealth(int health) {
		health_ = health_ + health > max_health_ ? max_health_ : health_ + health;
		setHealthText();
	}
	void subtractHealth(int damage) {
		health_ -= damage;
		setHealthText();
	}
	void enableShield() { shield_ = true; }
	void useShield() { shield_ = false; }
	void increaseDamage(int damage) { damage_modifier_ += damage; }
	void resetDamage() { damage_modifier_ = 1; }

	// Getters
	std::string getPlayerName() { return player_name_; }
	char getHealthText() { return health_text_; }
	int getHealth() { return health_; }
	int getDamage() { return damage_modifier_; }
	bool hasShield() { return shield_; }
	bool hasDied() { return health_ <= 0 ? true : false; }
private:
	void setHealthText() { health_text_ = health_ + '0'; }

	int health_, damage_modifier_, max_health_;
	char health_text_;
	bool shield_;
	std::string player_name_;
};

#endif // !PLAYERDEFINITION_H
