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
	void loadVectorSpace(std::string vector_space_name);

	bool has_initialized_inventory_, has_initialized_battle_;
	int width_, height_;
	PlayerDefinition player_; // the real player health
	Matrix &screen_matrix_;
	std::string current_vector_space_;
	Inventory inventory_;
	Credits credits_;
	WorldBase world_;
	BitmapDefinition &image_file_path_;
};

#endif // !MatrixManager_H
