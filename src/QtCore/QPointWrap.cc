#include "QPointWrap.h"

Nan::Persistent<v8::Function> QPointWrap::constructor;

QPointWrap::QPointWrap()
  : Nan::ObjectWrap() {
  point_ = new QPoint();
}

QPointWrap::QPointWrap(const QPoint& point)
  : Nan::ObjectWrap() {
  point_ = new QPoint(point);
}

QPointWrap::QPointWrap(int x, int y)
  : Nan::ObjectWrap() {
	point_ = new QPoint(x, y);
}

QPointWrap::~QPointWrap() {
  delete point_;
}

void QPointWrap::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(QPointWrap::New);
  ctor->SetClassName(Nan::New("QPoint").ToLocalChecked());
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
  exports->Set(Nan::New("QPoint").ToLocalChecked(), ctor->GetFunction());
}

void QPointWrap::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  QPointWrap* point;
  if (info.Length() == 2) {
  	int x = info[0]->IsUndefined() ? 0 : Nan::To<int>(info[0]).FromJust();
  	int y = info[1]->IsUndefined() ? 0 : Nan::To<int>(info[1]).FromJust();

  	point = new QPointWrap(x, y);
  } else if (info.Length() == 1 && info[0]->IsExternal()) {
    QPointWrap* wrap = static_cast<QPointWrap*>(info[0].As<v8::External>()->Value());
    point = new QPointWrap(*wrap->point_);
  } else {
  	point = new QPointWrap();
  }

  point->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

void QPointWrap::isNull(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Boolean>(point->point_->isNull()));
}

void QPointWrap::x(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(point->point_->x()));
}

void QPointWrap::y(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(point->point_->y()));
}

void QPointWrap::setX(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsNumber()) {
    point->point_->setX(info[0]->NumberValue());
  }
}

void QPointWrap::setY(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsNumber()) {
    point->point_->setY(info[0]->NumberValue());
  }
}

void QPointWrap::multiply(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  if (info.Length() > 0) {
    if (info[0]->IsInt32()) {
      point->point_->operator*=((int) info[0]->IntegerValue());
    } else if (info[0]->IsNumber()) {
      point->point_->operator*=(info[0]->NumberValue());
    }
  }
}

void QPointWrap::plus(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsObject()) {
    QPointWrap* argpoint = Nan::ObjectWrap::Unwrap<QPointWrap>(info[0]->ToObject());
    point->point_->operator+=(*(argpoint->point_));
  }
}

void QPointWrap::minus(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsObject()) {
    QPointWrap* argpoint = Nan::ObjectWrap::Unwrap<QPointWrap>(info[0]->ToObject());
    point->point_->operator-=(*(argpoint->point_));
  }
}

void QPointWrap::divide(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Nan::HandleScope scope;
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsNumber()) {
    point->point_->operator/=(info[0]->NumberValue());
  }
}

v8::Local<v8::Object> QPointWrap::NewInstance(QPointWrap* wrap) {
  Nan::EscapableHandleScope scope;
  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { Nan::New<v8::External>(wrap) };
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);
  return scope.Escape(instance);
}