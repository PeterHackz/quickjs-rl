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

    JSRuntime *rt = JS_NewRuntime();
    JSContext *ctx = JS_NewContext(rt);

    if ((code = io_readfile(ctx, argv[1])) == NULL)
    {
        printf("Error: cannot read file %s\n", argv[1]);
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
        return 1;
    }

    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);

    JS_AddRLBindings(ctx);

    JSValue v = JS_Eval(ctx, code, strlen(code), argv[1], JS_EVAL_TYPE_MODULE);

    JSValue exc;

    if (JS_IsException(v))
        goto exception;

    JSValue result = JS_PromiseResult(ctx, v);
    int promise_state = JS_PromiseState(ctx, v);

    js_std_loop(ctx);

    JS_FreeValue(ctx, v);

    if (JS_IsException(result))
        goto exception;

    if (promise_state == JS_PROMISE_REJECTED)
    {
        JS_Throw(ctx, result);
        goto exception;
    }

    goto end;

exception:
    exc = JS_GetException(ctx);

    const char *excStr = JS_ToCString(ctx, exc);

    printf("[-] Exception: %s\n", excStr);

    JSValue stackval = JS_GetPropertyStr(ctx, exc, "stack");

    if (!JS_IsUndefined(stackval))
    {
        const char *stackstr = JS_ToCString(ctx, stackval);
        printf("[-] stack: %s", stackstr);
        JS_FreeCString(ctx, stackstr);
        JS_FreeValue(ctx, stackval);
    }

    JS_FreeCString(ctx, excStr);
    JS_FreeValue(ctx, exc);

end:

    js_free(ctx, (void *)code);

    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);

    return 0;
}