//*****************************************************************************************************************************************
//*************************************************  RAYLIB MANDELBROT SET VISUALIZER   ***************************************************
//********************************************************** BY JRAM0012  *****************************************************************
//*****************************************************************************************************************************************
#include "raylib.h"
#include <stdio.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"



typedef struct {
    Texture2D texture;
    int x, y;
}TexturedButton;

#ifdef PLATFORM_ANDROID
bool m_IsButtonPressed(TexturedButton* texturedbutton);
#endif

int main()
{
#ifndef PLATFORM_ANDROID
    int screenWidth = 1200, screenHeight = 700;
#else
    int screenWidth = 1544, screenHeight = 720 ;
#endif
    InitWindow(screenWidth, screenHeight, "mandelbort plotter v2");
    // if (IsWindowState(FLAG_WINDOW_RESIZABLE)) ClearWindowState(FLAG_WINDOW_RESIZABLE); else SetWindowState(FLAG_WINDOW_RESIZABLE);
    int maxIter = 256;
    // int lastIter = maxIter;
    char shaderCode[] = 
"#version 100\n\
#ifdef GL_FRAGMENT_PRECISION_HIGH\n\
precision highp float;\n\
#else\n\
precision mediump float;\n\
#endif\n\
uniform vec2 resolution;\n\
uniform vec2 location;\n\
uniform float zoom;\n\
uniform float vec4_1;\n\
uniform float vec4_2;\n\
uniform float vec4_3;\n\
uniform float vec4_4;\n\
uniform int maxIter;\n\
vec2 compsquare(vec2 z)\n\
{\n\
    float temp = z.x;\n\
    z.x = z.x * z.x - z.y * z.y;\n\
    z.y = 2.0 * temp * z.y;\n\
    return z;\n\
}\n\
vec3 hsv2rgb(vec3 hue){\n\
    vec4 K = vec4(vec4_1, vec4_2, vec4_3, vec4_4);\n\
    vec3 p = abs(fract(hue.xxx + K.xyz) * 6.0 - K.www);\n\
    return hue.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), hue.y);\n\
}\n\
vec3 mandelbort(vec2 point){\n\
    vec2 z = vec2(0.0);\n\
    float iters = 0.0;\n\
    for (iters = 0.0;   iters < float(maxIter); ++iters)\n\
    {\n\
        z = compsquare(z) + point;\n\
        if(dot(z, z) > 4.0) break;\n\
    }\n\
    float hue = iters / float(maxIter);\n\
    if(hue > 0.98) return vec3(0.0);\n\
    return hsv2rgb(vec3(hue, 1.0, 1.0));\n\
}\n\
void main()\n\
{\n\
    vec2 uv = gl_FragCoord.xy / resolution;\n\
    uv.x *= resolution.x / resolution.y;\n\
    uv -= vec2(0.7, 0.5);\n\
    // uv.x -= 0.5;\n\
    uv *= zoom;\n\
    uv -= location;\n\
    gl_FragColor = vec4(mandelbort(uv), 1.0);\n\
    // gl_FragColor = vec4(uv, 1.0, 1.0);\n\
}";


    Shader shader = LoadShaderCode(0, shaderCode);
    RenderTexture target = LoadRenderTexture(screenWidth, screenHeight);
    int resolutionLoc    = GetShaderLocation(shader, "resolution");
    int locationLoc      = GetShaderLocation(shader, "location");
    int zoomLoc          = GetShaderLocation(shader, "zoom");
    int vec4_1Loc        = GetShaderLocation(shader, "vec4_1");
    int vec4_2Loc        = GetShaderLocation(shader, "vec4_2");
    int vec4_3Loc        = GetShaderLocation(shader, "vec4_3");
    int vec4_4Loc        = GetShaderLocation(shader, "vec4_4");
    int maxiterLoc       = GetShaderLocation(shader, "maxIter");

    float res[2] = {screenWidth, screenHeight};
    float location[2] = {0.0, 0.0};
    float zoom = 2.0;

    float vec4_1 = 1.0f;
    float vec4_2 = 2.0f / 3.0f;
    float vec4_3 = 1.0f / 3.0f;
    float vec4_4 = 3.0f;

    SetShaderValue(shader, resolutionLoc, res,      UNIFORM_VEC2);
    SetShaderValue(shader, locationLoc,   location, UNIFORM_VEC2);
    SetShaderValue(shader, zoomLoc,       (const void*)&zoom,     UNIFORM_FLOAT);


    SetShaderValue(shader,  vec4_1Loc, (const void*)&vec4_1,  UNIFORM_FLOAT);
    SetShaderValue(shader,  vec4_2Loc, (const void*)&vec4_2,  UNIFORM_FLOAT);
    SetShaderValue(shader,  vec4_3Loc, (const void*)&vec4_3,  UNIFORM_FLOAT);
    SetShaderValue(shader,  vec4_4Loc, (const void*)&vec4_4,  UNIFORM_FLOAT);
    SetShaderValue(shader, maxiterLoc, (const void*)&maxIter, UNIFORM_INT);

    // float mousey = 0.0f;


#ifdef PLATFORM_ANDROID
    TexturedButton UI_Button_UP;
    TexturedButton UI_Button_DOWN;
    TexturedButton UI_Button_LEFT;
    TexturedButton UI_Button_RIGHT;
    TexturedButton UI_Button_PINCH_IN;
    TexturedButton UI_Button_PINCH_OUT;
    TexturedButton UI_Button_RESET;
    
    UI_Button_UP.texture              = LoadTexture("res/UI_Button_UP.png");
    UI_Button_DOWN.texture            = LoadTexture("res/UI_Button_DOWN.png");
    UI_Button_LEFT.texture            = LoadTexture("res/UI_Button_LEFT.png");
    UI_Button_RIGHT.texture           = LoadTexture("res/UI_Button_RIGHT.png");
    UI_Button_PINCH_IN.texture        = LoadTexture("res/UI_Button_PINCH_IN.png");
    UI_Button_PINCH_OUT.texture       = LoadTexture("res/UI_Button_PINCH_OUT.png");
    UI_Button_RESET.texture           = LoadTexture("res/UI_Button_RESET.png");


    int middlex = 1220, middley = 388;

    UI_Button_UP.x = middlex - 50; 
    UI_Button_UP.y = middley - 150;

    UI_Button_DOWN.x = middlex - 50;
    UI_Button_DOWN.y = middley + 50;
    
    UI_Button_LEFT.x = middlex - 150;
    UI_Button_LEFT.y = middley - 50;

    UI_Button_RIGHT.x = middlex + 50;
    UI_Button_RIGHT.y = middley - 50;

    UI_Button_RESET.x = middlex - 50;
    UI_Button_RESET.y = middley - 50;
    
    UI_Button_PINCH_IN.x = 1300;
    UI_Button_PINCH_IN.y = 590;
    UI_Button_PINCH_OUT.x = 1300; 
    UI_Button_PINCH_OUT.y = 450;


#endif
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(TextFormat("%d", maxIter), 12, 12, 12, PINK);
        BeginTextureMode(target);
            DrawRectangle(0,0,screenWidth, screenHeight, BLACK);
        EndTextureMode();
        BeginShaderMode(shader);
            DrawTexture(target.texture, 0, 0, WHITE);
        EndShaderMode();

#ifndef PLATFORM_ANDROID
        maxIter = (int) GuiSliderBar((Rectangle) {screenWidth - 350, 00, 330, 20}, TextFormat("MaxIter: %d", maxIter), NULL, maxIter, 20, 2200);
        vec4_1 =        GuiSliderBar((Rectangle) {screenWidth - 350, 20, 330, 20}, TextFormat( "vec4_1: %f", vec4_1), NULL,   vec4_1, 0.0f, 5.0f);
        vec4_2 =        GuiSliderBar((Rectangle) {screenWidth - 350, 40, 330, 20}, TextFormat( "vec4_2: %f", vec4_2), NULL,   vec4_2, 0.0f, 5.0f);
        vec4_3 =        GuiSliderBar((Rectangle) {screenWidth - 350, 60, 330, 20}, TextFormat( "vec4_3: %f", vec4_3), NULL,   vec4_3, 0.0f, 5.0f);
        vec4_4 =        GuiSliderBar((Rectangle) {screenWidth - 350, 80, 330, 20}, TextFormat( "vec4_4: %f", vec4_4), NULL,   vec4_4, 0.0f, 5.0f);
#else
        maxIter = (int) GuiSliderBar((Rectangle) {screenWidth - 480,  00, 330, 38}, TextFormat("MaxIter: %d", maxIter), NULL, maxIter, 20, 2200);
        vec4_1 =        GuiSliderBar((Rectangle) {screenWidth - 480,  40, 330, 38}, TextFormat( "vec4_1: %f", vec4_1), NULL,   vec4_1, 0.0f, 5.0f);
        vec4_2 =        GuiSliderBar((Rectangle) {screenWidth - 480,  80, 330, 38}, TextFormat( "vec4_2: %f", vec4_2), NULL,   vec4_2, 0.0f, 5.0f);
        vec4_3 =        GuiSliderBar((Rectangle) {screenWidth - 480, 120, 330, 38}, TextFormat( "vec4_3: %f", vec4_3), NULL,   vec4_3, 0.0f, 5.0f);
        vec4_4 =        GuiSliderBar((Rectangle) {screenWidth - 480, 160, 330, 38}, TextFormat( "vec4_4: %f", vec4_4), NULL,   vec4_4, 0.0f, 5.0f);
#endif

        DrawText(TextFormat("maxiter: %d, zoom: %f", maxIter, zoom), 12, 12, 10,  RED);
        DrawText(TextFormat("maxiter: %d, zoom: %f", maxIter, zoom), 12, 22, 10 , BLUE);
        DrawText(TextFormat("maxiter: %d, zoom: %f", maxIter, zoom), 12, 32, 10 , WHITE);
#ifdef PLATFORM_ANDROID
        DrawTexture(UI_Button_RIGHT.texture, UI_Button_RIGHT.x, UI_Button_RIGHT.y, WHITE);                  // UI_Button_RIGHT
        DrawTexture(UI_Button_LEFT.texture, UI_Button_LEFT.x, UI_Button_LEFT.y, WHITE);                     // UI_Button_LEFT
        DrawTexture(UI_Button_UP.texture, UI_Button_UP.x, UI_Button_UP.y, WHITE);                           // UI_Button_UP
        DrawTexture(UI_Button_DOWN.texture, UI_Button_DOWN.x, UI_Button_DOWN.y, WHITE);                     // UI_Button_DOWN
        DrawTexture(UI_Button_PINCH_IN.texture, UI_Button_PINCH_IN.x, UI_Button_PINCH_IN.y, WHITE);         // UI_Button_PINCH_IN
        DrawTexture(UI_Button_PINCH_OUT.texture, UI_Button_PINCH_OUT.x, UI_Button_PINCH_OUT.y, WHITE);      // UI_Button_PINCH_OUT
        DrawTexture(UI_Button_RESET.texture, UI_Button_RESET.x, UI_Button_RESET.y, WHITE);      // UI_Button_PINCH_OUT
#endif
        EndDrawing();

        if(GetScreenWidth() != screenWidth || GetScreenHeight() != screenHeight)
        {
            UnloadRenderTexture(target);
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
            target = LoadRenderTexture(screenWidth, screenHeight);
        }

#ifdef PLATFORM_ANDROID
        if(m_IsButtonPressed(&UI_Button_RIGHT))     location[0] += zoom * 0.019f;
        if(m_IsButtonPressed(&UI_Button_LEFT))      location[0] -= zoom * 0.019f;
        if(m_IsButtonPressed(&UI_Button_UP))        location[1] += zoom * 0.019f;
        if(m_IsButtonPressed(&UI_Button_DOWN))      location[1] -= zoom * 0.019f;
        if(m_IsButtonPressed(&UI_Button_PINCH_IN))  zoom += zoom * 0.04f;
        if(m_IsButtonPressed(&UI_Button_PINCH_OUT)) zoom -= zoom * 0.04f;
#else
        if(IsKeyDown(KEY_RIGHT))                   location[0] -= zoom * 0.05f;
        if(IsKeyDown(KEY_LEFT))                    location[0] += zoom * 0.05f;
        if(IsKeyDown(KEY_UP))                      location[1] -= zoom * 0.05f;
        if(IsKeyDown(KEY_DOWN))                    location[1] += zoom * 0.05f;
        if(IsKeyDown(KEY_S))                       zoom += zoom * 0.01f;
        if(IsKeyDown(KEY_W))                       zoom -= zoom * 0.01f;
#endif

//         start_game_button = GuiButton((Rectangle){ GetScreenWidth() / 3 + 100,GetScreenHeight() / 3 + 125,250,100 },"");

#ifdef PLATFORM_ANDROID
        if(m_IsButtonPressed(&UI_Button_RESET))
#else
            // break;
        if(IsKeyDown(KEY_R))
#endif
        {
            location[0] = 0.0;          
            location[1] = 0.0;
            zoom = 2.0;
            maxIter = 256;
            vec4_1 = 1.0f;
            vec4_2 = 2.0f / 3.0f;
            vec4_3 = 1.0f / 3.0f;
            vec4_4 = 3.0f;
        }


        SetShaderValue(shader, resolutionLoc,               res,        UNIFORM_VEC2);
        SetShaderValue(shader, locationLoc,                 location,   UNIFORM_VEC2);
        SetShaderValue(shader, zoomLoc,       (const void*)&zoom,       UNIFORM_FLOAT);
        SetShaderValue(shader, vec4_1Loc,     (const void*)&vec4_1,     UNIFORM_FLOAT);
        SetShaderValue(shader, vec4_2Loc,     (const void*)&vec4_2,     UNIFORM_FLOAT);
        SetShaderValue(shader, vec4_3Loc,     (const void*)&vec4_3,     UNIFORM_FLOAT);
        SetShaderValue(shader, vec4_4Loc,     (const void*)&vec4_4,     UNIFORM_FLOAT);
        SetShaderValue(shader, maxiterLoc,    (const void*)&maxIter,    UNIFORM_INT);
        if(IsKeyPressed(KEY_BACK))
            break;
    }
    
    UnloadShader(shader);
    UnloadRenderTexture(target);
