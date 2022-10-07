#include "../libs/raylib/src/raylib.h"
#include "helper.hpp"

Texture2D texture;

void loop() {
#if defined(PLATFORM_WEB)
    static int old_w=0,old_h=0;

    int w = getWindowWidth();
    int h = getWindowHeight();
    if(w!=old_w || h!=old_h){ SetWindowSize(w,h); }
#endif

    BeginDrawing();

    ClearBackground(RAYWHITE);

    const int texture_x = getWindowWidth() / 2 - texture.width / 2;
    const int texture_y = getWindowHeight()/ 2 - texture.height / 2;
    DrawTexture(texture, texture_x, texture_y, WHITE);

    const char* text = "OMG! IT WORKS!";
    const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
    DrawText(text, getWindowWidth() / 2.0 - text_size.x / 2, texture_y + texture.height + text_size.y + 10, 20, BLACK);

    EndDrawing();

}

int main(void) {
    // Setup window
#if defined(PLATFORM_WEB)
    InitWindow(getBrowserWindowWidth(), getBrowserWindowHeight(), PROJECT_NAME);
#else
    InitWindow(800, 500, PROJECT_NAME);
#endif
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);

    // Setup assets
    texture = LoadTexture("assets/test.png");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(loop, 0, 1);
#else
    while (!WindowShouldClose()) {
        loop();
    }
#endif

    // Cleanup
    CloseWindow();
    return 0;
}
