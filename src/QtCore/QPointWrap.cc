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
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("QPoint").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Accessors
  v8::Local<v8::ObjectTemplate> proto = tpl->PrototypeTemplate();
  Nan::SetAccessor(proto, Nan::New("x").ToLocalChecked(), x, setX);
  Nan::SetAccessor(proto, Nan::New("y").ToLocalChecked(), y, setY);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "isNull", isNull);
  Nan::SetPrototypeMethod(tpl, "manhattanLength", manhattanLength);
  Nan::SetPrototypeMethod(tpl, "multiply", multiply);
  Nan::SetPrototypeMethod(tpl, "plus", plus);
  Nan::SetPrototypeMethod(tpl, "minus", minus);
  Nan::SetPrototypeMethod(tpl, "divide", divide);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("QPoint").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(QPointWrap::New) {
  if (info.IsConstructCall()) {
    QPointWrap* point;
    if (info.Length() == 2) {
      int x = info[0]->IsUndefined() ? 0 : Nan::To<int>(info[0]).FromJust();
      int y = info[1]->IsUndefined() ? 0 : Nan::To<int>(info[1]).FromJust();
      point = new QPointWrap(x, y);
    } else if (info.Length() == 1 && info[0]->IsExternal()) {
      QPointWrap* wrap = static_cast<QPointWrap*>(info[0].As<v8::External>()->Value());
      point = new QPointWrap(*wrap->point_);
    } else if (info.Length() == 1 && info[0]->IsObject()) {
      QPointWrap* wrap = Nan::ObjectWrap::Unwrap<QPointWrap>(info[0]->ToObject());
      point = new QPointWrap(*wrap->point_);
    } else {
      point = new QPointWrap();
    }
    point->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    if (info.Length() == 1) {
      const int argc = 1;
      v8::Local<v8::Value> argv[argc] = { info[0] };
      v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
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

NAN_METHOD(QPointWrap::isNull) {
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Boolean>(point->point_->isNull()));
}

NAN_METHOD(QPointWrap::manhattanLength) {
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(point->point_->manhattanLength()));
}

NAN_GETTER(QPointWrap::x) {
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(point->point_->x()));
}

NAN_GETTER(QPointWrap::y) {
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(point->point_->y()));
}

NAN_SETTER(QPointWrap::setX) {
  if (value->IsNumber()) {
    QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
    point->point_->setX(value->IntegerValue());
  }
}

NAN_SETTER(QPointWrap::setY) {
  if (value->IsNumber()) {
    QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
    point->point_->setY(value->IntegerValue());
  }
}

NAN_METHOD(QPointWrap::multiply) {
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsNumber()) {
    point->point_->operator*=(info[0]->NumberValue());
  }
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(QPointWrap::plus) {
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsObject()) {
    QPointWrap* argpoint = Nan::ObjectWrap::Unwrap<QPointWrap>(info[0]->ToObject());
    point->point_->operator+=(*(argpoint->point_));
  }
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(QPointWrap::minus) {
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsObject()) {
    QPointWrap* argpoint = Nan::ObjectWrap::Unwrap<QPointWrap>(info[0]->ToObject());
    point->point_->operator-=(*(argpoint->point_));
  }
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(QPointWrap::divide) {
  QPointWrap* point = Nan::ObjectWrap::Unwrap<QPointWrap>(info.This());
  if (info.Length() > 0 && info[0]->IsNumber()) {
    point->point_->operator/=(info[0]->NumberValue());
  }
  info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> QPointWrap::NewInstance(QPointWrap* wrap) {
  Nan::EscapableHandleScope scope;
  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { Nan::New<v8::External>(wrap) };
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);
  return scope.Escape(instance);
}

v8::Local<v8::Object> QPointWrap::NewInstance(v8::Local<v8::Value> arg) {
  Nan::EscapableHandleScope scope;
  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { arg };
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);
  return scope.Escape(instance);
}