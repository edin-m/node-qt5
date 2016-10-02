#ifndef QSIZEWRAP_H
#define QSIZEWRAP_H

#include <nan.h>

#include <QSize>

class QSizeWrap : public Nan::ObjectWrap {
public:
  static void Init(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target);
  static v8::Local<v8::Object> NewInstance(QSizeWrap* wrap);
  static v8::Local<v8::Object> NewInstance(v8::Local<v8::Value> arg);

private:
  explicit QSizeWrap();
  explicit QSizeWrap(const QSize& size);
  explicit QSizeWrap(int width, int height);
  ~QSizeWrap();

  static NAN_METHOD(New);

  static NAN_GETTER(height);
  static NAN_SETTER(setHeight);

  static NAN_GETTER(width);
  static NAN_SETTER(setWidth);

  static NAN_METHOD(isEmpty);
  static NAN_METHOD(isNull);
  static NAN_METHOD(isValid);

  static NAN_METHOD(scale);
  static NAN_METHOD(scaled);

  static NAN_METHOD(transpose);
  static NAN_METHOD(transposed);

  static NAN_METHOD(multiply);
  static NAN_METHOD(plus);
  static NAN_METHOD(minus);
  static NAN_METHOD(divide);

  // TODO: ...
  // TODO: ...

  static Nan::Persistent<v8::Function> QSizeWrap::constructor;
  QSize* size_;
};

#endif // !QSIZEWRAP_H
