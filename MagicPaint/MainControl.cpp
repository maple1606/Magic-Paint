#include "MainControl.h"

MainControl::MainControl() {
    quit = false;
    window = NULL;
    canvas = NULL;
}

MainControl::~MainControl() {
    delete window;
    window = NULL;
    delete canvas;
    canvas = NULL;
}

bool MainControl::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MS Paint Clone", nullptr, nullptr);
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

    canvas = new Canvas(SCREEN_WIDTH, SCREEN_HEIGHT);
    return true;
}

void MainControl::setMode() {
    canvas->display(window);
}

void MainControl::close() {
    glfwTerminate();
}

bool MainControl::isQuit() const {
    return quit;
}