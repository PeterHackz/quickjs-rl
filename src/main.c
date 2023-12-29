#include "quickjs-libc.h"
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
    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);

    JS_AddRLBindings(ctx);

    JSValue v = JS_Eval(ctx, code, strlen(code), argv[1], JS_EVAL_TYPE_MODULE);

    if (JS_IsException(v))
    {
        JSValue exc = JS_GetException(ctx);
        printf("[-] Exception: %s\n", JS_ToCString(ctx, exc));
        JSValue stackval = JS_GetPropertyStr(ctx, exc, "stack");
        const char *stackstr = JS_ToCString(ctx, stackval);
        JS_FreeValue(ctx, stackval);
        JS_FreeValue(ctx, exc);
        JS_FreeCString(ctx, stackstr);
        printf("[-] stack: %s\n", stackstr);
    }

    JS_FreeValue(ctx, v);

    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);

    printf("done\n");

    return 0;
}