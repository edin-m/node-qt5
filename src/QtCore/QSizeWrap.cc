#include "QSizeWrap.h"

Nan::Persistent<v8::Function> QSizeWrap::constructor;

QSizeWrap::QSizeWrap()
  : Nan::ObjectWrap() {
  size_ = new QSize();
}

QSizeWrap::QSizeWrap(const QSize& size) {
  size_ = new QSize(size);
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
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(QSizeWrap::New);
  tpl->SetClassName(Nan::New("QSize").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  v8::Local<v8::ObjectTemplate> proto = tpl->PrototypeTemplate();
  // Prototype
  Nan::SetAccessor(proto, Nan::New("height").ToLocalChecked(), height, setHeight);
  Nan::SetAccessor(proto, Nan::New("width").ToLocalChecked(), width, setWidth);

  Nan::SetPrototypeMethod(tpl, "isEmpty", isEmpty);
  Nan::SetPrototypeMethod(tpl, "isNull",  isNull);
  Nan::SetPrototypeMethod(tpl, "isValid", isValid);
  Nan::SetPrototypeMethod(tpl, "scale",   scale);
  Nan::SetPrototypeMethod(tpl, "scaled",  scaled);

  constructor.Reset(tpl->GetFunction());
  Nan::Set(target, Nan::New("QSize").ToLocalChecked(), tpl->GetFunction());
}

v8::Local<v8::Object> QSizeWrap::NewInstance(QSizeWrap* wrap) {
  Nan::EscapableHandleScope scope;
  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { Nan::New<v8::External>(wrap) };
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);
  return scope.Escape(instance);
}

v8::Local<v8::Object> QSizeWrap::NewInstance(v8::Local<v8::Value> arg) {
  Nan::EscapableHandleScope scope;
  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { arg };
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);
  return scope.Escape(instance);
}

NAN_METHOD(QSizeWrap::New) {
  if (info.IsConstructCall()) {
    QSizeWrap* size;
    if (info.Length() == 2) {
      int width = info[0]->IsUndefined() ? 0 : Nan::To<int>(info[0]).FromJust();
      int height = info[1]->IsUndefined() ? 0 : Nan::To<int>(info[1]).FromJust();
      size = new QSizeWrap(width, height);
    } else if (info.Length() == 1 && info[0]->IsExternal()) {
      QSizeWrap* wrap = static_cast<QSizeWrap*>(info[0].As<v8::External>()->Value());
      size = new QSizeWrap(*wrap->size_);
    } else if (info.Length() == 1 && info[0]->IsObject()) {
      QSizeWrap* wrap = Nan::ObjectWrap::Unwrap<QSizeWrap>(info[0]->ToObject());
      size = new QSizeWrap(*wrap->size_);
    } else {
      size = new QSizeWrap();
    }
    size->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    if (info.Length() == 1) {
      const int argc = 1;
      v8::Local<v8::Value> argv[argc] = { info[0] };
      info.GetReturnValue().Set(cons->NewInstance(argc, argv));
    } else if (info.Length() == 2) {
      const int argc = 2;
      v8::Local<v8::Value> argv[argc] = { info[0], info[1] };
      info.GetReturnValue().Set(cons->NewInstance(argc, argv));
    } else {
      info.GetReturnValue().Set(cons->NewInstance(0, {}));
    }
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

NAN_METHOD(QSizeWrap::isEmpty) {
  QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Boolean>(size->size_->isEmpty()));
}

NAN_METHOD(QSizeWrap::isNull) {
  QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Boolean>(size->size_->isNull()));
}

NAN_METHOD(QSizeWrap::isValid) {
  QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Boolean>(size->size_->isValid()));
}

NAN_METHOD(QSizeWrap::scale) {
  QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
  // TODO: info.Length() == 2
  if (info.Length() == 3) {
    int w = info[0]->IntegerValue();
    int h = info[1]->IntegerValue();
    Qt::AspectRatioMode mode = static_cast<Qt::AspectRatioMode>(info[2]->IntegerValue());
    size->size_->scale(w, h, mode);
  }
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(QSizeWrap::scaled) {
  QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
  // TODO: info.Length() == 2
  if (info.Length() == 3) {
    int w = info[0]->IntegerValue();
    int h = info[1]->IntegerValue();
    Qt::AspectRatioMode mode = static_cast<Qt::AspectRatioMode>(info[2]->IntegerValue());
    QSize size2 = size->size_->scaled(w, h, mode);
    QSizeWrap* wrap = new QSizeWrap(size2);
    info.GetReturnValue().Set(QSizeWrap::NewInstance(wrap));
    delete wrap;
  }
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(QSizeWrap::transpose) {
  QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(QSizeWrap::transposed) {
  QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
  QSize size2 = size->size_->transposed();
  QSizeWrap* wrap = new QSizeWrap(size2);
  info.GetReturnValue().Set(QSizeWrap::NewInstance(wrap));
  delete wrap;
}

NAN_METHOD(QSizeWrap::multiply) {
  QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
  if (info.Length() == 1 && info[0]->IsNumber()) {
    double number = info[0]->NumberValue();
    size->size_->operator*=(number);
  }
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(QSizeWrap::plus) {
  QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
  if (info.Length() == 1 && info[0]->IsObject()) {
    QSizeWrap* size2 = Nan::ObjectWrap::Unwrap<QSizeWrap>(info[0]->ToObject());
    size->size_->operator+=(*size2->size_);
  }
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(QSizeWrap::minus) {
  QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
  if (info.Length() == 1 && info[0]->IsObject()) {
    QSizeWrap* size2 = Nan::ObjectWrap::Unwrap<QSizeWrap>(info[0]->ToObject());
    size->size_->operator-=(*size2->size_);
  }
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(QSizeWrap::divide) {
  QSizeWrap* size = Nan::ObjectWrap::Unwrap<QSizeWrap>(info.This());
  if (info.Length() == 1 && info[0]->IsNumber()) {
    double number = info[0]->NumberValue();
    size->size_->operator/=(number);
  }
  info.GetReturnValue().Set(info.This());
}
