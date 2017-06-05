////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																									
////		Name:		Asteroid Escape															
////																									
////		Purpose:	Main program																	
////																									
////		Author:		Sebastian Toy, created 3/14/17 																	
////																									
////////////////////////////////////////////////////////////////////////////////////////////////////////////

///31_3_17 = FINISHED IMPLEMENTING MENU LIBRARY
///3_4_17 = FINISHED IMPLEMENTING RESOURCE MANAGER/ERROR MANAGER AND ENTITYMAKER
///3_4_17 = GAME FUNCTIONALITY FINISHED, SOME BUGS WITH SHOOTING
///3_4_17 = BUGS FIXED, CLEAN UP NOW WORKS PROPERLY

#include "_2017_0313_test2DprojApp.h"
#include <time.h>
#include <cstdlib>
#include "Settings.h"

typedef unsigned int uInt;

int main() {
	srand((uInt)time(NULL));
	auto app = new _2017_0313_test2DprojApp();
	app->run("AIE", W_WIDTH, W_HEIGHT, false);
	delete app;

	return 0;
}