#include <iostream>
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stdio.h>
#include "src/Util.hh"
#include "src/State.hh"
#include "src/const.hh"


int main(int argc, char ** argv) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH, HEIGHT, TITLE);
    InitAudioDevice();
    SetTargetFPS(FPS);
    Texture font = LoadTexture("font.png");
    Assets assets(font);
    World world(1);
    RenderTexture buffer = LoadRenderTexture(WIDTH, HEIGHT);
    SetTextureFilter(buffer.texture, TEXTURE_FILTER_BILINEAR);
    std::vector<State *> states;
    states.push_back(new Input2DState(world, assets));
    while (!WindowShouldClose() && !states.empty()) {
        int c = GetKeyPressed();
        while (c != 0) {
            states.back()->onKey(c);
            c = GetKeyPressed();
        }
        assets.update();
        BeginDrawing();
        ClearBackground(BLACK);
        BeginTextureMode(buffer);
        ClearBackground(BLACK);
        states.back()->render();
        EndTextureMode();
        int width = GetScreenWidth();
        int height = GetScreenHeight();
        Rectangle screen{0, 0, (float)width, (float)height};
        Rectangle src{0, HEIGHT, WIDTH, -HEIGHT};
        Rectangle dst = Util::fit(WIDTH, HEIGHT, screen);
        DrawTexturePro(buffer.texture, src, dst, Vector2Zero(), 0, WHITE);
        EndDrawing();
    }
    UnloadTexture(font);
    CloseWindow();
    return 0;
}
