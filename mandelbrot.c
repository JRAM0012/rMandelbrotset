//*****************************************************************************************************************************************
//*************************************************  RAYLIB MANDELBROT SET VISUALIZER   ***************************************************
//********************************************************** BY JRAM0012  *****************************************************************
//*****************************************************************************************************************************************



#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define REAL 1
#define IMAG 0
#ifndef MOVE_SPEED
  #define MOVE_SPEED 9
#endif

typedef struct ComplexNumber
{
        float real;
        float imag;
}complex;

int MAXITER = 15;
int iter = 0;

complex maptograph(complex,int,int,int);
complex maptoscreen(complex);
complex compsquare(complex);
float splitcomponents(complex,int);
Color throwmesomeshade(int);
int absolutevalue(complex);
complex compadd(complex,complex);
int compabs(complex);
Color mandlebrot(int, int, int, int,int,int);

int main(int argc, char* argv[]) {

        SetConfigFlags(FLAG_MSAA_4X_HINT);

        int screenWidth = 400, screenHeight = 400;

        Color x[screenWidth][screenHeight];
        int SCALER = 120,scrollSpeed = 4,f = 0,s = 0,zr = 4;
        bool update = true;
        InitWindow(screenWidth, screenHeight, "mandlebrot set plotter");
        SetTargetFPS(60);
        while (!WindowShouldClose())
        {
                SCALER += (GetMouseWheelMove()*scrollSpeed);
                if(SCALER<10) SCALER = 10;
                if(IsKeyPressed(KEY_R)) {
                        SCALER = 120;
                        f = 0;
                        s = 0;
                        update = !update;
                }


                if(IsKeyDown(KEY_W)) {
                        f--;
                        update = !update;
                }
                else if(IsKeyDown(KEY_S)) {
                        f++;
                        update = !update;
                }
                else if(IsKeyDown(KEY_A)) {
                        s++;
                        update = !update;
                }
                else if(IsKeyDown(KEY_D)) {
                        s--;
                        update = !update;
                }
                if(IsKeyPressed(KEY_G)) {
                        zr++;
                        update = !update;
                }
                else if(IsKeyPressed(KEY_H)) {
                        zr--;
                        update = !update;
                }
                if(zr<1) zr = 1;

                if(update) {
                        for(int i=0; i<screenWidth; i++)
                                for(int j=0; j<screenHeight; j++)
                                        x[i][j] = mandlebrot(i,j,SCALER,f*MOVE_SPEED,s*MOVE_SPEED,zr);
                        update = !update;
                }
                BeginDrawing();
                ClearBackground(BLACK);
                for(int i=0; i<screenWidth; i++)
                {
                        for(int j=0; j<screenHeight; j++)
                        {
                                DrawPixel(i,j,x[i][j]);
                        }
                }
                DrawRectangle(20,20,20,20,BROWN);
                DrawText(FormatText("%d",SCALER),23,23,12,RED);
                EndDrawing();
        }
        return 1;
}


Color mandlebrot(int x, int y,int scl,int fr, int si,int zrn)
{
        complex c = { x, y }, z = { 0, 0 };
        c = maptograph(c, scl, fr, si);
        for(int iter = 1; iter <= MAXITER; iter++)
        {
                z = compadd(compsquare(z),c);
                if(compabs(z)>zrn)
                {
                        switch(iter)
                        {
                        case 1:
                                return BLUE;
                        case 2:
                                return WHITE;
                        case 3:
                                return ORANGE;
                        case 4:
                                return RED;
                        case 5:
                                return DARKPURPLE;
                        case 6:
                                return PINK;
                        case 7:
                                return DARKGRAY;
                        case 8:
                                return DARKBROWN;
                        case 9:
                                return DARKBLUE;
                        case 10:
                                return PURPLE;
                        case 11:
                                return BEIGE;
                        case 12:
                                return SKYBLUE;
                        case 13:
                                return BLACK;
                        case 14:
                                return MAGENTA;
                        case 15:
                                return BROWN;
                        case 16:
                                return LIGHTGRAY;
                        case 17:
                                return GOLD;
                        case 18:
                                return ORANGE;
                        case 19:
                                return DARKGREEN;
                        case 20:
                                return LIME;
                        case 21:
                                return BLUE;
                        }
                        return VIOLET;
                }
        }
        return BLACK;
}

int compabs(complex cx){
        int x;
        x = (cx.real*cx.real)+(cx.imag*cx.imag);
        return x;
}

complex compadd(complex c_1,complex c_2)
{
        complex cr;
        cr.real = c_1.real+c_2.real;
        cr.imag = c_1.imag+c_2.imag;
        return cr;
}


float splitcomponents(complex x,int COMP)
{
        if(COMP == REAL)
        {
                return x.real;
        } else {
                return x.imag;
        }

}


complex maptograph(complex x,int sc, int frn, int sid)
{

        complex z;
        z.real = (x.real - (GetScreenWidth()/2) - sid)/sc;
        z.imag = ((GetScreenHeight()/2) - x.imag - frn)/sc;
        return z;
}

/*
   complex maptoscreen(complex x)
   {
        complex z;
        z.real = (GetScreenWidth()/2) + (x.real*SCALER);
        z.imag = (GetScreenHeight()/2) - (x.imag*SCALER);
        return z;
   }

 */
complex compsquare(complex x)
{
        complex z;
        z.real = (x.real*x.real) - (x.imag*x.imag);
        z.imag = 2*x.real*x.imag;
        return z;
}
