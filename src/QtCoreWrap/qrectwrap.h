#ifndef QRECTWRAP_H
#define QRECTWRAP_H

#include "node_qt5_common.h"

#include <QRect>

#include "node_qt5_common.h"

namespace nodeqt {

class QRectWrap {
public:
  static void Init(napi_env env, napi_value exports);
  static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);

  explicit QRectWrap();
  ~QRectWrap();

private:
  static napi_value New(napi_env env, napi_callback_info info);
  static napi_ref constructor;

  static NAPI_METHOD(x);
  static NAPI_METHOD(setX);
  static NAPI_METHOD(y);
  static NAPI_METHOD(setY);
  static NAPI_METHOD(width);
  static NAPI_METHOD(setWidth);
  static NAPI_METHOD(height);
  static NAPI_METHOD(setHeight);
  static NAPI_METHOD(bottomLeft);

  napi_env env_;
  napi_ref wrapper_;
  QRect* rect_;
};

}

#endif // QRECTWRAP_H
