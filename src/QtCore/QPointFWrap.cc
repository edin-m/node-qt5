#include "QPointFWrap.h"

Nan::Persistent<v8::Function> QPointFWrap::constructor;

QPointFWrap::QPointFWrap()
  : Nan::ObjectWrap() {
	point_ = new QPointF();
}

QPointFWrap::QPointFWrap(double x, double y)
  : Nan::ObjectWrap() {
	point_ = new QPointF(x, y);
}

QPointFWrap::~QPointFWrap() {
  delete point_;
}

void QPointFWrap::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(QPointFWrap::New);
  ctor->SetClassName(Nan::New("QPointF").ToLocalChecked());
  ctor->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(ctor, "isNull", isNull);
  Nan::SetPrototypeMethod(ctor, "x", x);
  Nan::SetPrototypeMethod(ctor, "y", y);
  Nan::SetPrototypeMethod(ctor, "setX", setX);
  Nan::SetPrototypeMethod(ctor, "setY", setY);
  Nan::SetPrototypeMethod(ctor, "multiply", multiply);
  Nan::SetPrototypeMethod(ctor, "plus", plus);
  Nan::SetPrototypeMethod(ctor, "minus", minus);
  Nan::SetPrototypeMethod(ctor, "divide", divide);

  constructor.Reset(ctor->GetFunction());
  exports->Set(Nan::New("QPointF").ToLocalChecked(), ctor->GetFunction());
}

void QPointFWrap::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  QPointFWrap* point;
  if (info.Length() == 2) {
    double x = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();
    double y = info[1]->IsUndefined() ? 0 : Nan::To<double>(info[1]).FromJust();

  	point = new QPointFWrap(x, y);
  } else {
  	point = new QPointFWrap();
  }

  point->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void QPointFWrap::isNull(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointFWrap* point = Nan::ObjectWrap::Unwrap<QPointFWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Boolean>(point->point_->isNull()));
}

void QPointFWrap::x(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointFWrap* point = Nan::ObjectWrap::Unwrap<QPointFWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(point->point_->x()));
}

void QPointFWrap::y(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointFWrap* point = Nan::ObjectWrap::Unwrap<QPointFWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(point->point_->y()));
}

void QPointFWrap::setX(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointFWrap* point = Nan::ObjectWrap::Unwrap<QPointFWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsNumber()) {
    point->point_->setX(info[0]->NumberValue());
  }
}

void QPointFWrap::setY(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointFWrap* point = Nan::ObjectWrap::Unwrap<QPointFWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsNumber()) {
    point->point_->setY(info[0]->NumberValue());
  }
}

void QPointFWrap::multiply(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointFWrap* point = Nan::ObjectWrap::Unwrap<QPointFWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsNumber()) {
    point->point_->operator*=(info[0]->NumberValue());
  }
}

void QPointFWrap::plus(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointFWrap* point = Nan::ObjectWrap::Unwrap<QPointFWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsObject()) {
    QPointFWrap* argpoint = Nan::ObjectWrap::Unwrap<QPointFWrap>(info[0]->ToObject());
    point->point_->operator+=(*(argpoint->point_));
  }
}

void QPointFWrap::minus(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointFWrap* point = Nan::ObjectWrap::Unwrap<QPointFWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsObject()) {
    QPointFWrap* argpoint = Nan::ObjectWrap::Unwrap<QPointFWrap>(info[0]->ToObject());
    point->point_->operator-=(*(argpoint->point_));
  }
}

void QPointFWrap::divide(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointFWrap* point = Nan::ObjectWrap::Unwrap<QPointFWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsNumber()) {
    point->point_->operator/=(info[0]->NumberValue());
  }
}