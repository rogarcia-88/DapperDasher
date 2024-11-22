#include "raylib.h"

struct anim_data
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float update_time;
    float running_time;
};
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
    
    
    // Nebula properties
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // Nebula AnimData
    anim_data nebula_data {
        {0,0,nebula.width/8,nebula.height/8}, //Rectangle rec
        {window_dimensions[0], window_dimensions[1] - nebula.height/8}, // Vector2 pos
        0, //int frame
        1.0 / 12.0, //float update time
        0 //float running time
    };

    anim_data nebula2_data {
    {0, 0, nebula.width/8,nebula.height/8 },
    {window_dimensions[0] + 300, window_dimensions[1] - nebula.height/8},
    0,
    1.0 / 16.0,
    0
        
    };
    
    
    //Nebula Velocity
    int nebula_vel {-200};

   
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
        if (scarfy_data.pos.y >= window_dimensions[1] - scarfy_data.rec.height)
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
        scarfy_data.pos.y += velocity * dT;

        //Update Nebula position
        nebula_data.pos.x += nebula_vel * dT;
        
        //Update Nebula 2 position
        nebula2_data.pos.x += nebula_vel * dT;

        //Update Nebula running time, set frame speed
        nebula_data.running_time += dT;
        if (nebula_data.running_time >= nebula_data.update_time)
        {
            nebula_data.running_time = 0.0f;
            //Update animation frame
            nebula_data.rec.x = nebula_data.frame * nebula_data.rec.width;
            nebula_data.frame++;
            if(nebula_data.frame > 7)
            {
                nebula_data.frame = 0;
            }
        }

        //Update Nebula running time, set frame speed
        nebula2_data.running_time += dT;
        if (nebula2_data.running_time >= nebula2_data.update_time)
        {
            nebula2_data.running_time = 0.0f;
            nebula2_data.rec.x = nebula2_data.frame * nebula2_data.rec.width;
            nebula2_data.frame++;
            if(nebula2_data.frame > 7)
            {
                nebula2_data.frame = 0;
            }
        }
        
        // Update Scarfy running time, set frame speed
        scarfy_data.running_time += dT; 
        if (scarfy_data.running_time >= scarfy_data.update_time)
        {
            scarfy_data.running_time = 0.0f; // reset frame loop

            if (!is_in_air) // check if it's jumping and freezes frame
            {
                //Update animation frame
                scarfy_data.rec.x = scarfy_data.frame * scarfy_data.rec.width;
                scarfy_data.frame++;
                if (scarfy_data.frame > 5 )
                {
                    scarfy_data.frame = 0;
                }
            }
    
            }
            
        //Draw Nebula
        DrawTextureRec(nebula,nebula_data.rec,nebula_data.pos,WHITE);

        //Draw Nebula2
        DrawTextureRec(nebula,nebula2_data.rec,nebula2_data.pos,WHITE);
        
        //Draw Scarfy
        DrawTextureRec(scarfy,scarfy_data.rec,scarfy_data.pos,WHITE);
        
        // Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy); 
    UnloadTexture(nebula); 
    CloseWindow();
}
