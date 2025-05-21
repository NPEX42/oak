#ifndef OAK_RENDERER2D_H
#define OAK_RENDERER2D_H
#include <oak/types.h>


struct Renderer2DStats {
    float drawTime = 0.0f;
    float uploadTime = 0.0f;

    float drawPercent = 0.0f;
    float uploadPercent = 0.0f;

    float flushCPUTime = 0.0f;

    u16 batchCount = 0, quadCount = 0;
};

// Initializes OpenGL using glad.
// SAFETY: Assumes an OpenGL Context is available.
bool oak_r2d_init();
void oak_drawQuad(float x, float y, float w, float h);

void oak_drawQuad(vector3f pos, vector2f size, vector4f color = {1, 1, 1, 1});
void oak_r2d_flush();

void oak_background(float r, float g, float b);

void oak_r2d_shutdown();


Renderer2DStats oak_r2d_stats();

void oak_r2d_clear_stats();

#endif