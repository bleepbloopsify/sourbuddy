#pragma once

#include <vector>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Program.h"
#include "Entity.h"
#include "Glider.h"
#include "Enemy.h"

#define NUM_KEYS 300
#define NUM_ENEMIES 20

const GLfloat WHITE[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat BLACK[] = { 0.0f, 0.0f, 0.0f, 0.0f };

class Manager {
public:
  Manager();
  ~Manager();

// setup logic
  void loadShaders(const char*, const char*);


  void addEntity(Entity*);
// Hooks for opengl
  static void error_callback(int, const char*);
  static void key_callback(GLFWwindow*, int, int, int, int);
  void checkKeys() const;
// Game Logic
  void tick() const;
  void draw() const;
  void setup();
  void run();
  void cleanup();

private:
// display state
  GLFWwindow* window;
  static unsigned char keysPressed[NUM_KEYS];

  Program* program;
  std::vector<Entity*> entities;
  Entity* player;

} ;