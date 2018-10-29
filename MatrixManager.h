#include "MatrixBase.h"
#include "Image.h"
#include "Inventory.h"
#include "StartScreen.h"
#include "EnemyAttack.h"

#ifndef MatrixManager_H
#define MatrixManager_H

class MatrixManager : public MatrixBase
{
public:
	MatrixManager() : width_{ 0 }, height_{ 0 }, matrix_(0, std::vector<char>(0, ' ')), empty_vector_(0, ' ') {};
	MatrixManager(int width, int height, int player_health);

	// Setters
	void evaluatePlayerInput();
	void loadVectorSpace(std::string vector_space_name);
	void onShutdown();

	// Getters
	std::string getCurrentVectorSpace() { return current_vector_space_; };
private:
	void optimizeConsoleWindow();
	void hideTypingCursor();
	void indentLines(int number_of_indents);

	int width_ = 0;
	int height_ = 0;
	std::vector<char> empty_vector_;
	std::vector<std::vector<char>> matrix_;
	std::string current_vector_space_;
	Inventory inventory_;
	EnemyAttack debugAttack_;
	int player_health_;
};

#endif // !MatrixManager_H
