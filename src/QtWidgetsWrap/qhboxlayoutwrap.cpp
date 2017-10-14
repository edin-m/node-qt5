#include "qhboxlayoutwrap.h"

#include "qwidgetwrap.h"

namespace nodeqt {

napi_ref QHBoxLayoutWrap::constructor;

QHBoxLayoutWrap::QHBoxLayoutWrap()
  : env_(nullptr),
    wrapper_(nullptr),
    layout_(new QHBoxLayout) {

}

QHBoxLayoutWrap::~QHBoxLayoutWrap() {
  delete layout_;
  napi_delete_reference(env_, wrapper_);
}

/***** NAPI ******/

void QHBoxLayoutWrap::Destructor(napi_env env, void* nativeObject, void* /*finalize_hint*/) {
  reinterpret_cast<QHBoxLayoutWrap*>(nativeObject)->~QHBoxLayoutWrap();
}

void QHBoxLayoutWrap::Init(napi_env env, napi_value exports) {
  napi_property_descriptor properties[] = {
    DECLARE_NAPI_METHOD("addWidget", addWidget),
  };

  napi_value cons;
  CHECK_NAPI_RESULT(napi_define_class(env, "QHBoxLayout", -1, New, nullptr,
                                      1,
                                      properties, &cons));

  CHECK_NAPI_RESULT(napi_create_reference(env, cons, 1, &constructor));
  CHECK_NAPI_RESULT(napi_set_named_property(env, exports, "QHBoxLayout", cons));
}

napi_value QHBoxLayoutWrap::New(napi_env env, napi_callback_info info) {
  bool is_constructor = IsConstructCall(env, info);

  if (is_constructor) {
    NAPI_PULL_FN_ARGS(1);

    QHBoxLayoutWrap* obj = new QHBoxLayoutWrap();

    QWidgetWrap* pWrap;
    if (argc == 1) {
      napi_valuetype type[argc];
      if (type[0] == napi_object) {
        napi_value parent = args[0];;
        CHECK_NAPI_RESULT(napi_unwrap(env, parent,
                                      reinterpret_cast<void**>(&pWrap)));
        obj->layout_->setParent(pWrap->widget());
      }
    }

    obj->env_ = env;
    CHECK_NAPI_RESULT(napi_wrap(env,
                                jsthis,
                                reinterpret_cast<void*>(obj),
                                QHBoxLayoutWrap::Destructor,
                                nullptr,
                                &obj->wrapper_));
    return jsthis;
  } else {

  }
}

NAPI_METHOD(QHBoxLayoutWrap::addWidget) {
  QHBoxLayoutWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  if (argc == 1) {
    QWidgetWrap* pWidget;
    napi_value parent = args[0];
    CHECK_NAPI_RESULT(napi_unwrap(env, parent,
                                  reinterpret_cast<void**>(&pWidget)));
    obj->layout_->addWidget(pWidget->widget());
  }
  return nullptr;
}

bool QHBoxLayoutWrap::IsInstanceOf(napi_env env, napi_value value) {
  return NapiInstanceOf(constructor, env, value);
}

}
