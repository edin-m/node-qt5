#include "QRectWrap.h"

#include "QPointWrap.h"

Nan::Persistent<v8::Function> QRectWrap::constructor;

QRectWrap::QRectWrap()
  : Nan::ObjectWrap() {
  rect_ = new QRect();
}

QRectWrap::QRectWrap(int left, int top, int width, int height)
  : Nan::ObjectWrap() {
  rect_ = new QRect(left, top, width, height);
}

QRectWrap::~QRectWrap() {
  delete rect_;
}

void QRectWrap::Init(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target) {
  Nan::HandleScope scope;
  
  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(QRectWrap::New);
  ctor->SetClassName(Nan::New("QRect").ToLocalChecked());
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  
  v8::Local<v8::ObjectTemplate> proto = ctor->PrototypeTemplate();
  // Prototype
  // Nan::SetPrototypeMethod(ctor, "setHeight", setHeight);
  Nan::SetAccessor(proto, Nan::New("height").ToLocalChecked(), height, setHeight);
  Nan::SetAccessor(proto, Nan::New("width").ToLocalChecked(), width, setWidth);
  Nan::SetAccessor(proto, Nan::New("x").ToLocalChecked(), x, setX); 
  Nan::SetAccessor(proto, Nan::New("y").ToLocalChecked(), y, setY);
  Nan::SetAccessor(proto, Nan::New("bottom").ToLocalChecked(), bottom, setBottom);
  Nan::SetAccessor(proto, Nan::New("top").ToLocalChecked(), top, setTop);
  Nan::SetAccessor(proto, Nan::New("right").ToLocalChecked(), right, setRight);
  Nan::SetAccessor(proto, Nan::New("left").ToLocalChecked(), left, setLeft);

  Nan::SetPrototypeMethod(ctor, "bottomLeft", bottomLeft);
  Nan::SetPrototypeMethod(ctor, "bottomRight", bottomRight);
  Nan::SetPrototypeMethod(ctor, "center", center);

  Nan::SetPrototypeMethod(ctor, "isEmpty", isEmpty);
  Nan::SetPrototypeMethod(ctor, "isNull", isNull);
  Nan::SetPrototypeMethod(ctor, "isValid", isValid);

  constructor.Reset(ctor->GetFunction());
  Nan::Set(target, Nan::New("QRect").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(QRectWrap::New) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    QRectWrap* rect;
    if (info.Length() == 0) {
      rect = new QRectWrap();
    } else if (info.Length() == 4) {
      int left   = info[0]->IsUndefined() ? 0 : Nan::To<int>(info[0]).FromJust();
      int top    = info[1]->IsUndefined() ? 0 : Nan::To<int>(info[1]).FromJust();
      int width  = info[2]->IsUndefined() ? 0 : Nan::To<int>(info[2]).FromJust();
      int height = info[3]->IsUndefined() ? 0 : Nan::To<int>(info[3]).FromJust();
      rect = new QRectWrap(left, top, width, height);
    } else if (info.Length() == 2) {
      // TODO: not supported (QPoint, QPoint) and (QPoint, QSize)
    }
    rect->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    // TODO: support not only QRect()
    // const int argc = 1;
    // v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(0, {}));
  }
}

NAN_GETTER(QRectWrap::bottom) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(rect->rect_->bottom()));
}

NAN_METHOD(QRectWrap::bottomLeft) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  QPoint point = rect->rect_->bottomLeft();
  // TODO: check for leaks
  QPointWrap* wrap = new QPointWrap(point);
  info.GetReturnValue().Set(QPointWrap::NewInstance(wrap));
}

NAN_METHOD(QRectWrap::bottomRight) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  QPoint point = rect->rect_->bottomRight();
  QPointWrap* wrap = new QPointWrap(point);
  info.GetReturnValue().Set(QPointWrap::NewInstance(wrap));
}

NAN_METHOD(QRectWrap::center) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  QPoint point = rect->rect_->center();
  QPointWrap* wrap = new QPointWrap(point);
  info.GetReturnValue().Set(QPointWrap::NewInstance(wrap));
}

NAN_GETTER(QRectWrap::height) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(rect->rect_->height()));
}

NAN_GETTER(QRectWrap::left) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(rect->rect_->left()));
}

NAN_METHOD(QRectWrap::isEmpty) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Boolean>(rect->rect_->isEmpty()));
}

NAN_METHOD(QRectWrap::isNull) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Boolean>(rect->rect_->isNull()));
}

NAN_METHOD(QRectWrap::isValid) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Boolean>(rect->rect_->isValid()));
}

NAN_GETTER(QRectWrap::right) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(rect->rect_->right()));
}

NAN_SETTER(QRectWrap::setBottom) {
  if (value->IsNumber()) {
    QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
    rect->rect_->setBottom(value->Int32Value());
  }
}

NAN_SETTER(QRectWrap::setHeight) {
  if (value->IsNumber()) {
    QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
    rect->rect_->setHeight(value->Int32Value());
  }
}

NAN_SETTER(QRectWrap::setLeft) {
  if (value->IsNumber()) {
    QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
    rect->rect_->setLeft(value->Int32Value());
  }
}

NAN_SETTER(QRectWrap::setRight) {
  if (value->IsNumber()) {
    QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
    rect->rect_->setRight(value->Int32Value());
  }
}

NAN_SETTER(QRectWrap::setTop) {
  if (value->IsNumber()) {
    QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
    rect->rect_->setTop(value->Int32Value());
  }
}

NAN_SETTER(QRectWrap::setWidth) {
  if (value->IsNumber()) {
    QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
    rect->rect_->setWidth(value->Int32Value());
  }
}

NAN_SETTER(QRectWrap::setX) {
  if (value->IsNumber()) {
    QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
    rect->rect_->setX(value->Int32Value());
  }
}

NAN_SETTER(QRectWrap::setY) {
  if (value->IsNumber()) {
    QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
    rect->rect_->setY(value->Int32Value());
  }
}

NAN_GETTER(QRectWrap::top) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(rect->rect_->top()));
}

NAN_GETTER(QRectWrap::width) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(rect->rect_->width()));
}

NAN_GETTER(QRectWrap::x) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(rect->rect_->x()));
}

NAN_GETTER(QRectWrap::y) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  info.GetReturnValue().Set(Nan::New<v8::Number>(rect->rect_->y()));
}