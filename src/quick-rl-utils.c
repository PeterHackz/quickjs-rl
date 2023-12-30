#include "quick-rl-utils.h"
#include "quickjs.h"
#include <stdbool.h>

JSValue get_array_buffer_contents(JSContext *ctx, JSValue val, uint8_t **buf,
                                  size_t *buf_len)
{
    JSValue exception;
    bool is_empty, is_array_buffer;

    if (JS_IsUndefined(val))
    {
        return JS_ThrowTypeError(ctx,
                                 "expected an array buffer, got undefined");
    }
    else if (JS_IsNull(val))
    {
        return JS_ThrowTypeError(ctx, "expected an array buffer, got null");
    }

    *buf = JS_GetArrayBuffer(ctx, buf_len, val);

    is_empty = *buf == NULL && JS_IsNull(exception);
    JS_FreeValue(ctx, exception);

    is_array_buffer = *buf != NULL || is_empty;

    if (is_array_buffer)
        return JS_UNDEFINED;

    JSValue buffer;
    size_t byte_offset;

    buffer = JS_GetTypedArrayBuffer(ctx, val, &byte_offset, buf_len, NULL);
    if (!JS_IsException(buffer))
    {
        *buf = JS_GetArrayBuffer(ctx, buf_len, buffer) + byte_offset;
        JS_FreeValue(ctx, buffer);
        return JS_UNDEFINED;
    }
    else
    {
        JS_FreeValue(ctx, JS_GetException(ctx));

        JSValue buffer = JS_GetPropertyStr(ctx, val, "buffer");
        if (JS_IsException(buffer))
            JS_FreeValue(ctx, JS_GetException(ctx));
        else
        {
            *buf = JS_GetArrayBuffer(ctx, buf_len, buffer);
            JS_FreeValue(ctx, buffer);
            if (*buf)
                return JS_UNDEFINED;
        }

        JSValue ctor, ctorName;

        ctor = JS_GetPropertyStr(ctx, val, "constructor");
        if (JS_IsException(ctor))
            return JS_EXCEPTION;
        ctorName = JS_GetPropertyStr(ctx, ctor, "name");
        if (JS_IsException(ctorName))
        {
            JS_FreeValue(ctx, ctor);
            return JS_EXCEPTION;
        }
        const char *cStr = JS_ToCString(ctx, ctorName);
        JSValue error =
            JS_ThrowTypeError(ctx, "expected an array buffer, got %s", cStr);
        JS_FreeCString(ctx, cStr);
        JS_FreeValue(ctx, ctorName);
        JS_FreeValue(ctx, ctor);

        return error;
    }

    return JS_ThrowTypeError(ctx, "expected an array buffer");
}