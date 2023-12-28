#include "quickjs-rl.h"
#include "quickjs.h"
#include <string.h>

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        printf("Usage: %s <script.js>\n", argv[0]);
        return 1;
    }

    const char *code;

    if ((code = io_readfile(argv[1])) == NULL)
    {
        printf("Error: cannot read file %s\n", argv[1]);
        return 1;
    }

    JSRuntime *rt = JS_NewRuntime();
    JSContext *ctx = JS_NewContext(rt);

    JS_AddRLBindings(ctx);

    JSValue v = JS_Eval(ctx, code, strlen(code), argv[1], 0);

    if (JS_IsException(v))
    {
        JSValue e = JS_GetException(ctx);
        JSValue s = JS_ToString(ctx, e);
        const char *str = JS_ToCString(ctx, s);
        printf("Exception: %s\n", str);
        JS_FreeCString(ctx, str);
        JS_FreeValue(ctx, s);
        JS_FreeValue(ctx, e);
    }

    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);

    return 0;
}