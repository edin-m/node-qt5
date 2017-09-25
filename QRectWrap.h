#ifndef QRECTWRAP_H
#define QRECTWRAP_H

#include <nan.h>

#include <QRect>

class QRectWrap : public Nan::ObjectWrap {
 public:
  static void Init(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target);
  static v8::Local<v8::Object> NewInstance(QRectWrap* wrap);
  static v8::Local<v8::Object> NewInstance(v8::Local<v8::Value> arg);

 private:
   explicit QRectWrap();
   explicit QRectWrap(const QRect& rect);
   explicit QRectWrap(int left, int top, int width, int height);
  ~QRectWrap();

  static NAN_METHOD(New);

  static NAN_METHOD(adjust);
  static NAN_METHOD(adjusted);
  static NAN_GETTER(bottom);
  // static NAN_METHOD(bottomLeft);
  // static NAN_METHOD(bottomRight);
  // static NAN_METHOD(center);
  static NAN_METHOD(contains);
  static NAN_GETTER(height);
  // TODO: intersected intersects
  static NAN_METHOD(isEmpty);
  static NAN_METHOD(isNull);
  static NAN_METHOD(isValid);
  static NAN_GETTER(left);
  // TODO: ...
  static NAN_GETTER(right);
  // TODO: ...
  static NAN_SETTER(setBottom);
  // TODO: ...
  static NAN_SETTER(setHeight);
  static NAN_SETTER(setLeft);
  // TODO: ...
  static NAN_SETTER(setRight);
  // TODO: ...
  static NAN_SETTER(setTop);
  // TODO: ...
  static NAN_SETTER(setWidth);
  static NAN_SETTER(setX);
  static NAN_SETTER(setY);
  // TODO: ...
  static NAN_GETTER(top);
  // TODO: ...
  static NAN_GETTER(width);
  static NAN_GETTER(x);
  static NAN_GETTER(y);

  static Nan::Persistent<v8::Function> constructor;
  QRect* rect_;
};

#endif // QRECTWRAP_H