#pragma once

#include "Entity.h"
#include "utils.h"

class Enemy : public Entity {
public:
  Enemy();

  int getNumIndices() const override;

  void tick() override;
protected:
  const float vertices[16] = {
    -0.25f, -0.25f, 1.0f,
    0.25f, -0.25f, 1.0f,
    0.25f, 0.25f, 1.0f,
    -0.25f, 0.25f, 1.0f,
  };
  const int indices[6] = { 
    0, 1, 2,
    0, 2, 3,
  };
} ;
