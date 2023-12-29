#ifndef QUICKJS_RL_H
#define QUICKJS_RL_H

#include "quickjs.h"

char *io_readfile(const char *filename);

#define CHECK_FOR_EXCEPTION(condition)                                         \
    if (condition)                                                             \
    {                                                                          \
        return JS_EXCEPTION;                                                   \
    }

#define _JS_FUNC(name)                                                         \
    JSValue js_rl_##name(JSContext *ctx, JSValueConst this_val, int argc,      \
                         JSValueConst *argv)

#define _JS_GETTER_MAGIC(claz, name)                                           \
    JSValue js_rl_##claz##_get_##name(JSContext *ctx, JSValueConst this_val,   \
                                      int magic)

#define _JS_SETTER_MAGIC(claz, name)                                           \
    JSValue js_rl_##claz##_set_##name(JSContext *ctx, JSValueConst this_val,   \
                                      JSValue val, int magic)

#define _JS_GET_SET_MAGIC(claz, name, _)                                       \
    _JS_GETTER_MAGIC(claz, name, _);                                           \
    _JS_SETTER_MAGIC(claz, name, _);

#define JS_RL_FUNC_RET_BOOL(name, value)                                       \
    JSValue js_rl_##name(JSContext *ctx, JSValueConst this_val, int argc,      \
                         JSValueConst *argv)                                   \
    {                                                                          \
        return JS_NewBool(ctx, value);                                         \
    }

#define JS_RL_FUNC(name) _JS_FUNC(name);
#define JS_RL_GETTER_MAGIC(claz, name) _JS_GETTER_MAGIC(claz, name)
#define JS_RL_SETTER_MAGIC(claz, name) _JS_SETTER_MAGIC(claz, name)
#define JS_RL_GET_SET_MAGIC(claz, name) _JS_GET_SET_MAGIC(claz, name, _);

#define JS_RL_CLASS_FINALIZER(name)                                            \
    void js_rl_##name##_finalizer(JSRuntime *rt, JSValue val)

#define _JS_CLASS_CTOR(name)                                                   \
    JSValue js_rl_##name##_ctor(JSContext *ctx, JSValueConst new_target,       \
                                int argc, JSValueConst *argv)

#define JS_RL_CLASS_CTOR(name) _JS_CLASS_CTOR(name)

#define _JS_RL_CLASS_INIT(name)                                                \
    extern JSClassID js_rl_##name##_class_id;                                  \
    extern JSClassDef js_rl_##name##_class;                                    \
    extern JSValue js_rl_##name##_proto;                                       \
    void js_rl_##name##_init(JSContext *ctx)

#define JS_RL_CLASS_INIT _JS_RL_CLASS_INIT

#define _JS_RL_PREPARE(claz) void js_rl_##claz##_prepare(JSContext *ctx)

#define JS_RL_PREPARE _JS_RL_PREPARE

#define JS_RL_CLASS_DECLARE_INIT2(name, code)                                  \
    JSClassID js_rl_##name##_class_id;                                         \
    JSValue js_rl_##name##_proto;                                              \
    void js_rl_##name##_init(JSContext *ctx)                                   \
    {                                                                          \
        JSValue name##_class;                                                  \
        JS_NewClassID(&js_rl_##name##_class_id);                               \
        JS_NewClass(JS_GetRuntime(ctx), js_rl_##name##_class_id,               \
                    &js_rl_##name##_class);                                    \
        js_rl_##name##_proto = JS_NewObject(ctx);                              \
        JS_SetPropertyFunctionList(ctx, js_rl_##name##_proto,                  \
                                   js_rl_##name##_proto_funcs,                 \
                                   countof(js_rl_##name##_proto_funcs));       \
        name##_class = JS_NewCFunction2(ctx, js_rl_##name##_ctor, #name, 2,    \
                                        JS_CFUNC_constructor, 0);              \
        JS_SetConstructor(ctx, name##_class, js_rl_##name##_proto);            \
        JS_SetClassProto(ctx, js_rl_##name##_class_id, js_rl_##name##_proto);  \
        JSValue global_obj = JS_GetGlobalObject(ctx);                          \
        JSValue rl_obj = JS_GetPropertyStr(ctx, global_obj, "rl");             \
        JS_SetPropertyStr(ctx, rl_obj, #name, name##_class);                   \
                                                                               \
        code; /* incase *etra* init code was needed */                         \
                                                                               \
        JS_FreeValue(ctx, global_obj);                                         \
        JS_FreeValue(ctx, rl_obj);                                             \
    }

#define JS_RL_CLASS_DECLARE_INIT(name) JS_RL_CLASS_DECLARE_INIT2(name, )

#define JS_RL_CLASS_PROTO_FUNCS(claz)                                          \
    const JSCFunctionListEntry js_rl_##claz##_proto_funcs[] =

#define JS_RL_CLASS_DEF(claz)                                                  \
    JSClassDef js_rl_##claz##_class = {                                        \
        #claz,                                                                 \
        .finalizer = js_rl_##claz##_finalizer,                                 \
    }

#define JS_RL_CLASSES
#define JS_RL_FUNCS
#define JS_RL_CLASSES_INITS

#include "quick-rf-funcs.h"

#undef JS_RL_CLASSES_INITS
#undef JS_RL_FUNCS
#undef JS_RL_CLASSES

void JS_AddRLBindings(JSContext *ctx);

#endif // QUICKJS_RL_H