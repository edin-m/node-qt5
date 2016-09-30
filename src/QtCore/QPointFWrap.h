#ifndef QPOINTFWRAP_H
#define QPOINTFWRAP_H

#include <nan.h>

#include <QPointF>

class QPointFWrap : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit QPointFWrap();
  explicit QPointFWrap(double x, double y);
  ~QPointFWrap();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static void isNull(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void x(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void y(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void setX(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void setY(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void multiply(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void plus(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void minus(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void divide(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static Nan::Persistent<v8::Function> constructor;
  QPointF* point_;
};

#endif // QPOINTFWRAP_H