#ifdef PLATFORM_ANDROID
    UnloadTexture(UI_Button_RIGHT.texture);
    UnloadTexture(UI_Button_LEFT.texture);
    UnloadTexture(UI_Button_UP.texture);
    UnloadTexture(UI_Button_DOWN.texture);
    UnloadTexture(UI_Button_PINCH_IN.texture);
    UnloadTexture(UI_Button_PINCH_OUT.texture);
    UnloadTexture(UI_Button_RESET.texture);
#endif


    CloseWindow();
    exit(EXIT_SUCCESS);
    return 0;
}


bool m_IsButtonPressed(TexturedButton* texbutton)
{
    // int x = GetMouseX(), y = GetMouseY();
    Vector2 touch = GetTouchPosition(0);
    if(IsGestureDetected(GESTURE_HOLD))
        if(touch.x > texbutton->x && touch.y > texbutton->y && touch.x < (texbutton->x + texbutton->texture.width) && touch.y < (texbutton->y + texbutton->texture.width))
            return true;
    // if(IsGestureDetected(GESTURE_HOLD))
    //  if( touch.x > texbutton->x &&  touch.y > texbutton->y )
    //      if( touch.x < (texbutton->x + texbutton->x + texbutton->texture.width ) &&
    //          touch.y < (texbutton->y + texbutton->y + texbutton->texture.height))
                // return true;
    return false;
}