#include "MainScreen.hpp"
#include "../ui/button.hpp"
#include "../helper.hpp"
#include <memory>
#include "SpaceScreen.hpp"

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_MARGIN 10

MainScreen::MainScreen(Game *context) : Screen(context) {
    std::cout << "Main Screen enter" << std::endl;
}

void MainScreen::loop() {
    // Get the center of screen
    Vector2 centerOfScreen;
    centerOfScreen.x = getWindowWidth() / 2.0;
    centerOfScreen.y = getWindowHeight() / 2.0;

    BeginDrawing();
    ClearBackground({18, 18, 18, 255});


    // Draw Background
    Rectangle source = { 0, 0, (float)this->context->asset.titleBackgorund.width, (float)this->context->asset.titleBackgorund.height };
    float aspectRatio = source.width/source.height;
    float width = getWindowWidth();
    float height = width/aspectRatio;
    if (height < getWindowHeight()) {
        height = getWindowHeight();
        width = height*aspectRatio;
    }
    Rectangle dest = {centerOfScreen.x - width/2, centerOfScreen.y - height/2, width, height};
    // DrawTexturePro(this->context->asset.titleBackgorund, source, dest, {0, 0}, 0, WHITE);

    // Draw UI
    // Title
    Vector2 titleTextSize = MeasureTextEx(context->asset.font, PROJECT_NAME, 40, 0);
    Vector2 titlePosition;
    titlePosition.x = centerOfScreen.x - (titleTextSize.x/2.0);
    titlePosition.y = 100;
    DrawTextEx(context->asset.font, PROJECT_NAME, titlePosition, 40, 0, WHITE);

    // Start button
    Vector2 buttonPosition;
    buttonPosition.x = centerOfScreen.x - (BUTTON_WIDTH/2.0);
    buttonPosition.y = 250;

    Vector2 buttonSize;
    buttonSize.x = BUTTON_WIDTH;
    buttonSize.y = BUTTON_HEIGHT;

    if (button(context, "Start", buttonPosition, buttonSize)) {
        std::cout << "Start Clicked" << std::endl;
        context->changeCurrentScreen(std::shared_ptr<Screen>(new SpaceScreen(context)));
    }

    buttonPosition.y += BUTTON_MARGIN + BUTTON_HEIGHT;

    if (button(context, "Continue", buttonPosition, buttonSize)) {
        std::cout << "Continue Clicked" << std::endl;
    }

    buttonPosition.y += BUTTON_MARGIN + BUTTON_HEIGHT;

    if (button(context, "Exit", buttonPosition, buttonSize)) {
        this->context->running = false;
    }

    EndDrawing();
}

MainScreen::~MainScreen() {
    std::cout << "Main Screen leaves" << std::endl;
}
