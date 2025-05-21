#ifndef OAK_ARENA_H
#define OAK_ARENA_H 1
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
typedef struct {
    uint16_t next;
    uint16_t capacity;
    uint8_t* data;
} oak_arena_t;

// Allocate & Initialize A new Arena on the Heap
oak_arena_t* oak_new_arena(uint16_t capacity);

// Initialize a new arena of size [capacity] bytes.
void oak_init_arena(oak_arena_t* arena, uint16_t capacity);
// Frees Arena & memory
void oak_deinit_arena(oak_arena_t* arena);

// Attempts to allocate [size] bytes from arena.
// SAFETY: Returns NULL when not enough space is left OR when [arena] is NULL.
void* oak_arena_alloc(oak_arena_t* arena, uint16_t size);

// Frees ALL allocated data.
void  oak_arena_free(oak_arena_t* arena);


#endif