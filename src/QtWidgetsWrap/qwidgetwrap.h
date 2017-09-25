#ifndef QWIDGETWRAP_H
#define QWIDGETWRAP_H

#include "node_qt5_common.h"

#include <QWidget>

namespace nodeqt {

class QWidgetWrap {
public:
  static void Init(napi_env env, napi_value exports);
  static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);
  static bool IsInstanceOf(napi_env env, napi_value value);

  explicit QWidgetWrap();
  ~QWidgetWrap();

  inline QWidget* widget() { return widget_; }
private:
  static napi_value New(napi_env env, napi_callback_info info);
  static napi_ref constructor;

  static NAPI_METHOD(show);
  static NAPI_METHOD(resize);

  napi_env env_;
  napi_ref wrapper_;
  QWidget* widget_;
};

}

#endif // QWIDGETWRAP_H
