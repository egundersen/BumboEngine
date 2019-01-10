// Exclude the min and max macros from Windows.h
#define NOMINMAX
#include "stdafx.h"
#include "WinMainParameters.h"
#include "MatrixManager.h"
#include "SplashScreen.h"
#include "resource.h"

using namespace WinMainParameters;

#define MAX_LOADSTRING 100

// Global Variables (are (usually) evil; this code comes from the Visual C++ Win32 Application project template):
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Global (To main.cpp only) Variables for width, height and the output display screens
bool should_exit_G = false;
int width_G = 79;
int height_G = 35;
BitmapDefinition bitmap_G("", 160, 0);
Matrix screen_matrix_G(width_G, height_G);

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// ISO C++ conformant entry point. The project properties explicitly sets this as the entry point in the manner
// documented for the linker's /ENTRY option: http://msdn.microsoft.com/en-us/library/f9t8842e.aspx . As per
// the documentation, the value set as the entry point is "mainCRTStartup", not "main". Every C or C++ program
// must perform any initialization required by the language standards before it begins executing our code. In
// Visual C++, this is done by the *CRTStartup functions, each of which goes on to call the developer's entry
// point function.
int main(int /*argc*/, char* /*argv*/[]) {
	// Use the functions from WinMainParameters.h to get the values that would've been passed to WinMain.
	// Note that these functions are in the WinMainParameters namespace.
	HINSTANCE hInstance = GetHInstance();
	HINSTANCE hPrevInstance = GetHPrevInstance();
	LPWSTR lpCmdLine = GetLPCmdLine();
	int nCmdShow = GetNCmdShow();

	// Assert that the values returned are expected.
	assert(hInstance != nullptr);
	assert(hPrevInstance == nullptr);
	assert(lpCmdLine != nullptr);

	// Close the console window. This is not required, but if you do not need the console then it should be
	// freed in order to release the resources it is using. If you wish to keep the console open and use it
	// you can remove the call to FreeConsole. If you want to create a new console later you can call
	// AllocConsole. If you want to use an existing console you can call AttachConsole.
	int debug_mode = false;
#ifdef _DEBUG
	debug_mode = true;
#endif
	if (!debug_mode)
		FreeConsole();

	// ***********************
	// If you want to avoid creating a console in the first place, you can change the linker /SUBSYSTEM
	// option in the project properties to WINDOWS as documented here:
	// http://msdn.microsoft.com/en-us/library/fcc1zstk.aspx . If you do that you should comment out the
	// above call to FreeConsole since there will not be any console to free. The program will still
	// function properly. If you want the console back, change the /SUBSYSTEM option back to CONSOLE.
	// ***********************

	// Note: The remainder of the code in this file comes from the default Visual C++ Win32 Application
	// template (with a few minor alterations). It serves as an example that the program works, not as an
	// example of good, modern C++ code style.

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LAUNCHWIN32WINDOWFROMCONSOLE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAUNCHWIN32WINDOWFROMCONSOLE));

	// Loading/Splash Screen
	SplashScreen splash(width_G, height_G, screen_matrix_G);
	GetMessage(&msg, NULL, 0, 0);
	RedrawWindow(msg.hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ALLCHILDREN |
		RDW_ERASE | RDW_NOFRAME | RDW_UPDATENOW);

	// MAIN SOURCE PORT - Bumbo Engine -----------------------------------------------------
	MatrixManager grid(width_G, height_G, screen_matrix_G, 5, bitmap_G);
	GetMessage(&msg, NULL, 0, 0);
	RedrawWindow(msg.hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ALLCHILDREN |
		RDW_ERASE | RDW_NOFRAME | RDW_UPDATENOW);

	// Game loop
	while (true)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (should_exit_G || msg.message == WM_QUIT)
		{
			break;
		}

		// Update the game (loop)
		grid.evaluatePlayerInput();
		RedrawWindow(msg.hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ALLCHILDREN |
			RDW_ERASE | RDW_NOFRAME | RDW_UPDATENOW);
	}

	return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAUNCHWIN32WINDOWFROMCONSOLE));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_LAUNCHWIN32WINDOWFROMCONSOLE);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	RECT wr = { 0, 0, 795, 545 };    // set the window size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the window size
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

#define COLORREF2RGB(Color) (Color & 0xff00) | ((Color >> 16) & 0xff) \
                                 | ((Color << 16) & 0xff0000)

