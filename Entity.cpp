#include "Entity.h"

Entity::Entity() {
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), this->vertices, GL_STATIC_DRAW);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

Entity::~Entity() {
  printf("Destroying entity\n");
}

int Entity::getNumIndices() const { return 3; }

void Entity::draw(const Program& program) const {
  program.use();

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glUniform4f(program.color, 1.0f, 1.0f, 0.0f, 1.0f);
  glUniformMatrix4fv(program.projectionMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);    
  glUniformMatrix4fv(program.viewMatrix, 1, GL_FALSE, &viewMatrix[0][0]);

  glm::mat4 transformMatrix = modelMatrix;
  transformMatrix = glm::translate(transformMatrix, glm::vec3(x, y, 0.0f));
  transformMatrix = glm::scale(transformMatrix, glm::vec3(0.5f, 0.5f, 0.0f));

  glUniformMatrix4fv(program.modelMatrix, 1, GL_FALSE, &transformMatrix[0][0]);
  glVertexAttribPointer(program.position, 2, GL_FLOAT, GL_FALSE, 0, &vertices);

  glVertexAttribPointer(program.position, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  glEnableVertexAttribArray(program.position);
  glDrawElements(GL_TRIANGLES, this->getNumIndices(), GL_UNSIGNED_INT, 0);
  glDisableVertexAttribArray(program.position);
}

void Entity::move() {
    x += dx; y += dy;
}

// pass config in here
void Entity::bounds() {
  if (x < -1.0f || x > 1.0f) {
    dx = 0;
    if (x < -1.0f) x = -1.0f;
    else x = 1.0f;
  }

  if (y < -1.0f || y > 1.0f) {
    dy = 0;

    if (y < -1.0f) y = -1.0f;
    else y = 1.0f;
  }
}

void Entity::tick() {
  // printf("%10.5f, %10.5f, %10.5f, %10.5f, %10.5f, %10.5f\n", x, y, dx, dy, d2x, d2y);
  this->move();
  this->resetVelocity();
  this->bounds();
  // this->friction();
  this->accel();
}

void Entity::accel() {
  dx = fmin(max_velocity, d2x + dx); 
  dx = fmax(-1 * max_velocity, dx);

  dy = fmin(max_velocity, d2y + dy);
  dy = fmax(-1 * max_velocity, dy);
}

void Entity::applyForce(float xacc, float yacc) {

  dx = fmin(max_velocity, dx + xacc);
  dx = fmax(-1 * max_velocity, dx);
  dy = fmin(max_velocity, dy + yacc);
  dy = fmax(-1 * max_velocity, dy);
  // d2x = fmin(max_accel, d2x + xacc);
  // d2y = fmin(max_accel, d2y + yacc);
}

void Entity::resetVelocity() {
  dx = 0;
  dy = 0;
}


bool isColliding(const Entity& rhs, const Entity& lhs)
{
  return false;
}