#pragma once
#define W_WIDTH 1280
#define W_HEIGHT 720
#define DEFAULT_BTN_TINT 0x05F705ff    //Highlight green
#define DEFAULT_BTN_WIDTH 200
#define DEFAULT_BTN_HEIGHT 50
#define BTN_Y_INCREMENT 100
#define BTN_TXT_X_OFFSET 15
#define BTN_TXT_Y_OFFSET 4
#define FLOOR_HEIGHT 200
#define MENU_VOLUME 0.5f
#define MUSIC_VOLUME 0.5f     //Volume of background tracks
#define SHRINK_FACTOR 10      //How much to decrease radius on hit
#define MIN_RADIUS 10         

#define PLAYER_HEALTH 60     //Also acts as radius   
#define PLAYER_SPEED 200
#define PLAYER_DMG 50

#define BULLET_HEALTH 1
#define BULLET_SPEED 500
#define BULLET_WIDTH 10
#define BULLET_HEIGHT 50
#define BULLET_RATE .35f      //Seconds between bullets
#define BULLET_VOLUME 0.15f    //How loud to play bullet sounds

#define AST_HEALTH 40
#define AST_SPEED 100
#define AST_DMG 10
#define MIN_ASTEROIDS 20
#define MAX_ASTEROIDS 40    //Maximum asteroids to draw
#define CMT_HEALTH 20
#define CMT_SPEED 200
#define CMT_DMG 40

#define MTR_HEALTH 80
#define MTR_SPEED 50
#define MTR_DMG 80
#include "Vector2.h"
#include <vector>
#include <iostream>
#include <algorithm>
#define PLAYER_STARTPOS Vector2{W_WIDTH / 2, W_HEIGHT / 2}
typedef unsigned int uInt;
using std::vector;
using std::cout;
using std::endl;
///Co-written by Sebastian Toy and Jack McCall
//For input, handled in whole numbers
struct COORD {
	int x, y;
};
struct BoundingBox {
	float x, y, width, height;

	bool IntersectsWith(BoundingBox &a_other) const {
		if (x + width / 2 < a_other.x - a_other.width / 2 || x - width / 2 > a_other.x + a_other.width / 2) return false;
		if (y + height / 2 < a_other.y - a_other.height / 2 || y - height / 2 > a_other.y + a_other.height / 2) return false;

		return true;
	}
	bool Contains(COORD &a_pt) const {
		if (a_pt.x < x - width / 2 || a_pt.x > x + width / 2) return false;
		if (a_pt.y < y - height / 2 || a_pt.y > y + height / 2) return false;

		return true;
	}
	bool Contains(Vector2 &a_v2d) const {
		if (a_v2d.x < x - width / 2 || a_v2d.x > x + width / 2) return false;
		if (a_v2d.y < y - height / 2 || a_v2d.y > y + height / 2) return false;

		return true;
	}
};
///Small lists || large lists with mostly sorted data. VERY inefficient so just for testing and education purposes.
template<typename T>
void BubbleSort(vector<T> &a_array) {
	int size = a_array.size();            //Save as integer to avoid warnings with .size()
										  //DEBUGGING PURPOSES
	cout << endl << "Starting array: ";
	for (T item : a_array) {
		cout << item << " ";
	}
	//DESCENDING ORDER
	for (int i = 0; i < size; ++i) {
		bool swap = false;                 //Only stop sorting when no swaps have been done in the current pass
		for (int j = 0; j < size - (i + 1); ++j) {     //Sort backwards in ascending order
			if (a_array[j] > a_array[j + 1]) {
				std::swap(a_array[j], a_array[j + 1]);
				swap = true;
			}
		}
		//DEBUGGING PURPOSES
		cout << endl << "Array after pass: ";
		for (T item : a_array) {
			cout << item << " ";
		}
		if (!swap) break;
	}
}
///Efficient on small arrays and is improved by initial ordering of values. SORTS BY HEALTH
template<typename T>
void SelectionSort(vector<T> &a_array) {
	//DESCENDING ORDER
	for (size_t pass = 0; pass < a_array.size(); ++pass) {
		float max = a_array[pass]->getHealth();
		for (size_t i = 0; i < a_array.size(); ++i) {
			if (a_array[i]->getHealth() > max) {
				max = a_array[i]->getHealth();
			}
			//If element to sort is not the maximum, then swap it for the maximum
			if (a_array[pass]->getHealth() != max) {
				std::swap(a_array[pass], a_array[i]);
			}
		}
	}
}

enum eColor {
	RED = 0xff0000ff, DK_RED = 0x800000ff, YELLOW = 0xffff00ff, ORANGE = 0xff8000ff,
	GREY = 0xC0C0C0ff, DK_GREY = 0x808080ff, GREEN = 0x00ff00ff,
	DK_GREEN = 0x008000ff, CYAN = 0x00ffffff, DK_CYAN = 0x008080ff,
	BLUE = 0x0000ffff, DK_BLUE = 0x000080ff, WHITE = 0xffffffff, PURPLE = 0x8034f280           //PURPLE is semi transparent because alpha != 255
};
enum eAsteroidType {ASTEROID, COMET, METEOR};
enum textureID {SPLASH, TITLE, BTN, M_BG, G_BG, PLAYER_SPRITE, BULLET_SPRITE, AST_SPRITE, CMT_SPRITE, MTR_SPRITE};
enum fontID {TITLE_TXT, BTN_TXT, DEBUG_TXT};
enum audioID {MENU_MUS, BTN_HVR, BTN_CLICK, GAME_MUS_INTRO, GAME_MUS_LOOP, GAME_END_STING, BULLET_FIRE, HIT};