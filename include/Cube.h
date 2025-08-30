#ifndef CUBE_H
#define CUBE_H
#include "raylib.h"

class Cube {
public:
  Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
  Vector3 cubeSize = {2.0f, 2.0f, 2.0f};
  float speed = 0.5f;
  float moveSpeed = 0.3f;
  float velocityY = 0.0f;   
  float gravity = -0.8f;
  float groundY = -24.0f;

  void draw(){
    DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWiresV(cubePosition, cubeSize, BLACK);
  }

  void update(int screenW) {
    //cubePosition.z -= speed;
    velocityY += gravity * GetFrameTime();

    
    cubePosition.y += velocityY;

    if (cubePosition.y - cubeSize.y/2 <= groundY) {
      cubePosition.y = groundY + cubeSize.y/2; 
      velocityY = 0.0f; 
    }
    
    if (IsKeyDown(KEY_RIGHT))
      cubePosition.x += moveSpeed;
    if (IsKeyDown(KEY_LEFT))
      cubePosition.x -= moveSpeed;
  }
};

#endif
