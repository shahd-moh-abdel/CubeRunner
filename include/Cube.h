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
        position.z += speed; 
    }

    void draw() {
        if (active) {
            DrawCube(position, size.x, size.y, size.z, PURPLE);
            DrawCubeWiresV(position, size, BLACK);
        }
    }

    bool isOffScreen() {
        return position.z > 15.0f; 
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
    float randomX = (rand() % 21 - 10); 
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

    
    if (cubePosition.x < -23.0f) cubePosition.x = -23.0f;
    if (cubePosition.x > 23.0f) cubePosition.x = 23.0f;

    monsterSpawnTimer++;
    if (monsterSpawnTimer >= monsterSpawnInterval) {
      spawnMonster();
      monsterSpawnTimer = 0.0f;
      if (monsterSpawnInterval > 60.0f) {
	monsterSpawnInterval -= 2.0f;
      }
    }

    for (auto& monster : monsters) {
      monster.update();
            
      if (monster.active && monster.checkCollision(cubePosition, cubeSize)) {
	gameOver = true;
      }
    }

    for (int i = monsters.size() - 1; i >= 0; i--) {
      if (monsters[i].isOffScreen()) {
	if (monsters[i].active) {
	  score += 10; 
	}
	monsters.erase(monsters.begin() + i);
      }
    }

  }

  void reset() {
    cubePosition = { 0.0f, 1.0f, 0.0f };
    monsters.clear();
    score = 0;
    gameOver = false;
    monsterSpawnTimer = 0.0f;
    monsterSpawnInterval = 120.0f;
    isJumping = false;
    jumpSpeed = 0.0f;
  }
};

#endif
