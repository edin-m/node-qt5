#ifndef QPUSHBUTTONWRAP_H
#define QPUSHBUTTONWRAP_H

#include "node_qt5_common.h"

#include <QObject>
#include <QPushButton>
#include <QList>

namespace nodeqt {

class QPushButtonWrap {
public:
  static void Init(napi_env env, napi_value exports);
  static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);
  static bool IsInstanceOf(napi_env env, napi_value value);

  explicit QPushButtonWrap();
  ~QPushButtonWrap();

private:
  static napi_value New(napi_env env, napi_callback_info info);
  static napi_ref constructor;

  napi_env env_;
  napi_ref wrapper_;
  QPushButton* button_;
  QList<QMetaObject::Connection> connections_;
};

}

#endif // QPUSHBUTTONWRAP_H
