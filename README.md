# Pacman
C++ & SDL2 Pacman Clone, project of Advanced Programming (INT2215)

## Installation
- Requirement:
  * [CodeBlock](https://sourceforge.net/projects/codeblocks/)
  * [MinGW](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download)
  * [SDL2 Graphic Library](https://www.libsdl.org/)
- How to run:
  * Option 1: Open *.cbp with CodeBlock, then click *Run* or press *F9*
  * Option 2: Click *.exe to run

### Structure
- BaseObject, CommonFunction: include basic funtion to load, render.
- Main: includes game loop, logic game(set+get status flag of pacman & ghost, collision), draws objects to screen.
- Pacman: includes handle input from keyboard to move, checks collision with ghost and wall, set animations
- Ghost: same as Pacman except them randomly move
- Map: includes all rect of wall(to check collison with ghost, pacman).
- Point: has maze of foods in order to Pacman eat them
(so on)

#### Demonstrate
- [Youtube]()

<img src="https://imgur.com/QxsvuvW">
