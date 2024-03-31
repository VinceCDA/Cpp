#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include <string>
#include <vector>
using namespace std;

bool IsAllEnemiesDead(vector<Enemy *> v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i]->GetAlive())
        {
            return false;
        }
    }
    return true;
}

int main()
{
    // Window dimensions
    const int windowWidth{384};
    const int windowHeight{384};

    // Initialize window
    InitWindow(windowWidth, windowHeight, "TopDown");

    // Loading textures
    Texture2D mapTexture = LoadTexture("./nature_tileset/OpenWorldMap24x24.png");
    Texture2D rockTexture = LoadTexture("./nature_tileset/Rock.png");
    Texture2D logTexture = LoadTexture("./nature_tileset/Log.png");
    Texture2D knightTextureIdle = LoadTexture("./characters/knight_idle_spritesheet.png");
    Texture2D knightTextureRun = LoadTexture("./characters/knight_run_spritesheet.png");
    Texture2D swordTexture = LoadTexture("./characters/weapon_sword.png");
    Texture2D goblinTextureIdle = LoadTexture("./characters/goblin_idle_spritesheet.png");
    Texture2D goblinTextureRun = LoadTexture("./characters/goblin_run_spritesheet.png");
    Texture2D slimeTextureIdle = LoadTexture("./characters/slime_idle_spritesheet.png");
    Texture2D slimeTextureRun = LoadTexture("./characters/slime_run_spritesheet.png");

    //  Loading character
    Character knight{&knightTextureIdle, &knightTextureRun, &swordTexture, windowWidth, windowHeight};
    Enemy goblin{Vector2{800.0f, 300.0f}, &goblinTextureIdle, &goblinTextureRun};
    Enemy slime{Vector2{500.0f, 700.0f}, &slimeTextureIdle, &slimeTextureRun};
    vector<Enemy *> enemies{&goblin, &slime};
    for (auto enemy : enemies)
    {
        enemy->SetTarget(&knight);
    }

    Prop props[2]{
        Prop{Vector2{600.0f, 300.0f}, &rockTexture},
        Prop{Vector2{400.0f, 500.0f}, &logTexture}};

    Vector2 mapPosition{0.0, 0.0};
    const float mapScale{4.0f};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);
        // Draw maps and props
        mapPosition = Vector2Scale(knight.GetWorldPosition(), -1.0f);
        DrawTextureEx(mapTexture, mapPosition, 0.0, mapScale, WHITE);        
        for (auto prop : props)
        {
            prop.Render(knight.GetWorldPosition());
        }

        // Check win/lose condtions.
        if (!knight.GetAlive())
        {
            DrawText("Game Over !", 55.0f, 45.0f, 40, RED);
            EndDrawing();
            continue;
        }
        else if (IsAllEnemiesDead(enemies))
        {
            DrawText("You Win !", 55.0f, 45.0f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            string knightHealth = "Health: ";
            knightHealth.append(to_string(knight.GetHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.0f, 45.0f, 40, RED);
        }

        // Update behavior
        knight.Tick(GetFrameTime());
        for (auto enemy : enemies)
        {
            enemy->Tick(GetFrameTime());

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (CheckCollisionRecs(enemy->GetCollisionRectangle(), knight.GetWeaponCollisionRectangle()))
                {
                    enemy->SetAlive(false);
                }
            }
        }

        // Check map bounds.
        if (knight.GetWorldPosition().x < 0.0f ||
            knight.GetWorldPosition().y < 0.0f ||
            knight.GetWorldPosition().x + windowWidth > mapTexture.width * mapScale ||
            knight.GetWorldPosition().y + windowHeight > mapTexture.height * mapScale)
        {
            knight.UndoMovement();
        }

        // Check props collision.
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.GetCollisionRectangle(knight.GetWorldPosition()), knight.GetCollisionRectangle()))
            {
                knight.UndoMovement();
            }
        }

        // Stop drawing
        EndDrawing();
    };
    UnloadTexture(mapTexture);
    UnloadTexture(rockTexture);
    UnloadTexture(knightTextureIdle);
    UnloadTexture(knightTextureRun);
    UnloadTexture(swordTexture);
    UnloadTexture(goblinTextureIdle);
    UnloadTexture(goblinTextureRun);
    UnloadTexture(slimeTextureIdle);
    UnloadTexture(slimeTextureRun);
    CloseWindow();
}
