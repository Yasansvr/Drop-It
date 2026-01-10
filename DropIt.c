#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
#include "raylib.h"
#include<stdio.h>


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    int redscore = 0;
    int bluescore = 0;

    bool start = false;
    bool shot = false;
    bool shotblue = false;
    bool draw =false;
    bool bluewin = false;
    bool redwin = false;
    
    Vector2 Circle1 = {300,400};
    Vector2 Circle2 = {500,400};

    Rectangle rect = {350,100,20,20};
    
    float speed = 50.0f;
    float x,y;
    float timescore = GetFrameTime();
    float timeLeft;
    Vector2 red = {x,y};
    Vector2 blue = {x,y};
    

    InitWindow(screenWidth, screenHeight, "DROP IT");
    Vector2 redwins = MeasureTextEx(GetFontDefault(),"RED WINS!",20,3);
    Vector2 bluewins = MeasureTextEx(GetFontDefault(),"BLUE WINS!",20,3);
    Vector2 draw1 =  MeasureTextEx(GetFontDefault(),"DRAW",20,3);
    Vector2 Starter = MeasureTextEx(GetFontDefault(),"PRESS ENTER TO START!",20,3);
    Texture2D redball = LoadTexture("assets/redball.png");
    Texture2D blueball = LoadTexture("assets/blueball.png");


    SetTargetFPS(60); 
    while (!WindowShouldClose())
    {
    
        if (IsKeyPressed(KEY_ENTER) && !start){
            draw = false;
            redwin = false;
            bluewin = false;
            timeLeft = 10.0f;
            redscore = 0;
            bluescore = 0;
            start = true;
        } 
        if (start)
        {   
            if (timeLeft > 0.0f)
            {
            timeLeft -= GetFrameTime(); 
            if (timeLeft < 0.0f) timeLeft = 0.0f;  
            }
            if (timeLeft <= 0 && (redscore==0 && bluescore==0)|| timeLeft <= 0 && (redscore == bluescore))
            {
                draw = true;
            }
            if (draw)
            {
                start = false;
                shot = false;
                shotblue = false;
                Circle1.x =300, Circle1.y= 400;
                Circle2.x = 500, Circle2.y = 400;

            }
            
            if (timeLeft == 0 && redscore > bluescore) {
                redwin=true;
                shot = false;
                shotblue = false;
                Circle1.x =300, Circle1.y= 400;
                Circle2.x = 500, Circle2.y = 400;
            }
            if (timeLeft == 0 && redscore < bluescore) {
                bluewin=true;
                shot = false;
                shotblue = false;
                Circle1.x =300, Circle1.y= 400;
                Circle2.x = 500, Circle2.y = 400;
            }
            if (timeLeft > 0 )
            {
                if (CheckCollisionCircles(Circle1, 10, blue, 10)) bluescore++;
                if (CheckCollisionCircles(Circle2, 10, red, 10)) redscore++;
            }
            
            
            if (IsKeyDown(KEY_W))Circle1.y -= 10;
            if (IsKeyDown(KEY_S))Circle1.y += 10;
            if (IsKeyDown(KEY_D))Circle1.x += 10;
            if (IsKeyDown(KEY_A))Circle1.x -= 10;
            if(IsKeyPressed(KEY_SPACE)) {
                shot = true;
                red.x = Circle1.x;
                red.y = Circle1.y;
            }
            
            if (IsKeyDown(KEY_UP))Circle2.y -= 10;
            if (IsKeyDown(KEY_DOWN))Circle2.y += 10;
            if (IsKeyDown(KEY_RIGHT))Circle2.x += 10;
            if (IsKeyDown(KEY_LEFT))Circle2.x -= 10;
            if(IsKeyPressed(KEY_RIGHT_SHIFT)) {
                shotblue = true;
                blue.x = Circle2.x;
                blue.y = Circle2.y;
            }
        }
    
    
    
        
    
    
    
        
        BeginDrawing();
            if (!start){
                ClearBackground(RAYWHITE);
                DrawText("PRESS ENTER TO START!", (screenWidth-Starter.x)/2,(screenHeight-Starter.y)/2, 20, LIGHTGRAY);
        
            }

            if (draw)
            {
                ClearBackground(DARKGRAY);
                DrawText("DRAW", (screenWidth-draw1.x)/2,(screenHeight-draw1.y)/2 - 40, 20, LIGHTGRAY);
            }

            if (start){
                for (int y = 0; y <=800; y+=40)
                {
                    for (int x = 0; x <= 800; x+=40)
                    {
                        DrawRectangleLines(y,x, 40, 40, DARKGRAY);
                    }
                }
                DrawTextEx(GetFontDefault(),TextFormat("Time : %.1f",timeLeft),(Vector2){20,20},20,3,WHITE);
                DrawTextEx(GetFontDefault(),TextFormat("Blue : %d",bluescore),(Vector2){20,60},20,3,BLUE);
                DrawTextEx(GetFontDefault(),TextFormat("Red : %d",redscore),(Vector2){20,100},20,3,RED);
                ClearBackground(BLACK);
                DrawCircleV(Circle1,10,WHITE);
                DrawCircleV(Circle2,10,WHITE);
                DrawLineV(Circle1,Circle2,WHITE);
                
                if (shot)
                {
                DrawLineV(Circle1,red,WHITE);
                DrawTexture(redball,red.x-10,red.y-10,WHITE);
                }
                if (shotblue)
                {
                DrawLineV(Circle2,blue,WHITE);
                DrawTexture(blueball,blue.x-10,blue.y-10,WHITE);
                }
                
            }
            
            if (redwin) {
                DrawText("RED WINS!",(screenWidth-redwins.x)/2,(screenHeight-redwins.y)/2 -40,20,RED);
                start = false;
            }
            if (bluewin) {
                DrawText("BLUE WINS!",(screenWidth-bluewins.x)/2,(screenHeight-bluewins.y)/2 -40,20,BLUE);
                start = false;
            }
                
            
            
        EndDrawing();
    }
    
    CloseWindow();   
    

    return 0;
}