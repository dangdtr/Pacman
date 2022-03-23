# Pacman
C++ & SDL2 Pacman Clone, project of Advanced Programming (INT2215)

# Installation

## Requirement: **Using x86_64**
  * [CodeBlock](https://sourceforge.net/projects/codeblocks/)
  * [MinGW](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download)
  * [SDL2 Graphic Library](https://drive.google.com/drive/folders/1mjlb9ViC-MPrLuh3Q5_GcDl1UzFN3Wtx?usp=sharing): download and move them folder contains `*.cbp` (It is workspace)
 
## How to run:
  * Option 1: Open `*.cbp` with CodeBlock, then click `*Run*` or press `*F9*`
  * Option 2: Click *.exe to run

# Config with Visual Studio Code (VSCode)

## Requirement:
* As above
* [Visual Studio Code](https://code.visualstudio.com/download)

## How to run
* Press `F5`

## Explain

Dùng Tiếng Việt nhé :D
* Để chạy SDL2 trong VSCode thì vần copy cái folder `.vscode` và folder SDL2 (tải ở link trên) vào project của bạn.
* Tại sao cần tải Codeblock? Vì khi bắt đầu học các bạn sẽ dùng Codeblock để setup, do đó mình dùng luôn cái gcc/g++/gdb (MinGW) của Codeblock để bước đầu có thể chạy được luôn.
* Config thế nào? (${workspaceFolder} là thư mục gốc của project)
	* File `c_cpp_properties.json`: Dòng 7->10 là đường dẫn đến include của SDL (gốc, hình ảnh, âm thanh và ttf). Dòng 20: dùng MinGW của Codeblock, thay đổi thì để ý dấu gạch `/`.
	* File `launch.json`: dòng 15 dùng MinGW (gdb) của Codeblock, thay đổi thì để ý dấu gạch `\\`. 
	* File `tasks.json`: file này thì nếu đổi thì đổi path của cái thư viện SDL thôi. Tự mò nhé.
	
	
# Demonstrate
- [Youtube](https://youtu.be/uUaygTeQNYE)
