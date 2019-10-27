#include "Program.h"

Program::Program() {
  programID = glCreateProgram();
  glUseProgram(programID);
}

Program::~Program() {
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(programID);
}

void Program::load(const std::string& fname, GLenum type) {
  std::ifstream istream(fname);
  std::stringstream buffer;

  if (istream.fail()) {
    std::cerr << "Failed to open file " << fname << std::endl;
    exit(1);
  }

  buffer << istream.rdbuf();

  return Program::loads(buffer.str(), type);
}

void Program::loads(const std::string& contents, GLenum type) {
  GLuint shaderID = glCreateShader(type);
  const char* contentsp = contents.c_str();
  GLint contentsLength = (GLint)contents.size();
  GLint compileSuccess;

  glShaderSource(shaderID, 1, &contentsp, &contentsLength);
  glCompileShader(shaderID);
  
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileSuccess);
  if (compileSuccess == GL_FALSE) {
    GLchar messages[512];
    glGetShaderInfoLog(shaderID, sizeof(messages), 0, &messages[0]);
    std::cerr << messages << std::endl;
    exit(1);
  }

  glAttachShader(programID, shaderID);

  shaders.push_back(shaderID);
}
void Program::link() {
  GLint linkSuccess;

  glLinkProgram(programID);
  glGetProgramiv(programID, GL_LINK_STATUS, &linkSuccess);

  if(linkSuccess == GL_FALSE) {
    std::cerr << "Error linking program" << std::endl;
    exit(1);
  };

  // we can only read these variables after linking. We do it 
  // here for ease of access
  modelMatrix = glGetUniformLocation(programID, "modelMatrix");
  projectionMatrix = glGetUniformLocation(programID, "projectionMatrix");
  viewMatrix = glGetUniformLocation(programID, "viewMatrix");
  color = glGetUniformLocation(programID, "color");
  position = glGetAttribLocation(programID, "position");
  texCoord = glGetAttribLocation(programID, "texCoord");

  // for(GLuint shaderID : shaders) {
  //   glDeleteShader(shaderID);
  // }

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
}

void Program::use() const {
  glUseProgram(programID);
  glBindVertexArray(vao);
}
