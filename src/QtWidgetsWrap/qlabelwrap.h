#ifndef QLABELWRAP_H
#define QLABELWRAP_H

#include "node_qt5_common.h"

#include <QLabel>

namespace nodeqt {

class QLabelWrap {
public:
  static void Init(napi_env env, napi_value exports);
  static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);
  static bool IsInstanceOf(napi_env env, napi_value value);

  explicit QLabelWrap();
  ~QLabelWrap();

  inline QLabel* label() { return label_; }

private:
  static napi_value New(napi_env env, napi_callback_info info);
  static napi_ref constructor;

  static NAPI_METHOD(text);
  static NAPI_METHOD(setText);
  static NAPI_METHOD(setParent);

  napi_env env_;
  napi_ref wrapper_;
  QLabel* label_;
};

}

#endif // QLABELWRAP_H
