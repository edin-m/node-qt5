#ifndef QHBOXLAYOUTWRAP_H
#define QHBOXLAYOUTWRAP_H


#include "node_qt5_common.h"

#include <QLayout>
#include <QHBoxLayout>

namespace nodeqt {

class QHBoxLayoutWrap {
public:
  static void Init(napi_env env, napi_value exports);
  static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);
  static bool IsInstanceOf(napi_env env, napi_value value);

  explicit QHBoxLayoutWrap();
  ~QHBoxLayoutWrap();

  inline QLayout* layout() { return layout_; }

private:
  static napi_value New(napi_env env, napi_callback_info info);
  static napi_ref constructor;

  static NAPI_METHOD(addWidget);

  napi_env env_;
  napi_ref wrapper_;
  QHBoxLayout* layout_;
};

}


#endif // QHBOXLAYOUTWRAP_H
