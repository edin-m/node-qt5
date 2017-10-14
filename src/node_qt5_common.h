#ifndef NODE_QT5_COMMON_H
#define NODE_QT5_COMMON_H

#include <cassert>
#include <iostream>

#include "node_api.h"

#define DECLARE_NAPI_METHOD(name, func) \
{ name, 0, func, 0, 0, 0, napi_default, 0 }

#define CHECK_NAPI_RESULT(condition) (assert((condition) == napi_ok))

/**
  * Method signature shorthand
  */
#define NAPI_METHOD(name) \
  napi_value name(napi_env env, napi_callback_info info)

/**
  * NAPI_FN_EXTRACT_ARG
  * Extract an arg from existing args
  * Requires: `args` in the scope, variable must be registered before this macro
  * See: QPointWrap
  */
#define NAPI_FN_EXTRACT_ARG(name, pos, typefn) \
  napi_valuetype valuetype_##name; \
  CHECK_NAPI_RESULT(napi_typeof(env, args[pos], &valuetype_##name)); \
  if (valuetype_##name != napi_undefined) { \
    CHECK_NAPI_RESULT(napi_get_value_##typefn(env, args[pos], &name)); \
  }

/**
  * NAPI_PULL_FN_ARGS
  * registers argnum args in the current scope (argc, args, jshint) values
  * argc - num of args (populated)
  * args - arg values
  * jsthis - this pointer
  */
#define NAPI_PULL_FN_ARGS(argnum) \
  size_t argc = argnum; \
  napi_value args[argnum]; \
  napi_value jsthis; \
  CHECK_NAPI_RESULT(napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr));

/**
  * NAPI_UNWRAP_THIS
  * Extracts jsthis, and populates *obj which must be registered before this macro
  */
#define NAPI_UNWRAP_THIS() \
  napi_value jsthis; \
  CHECK_NAPI_RESULT(napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr)); \
  CHECK_NAPI_RESULT(napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj)))

/**
  * NAPI_UNWRAP_THIS_WITH_ARGS
  * Populates current class' *obj and extracts arguments
  */
#define NAPI_UNWRAP_THIS_WITH_ARGS(argnum) \
  size_t argc = argnum; \
  napi_value args[argnum]; \
  napi_value jsthis; \
  CHECK_NAPI_RESULT(napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr)); \
  CHECK_NAPI_RESULT(napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj)))

bool IsConstructCall(napi_env env, napi_callback_info info);

bool NapiInstanceOf(napi_ref ctor, napi_env env, napi_value value);

#endif // NODE_QT5_COMMON_H
