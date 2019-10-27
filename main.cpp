#include "main.h"


int main() {
  Manager manager;
  manager.loadShaders("/Users/pa_ssion/github/sourbuddy/resources/vertex.glsl", "/Users/pa_ssion/github/sourbuddy/resources/color.glsl");

  printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

  manager.setup();
  manager.run();
  manager.cleanup();

  return 0;
}

void generateEnemies() {
  
}