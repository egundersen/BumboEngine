#include "AudioManager.h"

void AudioManager::createMP3Files()
{
	HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

	HRSRC hResInfo = ::FindResource(hInstance, MAKEINTRESOURCE(IDR_MP32), RT_BITMAP);
	HGLOBAL hRes = ::LoadResource(hInstance, hResInfo);
	LPVOID memRes = ::LockResource(hRes);
	DWORD sizeRes = ::SizeofResource(hInstance, hResInfo);

	HANDLE hFile = ::CreateFile(L"C:\\demo.mp3", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwWritten = 0;
	::WriteFile(hFile, memRes, sizeRes, &dwWritten, NULL);
	::CloseHandle(hFile);
}

void AudioManager::destroyMP3Files()
{
}
