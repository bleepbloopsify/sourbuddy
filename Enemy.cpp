#include "Enemy.h"

Enemy::Enemy() {
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), this->vertices, GL_STATIC_DRAW);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  this->x = randomFloat(-1.0f, 1.0f);
  this->y = randomFloat(-1.0f, 1.0f);
}

int Enemy::getNumIndices() const { return 6; }

void Enemy::tick() {

  this->x += randomFloat(-0.01f, 0.01f);
  this->y += randomFloat(-0.01f, 0.01f);

  Entity::tick();
}