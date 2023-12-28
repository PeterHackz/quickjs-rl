#include "quickjs-rl.h"
#include "cutils.h"
#include <quickjs.h>
#include <raylib.h>

const JSCFunctionListEntry js_rl_funcs[] = {

#ifdef JS_RL_FUNC
#undef JS_RL_FUNC
#endif

#define JS_RL_FUNC(name) JS_CFUNC_DEF(#name, 1, js_rl_##name),

#include "quick-rf-funcs.h"

#undef JS_RL_FUNC
#define JS_RL_FUNC _JS_FUNC

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

JS_RL_FUNC_RET_BOOL(WindowShouldClose, WindowShouldClose());

JS_RL_FUNC(CloseWindow)
{
    CloseWindow();
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