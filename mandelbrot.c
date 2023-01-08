//*****************************************************************************************************************************************
//*************************************************  RAYLIB MANDELBROT SET VISUALIZER   ***************************************************
//********************************************************** BY JRAM0012  *****************************************************************
//*****************************************************************************************************************************************

#include "raylib.h"
#include "stdlib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#ifdef PLATFORM_ANDROID
    #define SCREENWIDTH 1544
    #define SCREENHEIGTH 720

    #define GUISLIDERX 1064              
                // SCREENWIDTH - 480
    #define GUISLIDERY 40

    #define GUISLIDERSDISTANCE 40
    #define CENTERX 1240
    #define CENTERY 540


#else
    #define SCREENWIDTH 1200
    #define SCREENHEIGTH 700

    #define GUISLIDERX 850
                // SCREENWIDTH - 350
    #define GUISLIDERY 20

    #define GUISLIDERSDISTANCE 20
#endif

typedef struct {
    Texture2D texture;
    Rectangle buttonBounds;
}TexturedButton;

bool guibuttonselected = false;
bool ImageButton(TexturedButton* button);

int main()
{
    int screenWidth = SCREENWIDTH, screenHeight = SCREENHEIGTH;

    InitWindow(screenWidth, screenHeight, "mandelbort plotter v2");
    // if (IsWindowState(FLAG_WINDOW_RESIZABLE)) ClearWindowState(FLAG_WINDOW_RESIZABLE); else SetWindowState(FLAG_WINDOW_RESIZABLE);
    int maxIter = 256;
    Shader shader = LoadShader(0, "res/shader.glsl");
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

    SetShaderValue(shader, resolutionLoc, res,                    SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, locationLoc,   location,               SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, zoomLoc,       (const void*)&zoom,     SHADER_UNIFORM_FLOAT);

    SetShaderValue(shader,  vec4_1Loc,    (const void*) &vec4_1,  SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader,  vec4_2Loc,    (const void*) &vec4_2,  SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader,  vec4_3Loc,    (const void*) &vec4_3,  SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader,  vec4_4Loc,    (const void*) &vec4_4,  SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, maxiterLoc,    (const void*) &maxIter, SHADER_UNIFORM_INT);

    TexturedButton Button_UP, Button_DOWN, Button_LEFT,
                Button_RIGHT, Button_ZOOM_IN, Button_ZOOM_OUT, 
                Button_RESET;

#ifdef PLATFORM_ANDROID
    
    Button_UP.texture            = LoadTexture("res/Button1.png");
    Button_UP.buttonBounds       = (Rectangle) {CENTERX -  50, CENTERY - 150, 100, 100};
    Button_DOWN.texture          = LoadTexture("res/Button2.png");
    Button_DOWN.buttonBounds     = (Rectangle) {CENTERX -  50, CENTERY +  50, 100, 100};
    Button_LEFT.texture          = LoadTexture("res/Button3.png");
    Button_LEFT.buttonBounds     = (Rectangle) {CENTERX - 150, CENTERY -  50, 100, 100};
    Button_RIGHT.texture         = LoadTexture("res/Button4.png");
    Button_RIGHT.buttonBounds    = (Rectangle) {CENTERX +  50, CENTERY -  50, 100, 100};
    Button_ZOOM_IN.texture       = LoadTexture("res/Button5.png");
    Button_ZOOM_IN.buttonBounds  = (Rectangle) {CENTERX - 250, CENTERY +  50, 100, 100};
    Button_ZOOM_OUT.texture      = LoadTexture("res/Button6.png");
    Button_ZOOM_OUT.buttonBounds = (Rectangle) {CENTERX - 250, CENTERY - 150, 100, 100};
    Button_RESET.texture         = LoadTexture("res/Button7.png");
    Button_RESET.buttonBounds    = (Rectangle) {CENTERX -  50, CENTERY -  50, 100, 100};

#endif

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginTextureMode(target);
            DrawRectangle(0,0,screenWidth, screenHeight, BLACK);
        EndTextureMode();
        BeginShaderMode(shader);
            DrawTexture(target.texture, 0, 0, WHITE);
        EndShaderMode();

        maxIter = (int) GuiSliderBar((Rectangle) {GUISLIDERX, GUISLIDERY * 0, 330, GUISLIDERSDISTANCE}, TextFormat("MaxIter: %d", maxIter), NULL, maxIter, 20, 2200);
        vec4_1  =       GuiSliderBar((Rectangle) {GUISLIDERX, GUISLIDERY * 2, 330, GUISLIDERSDISTANCE}, TextFormat( "vec4_1: %f", vec4_1), NULL,   vec4_1, 0.0f, 5.0f);
        vec4_2  =       GuiSliderBar((Rectangle) {GUISLIDERX, GUISLIDERY * 4, 330, GUISLIDERSDISTANCE}, TextFormat( "vec4_2: %f", vec4_2), NULL,   vec4_2, 0.0f, 5.0f);
        vec4_3  =       GuiSliderBar((Rectangle) {GUISLIDERX, GUISLIDERY * 6, 330, GUISLIDERSDISTANCE}, TextFormat( "vec4_3: %f", vec4_3), NULL,   vec4_3, 0.0f, 5.0f);
        vec4_4  =       GuiSliderBar((Rectangle) {GUISLIDERX, GUISLIDERY * 8, 330, GUISLIDERSDISTANCE}, TextFormat( "vec4_4: %f", vec4_4), NULL,   vec4_4, 0.0f, 5.0f);

        DrawText(TextFormat("maxiter: %d, zoom: %f", maxIter, zoom), 12, 12, 10,  RED);
        DrawText(TextFormat("maxiter: %d, zoom: %f", maxIter, zoom), 12, 22, 10 , BLUE);
        DrawText(TextFormat("maxiter: %d, zoom: %f", maxIter, zoom), 12, 32, 10 , WHITE);
        
        if(IsKeyDown(KEY_UP)    || ImageButton(&Button_UP))       location[1] -= zoom * 0.05f;
        if(IsKeyDown(KEY_DOWN)  || ImageButton(&Button_DOWN))     location[1] += zoom * 0.05f;
        if(IsKeyDown(KEY_RIGHT) || ImageButton(&Button_RIGHT))    location[0] -= zoom * 0.05f;
        if(IsKeyDown(KEY_LEFT)  || ImageButton(&Button_LEFT))     location[0] += zoom * 0.05f;
        if(IsKeyDown(KEY_S)     || ImageButton(&Button_ZOOM_IN))  zoom += zoom * 0.01f;
        if(IsKeyDown(KEY_W)     || ImageButton(&Button_ZOOM_OUT)) zoom -= zoom * 0.01f;

        if(IsKeyDown(KEY_R) || ImageButton(&Button_RESET))
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

        EndDrawing();
        SetShaderValue(shader, resolutionLoc, res,                      SHADER_UNIFORM_VEC2);
        SetShaderValue(shader, locationLoc,   location,                 SHADER_UNIFORM_VEC2);
        SetShaderValue(shader, zoomLoc,       (const void*)&zoom,       SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, vec4_1Loc,     (const void*)&vec4_1,     SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, vec4_2Loc,     (const void*)&vec4_2,     SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, vec4_3Loc,     (const void*)&vec4_3,     SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, vec4_4Loc,     (const void*)&vec4_4,     SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, maxiterLoc,    (const void*)&maxIter,    SHADER_UNIFORM_INT);
        if(IsKeyPressed(KEY_BACK))
            break;
    }
    
    UnloadShader(shader);
    UnloadRenderTexture(target);

#ifdef PLATFORM_ANDROID
    UnloadTexture(Button_RIGHT.texture);
    UnloadTexture(Button_LEFT.texture);
    UnloadTexture(Button_UP.texture);
    UnloadTexture(Button_DOWN.texture);
    UnloadTexture(Button_ZOOM_IN.texture);
    UnloadTexture(Button_ZOOM_OUT.texture);
    UnloadTexture(Button_RESET.texture);
#endif


    CloseWindow();
    exit(0);
    return 0;
}




// Image button control, returns true when clicked
bool ImageButton(TexturedButton* button)
{
    bool clicked = false;
#ifdef PLATFORM_ANDROID
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, button->buttonBounds) && !guibuttonselected)
    {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) )
        {
            clicked = true;
            guibuttonselected = true;
        }
    } else { guibuttonselected = false; }
    if (button->texture.id > 0)
        DrawTexture(button->texture, button->buttonBounds.x, button->buttonBounds.y, WHITE);
#endif
    return clicked;
}