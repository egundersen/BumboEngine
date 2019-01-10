#ifndef MatrixManager_H
#define MatrixManager_H

#include "WorldBase.h"
#include "Inventory.h"
#include "StartScreen.h"
#include "Credits.h"

class MatrixManager : public MatrixBase
{
public:
	MatrixManager(int width, int height, Matrix &screen_matrix, int player_health, BitmapDefinition &image_file_path);

	// Setters
	void evaluatePlayerInput();

	// Getters
	std::string getCurrentVectorSpace() { return current_vector_space_; };
private:
	// Setters
	void loadVectorSpace(std::string vector_space_name);
	void hideTypingCursor();
	void indentLines(int number_of_indents);
	bool has_initialized_inventory_, has_initialized_battle_;

	PlayerDefinition player_; // the real player health
	int width_, height_;
	Matrix &screen_matrix_;
	std::string current_vector_space_;
	Inventory inventory_;
	Credits credits_;
	WorldBase world_;
};

#endif // !MatrixManager_H
