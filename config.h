#include <vector>
#include <string>
#include <iostream>

// Global Variables for width, height and the output display screen 
// I debated using references... but decided to rewrite code using these 3 variables to make it easier to read

const int width_G = 79; // DANGEROUS! DO NOT USE THIS VARIABLE
const int height_G = 34; // DANGEROUS! DO NOT USE THIS VARIABLE
std::vector<std::vector<std::string>> matrix_display_G(height_G, std::vector<std::string>(width_G, " ")); // DANGEROUS! DO NOT USE THIS VARIABLE

// Prints input matrix on the GUI
/*void displayScreen(std::vector<std::vector<char>> &matrix_) {
	/*for (int i = 0; i < height_G; i++) {
		for (int j = 0; j < width_G; j++) {
			matrix_display_G[i][j] = std::string(1, matrix_[i][j]);
		}
	}
}//*/