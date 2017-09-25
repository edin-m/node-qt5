#include "qpushbuttonwrap.h"

#include "qwidgetwrap.h"

namespace nodeqt {

napi_ref QPushButtonWrap::constructor;

QPushButtonWrap::QPushButtonWrap()
  : env_(nullptr),
    wrapper_(nullptr),
    button_(new QPushButton) {

}

QPushButtonWrap::~QPushButtonWrap() {
  delete button_;
  napi_delete_reference(env_, wrapper_);
}

/***** NAPI ******/

void QPushButtonWrap::Destructor(napi_env env, void* nativeObject, void* /*finalize_hint*/) {
  reinterpret_cast<QPushButtonWrap*>(nativeObject)->~QPushButtonWrap();
}

void QPushButtonWrap::Init(napi_env env, napi_value exports) {
  napi_property_descriptor properties[] = {
  };

  napi_value cons;
  CHECK_NAPI_RESULT(napi_define_class(env, "QPushButton", New, nullptr, 0, properties, &cons));

  CHECK_NAPI_RESULT(napi_create_reference(env, cons, 1, &constructor));
  CHECK_NAPI_RESULT(napi_set_named_property(env, exports, "QPushButton", cons));
}

napi_value QPushButtonWrap::New(napi_env env, napi_callback_info info) {
  bool is_constructor;
  CHECK_NAPI_RESULT(napi_is_construct_call(env, info, &is_constructor));

  if (is_constructor) {
    // TODO
    NAPI_PULL_FN_ARGS(2);

    QPushButtonWrap* obj = new QPushButtonWrap();

    napi_valuetype type[argc];
    CHECK_NAPI_RESULT(napi_typeof(env, args[0], &type[0]));
    CHECK_NAPI_RESULT(napi_typeof(env, args[1], &type[1]));
    if (argc == 2 && type[0] == napi_string) {
      char buffer[128];
      size_t size = 128;
      size_t copied;
      CHECK_NAPI_RESULT(
            napi_get_value_string_utf8(
              env, args[0], buffer, size, &copied));
      obj->button_->setText(QString(buffer));
    }
    if (argc == 2 && type[1] == napi_object) {
      QWidgetWrap* pWrap;
      napi_value parent = args[1];
      CHECK_NAPI_RESULT(napi_unwrap(env, parent,
                                    reinterpret_cast<void**>(&pWrap)));
      obj->button_->setParent(pWrap->widget());
    }

    obj->env_ = env;
    CHECK_NAPI_RESULT(napi_wrap(env,
                                jsthis,
                                reinterpret_cast<void*>(obj),
                                QPushButtonWrap::Destructor,
                                nullptr,
                                &obj->wrapper_));
    return jsthis;
  } else {
    // TODO
    return nullptr;
  }
}

bool QPushButtonWrap::IsInstanceOf(napi_env env, napi_value value) {
  return NapiInstanceOf(constructor, env, value);
}

}
