#include "Manager.h"

unsigned char Manager::keysPressed[NUM_KEYS];

Manager::Manager() {
  if (!glfwInit()) {
    fprintf(stderr, "Failed initialize GLFW.");
    exit(EXIT_FAILURE);
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // GLFW_OPENGL_FORWARD_COMPAT specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed.
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // Indicate we only want the newest core profile, rather than using backwards compatible and deprecated features.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Make the window resize-able.
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  window = glfwCreateWindow(800, 600, "SourBuddy", NULL, NULL);


  // If the window fails to be created, print out the error, clean up GLFW and exit the program.
  if(!window) {
    fprintf(stderr, "Failed to create GLFW window.");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Use the window as the current context (everything that's drawn will be place in this window).
  glfwMakeContextCurrent(window);

  glfwSetErrorCallback(Manager::error_callback);
  glfwSetKeyCallback(window, Manager::key_callback);

  // Makes sure all extensions will be exposed in GLEW and initialize GLEW.
  glewExperimental = GL_TRUE;
  glewInit();

  program = new Program();
}

Manager::~Manager() {
  puts("Manager dying");
  delete program;
}

void Manager::loadShaders(const char* vertexShader, const char* fragmentShader) {
  program->load(vertexShader, GL_VERTEX_SHADER);
  program->load(fragmentShader, GL_FRAGMENT_SHADER);

  program->link();
  program->use();
}

void Manager::addEntity(Entity* entity) {
  entities.push_back(entity);
}


void Manager::error_callback(int err, const char* description) {
  fputs(description, stderr);
}

void Manager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  switch(action) {
    case GLFW_PRESS:
      keysPressed[key] = 1;
      break;
    case GLFW_RELEASE:
      keysPressed[key] = 0;
      break;
    case GLFW_REPEAT:
      keysPressed[key] = 1;
      break;
  }
}


void Manager::checkKeys() const {
  if (keysPressed[GLFW_KEY_ESCAPE]) {
    puts("Closed window");
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  
  if (player != NULL) {
    if (keysPressed[GLFW_KEY_DOWN] || keysPressed[GLFW_KEY_S]) {
      player->applyForce(0.0f, -0.01f);
    }
    if (keysPressed[GLFW_KEY_UP] || keysPressed[GLFW_KEY_W]) {
      player->applyForce(0.0f, 0.01f);
    }
    if (keysPressed[GLFW_KEY_LEFT] || keysPressed[GLFW_KEY_A]) {
      player->applyForce(-0.01f, 0.0f);
    }
    if (keysPressed[GLFW_KEY_RIGHT] || keysPressed[GLFW_KEY_D]) {
      player->applyForce(0.01f, 0.0f);
    }
  }
}

void Manager::tick() const {
  glfwPollEvents();

  for (Entity* entity: entities) {
    entity->tick();
  }
}

void Manager::draw() const {
  glClearBufferfv(GL_COLOR, 0, BLACK);

  for (Entity* entity : entities) {
    entity->draw(*program);
  }

  glfwSwapBuffers(window);
  glfwPollEvents();
}

void Manager::setup() {
  player = new Glider();

  this->addEntity(player);

  for (size_t i = 0; i < NUM_ENEMIES; ++i) {
    Enemy* enemy = new Enemy();
    printf("Enemy num_indices %d\n", enemy->getNumIndices());
    this->addEntity(enemy);
  }
}

void Manager::run() {
  while (!glfwWindowShouldClose(window)) {
    this->checkKeys();
    this->draw();
    this->tick();
  }
}

void Manager::cleanup() {
  for (Entity* entity : entities) {
    delete entity;
  } // entities must not be used after this point
  glfwTerminate();
}