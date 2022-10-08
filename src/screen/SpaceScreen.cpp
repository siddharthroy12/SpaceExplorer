#include "SpaceScreen.hpp"
#include "../helper.hpp"
#include "../perlin.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>

#define LAYER_2_CHUNK_SIZE 500

RenderTexture generateBackgroundTextureChunk(int x, int y, int seed) {
    srand(seed + x + y);

    RenderTexture background = LoadRenderTexture(LAYER_2_CHUNK_SIZE, LAYER_2_CHUNK_SIZE);

    BeginTextureMode(background);

    for (int i = 0; i < 50; i++) {
        float _x = rand() % LAYER_2_CHUNK_SIZE;
        float _y = rand() % LAYER_2_CHUNK_SIZE;
        DrawPixel(_x, _y, WHITE);
    }

    EndTextureMode();
    return background;
}

SpaceScreen::SpaceScreen(Game* context) : Screen(context) {
    this->player = new Player(this);

    // Setup camera
    this->camera.target = {0, 0};
    this->camera.offset = {(float)getWindowWidth()/2, (float)getWindowHeight()/2};
    this->camera.zoom = 1.2;
    this->camera.rotation = 0;

}

void SpaceScreen::loop() {
    // Update
    this->camera.offset = {(float)getWindowWidth()/2, (float)getWindowHeight()/2};
    // Make camera follow player
    float cameraSpeed = GetFrameTime() * 6;
    this->camera.target = Vector2Add(this->player->position, Vector2Scale(this->player->velocity, 1));

    player->update();

    // ---- LAYER 2 ----
    Vector2 layer2Origin = {this->camera.target.x*(float)0.99, this->camera.target.y*(float)0.99};
    Vector2 layer2OriginToTarget = Vector2Subtract(this->camera.target, layer2Origin);
    int currentChunkX = (int)(layer2OriginToTarget.x/LAYER_2_CHUNK_SIZE) - (layer2OriginToTarget.x < 0 ? 1 : 0);
    int currentChunkY = (int)(layer2OriginToTarget.y/LAYER_2_CHUNK_SIZE) - (layer2OriginToTarget.y < 0 ? 1 : 0);

    // Unload out of range chunks
    std::vector<std::string> chunksToUnload;

    for (auto &pair : this->backgrounds) {
        int chunkX = atoi(pair.first.substr(0, pair.first.find("|")).c_str());
        int chunkY = atoi(pair.first.substr(pair.first.find("|")+1, pair.first.size()).c_str());

        if (chunkX < currentChunkX - 2 ||
            chunkY < currentChunkY - 2 ||
            chunkX > currentChunkX + 2 ||
            chunkY > currentChunkY + 2) {
            chunksToUnload.push_back(pair.first);
            UnloadRenderTexture(pair.second);
        }
    }

    for (auto &chunk : chunksToUnload) {
        this->backgrounds.erase(chunk);
    }

    // Load new chunks
    for (int i = currentChunkX-2; i < currentChunkX+2; i++) {
        for (int j = currentChunkY-2; j < currentChunkY+2; j++) {
            std::string key = std::to_string(i) + std::string("|") + std::to_string(j);

            if (this->backgrounds.find(key) == this->backgrounds.end()) {
                this->backgrounds.insert({key, generateBackgroundTextureChunk(i, j, this->seed)});
            }
        }
    }

    // Draw
    BeginDrawing();
    ClearBackground({18, 18, 18, 255});

    BeginMode2D(this->camera);

    // ---- LAYER 2 ----
    for (auto &pair : this->backgrounds) {
        int chunkX = atoi(pair.first.substr(0, pair.first.find("|")).c_str());
        int chunkY = atoi(pair.first.substr(pair.first.find("|")+1, pair.first.size()).c_str());
        float x = chunkX * LAYER_2_CHUNK_SIZE;
        float y = chunkY * LAYER_2_CHUNK_SIZE;
        DrawTextureEx(pair.second.texture, {layer2Origin.x+x, layer2Origin.y+y}, 0, 1, WHITE);

    }
    // DrawTextureEx(this->background.texture, layer2Origin, 0, 1, WHITE);

    // ---- LAYER 1 ----

    // Draw Planet
    DrawTexture(this->context->asset.planetEarth, 0, 0, WHITE);

    // Draw player
    player->draw();

    EndMode2D();

    // Draw UI
    int miniMapSize = 200;
    DrawRectangle(getWindowWidth() - (miniMapSize+10), 10, miniMapSize, miniMapSize, {18, 18, 18, 255});
    DrawRectangleLines(getWindowWidth() - (miniMapSize+10), 10, miniMapSize, miniMapSize, WHITE);

    EndDrawing();
}

SpaceScreen::~SpaceScreen() {
    delete this->player;
}

