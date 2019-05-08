#DESCRIPTION

The project demonstrates growing plants on small houses and big builldings.
It uses OpenGL API in C++.

----- INSTRUCTIONS TO EXECUTE ON WINDOWS -----

Install a C++ compiler and the GLUT library files. The procedure can be found in the following link

https://w3.cs.jmu.edu/bernstdh/Web/common/help/cpp_mingw-glut-setup.php

The command to execute the program can also be found in the link above.

Few changes have to be made in the `main.cpp` file to execute in Windows. They are as follows:

1. Include an extra header file before all the other header files

   `#include <windows.h>`

2. `#include <GL/glut.h>` may not work on windows. If it does not work, try
   `#include <GL\glut.h>`