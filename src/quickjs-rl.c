#include "quickjs-rl.h"
#include "cutils.h"
#include <assert.h>
#include <quickjs.h>
#include <raylib.h>

const JSCFunctionListEntry js_rl_funcs[] = {

#ifdef JS_RL_FUNC
#undef JS_RL_FUNC
#endif

#define JS_RL_FUNC(name) JS_CFUNC_DEF(#name, 1, js_rl_##name),

#ifdef JS_RL_CLASSES
#undef JS_RL_CLASSES
#endif

#ifndef JS_RL_FUNCS
#define JS_RL_FUNCS
#endif

#include "quick-rf-funcs.h"

#undef JS_RL_FUNC

#ifdef _JS_FUNC
#define JS_RL_FUNC _JS_FUNC
#endif

};

const JSCFunctionListEntry js_rl_obj[] = {

    JS_OBJECT_DEF("rl", js_rl_funcs, countof(js_rl_funcs),
                  JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE),

};

void JS_AddRLBindings(JSContext *ctx)
{
    JSValue global_obj = JS_GetGlobalObject(ctx);
    JS_SetPropertyFunctionList(ctx, global_obj, js_rl_obj, countof(js_rl_obj));
    JS_FreeValue(ctx, global_obj);

#undef JS_RL_FUNCS
#undef JS_RL_CLASSES
#ifndef JS_RL_CLASSES_INITS
#define JS_RL_CLASSES_INITS
#endif
#ifdef JS_RL_CLASS_INIT
#undef JS_RL_CLASS_INIT
#endif
#ifdef JS_RL_PREPARE
#undef JS_RL_PREPARE
#endif

#define JS_RL_CLASS_INIT(name) js_rl_##name##_init(ctx);
#define JS_RL_PREPARE(name) js_rl_##name##_prepare(ctx);

#include "quick-rf-funcs.h"

#undef JS_RL_CLASS_INIT
#undef JS_RL_PREPARE
#define JS_RL_CLASS_INIT _JS_RL_CLASS_INIT
#define JS_RL_PREPARE _JS_RL_PREPARE
}

JS_RL_FUNC(log)
{

    const char *str;

    for (int i = 0; i < argc; i++)
    {
        if (!(str = JS_ToCString(ctx, argv[i])))
        {
            return JS_EXCEPTION;
        }

        printf("%s", str);
        if (i != argc - 1)
            printf(" ");

        JS_FreeCString(ctx, str);
    }

    printf("\n");

    return JS_UNDEFINED;
}

JS_RL_FUNC(InitWindow)
{

    int width, height;
    const char *title = NULL;

    if (argc != 3)
    {
        return JS_ThrowTypeError(ctx, "expected 3 arguments, got %d", argc);
    }

    if (JS_ToInt32(ctx, &width, argv[0]) < 0)
        return JS_EXCEPTION;

    if (JS_ToInt32(ctx, &height, argv[1]) < 0)
        return JS_EXCEPTION;

    if ((title = JS_ToCString(ctx, argv[2])) == NULL)
        return JS_EXCEPTION;

    InitWindow(width, height, title);

    JS_FreeCString(ctx, title);

    return JS_UNDEFINED;
}

JS_RL_FUNC(CloseWindow)
{
    CloseWindow();
    return JS_UNDEFINED;
}

JS_RL_FUNC_RET_BOOL(WindowShouldClose, WindowShouldClose());

JS_RL_FUNC_RET_BOOL(IsWindowReady, IsWindowReady());

JS_RL_FUNC_RET_BOOL(IsWindowFullscreen, IsWindowFullscreen());

JS_RL_FUNC_RET_BOOL(IsWindowHidden, IsWindowHidden());

JS_RL_FUNC_RET_BOOL(IsWindowMinimized, IsWindowMinimized());

JS_RL_FUNC_RET_BOOL(IsWindowMaximized, IsWindowMaximized());

JS_RL_FUNC_RET_BOOL(IsWindowFocused, IsWindowFocused());

JS_RL_FUNC_RET_BOOL(IsWindowResized, IsWindowResized());

JS_RL_FUNC(ClearBackground)
{
    if (argc != 1)
    {
        return JS_ThrowTypeError(ctx, "expected exactly 1 argument, got %d",
                                 argc);
    }
    Color *color = JS_GetOpaque2(ctx, argv[0], js_rl_Color_class_id);
    if (!color)
        return JS_EXCEPTION;

    ClearBackground(*color);

    return JS_UNDEFINED;
}

JS_RL_FUNC(BeginDrawing)
{
    BeginDrawing();
    return JS_UNDEFINED;
}

JS_RL_FUNC(EndDrawing)
{
    EndDrawing();
    return JS_UNDEFINED;
}

JS_RL_CLASS_PROTO_FUNCS(Color){
#define COLOR_PROTO(name, magic)                                               \
    JS_CGETSET_MAGIC_DEF(#name, js_rl_Color_get_color, js_rl_Color_set_color,  \
                         magic)
    COLOR_PROTO(r, 0),
    COLOR_PROTO(g, 1),
    COLOR_PROTO(b, 2),
    COLOR_PROTO(a, 3),
#undef COLOR_PROTO
};

JS_RL_CLASS_DECLARE_INIT(Color)