//-------------------------------------------------------------------------------
// ReplaceColor
//
// Author    : Dimitri Rochette drochette@coldcat.fr
// Specials Thanks to Joe Woodbury for his comments and code corrections
//
// Includes  : Only <windows.h>

//
// hBmp         : Source Bitmap
// cOldColor : Color to replace in hBmp
// cNewColor : Color used for replacement
// hBmpDC    : DC of hBmp ( default NULL ) could be NULL if hBmp is not selected
//
// Retcode   : HBITMAP of the modified bitmap or NULL for errors
//
//-------------------------------------------------------------------------------
HBITMAP ReplaceColor(HBITMAP hBmp, COLORREF cOldColor, COLORREF cNewColor, HDC hBmpDC)
{
	HBITMAP RetBmp = NULL;
	if (hBmp)
	{
		HDC BufferDC = CreateCompatibleDC(NULL);    // DC for Source Bitmap
		if (BufferDC)
		{
			HBITMAP hTmpBitmap = (HBITMAP)NULL;
			if (hBmpDC)
				if (hBmp == (HBITMAP)GetCurrentObject(hBmpDC, OBJ_BITMAP))
				{
					hTmpBitmap = CreateBitmap(1, 1, 1, 1, NULL);
					SelectObject(hBmpDC, hTmpBitmap);
				}

			HGDIOBJ PreviousBufferObject = SelectObject(BufferDC, hBmp);
			// here BufferDC contains the bitmap

			HDC DirectDC = CreateCompatibleDC(NULL); // DC for working
			if (DirectDC)
			{
				// Get bitmap size
				BITMAP bm;
				GetObject(hBmp, sizeof(bm), &bm);

				// create a BITMAPINFO with minimal initilisation 
				// for the CreateDIBSection
				BITMAPINFO RGB32BitsBITMAPINFO;
				ZeroMemory(&RGB32BitsBITMAPINFO, sizeof(BITMAPINFO));
				RGB32BitsBITMAPINFO.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				RGB32BitsBITMAPINFO.bmiHeader.biWidth = bm.bmWidth;
				RGB32BitsBITMAPINFO.bmiHeader.biHeight = bm.bmHeight;
				RGB32BitsBITMAPINFO.bmiHeader.biPlanes = 1;
				RGB32BitsBITMAPINFO.bmiHeader.biBitCount = 32;

				// pointer used for direct Bitmap pixels access
				UINT * ptPixels;

				HBITMAP DirectBitmap = CreateDIBSection(DirectDC,
					(BITMAPINFO *)&RGB32BitsBITMAPINFO,
					DIB_RGB_COLORS,
					(void **)&ptPixels,
					NULL, 0);
				if (DirectBitmap)
				{
					// here DirectBitmap!=NULL so ptPixels!=NULL no need to test
					HGDIOBJ PreviousObject = SelectObject(DirectDC, DirectBitmap);
					BitBlt(DirectDC, 0, 0,
						bm.bmWidth, bm.bmHeight,
						BufferDC, 0, 0, SRCCOPY);

					// here the DirectDC contains the bitmap

					// Convert COLORREF to RGB (Invert RED and BLUE)
					cOldColor = COLORREF2RGB(cOldColor);
					cNewColor = COLORREF2RGB(cNewColor);

					// After all the inits we can do the job : Replace Color
					for (int i = ((bm.bmWidth*bm.bmHeight) - 1); i >= 0; i--)
					{
						if (ptPixels[i] == cOldColor) ptPixels[i] = cNewColor;
					}
					// little clean up
					// Don't delete the result of SelectObject because it's 
					// our modified bitmap (DirectBitmap)
					SelectObject(DirectDC, PreviousObject);

					// finish
					RetBmp = DirectBitmap;
				}
				// clean up
				DeleteDC(DirectDC);
			}
			if (hTmpBitmap)
			{
				SelectObject(hBmpDC, hBmp);
				DeleteObject(hTmpBitmap);
			}
			SelectObject(BufferDC, PreviousBufferObject);
			// BufferDC is now useless
			DeleteDC(BufferDC);
		}
	}
	return RetBmp;
}

