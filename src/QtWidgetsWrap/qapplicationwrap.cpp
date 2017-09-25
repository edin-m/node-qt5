#include "qapplicationwrap.h"

#include "uv.h"

namespace nodeqt {

QApplicationWrap* app;

napi_ref QApplicationWrap::constructor;

QApplicationWrap::QApplicationWrap()
  : env_(nullptr),
    wrapper_(nullptr) {
  int argc;
  application_ = new QApplication(argc, nullptr);
}

QApplicationWrap::~QApplicationWrap() {
  delete application_;
  napi_delete_reference(env_, wrapper_);
}

/***** NAPI ******/

void QApplicationWrap::Destructor(napi_env env, void* nativeObject, void* /*finalize_hint*/) {
  reinterpret_cast<QApplicationWrap*>(nativeObject)->~QApplicationWrap();
}

void QApplicationWrap::Init(napi_env env, napi_value exports) {
  napi_property_descriptor properties[] = {
    DECLARE_NAPI_METHOD("exec", exec)
  };

  napi_value cons;
  CHECK_NAPI_RESULT(napi_define_class(env, "QApplication", New, nullptr, 1, properties, &cons));

  CHECK_NAPI_RESULT(napi_create_reference(env, cons, 1, &constructor));
  CHECK_NAPI_RESULT(napi_set_named_property(env, exports, "QApplication", cons));
}

napi_value QApplicationWrap::New(napi_env env, napi_callback_info info) {
  bool is_constructor;
  CHECK_NAPI_RESULT(napi_is_construct_call(env, info, &is_constructor));

  if (is_constructor) {
    // TODO
    NAPI_PULL_FN_ARGS(0);

    QApplicationWrap* obj = new QApplicationWrap();
    app = obj;
    obj->env_ = env;
    CHECK_NAPI_RESULT(napi_wrap(env,
                                jsthis,
                                reinterpret_cast<void*>(obj),
                                QApplicationWrap::Destructor,
                                nullptr,
                                &obj->wrapper_));
    return jsthis;
  } else {

  }
  return nullptr;
}

bool QApplicationWrap::IsInstanceOf(napi_env env, napi_value value) {
  return NapiInstanceOf(constructor, env, value);
}

void process_UI(uv_idle_t* handle) {
//    // Compute extra-terrestrial life
//    // fold proteins
//    // computer another digit of PI
//    // or similar
//    fprintf(stderr, "Computing PI...\n");
//    // just to avoid overwhelming your terminal emulator
    QApplication::processEvents();
//    uv_idle_stop(handle);
}

uv_idle_t idler;
uv_loop_t* loop;

NAPI_METHOD(QApplicationWrap::exec) {
  QApplicationWrap* obj;
  NAPI_UNWRAP_THIS();

  loop = uv_default_loop();

  uv_idle_init(loop, &idler);
  uv_idle_start(&idler, process_UI);

//  int result = obj->application_->exec();
//  napi_value val;
//  CHECK_NAPI_RESULT(napi_create_int32(env, result, &val));
//  return val;
  return nullptr;
}

}
