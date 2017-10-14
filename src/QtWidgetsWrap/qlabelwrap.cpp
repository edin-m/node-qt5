#include "qlabelwrap.h"

#include <iostream>

#include "qwidgetwrap.h"

namespace nodeqt {

napi_ref QLabelWrap::constructor;

QLabelWrap::QLabelWrap()
  : env_(nullptr),
    wrapper_(nullptr),
    label_(new QLabel) {

}

QLabelWrap::~QLabelWrap() {
  delete label_;
  napi_delete_reference(env_, wrapper_);
}

/***** NAPI ******/

void QLabelWrap::Destructor(napi_env env, void* nativeObject, void* /*finalize_hint*/) {
  reinterpret_cast<QLabelWrap*>(nativeObject)->~QLabelWrap();
}

void QLabelWrap::Init(napi_env env, napi_value exports) {
  napi_property_descriptor properties[] = {
    { "text", 0, 0, text, setText, 0, napi_default, 0 },
    DECLARE_NAPI_METHOD("setParent", setParent),
  };

  napi_value cons;
  CHECK_NAPI_RESULT(napi_define_class(env, "QLabel", -1, New, nullptr,
                                      sizeof(properties) / sizeof(*properties),
                                      properties, &cons));

  CHECK_NAPI_RESULT(napi_create_reference(env, cons, 1, &constructor));
  CHECK_NAPI_RESULT(napi_set_named_property(env, exports, "QLabel", cons));
}

napi_value QLabelWrap::New(napi_env env, napi_callback_info info) {
  bool is_constructor = IsConstructCall(env, info);
  if (is_constructor) {
    // TODO
    NAPI_PULL_FN_ARGS(2);

    QLabelWrap* obj = new QLabelWrap();

    napi_valuetype type[argc];
    CHECK_NAPI_RESULT(napi_typeof(env, args[0], &type[0]));
    CHECK_NAPI_RESULT(napi_typeof(env, args[1], &type[1]));
    if ((argc == 1 && type[0] == napi_string) ||
        (argc == 2 && type[0] == napi_string)) {
      char buffer[128];
      size_t size = 128;
      size_t copied;
      CHECK_NAPI_RESULT(
            napi_get_value_string_utf8(
              env, args[0], buffer, size, &copied));
      obj->label_->setText(QString(buffer));
    }
    if (argc == 2 && type[1] == napi_number) {

    }
    if (argc == 2 && type[1] == napi_object) {
      QWidgetWrap* pWrap;
      napi_value parent = args[1];
      CHECK_NAPI_RESULT(napi_unwrap(env, parent,
                                    reinterpret_cast<void**>(&pWrap)));
      obj->label_->setParent(pWrap->widget());
    }

    obj->env_ = env;
    CHECK_NAPI_RESULT(napi_wrap(env,
                                 jsthis,
                                reinterpret_cast<void*>(obj),
                                QLabelWrap::Destructor,
                                nullptr,
                                &obj->wrapper_));
    return jsthis;
  } else {
    // TODO
    return nullptr;
  }
}

NAPI_METHOD(QLabelWrap::setParent) {
  QLabelWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  if (argc == 1) {
    QWidgetWrap* pWrap;
    napi_value parent = args[0];
    CHECK_NAPI_RESULT(napi_unwrap(env, parent,
                                  reinterpret_cast<void**>(&pWrap)));
    obj->label_->setParent(pWrap->widget());
  }
  return nullptr;
}

NAPI_METHOD(QLabelWrap::text) {
  QLabelWrap* obj;
  NAPI_UNWRAP_THIS();

  napi_value ret;
  QString text = obj->label_->text().toUtf8();
  QByteArray arr = text.toUtf8();
  int length = arr.size();
  CHECK_NAPI_RESULT(napi_create_string_utf8(env, text.toLatin1().data(), length, &ret));
  return ret;
}

NAPI_METHOD(QLabelWrap::setText) {
  QLabelWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  size_t buffSize = 2048;
  char buff[2048];
  size_t copied;
  CHECK_NAPI_RESULT(napi_get_value_string_utf8(env, args[0],
                    buff, buffSize, &copied));
  QString value = QString::fromUtf8(buff, copied);
  obj->label_->setText(value);
  return nullptr;
}

bool QLabelWrap::IsInstanceOf(napi_env env, napi_value value) {
  return NapiInstanceOf(constructor, env, value);
}

}
