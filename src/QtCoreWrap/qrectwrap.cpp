#include "qrectwrap.h"

#include "qpointwrap.h"
#include "qsizewrap.h"

namespace nodeqt {

napi_ref QRectWrap::constructor;

QRectWrap::QRectWrap()
  : env_(nullptr),
    wrapper_(nullptr),
    rect_(new QRect)
{}

QRectWrap::~QRectWrap() {
  delete rect_;
  napi_delete_reference(env_, wrapper_);
}

/***** NAPI ******/

void QRectWrap::Destructor(napi_env env, void* nativeObject, void* /*finalize_hint*/) {
  reinterpret_cast<QRectWrap*>(nativeObject)->~QRectWrap();
}

void QRectWrap::Init(napi_env env, napi_value exports) {
  napi_property_descriptor properties[] = {
    { "x", 0, 0, x, setX, 0, napi_default, 0 },
    { "y", 0, 0, y, setY, 0, napi_default, 0 },
    { "width", 0, 0, width, setWidth, 0, napi_default, 0 },
    { "height", 0, 0, height, setHeight, 0, napi_default, 0 },
    DECLARE_NAPI_METHOD("bottomLeft", bottomLeft)
  };

  napi_value cons;
  CHECK_NAPI_RESULT(napi_define_class(env, "QRect", New, nullptr, 5, properties, &cons));

  CHECK_NAPI_RESULT(napi_create_reference(env, cons, 1, &constructor));
  CHECK_NAPI_RESULT(napi_set_named_property(env, exports, "QRect", cons));
}

napi_value QRectWrap::New(napi_env env, napi_callback_info info) {
  bool is_constructor;
  CHECK_NAPI_RESULT(napi_is_construct_call(env, info, &is_constructor));

  if (is_constructor) {
    NAPI_PULL_FN_ARGS(4);

    QRectWrap* obj = new QRectWrap();

    napi_valuetype type0;
    CHECK_NAPI_RESULT(napi_typeof(env, args[0], &type0));
    if (type0 == napi_object) {
      if (argc == 2) {
        bool flagBothQPoint =
            QPointWrap::IsInstanceOf(env, args[0]) &&
            QPointWrap::IsInstanceOf(env, args[1]);
        bool flagQPointAndQSize =
            QPointWrap::IsInstanceOf(env, args[0]) &&
            QSizeWrap::IsInstanceOf(env, args[1]);
        if (flagBothQPoint) {
          QPointWrap* p1;
          QPointWrap* p2;
          CHECK_NAPI_RESULT(napi_unwrap(env, args[0], reinterpret_cast<void**>(&p1)));
          CHECK_NAPI_RESULT(napi_unwrap(env, args[1], reinterpret_cast<void**>(&p2)));
          obj->rect_->setTopLeft(*p1->point());
          obj->rect_->setBottomRight(*p2->point());
        } else if (flagQPointAndQSize) {
          QPointWrap* p;
          QSizeWrap* s;
          CHECK_NAPI_RESULT(napi_unwrap(env, args[0], reinterpret_cast<void**>(&p)));
          CHECK_NAPI_RESULT(napi_unwrap(env, args[1], reinterpret_cast<void**>(&s)));
          obj->rect_->setTopLeft(*p->point());
          obj->rect_->setSize(*s->size());
        }
      }
    } else {
      int x = 0;
      int y = 0;
      int width = 0;
      int height = 0;
      NAPI_FN_EXTRACT_ARG(x, 0, int32);
      NAPI_FN_EXTRACT_ARG(y, 1, int32);
      NAPI_FN_EXTRACT_ARG(width, 2, int32);
      NAPI_FN_EXTRACT_ARG(height, 3, int32);
      obj->rect_->setX(x);
      obj->rect_->setY(y);
      obj->rect_->setWidth(width);
      obj->rect_->setHeight(height);
    }

    obj->env_ = env;
    CHECK_NAPI_RESULT(napi_wrap(env,
                                jsthis,
                                reinterpret_cast<void*>(obj),
                                QRectWrap::Destructor,
                                nullptr,  // finalize_hint
                                &obj->wrapper_));

    return jsthis;
  } else {
    NAPI_PULL_FN_ARGS(4);

    const size_t argc_ = 4;
    napi_value argv_[argc_] = { args[0], args[1], args[2], args[3] };

    napi_value cons;
    CHECK_NAPI_RESULT(napi_get_reference_value(env, constructor, &cons));

    napi_value instance;
    CHECK_NAPI_RESULT(napi_new_instance(env, cons, argc_, argv_, &instance));

    return instance;
  }
}

NAPI_METHOD(QRectWrap::x) {
  QRectWrap* obj;
  NAPI_UNWRAP_THIS();

  napi_value val;
  CHECK_NAPI_RESULT(napi_create_int32(env, obj->rect_->x(), &val));
  return val;
}

NAPI_METHOD(QRectWrap::setX) {
  QRectWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  int x = 0;
  NAPI_FN_EXTRACT_ARG(x, 0, int32);
  obj->rect_->setX(x);
  return nullptr;
}

NAPI_METHOD(QRectWrap::y) {
  QRectWrap* obj;
  NAPI_UNWRAP_THIS();

  napi_value val;
  CHECK_NAPI_RESULT(napi_create_int32(env, obj->rect_->y(), &val));
  return val;
}

NAPI_METHOD(QRectWrap::setY) {
  QRectWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  int y = 0;
  NAPI_FN_EXTRACT_ARG(y, 0, int32);
  obj->rect_->setY(y);
  return nullptr;
}

NAPI_METHOD(QRectWrap::width) {
  QRectWrap* obj;
  NAPI_UNWRAP_THIS();

  napi_value val;
  CHECK_NAPI_RESULT(napi_create_int32(env, obj->rect_->width(), &val));
  return val;
}

NAPI_METHOD(QRectWrap::setWidth) {
  QRectWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  int width = 0;
  NAPI_FN_EXTRACT_ARG(width, 0, int32);
  obj->rect_->setWidth(width);
  return nullptr;
}

NAPI_METHOD(QRectWrap::height) {
  QRectWrap* obj;
  NAPI_UNWRAP_THIS();

  napi_value val;
  CHECK_NAPI_RESULT(napi_create_int32(env, obj->rect_->height(), &val));
  return val;
}

NAPI_METHOD(QRectWrap::setHeight) {
  QRectWrap* obj;
  NAPI_UNWRAP_THIS_WITH_ARGS(1);

  int height = 0;
  NAPI_FN_EXTRACT_ARG(height, 0, int32);
  obj->rect_->setHeight(height);
  return nullptr;
}

NAPI_METHOD(QRectWrap::bottomLeft) {
  QRectWrap* obj;
  NAPI_UNWRAP_THIS();

  QPoint point = obj->rect_->bottomLeft();

  napi_value val;
  QPointWrap::NewInstance(env, point, &val);
  return val;
}

}
