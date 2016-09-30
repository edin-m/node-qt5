#include "QSizeWrap.h"

Nan::Persistent<v8::Function> QSizeWrap::constructor;

QSizeWrap::QSizeWrap()
  : Nan::ObjectWrap() {
  size_ = new QSize();
}

QSizeWrap::QSizeWrap(int width, int height)
  : Nan::ObjectWrap() {
  size_ = new QSize(width, height);
}

QSizeWrap::~QSizeWrap() {
  delete size_;
}

void QSizeWrap::Init(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(QSizeWrap::New);
  ctor->SetClassName(Nan::New("QSize").ToLocalChecked());
  ctor->InstanceTemplate()->SetInternalFieldCount(1);

  v8::Local<v8::ObjectTemplate> proto = ctor->PrototypeTemplate();
  // Prototype
  // Nan::SetPrototypeMethod(ctor, "setHeight", setHeight);
  Nan::SetAccessor(proto, Nan::New("height").ToLocalChecked(), height, setHeight);
  Nan::SetAccessor(proto, Nan::New("width").ToLocalChecked(), width, setWidth);

  constructor.Reset(ctor->GetFunction());
  Nan::Set(target, Nan::New("QSize").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(QSizeWrap::New) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    QSizeWrap* size;
    if (info.Length() == 2) {
      int width = info[0]->IsUndefined() ? 0 : Nan::To<int>(info[0]).FromJust();
      int height = info[1]->IsUndefined() ? 0 : Nan::To<int>(info[1]).FromJust();
      size = new QSizeWrap(width, height);
    } else {
      size = new QSizeWrap();
    }
    size->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  }
  else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    // TODO: support not only QSize()
    // const int argc = 1;
    // v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(0, {}));
  }
}

NAN_GETTER(QSizeWrap::height) {
  QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(size->size_->height()));
}

NAN_SETTER(QSizeWrap::setHeight) {
  if (value->IsNumber()) {
    QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
    size->size_->setHeight(value->Int32Value());
  }
}

NAN_SETTER(QSizeWrap::setWidth) {
  if (value->IsNumber()) {
    QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
    size->size_->setWidth(value->Int32Value());
  }
}

NAN_GETTER(QSizeWrap::width) {
  QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(size->size_->width()));
}