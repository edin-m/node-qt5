#include "qapplicationwrap.h"

#include <QDebug>

#include "uv.h"

//#include "qt_eventdispatcher_libuv/src/eventdispatcher_libuv.h"
//#include "eventdispatcher.h"
//#include "../QtCoreWrap/wicked.h"
#include "qt-ed-mac/eventdispatcherlibuv.h"

namespace nodeqt {

QApplicationWrap* app;

napi_ref QApplicationWrap::constructor;

QApplicationWrap::QApplicationWrap()
  : env_(nullptr),
    wrapper_(nullptr) {
  int argc;

  // mac qt ev libuv
  auto dispatcher = new qtjs::EventDispatcherLibUv();
  QApplication::setEventDispatcher(dispatcher);

//  dispatcher->wakeUp();
  application_ = new QApplication(argc, nullptr);
  QObject::connect(application_, &QCoreApplication::aboutToQuit, [=]() {
    qDebug() << "about to quit";
  });
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
  CHECK_NAPI_RESULT(napi_define_class(env, "QApplication", -1, New, nullptr, 1, properties, &cons));

  CHECK_NAPI_RESULT(napi_create_reference(env, cons, 1, &constructor));
  CHECK_NAPI_RESULT(napi_set_named_property(env, exports, "QApplication", cons));
}

napi_value QApplicationWrap::New(napi_env env, napi_callback_info info) {
  bool is_constructor = IsConstructCall(env, info);

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

//void process_UI(uv_idle_t* handle) {
////    // Compute extra-terrestrial life
////    // fold proteins
////    // computer another digit of PI
////    // or similar
////    fprintf(stderr, "Computing PI...\n");
////    // just to avoid overwhelming your terminal emulator
//    QApplication::processEvents();
////    uv_idle_stop(handle);
//}

//uv_idle_t idler;
//uv_loop_t* loop;

NAPI_METHOD(QApplicationWrap::exec) {
  QApplicationWrap* obj;
  NAPI_UNWRAP_THIS();

//  loop = uv_default_loop();

//  uv_idle_init(loop, &idler);
//  uv_idle_start(&idler, process_UI);

  std::cout << "in 1" << std::endl;
  int result = obj->application_->exec();
//  int result = QCoreApplication::exec();
  std::cout << "in 2" << std::endl;
  napi_value val;
  std::cout << "in 3" << std::endl;
  CHECK_NAPI_RESULT(napi_create_int32(env, result, &val));
  std::cout << "in 4" << std::endl;
  return val;
//  return nullptr;
}



/*
 * Usage:
 https://groups.google.com/forum/#!topic/libuv/qSSaBRBwFoY
Qt application spawns a thread where libuv event loop will run. Calls
uv_poll there with the help of an async. Calls uv_wait in the main
thread to wait for events.

Hopefully I didn't completely miss the use case while thinking about this.
 */

}
