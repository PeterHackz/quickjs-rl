#ifndef QUICKJS_RL_H
#define QUICKJS_RL_H

#include "quickjs.h"

char *io_readfile(const char *filename);

#define CHECK_FOR_EXCEPTION(condition)                                         \
    if (condition)                                                             \
    {                                                                          \
        return JS_EXCEPTION;                                                   \
    }

#define _JS_FUNC(name)                                                          \
    JSValue js_rl_##name(JSContext *ctx, JSValueConst this_val, int argc,         \
                      JSValueConst *argv)

#define _JS_GETTER(name) JSValue js_rl_##name(JSContext *ctx, JSValueConst this_val)

#define JS_RL_FUNC_RET_BOOL(name, value)                                          \
    JSValue js_rl_##name(JSContext *ctx, JSValueConst this_val, int argc,         \
                      JSValueConst *argv)                                      \
    {                                                                          \
        return JS_NewBool(ctx, value);                                         \
    }

#define JS_RL_FUNC(name) _JS_FUNC(name);
#define JS_RL_GETTER(name) _JS_GETTER(name);

#include "quick-rf-funcs.h"

void JS_AddRLBindings(JSContext *ctx);

#endif // QUICKJS_RL_H