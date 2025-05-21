#ifndef OAK_RENDERER2D_H
#define OAK_RENDERER2D_H
#include <oak/types.h>

// Initializes OpenGL using glad.
// SAFETY: Assumes an OpenGL Context is available.
bool oak_r2d_init();
void oak_drawQuad(float x, float y, float w, float h);
void oak_r2d_flush();

void oak_background(float r, float g, float b);

#endif