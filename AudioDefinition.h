#ifndef AUDIODEFINITION_H
#define AUDIODEFINITION_H

#include <string>

class AudioDefinition {
public:
	AudioDefinition() 
		: file_path_{ "" }, is_playing_{ false }, duration_(0) {}
	AudioDefinition(std::string file_path) 
		: file_path_{ file_path }, is_playing_{ false }, duration_(0) {}

	// Setters
	void play() { is_playing_ = true; }
	void stop() { is_playing_ = false; }
	void setDuration(int duration) { duration_ = duration; }

	// Getters
	std::string getFilePath() { return file_path_; }
	int getDuration() { return duration_; }
	bool isPlaying() { return is_playing_; }
private:
	std::string file_path_;
	bool is_playing_;
	int duration_;
};

#endif // !AUDIODEFINITION_H
