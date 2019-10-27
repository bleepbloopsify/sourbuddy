#pragma once

#include "Entity.h"

class Glider : public Entity {
public:
  Glider();
// virtual void draw(const Program&) const;
protected:
  const float vertices[9] = {
    -0.25f, -0.25f, 1.0f,
    0.0f, 0.25f, 1.0f,
    0.25f, -0.25f, 1.0f,
  };
  const int indices[3] = { 0, 1, 2 };
  // static const float 
  // int indices[3] = { 0, 1, 2 };
  // glm::mat4 modelMatrix = glm::mat4(1.0f);
} ;

