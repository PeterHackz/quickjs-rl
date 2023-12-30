#ifndef QUICK_RL_UTILS_H
#define QUICK_RL_UTILS_H

#include "quickjs.h"

JSValue get_array_buffer_contents(JSContext *ctx, JSValue val, uint8_t **buf,
                                  size_t *buf_len);

#endif // QUICK_RL_UTILS_H