#include <oak/renderer2d.h>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


bool oak_r2d_init() {
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    return true;
}

void oak_drawQuad(float x, float y, float w, float h) {
    
}

void oak_r2d_flush() {

}

void oak_background(float r, float g, float b) {
    glClearColor(r, g, b, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}