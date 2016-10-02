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

  static NAN_METHOD(New);

  //static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static NAN_GETTER(x);
  static NAN_SETTER(setX);
  static NAN_GETTER(y);
  static NAN_SETTER(setY);

  static NAN_METHOD(isNull);
  static NAN_METHOD(multiply);
  static NAN_METHOD(plus);
  static NAN_METHOD(minus);
  static NAN_METHOD(divide);

  QPoint* point_;
};

#endif // QPOINTWRAP_H