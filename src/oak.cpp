// Licensed Under MIT
// (c) George Venn - 2025
// See LICENSE For details.

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <oak/oak.h>

#include <oak/shader.hpp>

#include <stdio.h>
#include <assert.h>

extern void install_hooks(struct oak_hooks* hooks);

int max_quads = 512;
int next_delta = max_quads / 2;

int main() {
    glfwInit();
    struct oak_hooks hooks = {0};
    install_hooks(&hooks);
    OAK_ASSERT(hooks.onUpdate != NULL);
    OAK_ASSERT(hooks.onRender != NULL);
    GLFWwindow* w = glfwCreateWindow(1080, 720, "Oak", NULL, NULL);
    glfwMakeContextCurrent(w);
    oak_r2d_init();

    glEnable(GL_DEPTH_TEST);  

    auto shader = oak::Shader::Load("assets/shaders/basic");
    shader->bind();

    if (hooks.onCreate) hooks.onCreate();

    while (!glfwWindowShouldClose(w)) {
        glfwPollEvents();
        hooks.onUpdate();
        hooks.onRender();
        

        Renderer2DStats stats = oak_r2d_stats();
        printf("Renderer2D Stats: \n\t- Draw Time: %f/16.67 ms (Avg %f ms / Batch, %f%% Of Frame) \n\t- Upload Time: %f us (%f%% Of Frame) us\n\t- Batches: %d (%d Quads)\n\t- CPU Flush: %f ms\n", 
            stats.drawTime / 1000.0f, 
            (stats.drawTime / (float) stats.batchCount) / 1000.0f,
            stats.drawPercent * 100.0f,
            stats.uploadTime, 
            stats.uploadPercent * 100.0f,
            stats.batchCount,
            stats.quadCount,
            stats.flushCPUTime * 1000.f
        );

        if (stats.drawTime / 1000.0f >= 16 || (stats.flushCPUTime * 1000.f > 16)) {
            max_quads -= next_delta;
            if (next_delta < 1) next_delta /= 2;
        } else {
            max_quads += next_delta;
        }

        oak_r2d_clear_stats();

        glfwSwapBuffers(w);
    }

    if (hooks.onShutdown) hooks.onShutdown();
    oak_r2d_shutdown();
    glfwDestroyWindow(w);
    glfwTerminate();
    return 0;
}


#ifdef OAK_STANDALONE_HOOKS

void onUpdate() {
    
}

#define ITERS (4096)

void onRender() {
    oak_background(0.1, 0.2, 0.3);
    for (int i = 0; i < max_quads; i++) {
        oak_drawQuad({0, 0, 0}, {2, 2}, {0, i / (float) max_quads , (float) max_quads, 1});
    }
    oak_r2d_flush();
}

void install_hooks(struct oak_hooks* hooks) {
    hooks->onUpdate = onUpdate;
    hooks->onRender = onRender;
}
#endif