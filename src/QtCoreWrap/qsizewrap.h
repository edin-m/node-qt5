#ifndef QSIZEWRAP_H
#define QSIZEWRAP_H

#include "node_qt5_common.h"

#include <QSize>

namespace nodeqt {

class QSizeWrap {
public:
  static void Init(napi_env env, napi_value exports);
  static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);
  static napi_status NewInstance(napi_env env, const QSize& p, napi_value* instance);
  static bool IsInstanceOf(napi_env env, napi_value value);

  explicit QSizeWrap();
  explicit QSizeWrap(const QSize& point);
  ~QSizeWrap();

  QSize* size() { return size_; }
private:
  static napi_value New(napi_env env, napi_callback_info info);
  static napi_ref constructor;

  static NAPI_METHOD(width);
  static NAPI_METHOD(setWidth);
  static NAPI_METHOD(height);
  static NAPI_METHOD(setHeight);
  static NAPI_METHOD(isNull);
  static NAPI_METHOD(isValid);

  napi_env env_;
  napi_ref wrapper_;
  QSize* size_;
};

}

#endif // QSIZEWRAP_H

