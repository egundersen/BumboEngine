#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <string>
#include <Windows.h>
#include "resource.h"

// Creates temporary MP3 File on startup, deleted it on shutdown
class AudioManager {
public:
	AudioManager(std::string temporary_file_path) { file_path_ = temporary_file_path; }

	void createMP3Files();
	void destroyMP3Files();
private:


	std::string file_path_;
};

#endif //!AUDIOMANAGER_H