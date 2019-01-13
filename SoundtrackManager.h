#ifndef SOUNDTRACKMANAGER_H
#define SOUNDTRACKMANAGER_H

#include "AudioDefinition.h"
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")

// Manages play & stop functionality for the AudioDefinition
class SoundtrackManager {
public:
	SoundtrackManager(AudioDefinition &audio);

	void refreshAudio();
private:
	std::string current_song_;
	AudioDefinition &audio_;
};

#endif // !SOUNDTRACKMANAGER_H
