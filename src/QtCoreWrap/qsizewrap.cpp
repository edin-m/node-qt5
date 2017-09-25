#include "qsizewrap.h"

namespace nodeqt {

napi_ref QSizeWrap::constructor;

QSizeWrap::QSizeWrap()
  : env_(nullptr),
    wrapper_(nullptr),
    size_(new QSize) {
}

QSizeWrap::QSizeWrap(const QSize& size)
  : env_(nullptr),
    wrapper_(nullptr),
    size_(new QSize(size.width(), size.height())) {
}

QSizeWrap::~QSizeWrap() {
  delete size_;
  napi_delete_reference(env_, wrapper_);
}

void QSizeWrap::Destructor(napi_env env, void* nativeObject, void* finalize_hint) {
  reinterpret_cast<QSizeWrap*>(nativeObject)->~QSizeWrap();
}

void QSizeWrap::Init(napi_env env, napi_value exports) {
  napi_property_descriptor properties[] = {
    { "width", 0, 0, width, setWidth, 0, napi_default, 0 },
    { "height", 0, 0, height, setHeight, 0, napi_default, 0 },
    DECLARE_NAPI_METHOD("isNull", isNull),
    DECLARE_NAPI_METHOD("isValid", isValid)
  };

  napi_value cons;
  CHECK_NAPI_RESULT(napi_define_class(env, "QSize", New, nullptr, 4, properties, &cons));

  CHECK_NAPI_RESULT(napi_create_reference(env, cons, 1, &constructor));
  CHECK_NAPI_RESULT(napi_set_named_property(env, exports, "QSize", cons));
}

napi_value QSizeWrap::New(napi_env env, napi_callback_info info) {
  bool is_constructor;
  CHECK_NAPI_RESULT(napi_is_construct_call(env, info, &is_constructor));

  if (is_constructor) {
    NAPI_PULL_FN_ARGS(2);

    int width = 0;
    int height = 0;
    NAPI_FN_EXTRACT_ARG(width, 0, int32);
    NAPI_FN_EXTRACT_ARG(height, 1, int32);

    QSizeWrap* obj = new QSizeWrap();

    obj->env_ = env;
    obj->size_->setWidth(width);
    obj->size_->setHeight(height);
    CHECK_NAPI_RESULT(napi_wrap(env,
                                jsthis,
                                reinterpret_cast<void*>(obj),
                                QSizeWrap::Destructor,
                                nullptr,
                                &obj->wrapper_));
    return jsthis;
  } else {
    NAPI_PULL_FN_ARGS(2);

    const size_t argc_ = 2;
    napi_value argv_[argc_] = { args[0], args[1] };

    napi_value cons;
    CHECK_NAPI_RESULT(napi_get_reference_value(env, constructor, &cons));

    napi_value instance;
    CHECK_NAPI_RESULT(napi_new_instance(env, cons, argc_, argv_, &instance));

    return instance;
  }
}

napi_status QSizeWrap::NewInstance(napi_env env, const QSize& p, napi_value* instance) {
  const int argc = 2;
  napi_value argv[argc];
  napi_create_int32(env, p.width(), &argv[0]);
  napi_create_int32(env, p.height(), &argv[1]);

  napi_value cons;
  CHECK_NAPI_RESULT(napi_get_reference_value(env, constructor, &cons));
  return napi_new_instance(env, cons, argc, argv, instance);
}

bool QSizeWrap::IsInstanceOf(napi_env env, napi_value value) {
  return NapiInstanceOf(constructor, env, value);
}

NAPI_METHOD(QSizeWrap::width) {
  QSizeWrap* obj;
  NAPI_UNWRAP_THIS();

  napi_value val;
  CHECK_NAPI_RESULT(napi_create_int32(env, obj->size_->width(), &val));
  return val;
}

NAPI_METHOD(QSizeWrap::setWidth) {
  QSizeWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  int width = 0;
  NAPI_FN_EXTRACT_ARG(width, 0, int32);
  obj->size_->setWidth(width);
  return nullptr;
}

NAPI_METHOD(QSizeWrap::height) {
  QSizeWrap* obj;
  NAPI_UNWRAP_THIS();

  napi_value val;
  CHECK_NAPI_RESULT(napi_create_int32(env, obj->size_->height(), &val));
  return val;
}

NAPI_METHOD(QSizeWrap::setHeight) {
  QSizeWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  int height = 0;
  NAPI_FN_EXTRACT_ARG(height, 0, int32);
  obj->size_->setHeight(height);
  return nullptr;
}

NAPI_METHOD(QSizeWrap::isNull) {
  QSizeWrap* obj;
  NAPI_UNWRAP_THIS();

  napi_value result;
  CHECK_NAPI_RESULT(napi_get_boolean(env, obj->size_->isNull(), &result));
  return result;
}

NAPI_METHOD(QSizeWrap::isValid) {
  QSizeWrap* obj;
  NAPI_UNWRAP_THIS();

  napi_value result;
  CHECK_NAPI_RESULT(napi_get_boolean(env, obj->size_->isValid(), &result));
  return result;
}

}
