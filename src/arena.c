#include <oak/arena.h>
#include <stdlib.h>
void oak_init_arena(oak_arena_t* arena, uint16_t capacity) {
    if (arena == NULL) return;
    arena->capacity = capacity;
    arena->data = malloc(capacity);
    arena->next = 0;
}

void oak_deinit_arena(oak_arena_t* arena) {
    if (arena == NULL) return;
    arena->capacity = 0;
    free(arena->data);
    arena->next = 0;
}

void* oak_arena_alloc(oak_arena_t* arena, uint16_t size) {
    if (arena == NULL) return NULL;
    if (arena->next >= (arena->capacity - size)) return NULL;
    void* ptr = &(arena->data[arena->next]);
    arena->next += size;
    return ptr;
}

void oak_arena_free(oak_arena_t* arena) {
    if (arena == NULL) return;
    arena->next = 0;
}

oak_arena_t* oak_new_arena(uint16_t capacity) {
    oak_arena_t* arena = malloc(sizeof(oak_arena_t));
    oak_init_arena(arena, capacity);
    return arena;
}