JS_RL_PREPARE(Color)
{
    JSValue global_obj, obj, rl_obj, color_class;

    global_obj = JS_GetGlobalObject(ctx);
    assert(!JS_IsException(global_obj));

    rl_obj = JS_GetPropertyStr(ctx, global_obj, "rl");
    assert(!JS_IsException(rl_obj));

    color_class = JS_GetPropertyStr(ctx, rl_obj, "Color");
    assert(!JS_IsException(color_class));

#define DEFINE_COLOR(name)                                                     \
    Color *c_##name;                                                           \
    c_##name = js_mallocz(ctx, sizeof(*c_##name));                             \
    c_##name->r = name.r;                                                      \
    c_##name->g = name.g;                                                      \
    c_##name->b = name.b;                                                      \
    c_##name->a = name.a;                                                      \
    obj =                                                                      \
        JS_NewObjectProtoClass(ctx, js_rl_Color_proto, js_rl_Color_class_id);  \
    if (JS_IsException(obj))                                                   \
        /* not handled yet */                                                  \
        ;                                                                      \
    JS_SetOpaque(obj, c_##name);                                               \
    JS_SetPropertyStr(ctx, color_class, #name, obj);

    DEFINE_COLOR(LIGHTGRAY);
    DEFINE_COLOR(GRAY);
    DEFINE_COLOR(DARKGRAY);
    DEFINE_COLOR(YELLOW);
    DEFINE_COLOR(GOLD);
    DEFINE_COLOR(ORANGE);
    DEFINE_COLOR(PINK);
    DEFINE_COLOR(RED);
    DEFINE_COLOR(MAROON);
    DEFINE_COLOR(GREEN);
    DEFINE_COLOR(LIME);
    DEFINE_COLOR(DARKGREEN);
    DEFINE_COLOR(SKYBLUE);
    DEFINE_COLOR(BLUE);
    DEFINE_COLOR(DARKBLUE);
    DEFINE_COLOR(PURPLE);
    DEFINE_COLOR(VIOLET);
    DEFINE_COLOR(DARKPURPLE);
    DEFINE_COLOR(BEIGE);
    DEFINE_COLOR(BROWN);
    DEFINE_COLOR(DARKBROWN);
    DEFINE_COLOR(WHITE);
    DEFINE_COLOR(BLACK);
    DEFINE_COLOR(BLANK);
    DEFINE_COLOR(MAGENTA);
    DEFINE_COLOR(RAYWHITE);

    JS_FreeValue(ctx, color_class);
    JS_FreeValue(ctx, rl_obj);
    JS_FreeValue(ctx, global_obj);

#undef DEFINE_COLOR
}

JS_RL_CLASS_DEF(Color);

JS_RL_CLASS_CTOR(Color)
{
    Color *c;
    int colorVal;
    JSValue obj = JS_UNDEFINED;

    if (argc > 4)
        return JS_ThrowRangeError(ctx, "expected at max 4 arguments, got %d",
                                  argc);

    c = js_mallocz(ctx, sizeof(*c));
    if (!c)
        return JS_EXCEPTION;

#define SET_COLOR(color)                                                       \
    if (argc > 0)                                                              \
    {                                                                          \
        argc--;                                                                \
        if (JS_ToInt32(ctx, &colorVal, argv[argc]) < 0)                        \
            goto fail;                                                         \
        if (colorVal < 0 || colorVal > 255)                                    \
        {                                                                      \
            JS_ThrowRangeError(ctx, "color value out of range");               \
            goto fail;                                                         \
        }                                                                      \
        c->color = (unsigned char)colorVal;                                    \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        c->color = 0;                                                          \
    }

    SET_COLOR(r);
    SET_COLOR(g);
    SET_COLOR(b);
    SET_COLOR(a);

#undef SET_COLOR

    // proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    // if (JS_IsException(proto))
    //    goto fail;
    obj = JS_NewObjectProtoClass(ctx, js_rl_Color_proto, js_rl_Color_class_id);
    if (JS_IsException(obj))
        goto fail;

    JS_SetOpaque(obj, c);
    return obj;
fail:
    js_free(ctx, c);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

JS_RL_CLASS_FINALIZER(Color)
{
    Color *s = JS_GetOpaque(val, js_rl_Color_class_id);
    js_free_rt(rt, s);
}

JS_RL_GETTER_MAGIC(Color, color)
{
    Color *color = JS_GetOpaque2(ctx, this_val, js_rl_Color_class_id);
    if (!color)
        return JS_EXCEPTION;

#define GET_COLOR(c, _magic)                                                   \
    if (magic == _magic)                                                       \
    {                                                                          \
        return JS_NewInt32(ctx, color->c);                                     \
    }
    GET_COLOR(r, 0);
    GET_COLOR(g, 1);
    GET_COLOR(b, 2);
    GET_COLOR(a, 3);

#undef GET_COLOR

    return JS_UNDEFINED;
}

JS_RL_SETTER_MAGIC(Color, color)
{
    Color *color = JS_GetOpaque2(ctx, this_val, js_rl_Color_class_id);
    if (!color)
        return JS_EXCEPTION;

    int colorVal;
    if (JS_ToInt32(ctx, &colorVal, val))
        return JS_EXCEPTION;

    if (colorVal < 0 || colorVal > 255)
        return JS_ThrowRangeError(ctx, "color value out of range");

#define SET_COLOR(c, _magic)                                                   \
    if (magic == _magic)                                                       \
    {                                                                          \
        color->c = (unsigned char)colorVal;                                    \
        return JS_UNDEFINED;                                                   \
    }
    SET_COLOR(r, 0);
    SET_COLOR(g, 1);
    SET_COLOR(b, 2);
    SET_COLOR(a, 3);

#undef SET_COLOR

    return JS_UNDEFINED;
}

char *io_readfile(const char *filename)
{
    FILE *f;
    long len;
    char *buf;

    f = fopen(filename, "rb");
    if (!f)
        return NULL;
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);
    buf = malloc(len + 1);
    if (!buf)
        return NULL;
    if (fread(buf, 1, len, f) != (size_t)len)
    {
        free(buf);
        return NULL;
    }
    fclose(f);
    buf[len] = '\0';
    return buf;
}