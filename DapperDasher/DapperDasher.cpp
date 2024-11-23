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

    const int size_of_nebulae{ 3};
    
    // Array of nebulae properties   
    anim_data nebulae[size_of_nebulae]{};

    for (int i = 0; i < size_of_nebulae; i++)
    {
        nebulae[i].rec.x = 0;
        nebulae[i].rec.y = 0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = window_dimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].running_time = 0.0f;
        nebulae[i].update_time = 1.0/16.0;
    }

    nebulae[0].pos.x = window_dimensions[0];
    nebulae[1].pos.x = window_dimensions[0] + 300;
    nebulae[2].pos.x = window_dimensions[0] + 600;
    
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

        for (int i = 0; i < size_of_nebulae; i++)
        {
            //Update Nebula position
            nebulae[i].pos.x += nebula_vel * dT;
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
        
        for (int i = 0; i < size_of_nebulae; i++)
        {
            //Update Nebula running time, set frame speed
            nebulae[i].running_time += dT;
            if (nebulae[i].running_time >= nebulae[i].update_time)
            {
                nebulae[i].running_time = 0.0f;
                //Update animation frame
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if(nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                }
            }  
        }
       
       for (int i = 0; i < size_of_nebulae; i++)
       {
           //Draw Nebula
           DrawTextureRec(nebula,nebulae[i].rec,nebulae[i].pos,WHITE);
       }     
        
        //Draw Scarfy
        DrawTextureRec(scarfy,scarfy_data.rec,scarfy_data.pos,WHITE);
        
        // Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy); 
    UnloadTexture(nebula); 
    CloseWindow();
}
