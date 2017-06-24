////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																									
////		Name:		Window Class																	
////																									
////		Purpose:	Defines the characteristics of the window and functions applied to it			
////																									
////		Authors:	Roger Keating, edited by Sebastian Toy																	
////																									
////////////////////////////////////////////////////////////////////////////////////////////////////////////

// the old way of making sure this is accessed only once
#ifndef WINDOW_H_			// 1.. is WINDOW_H_ defined ... if it is do not do this
#define WINDOW_H_			// 2.. define WINDOW_H_

#include <iostream>
#include <Windows.h>
#include <wincon.h>
#include <conio.h>
#include <string>
#include <vector>

// specify a couple of std fuctions so that they are easier to read in the program
using std::cout;
using std::endl;
using std::string;
using std::vector;
// colors used by the console system
enum eColor { BLACK, DARKBLUE, DARKGREEN, DARKCYAN, DARKRED, DARKMAGENTA, DARKYELLOW, LIGHTGRAY, GRAY, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE, MAX_COLORS };

//POSITION AND SIZE OF THE 2D SHAPE
struct Rect
{
	int x, y, width, height;
};

class Window
{
public:
	///Methods
	bool Initialise(int a_width, int a_height, char *name);
	void SetCursorVisibility(bool pShow);
	void SetTextColor(eColor pColor);
	BOOL SetXY(int pX, int pY);
	void DrawShape(int pX, int pY, vector<string> &a_shape, eColor a_color = WHITE);
	void DrawChar(int pX, int pY, unsigned char pLine, eColor a_color = WHITE);
	void DrawTextLine(int pX, int pY, eColor pColor, char *pChar, int p_max);
	void ClearScreen();
	void ClearSection(Rect pLocation);
	void DrawBorder(Rect pLocation, eColor pColor);
	static char* toChar(string &str) { return &str[0u]; }                      //Convert string to char array in order to print it out
	// getters
	COORD getMousePos();
	int getRoomHeight() { return mScreenHeight; }
	int getRoomWidth() { return mScreenWidth; }
private:
	///Variables
	int mScreenWidth;
	int mScreenHeight;
	eColor mCurrentColor;
	HANDLE mhSTDOut;
};

#endif						// 3.. close out the header for WINDOW_H_