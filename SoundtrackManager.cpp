#include "SoundtrackManager.h"

SoundtrackManager::SoundtrackManager(AudioDefinition & audio) 
	: audio_{ audio }, current_song_{ "" }
{
}

void SoundtrackManager::refreshAudio()
{
	if (audio_.shouldStop()) {
		mciSendString(L"stop soundtrack", NULL, 0, NULL);
		mciSendString(L"close soundtrack", NULL, 0, NULL);
		current_song_ = "";
		audio_.forceStop();
	}
	else if (audio_.isPlaying()) {
		if (current_song_ != audio_.getFilePath())
		{
			current_song_ = audio_.getFilePath();
			if (audio_.getFilePath() != "") {
				std::wstring songTemp = std::wstring(current_song_.begin(), current_song_.end());
				TCHAR * songTemp2 = (wchar_t *)songTemp.c_str();

				std::string volume = std::string("setaudio soundtrack volume to ") + std::to_string(audio_.getVolume());
				std::wstring volumeTemp = std::wstring(volume.begin(), volume.end());
				TCHAR * volumeTemp2 = (wchar_t *)volumeTemp.c_str();

				mciSendString(songTemp2, NULL, 0, NULL);
				mciSendString(volumeTemp2, NULL, 0, NULL);
				mciSendString(L"play soundtrack repeat", NULL, 0, NULL);
			}
		}
	}
}
