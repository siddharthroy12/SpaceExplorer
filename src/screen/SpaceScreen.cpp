#include "SpaceScreen.hpp"
#include "../helper.hpp"
#include "../perlin.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

#define LAYER_2_CHUNK_SIZE 500
#define WORLD_SiZE 10000

Playthrough::Playthrough(SpaceScreen* context, int seed) {
    this->seed = seed;
    srand(seed);

    // The amount of plants and astroids each start system will have
    // Planets, astroids
    int fillAmounts[4][2] = {
        {3, 4},
        {4, 5},
        {5, 6},
        {6, 7},
    };

    for (int i = 0; i < 5; i++) {
        StarSystem starSystem;
        // Generate planets
        for (int j = 0; j < fillAmounts[i][0]; j++) {
            Planet planet;
            planet.position.x = GetRandomValue((-WORLD_SiZE/2)+200, (WORLD_SiZE/2)-200);
            planet.position.y = GetRandomValue((-WORLD_SiZE/2)+200, (WORLD_SiZE/2)-200);
            starSystem.planets.push_back(planet);
        }

        // Generate astroids
        for (int j = 0; j < fillAmounts[i][1]; j++) {
            Astroid astroid(context, {(float)GetRandomValue((-WORLD_SiZE/2)+200, (WORLD_SiZE/2)-200), (float)GetRandomValue((-WORLD_SiZE/2)+200, (WORLD_SiZE/2)-200)}, AstroidSize::BIG);
            starSystem.astroids.push_back(astroid);
        }

        this->starSystems.push_back(starSystem);
    }
}

Vector2 worldToMap(Vector2 objectPosition, Vector2 playerPosition, bool center) {
    int miniMapSize = (!center) ? MINIMAP_EXPAND_SIZE : MINIMAP_SIZE;
    Rectangle miniMapRectange = {
        (float)(getWindowWidth() - (miniMapSize+10)),
        (float)(10),
        (float)(miniMapSize),
        (float)(miniMapSize),
    };

    Vector2 centerOfMiniMap = {miniMapRectange.x + miniMapRectange.width/2, miniMapRectange.y + miniMapRectange.height/2};

    Vector2 objectPositionInMap = Vector2Add(centerOfMiniMap,Vector2Multiply(Vector2Divide(objectPosition, {WORLD_SiZE, WORLD_SiZE}), {MINIMAP_EXPAND_SIZE, MINIMAP_EXPAND_SIZE}));

    if (center) {
        Vector2 playerPositionInMap = Vector2Add(centerOfMiniMap,Vector2Multiply(Vector2Divide(playerPosition, {WORLD_SiZE, WORLD_SiZE}), {MINIMAP_EXPAND_SIZE, MINIMAP_EXPAND_SIZE}));
        Vector2 centerToPlayer = Vector2Subtract(centerOfMiniMap, playerPositionInMap);
        objectPositionInMap = Vector2Add(objectPositionInMap, centerToPlayer);
    }

    return objectPositionInMap;
}

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
    this->camera.zoom = 1.3;
    this->camera.rotation = 0;
    DisableCursor();

   this->playthrough = new Playthrough(this, 10);
}

