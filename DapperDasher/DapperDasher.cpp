#include "raylib.h"

// Base struct for sprites properties
struct anim_data
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float update_time;
    float running_time;
};

// Ground check function
bool is_grounded(anim_data data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

// Update animation function
anim_data update_anim_data(anim_data data, float delta_time, int max_frame)
{
    //update anim frame
    data.running_time += delta_time;
    if (data.running_time >= data.update_time)
    {
        data.running_time = 0.0;
        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame >= max_frame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    int window_dimensions[2]; 
    window_dimensions[0] = 512;
    window_dimensions[1] = 380;
    
   

    // Initialize Window
    InitWindow(window_dimensions[0], window_dimensions[1], "Dapper Dasher!");

    // Acceleration due to gravity (pixels/sec)/s 
    constexpr int gravity{ 1'000 };

    // Scarfy properties
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    // Scarfy AnimData 
    anim_data scarfy_data;
    scarfy_data.rec.height = scarfy.width/6;
    scarfy_data.rec.width = scarfy.height;
    scarfy_data.rec.x = 0;
    scarfy_data.rec.y = 0;
    scarfy_data.pos.x = window_dimensions[0]/2 - scarfy_data.rec.width/2;
    scarfy_data.pos.y = window_dimensions[1]/2 - scarfy_data.rec.height;
    scarfy_data.frame = 0;
    scarfy_data.update_time = 1.0f/12.0f;
    scarfy_data.running_time = 0.0f;
    
    
    // Nebulae properties
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int size_of_nebulae{ 6}; // Edit for increase the amount of spawned nebulae
    
    // Array of nebulae properties   
    anim_data nebulae[size_of_nebulae]{};

    for (int i = 0; i < size_of_nebulae; i++)
    {
        nebulae[i].rec.x = 0;
        nebulae[i].rec.y = 0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.x = window_dimensions[0] + i * 300;
        nebulae[i].pos.y = window_dimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].running_time = 0.0f;
        nebulae[i].update_time = 1.0/16.0;
    }

    
    //Nebula Velocity
    int nebula_vel {-200};
   
    // is the rectangle in the air?
    bool is_in_air;
    // jump velocity pixels/s
    constexpr int jump_vel{ -600 };

    int velocity{ 0 };

    // Background
    Texture2D background = LoadTexture("textures/far-buildings.png");
    float background_tiling {};
   
    
    
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        //Get Delta Time (time since last frame)
        const float dT{ GetFrameTime()};
        
        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Draw the background
        background_tiling -= 20 * dT;
        if (background_tiling <= -background.width*2)
        {
            background_tiling = 0.0;
        }
        
        Vector2 background1_pos {background_tiling,0.0};
        DrawTextureEx(background, background1_pos, 0.0, 2, WHITE);
        Vector2 background2_pos {background_tiling + background.width*2,0.0};
        DrawTextureEx(background, background2_pos, 0.0, 2, WHITE);
                
        //Perform ground check
        if (is_grounded(scarfy_data, window_dimensions[1]))
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

        // Scarfy Jump on key
        if (IsKeyPressed(KEY_SPACE) && !is_in_air) 
         {
            velocity += jump_vel;
        }
        
        // Update Scarfy position
        scarfy_data.pos.y += velocity * dT;

        //Update Scarfy running time, set frame speed
        if (!is_in_air)
        {
            scarfy_data = update_anim_data(scarfy_data, dT, 5);
        }

        //Update Nebula position
        for (int i = 0; i < size_of_nebulae; i++)
        {
            nebulae[i].pos.x += nebula_vel * dT;
        }
        
        //Update Nebula running time, set frame speed
        for (int i = 0; i < size_of_nebulae; i++)
        {
            nebulae[i] = update_anim_data(nebulae[i], dT, 7);
        }

        //Draw Nebulae
       for (int i = 0; i < size_of_nebulae; i++)
       {
            DrawTextureRec(nebula,nebulae[i].rec,nebulae[i].pos,WHITE);
       }     
        
        //Draw Scarfy
        DrawTextureRec(scarfy,scarfy_data.rec,scarfy_data.pos,WHITE);
        
        // Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy); 
    UnloadTexture(nebula);
    UnloadTexture(background);
    CloseWindow();
}
