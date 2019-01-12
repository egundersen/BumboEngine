#ifndef AUDIODEFINITION_H
#define AUDIODEFINITION_H

#include <string>

class AudioDefinition {
public:
	AudioDefinition() 
		: file_path_{ "" }, is_playing_{ false }, should_stop_{ false }, duration_(0) {}
	AudioDefinition(std::string file_path) 
		: file_path_{ file_path }, is_playing_{ false }, should_stop_{ false }, duration_(0) {}

	// Setters
	void play() { is_playing_ = true; }
	void stop() { should_stop_ = true; }
	void setDuration(int duration) { duration_ = duration; }
	void setFilePath(std::string file_path) { file_path_ = file_path; }
	void forceStop() { is_playing_ = false; should_stop_ = false; } // <- main.cpp ONLY. DO NOT USE

	// Getters
	std::string getFilePath() { return file_path_; }
	int getDuration() { return duration_; }
	bool isPlaying() { return is_playing_; }
	bool shouldStop() { return should_stop_; }
private:
	std::string file_path_;
	bool is_playing_, should_stop_;
	int duration_;
};

#endif // !AUDIODEFINITION_H
