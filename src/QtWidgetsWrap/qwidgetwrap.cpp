#include "qwidgetwrap.h"

namespace nodeqt {

napi_ref QWidgetWrap::constructor;

QWidgetWrap::QWidgetWrap()
  : env_(nullptr),
    wrapper_(nullptr),
    widget_(new QWidget) {
}

QWidgetWrap::~QWidgetWrap() {
  delete widget_;
  napi_delete_reference(env_, wrapper_);
}

/***** NAPI ******/

void QWidgetWrap::Destructor(napi_env env, void* nativeObject, void* /*finalize_hint*/) {
  reinterpret_cast<QWidgetWrap*>(nativeObject)->~QWidgetWrap();
}

void QWidgetWrap::Init(napi_env env, napi_value exports) {
  napi_property_descriptor properties[] = {
    DECLARE_NAPI_METHOD("show", show),
    DECLARE_NAPI_METHOD("resize", resize)
  };

  napi_value cons;
  CHECK_NAPI_RESULT(napi_define_class(env, "QWidget", New, nullptr, 2, properties, &cons));

  CHECK_NAPI_RESULT(napi_create_reference(env, cons, 1, &constructor));
  CHECK_NAPI_RESULT(napi_set_named_property(env, exports, "QWidget", cons));
}

napi_value QWidgetWrap::New(napi_env env, napi_callback_info info) {
  bool is_constructor;
  CHECK_NAPI_RESULT(napi_is_construct_call(env, info, &is_constructor));

  if (is_constructor) {
    // TODO
    NAPI_PULL_FN_ARGS(0);

    QWidgetWrap* obj = new QWidgetWrap();
    obj->env_ = env;
    CHECK_NAPI_RESULT(napi_wrap(env,
                                jsthis,
                                reinterpret_cast<void*>(obj),
                                QWidgetWrap::Destructor,
                                nullptr,
                                &obj->wrapper_));
    return jsthis;
  } else {

  }
  return nullptr;
}

bool QWidgetWrap::IsInstanceOf(napi_env env, napi_value value) {
  return NapiInstanceOf(constructor, env, value);
}

NAPI_METHOD(QWidgetWrap::show) {
  QWidgetWrap* obj;
  NAPI_UNWRAP_THIS();

  obj->widget_->show();
  return nullptr;
}

NAPI_METHOD(QWidgetWrap::resize) {
  QWidgetWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(2);

  napi_valuetype type;
  CHECK_NAPI_RESULT(napi_typeof(env, args[0], &type));
  if (type == napi_object) {
    // TODO
  } else {
    int w = -1;
    int h = -1;
    NAPI_FN_EXTRACT_ARG(w, 0, int32);
    NAPI_FN_EXTRACT_ARG(h, 1, int32);
    obj->widget_->resize(w, h);
  }
  return nullptr;
}

}
