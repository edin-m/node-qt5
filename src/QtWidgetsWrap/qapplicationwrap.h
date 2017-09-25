#ifndef QAPPLICATIONWRAP_H
#define QAPPLICATIONWRAP_H

#include "node_qt5_common.h"

#include <QApplication>

namespace nodeqt {

class QApplicationWrap {
public:
  static void Init(napi_env env, napi_value exports);
  static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);
//  static napi_status NewInstance(napi_env env, const QPoint& p, napi_value* instance);
  static bool IsInstanceOf(napi_env env, napi_value value);

  explicit QApplicationWrap();
  ~QApplicationWrap();

private:
  static napi_value New(napi_env env, napi_callback_info info);
  static napi_ref constructor;

  static NAPI_METHOD(exec);

  napi_env env_;
  napi_ref wrapper_;
  QApplication* application_;
};

}


#endif // QAPPLICATIONWRAP_H
