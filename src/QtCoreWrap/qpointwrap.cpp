#include "qpointwrap.h"

namespace nodeqt {

napi_ref QPointWrap::constructor;

QPointWrap::QPointWrap()
  : env_(nullptr),
//    value_(0),
    wrapper_(nullptr),
    point_(new QPoint) {
}

QPointWrap::QPointWrap(const QPoint& point)
  : env_(nullptr),
    wrapper_(nullptr),
    point_(new QPoint(point.x(), point.y())) {
}

QPointWrap::~QPointWrap() {
  delete point_;
  napi_delete_reference(env_, wrapper_);
}

/***** NAPI ******/

void QPointWrap::Destructor(napi_env env, void* nativeObject, void* /*finalize_hint*/) {
  reinterpret_cast<QPointWrap*>(nativeObject)->~QPointWrap();
}

void QPointWrap::Init(napi_env env, napi_value exports) {
  napi_property_descriptor properties[] = {
//    { "value", 0, 0, GetValue, SetValue, 0, napi_default, 0 },
//    DECLARE_NAPI_METHOD("plusOne", PlusOne),
//    DECLARE_NAPI_METHOD("multiply", Multiply),
    DECLARE_NAPI_METHOD("multiply", multiply),
    DECLARE_NAPI_METHOD("plus", plus),
    DECLARE_NAPI_METHOD("minus", minus),
    DECLARE_NAPI_METHOD("divide", divide),
    DECLARE_NAPI_METHOD("isNull", isNull),
    DECLARE_NAPI_METHOD("manhattanLength", manhattanLength),
    { "x", 0, 0, x, setX, 0, napi_default, 0 },
    { "y", 0, 0, y, setY, 0, napi_default, 0 }
  };

  napi_value cons;
  CHECK_NAPI_RESULT(napi_define_class(env, "QPoint", -1, New, nullptr, 8, properties, &cons));

  CHECK_NAPI_RESULT(napi_create_reference(env, cons, 1, &constructor));
  CHECK_NAPI_RESULT(napi_set_named_property(env, exports, "QPoint", cons));
}

napi_value QPointWrap::New(napi_env env, napi_callback_info info) {
  bool is_constructor = IsConstructCall(env, info);
//  CHECK_NAPI_RESULT(napi_is_construct_call(env, info, &is_constructor));

  if (is_constructor) {
    NAPI_PULL_FN_ARGS(2);

    int xpos = 0;
    int ypos = 0;

    napi_valuetype type0;
    CHECK_NAPI_RESULT(napi_typeof(env, args[0], &type0));
    if (type0 == napi_object) {
      QPointWrap* point;
      napi_value point_obj = args[0];
      CHECK_NAPI_RESULT(napi_unwrap(env, point_obj, reinterpret_cast<void**>(&point)));
      xpos = point->point_->x();
      ypos = point->point_->y();
    } else {
      NAPI_FN_EXTRACT_ARG(xpos, 0, int32);
      NAPI_FN_EXTRACT_ARG(ypos, 1, int32);
    }

    QPointWrap* obj = new QPointWrap();

    obj->env_ = env;
//    obj->value_ = (double) xpos;
    obj->point_->setX(xpos);
    obj->point_->setY(ypos);
    CHECK_NAPI_RESULT(napi_wrap(env,
                                jsthis,
                                reinterpret_cast<void*>(obj),
                                QPointWrap::Destructor,
                                nullptr,  // finalize_hint
                                &obj->wrapper_));

    return jsthis;
  } else {
    // Invoked as plain function `QPoint(...)`, turn into construct call.
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

napi_status QPointWrap::NewInstance(napi_env env, const QPoint& p, napi_value* instance) {
  const int argc = 2;
  napi_value argv[argc];
  napi_create_int32(env, p.x(), &argv[0]);
  napi_create_int32(env, p.y(), &argv[1]);

  napi_value cons;
  CHECK_NAPI_RESULT(napi_get_reference_value(env, constructor, &cons));
  return napi_new_instance(env, cons, argc, argv, instance);
}

bool QPointWrap::IsInstanceOf(napi_env env, napi_value value) {
  return NapiInstanceOf(constructor, env, value);
//  bool result = false;
//  napi_value cons;
//  CHECK_NAPI_RESULT(napi_get_reference_value(env, constructor, &cons));
//  CHECK_NAPI_RESULT(napi_instanceof(env, value, cons, &result));
//  return result;
}

//napi_value QPointWrap::GetValue(napi_env env, napi_callback_info info) {
//  QPointWrap* obj;
//  NAPI_UNWRAP_THIS();

//  napi_value num;
//  CHECK_NAPI_RESULT(napi_create_double(env, obj->value_, &num));
//  return num;
//}

//napi_value QPointWrap::SetValue(napi_env env, napi_callback_info info) {
//  QPointWrap* obj;
//  NAPI_UNWRAP_THIS_WITH_ARGS(1);

//  CHECK_NAPI_RESULT(napi_get_value_double(env, args[0], &obj->value_));
//  return nullptr;
//}

//napi_value QPointWrap::PlusOne(napi_env env, napi_callback_info info) {
//  QPointWrap* obj;
//  NAPI_UNWRAP_THIS_WITH_ARGS(1);

//  double value = 1;
//  NAPI_FN_EXTRACT_ARG(value, 0, double);

//  obj->value_ += value;

//  napi_value num;
//  CHECK_NAPI_RESULT(napi_create_double(env, obj->value_, &num));
//  return num;
//}

//napi_value QPointWrap::Multiply(napi_env env, napi_callback_info info) {
//  QPointWrap* obj;
//  NAPI_UNWRAP_THIS_WITH_ARGS(1);

//  double multiple = 1;
//  NAPI_FN_EXTRACT_ARG(multiple, 0, double);

//  // constructing new - multiplied - instance
//  napi_value cons;
//  CHECK_NAPI_RESULT(napi_get_reference_value(env, constructor, &cons));

//  const int kArgCount = 1;
//  napi_value argv[kArgCount];
//  CHECK_NAPI_RESULT(napi_create_double(env, obj->value_ * multiple, argv));

//  napi_value instance;
//  CHECK_NAPI_RESULT(napi_new_instance(env, cons, kArgCount, argv, &instance));

//  return instance;
//}

NAPI_METHOD(QPointWrap::multiply) {
  QPointWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  napi_valuetype type;
  CHECK_NAPI_RESULT(napi_typeof(env, args[0], &type));

  if (type == napi_number) {
    double value = 1;
    CHECK_NAPI_RESULT(napi_get_value_double(env, args[0], &value));
    obj->point_->operator *=(value);
  }

  return jsthis;
}

NAPI_METHOD(QPointWrap::plus) {
  QPointWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  napi_valuetype type;
  CHECK_NAPI_RESULT(napi_typeof(env, args[0], &type));

  if (type == napi_object) {
    QPointWrap* point;
    napi_value point_obj = args[0];
    CHECK_NAPI_RESULT(napi_unwrap(env, point_obj, reinterpret_cast<void**>(&point)));
    (*(obj->point_)).operator +=(*(point->point_));
  }

  return jsthis;
}

NAPI_METHOD(QPointWrap::divide) {
  QPointWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  napi_valuetype type;
  CHECK_NAPI_RESULT(napi_typeof(env, args[0], &type));

  if (type == napi_number) {
    double value = 1;
    CHECK_NAPI_RESULT(napi_get_value_double(env, args[0], &value));
    obj->point_->operator /=(value);
  }

  return jsthis;
}

NAPI_METHOD(QPointWrap::minus) {
  QPointWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  napi_valuetype type;
  CHECK_NAPI_RESULT(napi_typeof(env, args[0], &type));

  if (type == napi_object) {
    QPointWrap* point;
    napi_value point_obj = args[0];
    CHECK_NAPI_RESULT(napi_unwrap(env, point_obj, reinterpret_cast<void**>(&point)));
    (*(obj->point_)).operator -=(*(point->point_));
  }

  return jsthis;
}

NAPI_METHOD(QPointWrap::isNull) {
  QPointWrap* obj;
  NAPI_UNWRAP_THIS();

  napi_value val;
  CHECK_NAPI_RESULT(napi_get_boolean(env, obj->point_->isNull(), &val));
  return val;
}

NAPI_METHOD(QPointWrap::manhattanLength) {
  QPointWrap* obj;
  NAPI_UNWRAP_THIS();

  napi_value val;
  CHECK_NAPI_RESULT(napi_create_int32(env, obj->point_->manhattanLength(), &val));
  return val;
}

NAPI_METHOD(QPointWrap::x) {
  QPointWrap* obj;
  NAPI_UNWRAP_THIS();

  napi_value val;
  CHECK_NAPI_RESULT(napi_create_int32(env, obj->point_->x(), &val));
  return val;
}

NAPI_METHOD(QPointWrap::setX) {
  QPointWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  int xpos = 0;
  NAPI_FN_EXTRACT_ARG(xpos, 0, int32);
  obj->point_->setX(xpos);
  return nullptr;
}

NAPI_METHOD(QPointWrap::y) {
  QPointWrap* obj;
  NAPI_UNWRAP_THIS();

  napi_value val;
  CHECK_NAPI_RESULT(napi_create_int32(env, obj->point_->y(), &val));
  return val;
}

NAPI_METHOD(QPointWrap::setY) {
  QPointWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  int ypos = 0;
  NAPI_FN_EXTRACT_ARG(ypos, 0, int32);
  obj->point_->setY(ypos);
  return nullptr;
}

}