HBITMAP ReplaceAllColorsExcept(HBITMAP hBmp, COLORREF cExcludedColor, COLORREF cNewColor, HDC hBmpDC)
{
	HBITMAP RetBmp = NULL;
	if (hBmp)
	{
		HDC BufferDC = CreateCompatibleDC(NULL);    // DC for Source Bitmap
		if (BufferDC)
		{
			HBITMAP hTmpBitmap = (HBITMAP)NULL;
			if (hBmpDC)
				if (hBmp == (HBITMAP)GetCurrentObject(hBmpDC, OBJ_BITMAP))
				{
					hTmpBitmap = CreateBitmap(1, 1, 1, 1, NULL);
					SelectObject(hBmpDC, hTmpBitmap);
				}

			HGDIOBJ PreviousBufferObject = SelectObject(BufferDC, hBmp);
			// here BufferDC contains the bitmap

			HDC DirectDC = CreateCompatibleDC(NULL); // DC for working
			if (DirectDC)
			{
				// Get bitmap size
				BITMAP bm;
				GetObject(hBmp, sizeof(bm), &bm);

				// create a BITMAPINFO with minimal initilisation 
				// for the CreateDIBSection
				BITMAPINFO RGB32BitsBITMAPINFO;
				ZeroMemory(&RGB32BitsBITMAPINFO, sizeof(BITMAPINFO));
				RGB32BitsBITMAPINFO.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				RGB32BitsBITMAPINFO.bmiHeader.biWidth = bm.bmWidth;
				RGB32BitsBITMAPINFO.bmiHeader.biHeight = bm.bmHeight;
				RGB32BitsBITMAPINFO.bmiHeader.biPlanes = 1;
				RGB32BitsBITMAPINFO.bmiHeader.biBitCount = 32;

				// pointer used for direct Bitmap pixels access
				UINT * ptPixels;

				HBITMAP DirectBitmap = CreateDIBSection(DirectDC,
					(BITMAPINFO *)&RGB32BitsBITMAPINFO,
					DIB_RGB_COLORS,
					(void **)&ptPixels,
					NULL, 0);
				if (DirectBitmap)
				{
					// here DirectBitmap!=NULL so ptPixels!=NULL no need to test
					HGDIOBJ PreviousObject = SelectObject(DirectDC, DirectBitmap);
					BitBlt(DirectDC, 0, 0,
						bm.bmWidth, bm.bmHeight,
						BufferDC, 0, 0, SRCCOPY);

					// here the DirectDC contains the bitmap

					// Convert COLORREF to RGB (Invert RED and BLUE)
					cExcludedColor = COLORREF2RGB(cExcludedColor);
					cNewColor = COLORREF2RGB(cNewColor);

					// After all the inits we can do the job : Replace Color
					for (int i = ((bm.bmWidth*bm.bmHeight) - 1); i >= 0; i--)
					{
						if (ptPixels[i] != cExcludedColor) ptPixels[i] = cNewColor;
					}
					// little clean up
					// Don't delete the result of SelectObject because it's 
					// our modified bitmap (DirectBitmap)
					SelectObject(DirectDC, PreviousObject);

					// finish
					RetBmp = DirectBitmap;
				}
				// clean up
				DeleteDC(DirectDC);
			}
			if (hTmpBitmap)
			{
				SelectObject(hBmpDC, hBmp);
				DeleteObject(hTmpBitmap);
			}
			SelectObject(BufferDC, PreviousBufferObject);
			// BufferDC is now useless
			DeleteDC(BufferDC);
		}
	}
	return RetBmp;
}

