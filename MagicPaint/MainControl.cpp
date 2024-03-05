#include "MainControl.h"

MainControl::MainControl() {
    quit = false;
    window = NULL;
    whiteBoard = NULL;
}

MainControl::~MainControl() {
    window = NULL;
}

bool MainControl::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    window = glfwCreateWindow(1500, 960, "MS Paint Clone", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
        return false;
    }

    if (GLEW_ARB_vertex_array_object) {
        std::cout << "OpenGL extension ARB_vertex_array_object is supported!" << std::endl;
    }
    else {
        std::cerr << "OpenGL extension ARB_vertex_array_object is not supported!" << std::endl;
        return false;
    }

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    whiteBoard = new WhiteBoard();
    return true;
}

void MainControl::setMode() {
    whiteBoard->run(window);
}

void MainControl::close() {
    glfwTerminate();
}

bool MainControl::isQuit() const {
    return quit;
}