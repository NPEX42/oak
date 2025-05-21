#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <oak/oak.h>

#include <stdio.h>
#include <assert.h>

extern void install_hooks(struct oak_hooks* hooks);

int main() {
    glfwInit();
    struct oak_hooks hooks = {0};
    install_hooks(&hooks);
    OAK_ASSERT(hooks.onUpdate != NULL);
    OAK_ASSERT(hooks.onRender != NULL);
    GLFWwindow* w = glfwCreateWindow(1080, 720, "Oak", NULL, NULL);
    glfwMakeContextCurrent(w);
    oak_r2d_init();

    if (hooks.onCreate) hooks.onCreate();

    while (!glfwWindowShouldClose(w)) {
        glfwPollEvents();
        hooks.onUpdate();
        hooks.onRender();
        glfwSwapBuffers(w);
    }

    if (hooks.onShutdown) hooks.onShutdown();
    glfwDestroyWindow(w);
    glfwTerminate();
    return 0;
}


#ifdef OAK_STANDALONE_HOOKS

void onUpdate() {

}

void onRender() {
    oak_background(0.1, 0.2, 0.3);
}

void install_hooks(struct oak_hooks* hooks) {
    hooks->onUpdate = onUpdate;
    hooks->onRender = onRender;
}
#endif