bool LoadAndBlitBitmap(LPCWSTR szFileName, HDC hWinDC, int position_x, int position_y)
{
	// Load the bitmap image file
	HBITMAP hBitmap;
	hBitmap = (HBITMAP)::LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE);
	// Verify that the image was loaded
	if (hBitmap == NULL)
	{
		::MessageBox(NULL, __T("LoadImage Failed"), __T("Error"), MB_OK);
		return false;
	}

	// Create a device context that is compatible with the window
	HDC hLocalDC;
	hLocalDC = ::CreateCompatibleDC(hWinDC);
	// Verify that the device context was created
	if (hLocalDC == NULL)
	{
		::MessageBox(NULL, __T("CreateCompatibleDC Failed"), __T("Error"), MB_OK);
		return false;
	}

	// Changes color (But since Bitmap is so pixelated, this is the only way we can include all colors
	HBITMAP hBitmapColored = ReplaceAllColorsExcept(hBitmap, 0x000000, bitmap_G.getRGBA().getHex(), hLocalDC);

	// Get the bitmap's parameters and verify the get
	BITMAP qBitmap;
	int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmapColored), sizeof(BITMAP),
		reinterpret_cast<LPVOID>(&qBitmap));
	if (!iReturn)
	{
		::MessageBox(NULL, __T("GetObject Failed"), __T("Error"), MB_OK);
		return false;
	}

	// Select the loaded bitmap into the device context
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hLocalDC, hBitmapColored);
	if (hOldBmp == NULL)
	{
		::MessageBox(NULL, __T("SelectObject Failed"), __T("Error"), MB_OK);
		return false;
	}

	/*if (std::get<2>(image_file_path_G).getHex() < 255)
	{
		// setting up the blend function
		BLENDFUNCTION bStruct;
		bStruct.BlendOp = AC_SRC_OVER;
		bStruct.BlendFlags = 0;
		bStruct.SourceConstantAlpha = std::get<2>(image_file_path_G).getHex();
		bStruct.AlphaFormat = 0;

		// Blit a transparent version of the dc onto the window's dc
		BOOL qTransBlit = ::AlphaBlend(hWinDC, position_x, 0, 475, 425, hLocalDC, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight, bStruct);
		if (!qTransBlit)
		{
			::MessageBox(NULL, __T("Blit Failed"), __T("Error"), MB_OK);
			return false;
		}
	}
	else
	{//*/
		// Blit the dc which holds the bitmap onto the window's dc
		SetStretchBltMode(hWinDC, HALFTONE);
		BOOL qRetBlit = ::StretchBlt(hWinDC, position_x, position_y, 475, 425,
			hLocalDC, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight, SRCCOPY);
		if (!qRetBlit)
		{
			::MessageBox(NULL, __T("Blit Failed"), __T("Error"), MB_OK);
			return false;
		}
	//}

	// Unitialize and deallocate resources
	::SelectObject(hLocalDC, hOldBmp);
	::DeleteDC(hLocalDC);
	::DeleteObject(hBitmap);
	::DeleteObject(hBitmapColored);
	return true;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HFONT font;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);
		if (hDC != NULL) {
			RECT rect;
			GetClientRect(hWnd, &rect);

			// Create bitmap image (To write everything on the window to)
			HDC hDCMem = CreateCompatibleDC(hDC);
			HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
			SelectObject(hDCMem, hBitmap);

			FillRect(hDCMem, &rect, (HBRUSH)(COLOR_BTNFACE + 1));
			FillRect(hDCMem, &rect, (HBRUSH)(COLOR_BACKGROUND + 1));

			// Load Complex Ascii-styled Image from provided file path
			if (bitmap_G.shouldShowBitmap())
			{
				std::string file_path = bitmap_G.getFilePath();
				std::wstring sTemp = std::wstring(file_path.begin(), file_path.end());
				LPCWSTR sw = sTemp.c_str();
				LoadAndBlitBitmap(sw, hDCMem, bitmap_G.getXOffset(), bitmap_G.getYOffset());
			}

			COLORREF blackTextColor = 0x00000000;
			SetBkMode(hDCMem, OPAQUE);
			SetBkColor(hDCMem, blackTextColor);
			for (int i = 0; i < height_G; i++)
				for (int j = 0; j < width_G; j++)
					if (std::string(1, screen_matrix_G[i][j]).c_str() != std::string(1, ' '))
					{
						COLORREF whiteTextColor = screen_matrix_G[i][j].getColor();
						if (SetTextColor(hDCMem, whiteTextColor) == CLR_INVALID)
						{
							PostQuitMessage(1);
						}
						ExtTextOutA(hDCMem, j * 10, i * 15, ETO_CLIPPED, &rect, std::string(1, screen_matrix_G[i][j]).c_str(), 1, NULL);
					}

			// Copy window image/bitmap to screen
			BitBlt(hDC, 0, 0, rect.right, rect.bottom, hDCMem, 0, 0, SRCCOPY);

			DeleteObject(hBitmap);
			DeleteDC(hDCMem);

			EndPaint(hWnd, &ps);
		}
	} return 0;

	case WM_ERASEBKGND:
		return 1;
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		should_exit_G = true;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}