#include "raylib.h"

class Cube {
public:
  Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
  Vector3 cubeSize = {2.0f, 2.0f, 2.0f};
  float speed = 0.5f;
  float moveSpeed = 8.0f;

  void draw(){
    DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWiresV(cubePosition, cubeSize, BLACK);
  }

  void update() {
    cubePosition.z -= speed;
    if (IsKeyDown(KEY_RIGHT))
      cubePosition.x++;
    if (IsKeyDown(KEY_LEFT))
      cubePosition.x--;
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
      cube.update();
      camera.position.z = cube.cubePosition.z + 10.0f;
      camera.target = cube.cubePosition;
      
      BeginDrawing();
      ClearBackground(BLUE);

      BeginMode3D(camera);
      
      cube.draw();      
      DrawGrid(100, 2.0);
      EndMode3D();
      DrawFPS(10, 10);
      EndDrawing();
    }
  CloseWindow();
  return 0;
}
