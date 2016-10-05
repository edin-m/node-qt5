#include "QRectWrap.h"

#include "QPointWrap.h"

Nan::Persistent<v8::Function> QRectWrap::constructor;

QRectWrap::QRectWrap()
  : Nan::ObjectWrap() {
  rect_ = new QRect();
}

QRectWrap::QRectWrap(const QRect& rect)
  : Nan::ObjectWrap() {
  rect_ = new QRect(rect);
}

QRectWrap::QRectWrap(int left, int top, int width, int height)
  : Nan::ObjectWrap() {
  rect_ = new QRect(left, top, width, height);
}

QRectWrap::~QRectWrap() {
  delete rect_;
}

v8::Local<v8::Object> QRectWrap::NewInstance(QRectWrap* wrap) {
  Nan::EscapableHandleScope scope;
  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { Nan::New<v8::External>(wrap) };
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);
  return scope.Escape(instance);
}

v8::Local<v8::Object> QRectWrap::NewInstance(v8::Local<v8::Value> arg) {
  Nan::EscapableHandleScope scope;
  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { arg };
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);
  return scope.Escape(instance);
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

  Nan::SetPrototypeMethod(ctor, "adjust", adjust);
  Nan::SetPrototypeMethod(ctor, "adjusted", adjusted);
  Nan::SetPrototypeMethod(ctor, "bottomLeft", bottomLeft);
  Nan::SetPrototypeMethod(ctor, "bottomRight", bottomRight);
  Nan::SetPrototypeMethod(ctor, "center", center);
  Nan::SetPrototypeMethod(ctor, "contains", contains);

  Nan::SetPrototypeMethod(ctor, "isEmpty", isEmpty);
  Nan::SetPrototypeMethod(ctor, "isNull", isNull);
  Nan::SetPrototypeMethod(ctor, "isValid", isValid);

  constructor.Reset(ctor->GetFunction());
  Nan::Set(target, Nan::New("QRect").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(QRectWrap::New) {
  if (info.IsConstructCall()) {
    QRectWrap* rect;
    if (info.Length() == 0) {
      rect = new QRectWrap();
    } else if (info.Length() == 1 && info[0]->IsExternal()) {
      QRectWrap* wrap = static_cast<QRectWrap*>(info[0].As<v8::External>()->Value());
      rect = new QRectWrap(*wrap->rect_);
    } else if (info.Length() == 1 && info[0]->IsObject()) {
      QRectWrap* wrap = Nan::ObjectWrap::Unwrap<QRectWrap>(info[0]->ToObject());
      rect = new QRectWrap(*wrap->rect_);
    } else if (info.Length() == 2) {
      // TODO: (QPoint, QPoint)
      // TODO: (QPoint, QSize)
    } else if (info.Length() == 4) {
      int left   = info[0]->IsUndefined() ? 0 : Nan::To<int>(info[0]).FromJust();
      int top    = info[1]->IsUndefined() ? 0 : Nan::To<int>(info[1]).FromJust();
      int width  = info[2]->IsUndefined() ? 0 : Nan::To<int>(info[2]).FromJust();
      int height = info[3]->IsUndefined() ? 0 : Nan::To<int>(info[3]).FromJust();
      rect = new QRectWrap(left, top, width, height);
    }
    rect->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    // TODO: (QPoint, QPoint)
    // TODO: (QPoint, QSize)
    if (info.Length() == 1) {
      const int argc = 1;
      v8::Local<v8::Value> argv[argc] = { info[0] };
      v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
      info.GetReturnValue().Set(cons->NewInstance(argc, argv));
    } else if (info.Length() == 4) {
      const int argc = 4;
      v8::Local<v8::Value> argv[argc] = { info[0], info[1], info[2], info[3] };
      v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
      info.GetReturnValue().Set(cons->NewInstance(argc, argv));
    } else {
      info.GetReturnValue().Set(cons->NewInstance(0, {}));
    }
  }
}

NAN_METHOD(QRectWrap::adjust) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  if (info.Length() == 4) {
    int dx1 = info[0]->IsUndefined() ? 0 : info[0]->Int32Value();
    int dx2 = info[1]->IsUndefined() ? 0 : info[1]->Int32Value();
    int dx3 = info[2]->IsUndefined() ? 0 : info[2]->Int32Value();
    int dx4 = info[3]->IsUndefined() ? 0 : info[3]->Int32Value();
    rect->rect_->adjust(dx1, dx2, dx3, dx4);
  }
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(QRectWrap::adjusted) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  if (info.Length() == 4) {
    int dx1 = info[0]->IsUndefined() ? 0 : info[0]->Int32Value();
    int dx2 = info[1]->IsUndefined() ? 0 : info[1]->Int32Value();
    int dx3 = info[2]->IsUndefined() ? 0 : info[2]->Int32Value();
    int dx4 = info[3]->IsUndefined() ? 0 : info[3]->Int32Value();
    QRect rect2 = rect->rect_->adjusted(dx1, dx2, dx3, dx4);
    QRectWrap* wrap = new QRectWrap(rect2);
    info.GetReturnValue().Set(QRectWrap::NewInstance(wrap));
    delete wrap;
  } else {
    info.GetReturnValue().Set(Nan::Undefined());
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
  delete wrap;
}

NAN_METHOD(QRectWrap::bottomRight) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  QPoint point = rect->rect_->bottomRight();
  QPointWrap* wrap = new QPointWrap(point);
  info.GetReturnValue().Set(QPointWrap::NewInstance(wrap));
  delete wrap;
}

NAN_METHOD(QRectWrap::center) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  QPoint point = rect->rect_->center();
  QPointWrap* wrap = new QPointWrap(point);
  info.GetReturnValue().Set(QPointWrap::NewInstance(wrap));
  delete wrap;
}

NAN_METHOD(QRectWrap::contains) {
  QRectWrap* rect = Nan::ObjectWrap::Unwrap<QRectWrap>(info.This());
  // TODO: only supported here is (x, y)
  if (info.Length() == 2) {
    if (info[0]->IsNumber() && info[1]->IsNumber()) {
      int x = info[0]->Int32Value();
      int y = info[1]->Int32Value();
      info.GetReturnValue().Set(Nan::New<v8::Boolean>(rect->rect_->contains(x, y)));
    }
  } else {
    info.GetReturnValue().Set(Nan::Undefined());
  }
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