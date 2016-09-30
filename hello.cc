#include <nan.h>

#include "src/QtCore/QPointWrap.h"
#include "src/QtCore/QPointFWrap.h"
#include "src/QtCore/QRectWrap.h"

void Method(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  info.GetReturnValue().Set(Nan::New("world wtf").ToLocalChecked());
}

void Init(v8::Local<v8::Object> exports) {
  QPointWrap::Init(exports);
  QPointFWrap::Init(exports);
  QRectWrap::Init(exports);
  	exports->Set(Nan::New("hello").ToLocalChecked(), 
  		Nan::New<v8::FunctionTemplate>(Method)->GetFunction());
}

NODE_MODULE(hello, Init)