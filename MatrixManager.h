#include "MatrixBase.h"
#include "Image.h"
#include "Inventory.h"
#include "StartScreen.h"
#include "AttackPatterns.h"

#ifndef MatrixManager_H
#define MatrixManager_H

class MatrixManager : public MatrixBase
{
public:
	MatrixManager(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int player_health);

	// Setters
	void evaluatePlayerInput();
	void loadVectorSpace(std::string vector_space_name);
	void onShutdown();

	// Getters
	std::string getCurrentVectorSpace() { return current_vector_space_; };
private:
	void hideTypingCursor();
	void indentLines(int number_of_indents);

	int width_ = 0;
	int height_ = 0;
	std::vector<std::vector<std::string>> &matrix_display_;
	std::vector<char> empty_vector_;
	std::vector<std::vector<char>> matrix_;
	std::string current_vector_space_;
	Inventory inventory_;
	AttackPattern_ShootHorizontal debugAttack_;
	int player_health_;
};

#endif // !MatrixManager_H
