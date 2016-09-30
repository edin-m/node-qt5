#ifndef QPOINTWRAP_H
#define QPOINTWRAP_H

#include <nan.h>

#include <QPoint>

class QPointWrap : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance(QPointWrap* wrap);

  explicit QPointWrap();
  explicit QPointWrap(const QPoint& point);
  explicit QPointWrap(int x, int y);
  ~QPointWrap();

  static Nan::Persistent<v8::Function> constructor;

private:

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

  QPoint* point_;
};

#endif // QPOINTWRAP_H