void SpaceScreen::loop() {
    // Update

    // Limit cursor position
    if (GetMousePosition().x < 0) {
        SetMousePosition(0, GetMousePosition().y);
    }
    if (GetMousePosition().x > getWindowWidth()) {
        SetMousePosition(getWindowWidth(), GetMousePosition().y);
    }
    if (GetMousePosition().y < 0) {
        SetMousePosition(GetMousePosition().x, 0);
    }
    if (GetMousePosition().y > getWindowHeight()) {
        SetMousePosition(GetMousePosition().x, getWindowHeight());
    }

    if (IsKeyPressed(KEY_TAB)) {
        this->miniMapExpand = !this->miniMapExpand;
    }

    // This fixes camera's aspect ratio when the window is resized
    this->camera.offset = {(float)getWindowWidth()/2, (float)getWindowHeight()/2};

    // Make camera follow player
    float cameraSpeed = GetFrameTime() * 6;
    this->camera.target = Vector2Add(this->player->position, Vector2Scale(this->player->velocity, 0.3));


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
                this->backgrounds.insert({key, generateBackgroundTextureChunk(i, j, this->playthrough->seed)});
            }
        }
    }

    // Update in game objects
    player->update();

    for (auto& bullet : this->bullets) {
        bullet.update();
    }

   // Remove dead bullets
    bullets.erase(
        std::remove_if(
            bullets.begin(),
            bullets.end(),
            [&](Bullet& bullet) {
                return bullet.isDead;
            }
        ),
        bullets.end()
    );

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

    // Draw boundry
    DrawRectangleLines(-(WORLD_SiZE/2), -(WORLD_SiZE/2), WORLD_SiZE, WORLD_SiZE, WHITE);

    // Draw Planets
    for (auto& planet : this->playthrough->starSystems[this->playthrough->currentStarSystem].planets) {
        DrawTexturePro(
            this->context->asset.planetEarth,
            {
                .x = 0,
                .y = 0,
                .width = (float)this->context->asset.planetEarth.width,
                .height = (float)this->context->asset.planetEarth.height
            },
            {
                .x = planet.position.x,
                .y = planet.position.y,
                .width = (float)this->context->asset.planetEarth.width,
                .height = (float)this->context->asset.planetEarth.height,
            },
            {
                (float)this->context->asset.planetEarth.width/2,
                (float)this->context->asset.planetEarth.height/2
            },
            0,
            WHITE
        );
    }

    // Draw astroids
    for (auto& astroid : this->playthrough->starSystems[this->playthrough->currentStarSystem].astroids) {
        astroid.draw();
    }

    // Draw player
    player->draw();

    for (auto& bullet : this->bullets) {
        bullet.draw();
    }

    EndMode2D();

    // Draw UI

    // Draw MiniMap
    int miniMapSize = this->miniMapExpand ? MINIMAP_EXPAND_SIZE : MINIMAP_SIZE;
    Rectangle miniMapRectange = {
        (float)(getWindowWidth() - (miniMapSize+10)),
        (float)(10),
        (float)(miniMapSize),
        (float)(miniMapSize),
    };
    Vector2 centerOfMiniMap = {miniMapRectange.x + miniMapRectange.width/2, miniMapRectange.y + miniMapRectange.height/2};

    // Draw background of map
    DrawRectangleRec(miniMapRectange, {33, 33, 33, 255});

    // Draw Inside map
    BeginScissorMode(miniMapRectange.x, miniMapRectange.y, miniMapRectange.width, miniMapRectange.height);

    // Draw Player
    Vector2 playerPositionInMap = worldToMap(this->player->position, this->player->position, !this->miniMapExpand);
    Vector2 mousePositionInWorld = GetScreenToWorld2D(GetMousePosition(), this->camera);

    Vector2 playerToMouse = Vector2Subtract(this->player->position, mousePositionInWorld);

    float rotation = Vector2Angle({0, 0}, playerToMouse);

    DrawTexturePro(
        this->context->asset.minimapPlayer,
        {
            .x = 0,
            .y = 0,
            .width = (float)this->context->asset.minimapPlayer.width,
            .height = (float)this->context->asset.minimapPlayer.height
        },
        {
            .x = playerPositionInMap.x,
            .y = playerPositionInMap.y,
            .width = (float)this->context->asset.minimapPlayer.width,
            .height = (float)this->context->asset.minimapPlayer.height,
        },
        {
            (float)this->context->asset.minimapPlayer.width/2,
            (float)this->context->asset.minimapPlayer.height/2
        },
        (rotation*RAD2DEG) - 90.0f,
        WHITE
    );

    // Draw planets
    for (auto& planet : this->playthrough->starSystems[this->playthrough->currentStarSystem].planets) {
        Vector2 planetPosition = worldToMap(planet.position, this->player->position, !this->miniMapExpand);
        DrawCircleV(planetPosition, 5, GRAY);
    }

    // Draw Astroids
    for (auto& astroid : this->playthrough->starSystems[this->playthrough->currentStarSystem].astroids) {
        Vector2 astroidPosition = worldToMap(astroid.position, this->player->position, !this->miniMapExpand);
        DrawCircleV(astroidPosition, 2, GRAY);
    }

    EndScissorMode();

    // Draw Map border
    DrawRectangleLinesEx(miniMapRectange, 1, WHITE);

    // Draw cursor
    DrawTexturePro(
        this->context->asset.cursor,
        {
            .x = 0,
            .y = 0,
            .width = (float)this->context->asset.cursor.width,
            .height = (float)this->context->asset.cursor.height
        },
        {
            .x = GetMousePosition().x,
            .y = GetMousePosition().y,
            .width = (float)this->context->asset.cursor.width,
            .height = (float)this->context->asset.cursor.height,
        },
        {
            (float)this->context->asset.cursor.width/2,
            (float)this->context->asset.cursor.height/2
        },
        (rotation*RAD2DEG) - 90.0f,
        WHITE
    );

    EndDrawing();
}

SpaceScreen::~SpaceScreen() {
    delete this->player;
    delete this->playthrough;
}

