#include "raylib.h"

struct AnimData
{
    Rectangle rectangle;
    Vector2 position;
    int frame;
    float updateTime;
    float runningTime;
};

/// @brief Check if the player character in on ground.
/// @param data 
/// @param windowHeight 
/// @return 
bool isOnGround(AnimData data, int windowHeight)
{
    return data.position.y >= windowHeight - data.rectangle.height;
}

/// @brief Update of the sprite sheets to make an animation.
/// @param data 
/// @param deltaTime 
/// @param maxFrame 
/// @return 
AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // Update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;

        data.rectangle.x = data.frame * data.rectangle.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    // Window dimensions
    const int windowWidth{512};
    const int windowHeight{380};
    // Initialize window
    InitWindow(windowWidth, windowHeight, "Dasher");

    // Loading textures
    Texture2D scarfy = LoadTexture("./textures/scarfy.png");
    Texture2D nebula = LoadTexture("./textures/12_nebula_spritesheet.png");
    Texture2D background = LoadTexture("./textures/far-buildings.png");
    Texture2D midground = LoadTexture("./textures/back-buildings.png");
    Texture2D foreground = LoadTexture("./textures/foreground.png");

    float backgroundX{};
    float midgroundX{};
    float foregroundX{};
 
    AnimData scarfyData;
    scarfyData.rectangle.width = scarfy.width / 6;
    scarfyData.rectangle.height = scarfy.height;
    scarfyData.rectangle.x = 0;
    scarfyData.rectangle.y = 0;
    scarfyData.position.x = windowWidth / 2 - scarfyData.rectangle.width / 2;
    scarfyData.position.y = windowHeight - scarfyData.rectangle.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    const int sizeNebulae{3};
    AnimData nebulae[sizeNebulae]{};
    for (int i = 0; i < sizeNebulae; i++)
    {
        nebulae[i].rectangle.x = 0.0;
        nebulae[i].rectangle.y = 0.0;
        nebulae[i].rectangle.width = nebula.width / 8;
        nebulae[i].rectangle.height = nebula.height / 8;
        nebulae[i].position.x = windowWidth + i * 300;
        nebulae[i].position.y = windowHeight - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 12.0;
    }

    
    // Game rules
    const int gravity{1000}; // Acceleration due to gravity (pixel/second)/second
    const int jumpVelocity{-600}; // (pixel/second)/second
    const int nebulaVelocity{-200}; // (pixel/second)/second
    int velocity{0};
    bool isInAir{false};
    bool collision{false};
    float finishLine{nebulae[sizeNebulae - 1].position.x};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Delta time (time since last frame)
        const float deltaTime{GetFrameTime()};

        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Moving background,midground and foreground textures.
        backgroundX -= 20 * deltaTime;
        if (backgroundX <= -background.width * 2)
        {
            backgroundX = 0.0;
        }
        midgroundX -= 40 * deltaTime;
        if (midgroundX <= -midground.width * 2)
        {
            midgroundX = 0.0;
        }
        foregroundX -= 80 * deltaTime;
        if (foregroundX <= -foreground.width * 2)
        {
            foregroundX = 0.0;
        }

        // Drawing background,midground and foreground textures.
        Vector2 background1Position{backgroundX, 0.0};
        Vector2 background2Position{backgroundX + background.width * 2, 0.0};
        DrawTextureEx(background, background1Position, 0.0, 2.0, WHITE);
        DrawTextureEx(background, background2Position, 0.0, 2.0, WHITE);

        Vector2 midground1Position{midgroundX, 0.0};
        Vector2 midground2Position{midgroundX + midground.width * 2, 0.0};
        DrawTextureEx(midground, midground1Position, 0.0, 2.0, WHITE);
        DrawTextureEx(midground, midground2Position, 0.0, 2.0, WHITE);

        Vector2 foreground1Position{foregroundX, 0.0};       
        Vector2 foreground2Position{foregroundX + foreground.width * 2, 0.0};
        DrawTextureEx(foreground, foreground1Position, 0.0, 2.0, WHITE);
        DrawTextureEx(foreground, foreground2Position, 0.0, 2.0, WHITE);


        // Ground check
        if (isOnGround(scarfyData, windowHeight))
        {
            isInAir = false;
            // rectangle on the ground
            velocity = 0;
        }
        else
        {
            isInAir = true;
            // Apply gravity
            velocity += gravity * deltaTime;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }

        // Update position
        scarfyData.position.y += velocity * deltaTime;
        for (int i = 0; i < sizeNebulae; i++)
        {
            nebulae[i].position.x += nebulaVelocity * deltaTime;
        }

        finishLine += nebulaVelocity * deltaTime;

        // Update scarfy animation frame
        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, deltaTime, 5);
        }

        // Update nebula animation frame
        for (int i = 0; i < sizeNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], deltaTime, 7);
        }

        for (AnimData nebula : nebulae)
        {
            
            float pad{50}; // Padding to make the collision box closer to the sprite.

            // Creation of collision box.
            Rectangle nebulaRec{
                nebula.position.x + pad,
                nebula.position.y + pad,
                nebula.rectangle.width - 2 * pad,
                nebula.rectangle.height - 2 * pad};
            Rectangle scarfyRectangle{
                scarfyData.position.x,
                scarfyData.position.y,
                scarfyData.rectangle.width,
                scarfyData.rectangle.height};

            if (CheckCollisionRecs(nebulaRec, scarfyRectangle))
            {
                collision = true;
            }
        }
        if (collision)
        {
            DrawText("Game Over !", windowWidth / 4, windowHeight / 2, 40, RED);
        }
        else if (scarfyData.position.x >= finishLine)
        {
            DrawText("You Win !", windowWidth / 4, windowHeight / 2, 40, RED);
        }

        else
        {
            // Draw scarfy
            DrawTextureRec(scarfy, scarfyData.rectangle, scarfyData.position, WHITE);
            // Draw nebula
            for (int i = 0; i < sizeNebulae; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rectangle, nebulae[i].position, WHITE);
            }
        }

        // Stop drawing
        EndDrawing();
    }
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}