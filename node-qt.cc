//#include <nan.h>

//// #include "QPointWrap.h"
////#include "src/QtCore/QPointFWrap.h"
//#include "QRectWrap.h"
////#include "src/QtCore/QSizeWrap.h"
////#include "src/QtCore/myobject.h"

//void Method(const Nan::FunctionCallbackInfo<v8::Value>& info) {
//  info.GetReturnValue().Set(Nan::New("world wtf").ToLocalChecked());
//}

//void Init(v8::Local<v8::Object> exports) {
//  // QPointWrap::Init(exports);
////  QPointFWrap::Init(exports);
////  MyObject::Init(exports);
// QRectWrap::Init(exports);
////  QSizeWrap::Init(exports);
//  	exports->Set(Nan::New("hello").ToLocalChecked(),
//  		Nan::New<v8::FunctionTemplate>(Method)->GetFunction());
//}

//NODE_MODULE(hello, Init)

//#include <napi.h>
#include <node_api.h>
#include <uv.h>

#include "src/QtCoreWrap/qpointwrap.h"
#include "src/QtCoreWrap/qrectwrap.h"
#include "src/QtCoreWrap/qsizewrap.h"

#include "src/QtWidgetsWrap/qwidgetwrap.h"
#include "src/QtWidgetsWrap/qapplicationwrap.h"
#include "src/QtWidgetsWrap/qpushbuttonwrap.h"
#include "src/QtWidgetsWrap/qlabelwrap.h"
#include "src/QtWidgetsWrap/qhboxlayoutwrap.h"

using namespace nodeqt;

//Napi::String Method(const Napi::CallbackInfo& info) {
//  Napi::Env env = info.Env();
//  return Napi::String::New(env, "world wicked");
//}

//void Init(Napi::Env env, Napi::Object exports, Napi::Object module) {
////  nodeqt::QPointWrap::Init(env.operator napi_env());
////    Napi::Object exports = Napi::Object::New(env);

////  exports.Set(Napi::String::New(env, "hello"),
////              Napi::Function::New(env, Method));
//  QPointWrap::Init(env.operator napi_env(), exports.operator napi_value());
//  QRectWrap::Init(env.operator napi_env(), exports.operator napi_value());
//  QSizeWrap::Init(env.operator napi_env(), exports.operator napi_value());

//  QWidgetWrap::Init(env.operator napi_env(), exports.operator napi_value());
//  QApplicationWrap::Init(env.operator napi_env(), exports.operator napi_value());
//  QPushButtonWrap::Init(env.operator napi_env(), exports.operator napi_value());

//}

//NODE_API_MODULE(hello, Init)

// node api 8.6 change: https://github.com/nodejs/abi-stable-node/issues/256

napi_value Init(napi_env env, napi_value exports) {
  QPointWrap::Init(env, exports);
  QRectWrap::Init(env, exports);
  QSizeWrap::Init(env, exports);

  QWidgetWrap::Init(env, exports);
  QApplicationWrap::Init(env, exports);
  QPushButtonWrap::Init(env, exports);
  QLabelWrap::Init(env, exports);
  QHBoxLayoutWrap::Init(env, exports);
  return exports;
}

NAPI_MODULE(hello, Init)
