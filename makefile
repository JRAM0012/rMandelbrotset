all:
	C:\raylib\mingw\bin\gcc.exe -o mandelbrot.exe mandelbrot.c C:\raylib\raylib\src\raylib.rc.data -s -O2 -std=c99 -Wall -lraylib -lopengl32 -lgdi32 -lwinmm -Iexternal -Wl,--subsystem,windows