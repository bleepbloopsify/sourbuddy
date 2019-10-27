#pragma once

#include <math.h>
#include "glm/gtc/matrix_transform.hpp"

#include "Program.h"

class Entity {
public:
  Entity();
  virtual ~Entity();

  virtual int getNumIndices() const;

  virtual void tick();
  virtual void applyForce(float, float);
  virtual void draw(const Program&) const;
private:
  // float width, heigh;
protected:
  const float vertices[9] = {
    -0.5f, -0.5f, 1.0f, 
    -0.25f, 0.5f, 1.0f,
    0.5f, 0.5f, 1.0f,
  };
  const int indices[3] = { 0, 1, 2 };
  virtual void bounds();
  virtual void accel();
  virtual void resetVelocity();

  GLuint vbo, ebo;
  // glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);

  float x = 0.0f, y = 0.0f;
  float dx = 0.0f, dy = 0.0f;
  float max_velocity = 0.002f;
  float d2x = 0.0f, d2y = 0.0f;
  float max_accel = 0.05f;
   // default weight for entities to calculate friction
  float weight = 1.0f;
  float coef_fric = 0.03f;

  glm::mat4 projectionMatrix = glm::mat4(1.0f);
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  glm::mat4 viewMatrix = glm::mat4(1.0f);

  virtual void move();
} ;

bool isColliding(const Entity&, const Entity&);
