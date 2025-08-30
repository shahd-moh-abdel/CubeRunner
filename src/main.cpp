#include "raylib.h"

class Cube {
public:
  Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
  Vector3 cubeSize = {2.0f, 2.0f, 2.0f};

  void draw(){
    DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWiresV(cubePosition, cubeSize, BLACK);
  }

  void update() {
    if (IsKeyPressed(KEY_RIGHT))
      cubePosition.x++;
    if (IsKeyPressed(KEY_LEFT))
      cubePosition.x--;
    if (IsKeyPressed(KEY_UP))
      cubePosition.z--;
    if (IsKeyPressed(KEY_DOWN))
      cubePosition.z++;
  }
};

int main() {
  InitWindow(1200,  800, "Cube Runner");

  SetConfigFlags(FLAG_MSAA_4X_HINT);

  Camera3D camera = { 0 };
  camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  
  camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; 
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
  camera.fovy = 45.0f;                           
  camera.projection = CAMERA_PERSPECTIVE;

  Cube cube;
  
  SetTargetFPS(60);

  while(!WindowShouldClose())
    {
      BeginDrawing();
      ClearBackground(BLUE);

      BeginMode3D(camera);
      
      cube.draw();
      cube.update();
      
      EndMode3D();
      DrawFPS(10, 10);
      EndDrawing();
    }
  CloseWindow();
  return 0;
}
