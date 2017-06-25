~~~~~~~~~~~~~~~~~~~~
Asteroid Fall Code Design
~~~~~~~~~~~~~~~~~~~~
=======================================================================================================================================================
1. HOW TO START THE GAME
------------------------
- Run the .exes in the Asteroid Fall V2 folder.
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
- Use of coding design patterns:
	- Factory for creating entities.
	- Components for handling specific functions for entities
	- Iterator for traversing Map and LinkedList custom containers
	- Facade interfaces for entities, states and components
	- Template methods for custom containers
	- Lazy initialization for states with the Startup function that is called when they are Set, not when they are constructed.
- In-built Unit Testing for all custom containers and their functions
	- Memory leak detector confirms that the containers have no memory leaks.
- Menu system
- State Manager library that can process active states lower on the stack.
- Header only library of custom containers (Map, List, LinkedList, Stack, Queue)
- Automatic DOS command that copies the contents of Bootstrap's bin on  into the output directory of the game (post-build event), 
for ease of compiling and running outside of the environment.
=======================================================================================================================================================
3. REPOSITORY LINKS
--------------------

Custom Containers: https://github.com/DarthDementous/2017_05_31_CustomContainers

Game State Manager: https://github.com/DarthDementous/2017_05_29_GameStateManagement

Asteroid Fall Code Design Project: https://github.com/DarthDementous/2017_06_06_AsteroidCodeDesignProject
=======================================================================================================================================================