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

    // Nebula properties
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebula_rec;
    nebula_rec.width = nebula.width/8;
    nebula_rec.height = nebula.height/8;
    nebula_rec.x = 0;
    nebula_rec.y = 0;
    Vector2 nebula_pos;
    nebula_pos.x = window_width;
    nebula_pos.y = window_height - nebula_rec.height;
    //Nebula animation properties
    int nebula_frame {};
    const float nebula_update_time {1.0f/12.0f};
    float nebula_running_time {0.0f};
    
    //Nebula Velocity
    int nebula_vel {-200};

    //Animation frame
    int frame{};
    //Amount of time before we update the animation frame
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
            //Scarfy is on the ground
            velocity = 0;
            is_in_air = false;
        }
        else
        {
            // Scarfy is on air
            //Apply gravity 
            velocity += gravity * dT;
            is_in_air = true;
        }

        // Rectangle Jump on key
        if (IsKeyPressed(KEY_SPACE) && !is_in_air) 
         {
            velocity += jump_vel;
        }
        
        // Update scarfy position
        scarfy_pos.y += velocity * dT;

        //Update Nebula position
        nebula_pos.x += nebula_vel * dT;

        //Update Nebula running time, set frame speed
        nebula_running_time += dT;
        if (nebula_running_time >= nebula_update_time)
        {
            nebula_running_time = 0.0f;
            //Update animation frame
            nebula_rec.x = nebula_frame * nebula_rec.width;
            nebula_frame++;
            if(nebula_frame > 7)
            {
                nebula_frame = 0;
            }
        }
        
        // Update Scarfy running time, set frame speed
        running_time += dT; 
        if (running_time >= update_time)
        {
            running_time = 0.0f; // reset frame loop

            if (!is_in_air) // check if it's jumping and freezes frame
            {
                //Update animation frame
                scarfy_rec.x = frame * scarfy_rec.width;
                frame++;
                if (frame > 5 )
                {
                    frame = 0;
                }
            }
    
            }
            
        //Draw Nebula
        DrawTextureRec(nebula,nebula_rec,nebula_pos,WHITE);
        
        //Draw Scarfy
        DrawTextureRec(scarfy,scarfy_rec,scarfy_pos,WHITE);
        
        // Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy); 
    UnloadTexture(nebula); 
    CloseWindow();
}
