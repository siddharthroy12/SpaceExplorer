#include "../libs/raylib/src/raylib.h"
#include "helper.hpp"
#include "Game.hpp"

Game *game;

void loop() {
#if defined(PLATFORM_WEB)
    static int old_w=0,old_h=0;

    int w = getWindowWidth();
    int h = getWindowHeight();
    if(w!=old_w || h!=old_h){ SetWindowSize(w,h); }
#endif
    game->loop();
}

int main(void) {
    // Setup window
    SetConfigFlags(FLAG_MSAA_4X_HINT);
#if defined(PLATFORM_WEB)
    InitWindow(getBrowserWindowWidth(), getBrowserWindowHeight(), PROJECT_NAME);
#else
    InitWindow(800, 500, PROJECT_NAME);
#endif
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);

    SetExitKey(0);

    game = new Game();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(loop, 0, 1);
#else
    while (game->running && !WindowShouldClose()) {
        loop();
    }
#endif

    // Cleanup
    delete game;
    CloseWindow();
    return 0;
}
