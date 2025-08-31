#ifndef CUBE_H
#define CUBE_H
#include "raylib.h"

#include <vector>
#include <cstdlib>
#include <ctime>

class Monster {
public:
    Vector3 position;
    Vector3 size = {2.0f, 2.0f, 2.0f};
    float speed = 0.2f;
    bool active = true;

    Monster(float x, float y, float z) : position({x, y, z}) {}

    void update() {
        position.z += speed; // Move towards player
    }

    void draw() {
        if (active) {
            DrawCube(position, size.x, size.y, size.z, PURPLE);
            DrawCubeWiresV(position, size, BLACK);
        }
    }

    bool isOffScreen() {
        return position.z > 15.0f; // Past the player
    }

    bool checkCollision(Vector3 playerPos, Vector3 playerSize) {
        return (position.x - size.x/2 < playerPos.x + playerSize.x/2 &&
                position.x + size.x/2 > playerPos.x - playerSize.x/2 &&
                position.y - size.y/2 < playerPos.y + playerSize.y/2 &&
                position.y + size.y/2 > playerPos.y - playerSize.y/2 &&
                position.z - size.z/2 < playerPos.z + playerSize.z/2 &&
                position.z + size.z/2 > playerPos.z - playerSize.z/2);
    }
};

class Cube {
public:
  Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
  Vector3 cubeSize = {2.0f, 2.0f, 2.0f};
  float speed = 0.5f;
  float moveSpeed = 0.3f;
  float velocityY = 0.0f;   
  float gravity = -0.02f;
  float jumpSpeed = 0.0f;
  float groundY = 0.0f;
  bool isJumping = false;

  
  std::vector<Monster> monsters;
  float monsterSpawnTimer = 0.0f;
  float monsterSpawnInterval = 120.0f;
  int score = 0;
  bool gameOver = false;

  Cube() {
    srand(time(nullptr));
  }

  void draw(){
    DrawCubeV(cubePosition, cubeSize, RED);
    DrawCubeWiresV(cubePosition, cubeSize, BLACK);

    for (auto& monster : monsters) {
      monster.draw();
    }
  }

  void spawnMonster() {
    float randomX = (rand() % 21 - 10) * 2.0f; // Random x between -20 and 20
    monsters.push_back(Monster(randomX, 1.0f, -25.0f));
  }

  void update(int screenW) {
    if (gameOver) return;
    
    //cubePosition.z -= speed;
    velocityY += gravity * GetFrameTime();

    
    cubePosition.y += velocityY;

    
    bool onPlatform = (cubePosition.x >= -25.0f && cubePosition.x <= 25.0f && 
                       cubePosition.z >= -25.0f && cubePosition.z <= 25.0f);

    if (onPlatform && cubePosition.y - cubeSize.y/2 <= groundY) {
      cubePosition.y = groundY + cubeSize.y/2; 
      velocityY = 0.0f; 
    }
    
    if (IsKeyDown(KEY_RIGHT))
      cubePosition.x += moveSpeed;
    if (IsKeyDown(KEY_LEFT))
      cubePosition.x -= moveSpeed;

    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && !isJumping) {
      jumpSpeed = 0.4f;
      isJumping = true;
    }

    if (isJumping) {
      cubePosition.y += jumpSpeed;
      jumpSpeed += gravity;
            
      if (cubePosition.y <= groundY + cubeSize.y/2) {
	cubePosition.y = groundY + cubeSize.y/2;
	isJumping = false;
	jumpSpeed = 0.0f;
      }
    }
  }
};

#endif
