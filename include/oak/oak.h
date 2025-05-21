#ifndef OAK_H
#define OAK_H
#include <oak/renderer2d.hpp>
#include "./arena.h"

#define OAK_ASSERT(cond) if (!(cond)) {__assert_fail(#cond, __FILE__, __LINE__, __PRETTY_FUNCTION__);} 


typedef void (*onUpdateFn)();
typedef void (*onRenderFn)();
typedef void (*onShutdownFn)();
typedef void (*onCreateFn)();
struct oak_hooks {
    onCreateFn onCreate;
    onUpdateFn onUpdate;
    onRenderFn onRender;
    onShutdownFn onShutdown;
};

#endif