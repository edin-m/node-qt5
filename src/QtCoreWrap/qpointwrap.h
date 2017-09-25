#ifndef QPOINTWRAP_H
#define QPOINTWRAP_H

#include <string>
#include <iostream>

#include "node_qt5_common.h"

// https://github.com/nodejs/abi-stable-node/blob/api-prototype-6.2.0/src/node_api_helpers.h

#include <QPoint>

namespace nodeqt {

class QPointWrap {
public:
  static void Init(napi_env env, napi_value exports);
  static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);
  static napi_status NewInstance(napi_env env, const QPoint& p, napi_value* instance);
  static bool IsInstanceOf(napi_env env, napi_value value);

  explicit QPointWrap();
  explicit QPointWrap(const QPoint& point);
  ~QPointWrap();

  QPoint* point() { return point_; }
private:

  static napi_value New(napi_env env, napi_callback_info info);
  static napi_ref constructor;

  //  static napi_value GetValue(napi_env env, napi_callback_info info);
  //  static napi_value SetValue(napi_env env, napi_callback_info info);
  //  static napi_value PlusOne(napi_env env, napi_callback_info info);
  //  static napi_value Multiply(napi_env env, napi_callback_info info);
  static NAPI_METHOD(multiply);
  static NAPI_METHOD(plus);
  static NAPI_METHOD(minus);
  static NAPI_METHOD(divide);
  static NAPI_METHOD(isNull);
  static NAPI_METHOD(manhattanLength);
  static NAPI_METHOD(x);
  static NAPI_METHOD(setX);
  static NAPI_METHOD(y);
  static NAPI_METHOD(setY);
  //  double value_;
  napi_env env_;
  napi_ref wrapper_;
  QPoint* point_;
};

}

#endif // QPOINTWRAP_H
