#pragma once

#include <GL/glew.h>
#define GL_GLEXT_PROTOTYPES 1
#include <string>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "glm/mat4x4.hpp"
#include <pwd.h>
#include <unistd.h>
#include <vector>

class Program {
public:
  Program();
  ~Program();
  void load(const std::string&, GLenum);
  void loads(const std::string&, GLenum);
  void link();
  void use() const;
public:
  GLuint modelMatrix, projectionMatrix, viewMatrix,color, position, texCoord;
private:
  GLuint programID, vao;
  std::vector<GLuint> shaders;
} ;