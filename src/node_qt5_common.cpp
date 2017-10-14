#include "node_qt5_common.h"

bool IsConstructCall(napi_env env, napi_callback_info info) {
  napi_value target;
  CHECK_NAPI_RESULT(napi_get_new_target(env, info, &target));
  return target != nullptr;
}

bool NapiInstanceOf(napi_ref ctor, napi_env env, napi_value value) {
  bool result = false;
  napi_value cons;
  CHECK_NAPI_RESULT(napi_get_reference_value(env, ctor, &cons));
  CHECK_NAPI_RESULT(napi_instanceof(env, value, cons, &result));
  return result;
}
