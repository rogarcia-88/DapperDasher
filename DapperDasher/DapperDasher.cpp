#include "raylib.h"

int main()
{
    // Window Dimensions
    constexpr int window_width  {512};
    constexpr int window_height {380};

    // Initialize Window
    InitWindow(window_width, window_height, "Dapper Dasher!");

    // Acceleration due to gravity (pixels/sec)/s 
    constexpr int gravity{ 1'000 };

    // Scarfy properties
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfy_rec;
    scarfy_rec.width = scarfy.width/6;
    scarfy_rec.height = scarfy.height;
    scarfy_rec.x = 0;
    scarfy_rec.y = 0;
    Vector2 scarfy_pos;
    scarfy_pos.x = window_width / 2 - scarfy_rec.width / 2;
    scarfy_pos.y = window_height - scarfy_rec.height;

    //Animation frame
    int frame{};
    const float update_time { 1.0f / 12.0f };
    float running_time{ 0.0f };

    // is the rectangle in the air?
    bool is_in_air;
    // jump velocity pixels/s
    constexpr int jump_vel{ -600 };

    int velocity{ 0 };
    
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //Get Delta Time (time since last frame)
        const float dT{ GetFrameTime()};
          
        //Perform ground check
        if (scarfy_pos.y >= window_height - scarfy_rec.height)
        {
            //rectangle is on the ground
            velocity = 0;
            is_in_air = false;
        }
        else
        {
            // rectangle is on air
            //Apply gravity 
            velocity += gravity * dT;
            is_in_air = true;
        }

        // Rectangle Jump on key
        if (IsKeyPressed(KEY_SPACE) && !is_in_air) 
         {
            velocity += jump_vel;
        }
        
       // Update position
        scarfy_pos.y += velocity * dT;

        running_time += dT; // set frame speed
        if (running_time >= update_time)
        {
            running_time = 0.0f; // reset frame loop

            //Update animation frame
            scarfy_rec.x = frame * scarfy_rec.width;
            frame++;
            if (frame > 5)
            {
                frame = 0;
            }
        }

        
        
        DrawTextureRec(scarfy,scarfy_rec,scarfy_pos,WHITE);

        // Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy); 
    CloseWindow();
}
