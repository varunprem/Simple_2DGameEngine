# Simple_2DGameEngine
A game engine with Component Based Architecture written in C++ and using SDL for window handling and OPENGL for Rendering.
# varundev
Game Engine
/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology.
File Name: README.txt
Purpose: Function definitions of the various mathematics operations
Language: C++ Visual Studio Enterprise 2015
Platform: Microsoft <R> C/C++ Optimizing Compiler Version 19.00.24210 Windows7
Project: cs529_Final_Project
Author: Varun Premchandran varun.premchandran 60001117
Creation date : 21st October 2017 - Creation of basic window handling using SDL and FrameRate Controller and Input Manager
Update date: 5th November 2017   - Component based game engine architecture and creation of archetypes - Game Object Factory
Update Date : 15th November 2017 - Event manager and collision manager 
Update Date : 27th November 2017 - Hardware Accelarated Graphics - OPEN GL with Texture Rendering system
- End Header --------------------------------------------------------*/


Compiled With:

Operating System : Windows 7 Professional
IDE : Microsoft Visual Studio Enterprise 2015
Compiler : Microsoft <R> C/C++ Optimizing Compiler Version 19.00.24210
Language : C/C++
Platform : Windows x86


				// ---------------------------------------------------------------------------
								Tripper Engine v1.5
				// ---------------------------------------------------------------------------

Project Details: 

This project is a component based game engine as a final project for cs529 

The engine has the following components
There is a main function that loads the game from MainGame.cpp which is a class that handles all the input, frame rate and resource manager calls 
1.Input Manager- handles several keyboard events like 
		1. Trigger events for moving left, right, up and down 
		2. Key pressed events for moving left, right, up and down
		3. Key released events for stoping the left, right , up and down movement of the character 
		using SDL events for key presses and window management. 
		4. The trigger released events is provided in the console print statements 

2. Frame Rate Controller- handles the FPS(Frames per second of the game)
			- returns a function GetFrameTime() at the display of the window

3. Resource Manager- for the loading and cleaning  of image assets 
		   - a dictionary is created as an unordered map which stores on a SDL surface for rendering or drawing an image on screen 

4. Physics Manager - for handing the kinematics and physics body collision of various game objects in a scene 
		   - Shapes are registered for rectangles  and circles 
5. Collision Manager - A manager handing the events for collision and checking for a collision event and number of collisions with various objects in the scene 

6. GameObject Manager - for handling the various components from the architecture to load objects using simple file handling serialization 

7. Game Object instance Manager - for handling events for the adding and getting various components to a game Object 

8. Event Manager - for event handling for example collisions, trigger events, listener events, etc 
		 - Main goal of event manger is to broadcast events to gameobjects. This is done several ways
			1. Broadcast event to all objects 
			2. Make timed events 
			3. Make a subscribed event 

9. Component - Abstract class of the componenet architecture which containts the following components 
		1. Transform - handles the movement of the gameobject 
		2. Sprite- renders the sprite component of a gameobject using SDL 
		3. Body - For the kinematics of the bodies accessed in the scene 
		4. Controller - for movement of a gameobject 
		The component is used to form the various ARCHETYPES/PREFABS in the level loader from the respective files.

10. Open GL - Hardware Accelarated Graphics through Open GL and Transformation Matrix library using GLM. The rendering system involves a texture on a quad mesh too. 
	      The qauds can be accessed from a local file through the vertices been data driven from a file. 
