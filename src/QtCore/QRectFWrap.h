#ifndef QPOINTWRAP_H
#define QPOINTWRAP_H

#include <nan.h>

#include <QPoint>

class QPointWrap : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit QPointWrap();
  ~QPointWrap();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static Nan::Persistent<v8::Function> constructor;
  QPoint* point_;
};

#endif // QPOINTWRAP_H