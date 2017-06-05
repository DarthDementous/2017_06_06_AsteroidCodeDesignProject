~~~~~~~~~~~~~~~~~~~~
Asteroid Fall
~~~~~~~~~~~~~~~~~~~~
=======================================================================================================================================================
1. HOW TO START THE GAME
------------------------
- Run the .exe in Release\
- To compile, open the Bootstrap.sln and set the start-up file to Asteroids2DBootstrap V0
	- There is a limitation of Bootstrap which is that it may not compile if the total directory length is too long. To avoid this, drag the Bootstrap
	folder to something more direct like C:/Bootstrap.
        - Occasionally it may throw up a MSVCRT default lib error, to fix this rebuild the solution.

=======================================================================================================================================================
2. GAME FEATURES
----------------
- Dodge and shoot three types of asteroids for as long as you can!
	- Asteroids: Medium damage, medium speed
	- Comet: High damage, high speed
	- Meteor: very high damage, slow speed
- The smaller you are, the faster you move but beware because there will be more asteroids to dodge!
- Controls:
	- WASD/Arrow Keys = Movement
	- SPACE BAR = Shoot
- Custom sound effects, music and sprites
- Resource and error manager
- Entity sorter and cleaner when objects go outside of the bounds
- Menu system
=======================================================================================================================================================