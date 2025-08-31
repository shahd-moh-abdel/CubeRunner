#include "raylib.h"
#include "../include/Cube.h"
#include <string>
#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 1200

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cube Runner");

  SetConfigFlags(FLAG_MSAA_4X_HINT);

  Camera3D camera = { 0 };
  camera.position = (Vector3){ 0.0f, 15.0f, 10.0f };  
  camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; 
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
  camera.fovy = 45.0f;                           
  camera.projection = CAMERA_PERSPECTIVE;

  Cube cube;
  
  SetTargetFPS(60);

  while(!WindowShouldClose())
    {
      cube.update(SCREEN_WIDTH);
      
      BeginDrawing();
      ClearBackground(SKYBLUE);

      BeginMode3D(camera);
      
      cube.draw();      
      DrawPlane({0.0f, 0.0f, 0.0f}, {50.0f, 50.0f}, DARKGREEN); 
 
      EndMode3D();

      DrawFPS(10, 10);

      std::string scoreText = "Score: " + std::to_string(cube.score);
      DrawText(scoreText.c_str(), SCREEN_WIDTH - 150, 10, 20, WHITE);

             // Game Over screen
        if (cube.gameOver) {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.7f));
            
            const char* gameOverText = "GAME OVER!";
            int gameOverWidth = MeasureText(gameOverText, 60);
            DrawText(gameOverText, SCREEN_WIDTH/2 - gameOverWidth/2, SCREEN_HEIGHT/2 - 60, 60, RED);
            
            std::string finalScore = "Final Score: " + std::to_string(cube.score);
            int scoreWidth = MeasureText(finalScore.c_str(), 30);
            DrawText(finalScore.c_str(), SCREEN_WIDTH/2 - scoreWidth/2, SCREEN_HEIGHT/2, 30, WHITE);
            
            const char* restartText = "Press R to Restart";
            int restartWidth = MeasureText(restartText, 20);
            DrawText(restartText, SCREEN_WIDTH/2 - restartWidth/2, SCREEN_HEIGHT/2 + 40, 20, LIGHTGRAY);
            
            if (IsKeyPressed(KEY_R)) {
                cube.reset();
            }
        }
	
      EndDrawing();
    }
  CloseWindow();
  return 0;
}
