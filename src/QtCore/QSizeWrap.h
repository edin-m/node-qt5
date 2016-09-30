#ifndef QSIZEWRAP_H
#define QSIZEWRAP_H

#include <nan.h>

#include <QSize>

class QSizeWrap : public Nan::ObjectWrap {
public:
  static void Init(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target);

private:
  explicit QSizeWrap();
  explicit QSizeWrap(int width, int height);
  ~QSizeWrap();

  static NAN_METHOD(New);

  static NAN_GETTER(height);
  // TODO: ...
  static NAN_SETTER(setHeight);
  static NAN_SETTER(setWidth);
  // TODO: ...
  static NAN_GETTER(width);

  static Nan::Persistent<v8::Function> QSizeWrap::constructor;
  QSize* size_;
};

#endif // !QSIZEWRAP_H
