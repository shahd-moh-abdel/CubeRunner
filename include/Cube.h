#ifndef CUBE_H
#define CUBE_H
#include "raylib.h"

class Cube {
public:
  Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
  Vector3 cubeSize = {2.0f, 2.0f, 2.0f};
  float speed = 0.5f;
  float moveSpeed = 4.0f;

  void draw(){
    DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWiresV(cubePosition, cubeSize, BLACK);
  }

  void update(int screenW) {
    //cubePosition.z -= speed;
    if (IsKeyDown(KEY_RIGHT))
      cubePosition.x++;
    if (IsKeyDown(KEY_LEFT))
      cubePosition.x--;
  }
};

#endif
