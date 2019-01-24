#ifndef AUDIODEFINITION_H
#define AUDIODEFINITION_H

#include <string>

// Container for soundtrack audio file name, to be passed to the soundtrack manager. Can play, stop audio.
class AudioDefinition {
public:
	AudioDefinition()
		: directory_{ "" }, file_name_{ "" }, is_playing_{ false }, should_stop_{ false }, duration_(0), volume_(50) {}
	AudioDefinition(std::string directory)
		: directory_{ directory }, file_name_{ "" }, is_playing_{ false }, should_stop_{ false }, duration_(0), volume_(50) {}

	// Setters
	void play() { is_playing_ = true; }
	void stop() { should_stop_ = true; }
	void setDuration(int duration) { duration_ = duration; }
	void setFileName(std::string file_name) { file_name_ = file_name; }
	void setVolume(int volume) { volume_ = volume; }
	void forceStop() { is_playing_ = false; should_stop_ = false; } // <- main.cpp ONLY. DO NOT USE
	void setDirectory(std::string directory) { directory_ = directory; }

	// Getters
	std::string getDirectory() { return directory_; }
	std::string getFileName() { return file_name_; }
	int getDuration() { return duration_; }
	int getVolume() { return volume_; }
	bool isPlaying() { return is_playing_; }
	bool shouldStop() { return should_stop_; }
private:
	std::string file_name_, directory_;
	bool is_playing_, should_stop_;
	int duration_, volume_;
};

#endif // !AUDIODEFINITION_H
