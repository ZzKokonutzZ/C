#include "raylib.h"

int main(void)
{
    int width=800;
    int height=600;
    InitWindow(width, height, "test shaders");
    //SetTargetFPS(60);
    Shader shader=LoadShader(0,"shader.fs");

    float resolution[2] = {(float)width,(float)height};
    SetShaderValue(shader,GetShaderLocation(shader,"resolution"),resolution,SHADER_UNIFORM_VEC2);

    float time=0.0;

    SetShaderValue(shader,GetShaderLocation(shader,"time"),&time,SHADER_UNIFORM_FLOAT);

    while (!WindowShouldClose())
    {
        time+=GetFrameTime();
        SetShaderValue(shader,GetShaderLocation(shader,"time"),&time,SHADER_UNIFORM_FLOAT);
        BeginDrawing();
        ClearBackground(WHITE);
        BeginShaderMode(shader);
        DrawRectangle(0,0,width,height,WHITE);
        EndShaderMode();
        DrawFPS(10,10);
        EndDrawing();
    }
    UnloadShader(shader);
    CloseWindow();

    return 0;
}