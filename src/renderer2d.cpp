// Licensed Under MIT
// (c) George Venn - 2025
// See LICENSE For details.

#include <oak/renderer2d.hpp>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


#include <cstdio>
#include <cstring>

#include <oak/assert.h>
#include <oak/timer.hpp>


#define MAX_QUADS (512)

#define MAX_VERTS (MAX_QUADS * 6)




typedef struct vertex {
    vector3f position;
    vector2f uv0;
    vector4f color;
} vertex_t;

static u32 vaoID, vboID;
static u16 vertexCount;

static vertex_t vertices[MAX_VERTS];


static std::unique_ptr<oak::GPUTimer> drawTimer = nullptr, uploadTimer = nullptr;

static Renderer2DStats sStats;

bool oak_r2d_init() {

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) return false;

    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    OAK_ASSERT(sizeof(vector4f) == 4 * sizeof(float));

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * MAX_VERTS, vertices, GL_STREAM_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex_t), (void*) offsetof(vertex_t, position));
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(vector2f), (void*) offsetof(vertex_t, uv0));
    glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(vertex_t), (void*) offsetof(vertex_t, color));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    drawTimer = oak::GPUTimer::Create();
    uploadTimer = oak::GPUTimer::Create();

    return true;
}

void _push_vertex(vertex_t vert) {
    if (vertexCount >= MAX_VERTS) oak_r2d_flush();

    vertices[vertexCount] = vert;
    vertexCount++;
}


void oak_drawQuad(float x, float y, float w, float h) {
    oak_drawQuad({x, y}, {w, h});
}

void oak_r2d_flush() {
    double start, end;
    start = glfwGetTime();
    if (vertexCount == 0) return;
    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    uploadTimer->start();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * vertexCount, vertices, GL_STREAM_DRAW);
    uploadTimer->end();

    drawTimer->start();
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    drawTimer->end();

    end = glfwGetTime();


    sStats.batchCount++;

    sStats.flushCPUTime += end - start;

    #ifdef OAK_PROFILE_DRAW_SYNC
    while(!drawTimer->isAvailable()) {}
    #endif

    sStats.drawTime += drawTimer->durationNS() / 1000.0f;

    sStats.uploadTime += uploadTimer->durationNS() / 1000.0f;

    vertexCount = 0;
}

void oak_background(float r, float g, float b) {
    glClearColor(r, g, b, 1);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void oak_drawQuad(vector3f pos, vector2f size, vector4f color) {

    float x = pos.x, y = pos.y, w = size.x, h = size.y;

    vertex_t tr = {.position = {.x = x + w / 2.0f, .y = y + h / 2.0f, .z = pos.z}, .uv0 = {1, 1}, .color = color};
    vertex_t tl = {.position = {.x = x - w / 2.0f, .y = y + h / 2.0f, .z = pos.z}, .uv0 = {0, 1}, .color = color};
    vertex_t br = {.position = {.x = x + w / 2.0f, .y = y - h / 2.0f, .z = pos.z}, .uv0 = {1, 0}, .color = color};
    vertex_t bl = {.position = {.x = x - w / 2.0f, .y = y - h / 2.0f, .z = pos.z}, .uv0 = {0, 0}, .color = color};



    _push_vertex(bl);
    _push_vertex(tl);
    _push_vertex(tr);

    _push_vertex(bl);
    _push_vertex(tr);
    _push_vertex(br);

    sStats.quadCount++;
}

void oak_r2d_shutdown() {
    drawTimer = nullptr;
    uploadTimer = nullptr;
}

Renderer2DStats oak_r2d_stats() {
    sStats.drawPercent = ((sStats.drawTime / 1000.0f) / 16.67);
    sStats.uploadPercent = ((sStats.uploadTime / 1000.0f) / 16.67);
    return sStats;
}

void oak_r2d_clear_stats() {
    memset(&sStats, 0, sizeof(Renderer2DStats));
}