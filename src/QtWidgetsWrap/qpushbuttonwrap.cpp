#include "qpushbuttonwrap.h"

#include <QDebug>

#include "qwidgetwrap.h"

#include "qt_helpers.h"

namespace nodeqt {

napi_ref QPushButtonWrap::constructor;

QPushButtonWrap::QPushButtonWrap()
  : env_(nullptr),
    wrapper_(nullptr),
    button_(new QPushButton) {

  QObject::connect(button_, &QPushButton::clicked, [=](bool clicked) {
    qDebug() << "clicked" << clicked;
//    napi_handle_scope scope;
//    napi_open_handle_scope(env_, &scope);
//    napi_value val;
//    napi_create_double(env_, 1.0, &val);
//    napi_valuetype emittype;
//    CHECK_NAPI_RESULT(napi_typeof(env_, val, &emittype));
//    if (emittype == napi_function) {
//      qDebug() << "emit func typeof func";
//    } else {
//      qDebug() << "emit func not typeof func";
//    }
//    napi_close_handle_scope(env_, scope);

    CHECK_NAPI_RESULT(napi_open_handle_scope(env_, &scope_));
    napi_value emit_func;
    CHECK_NAPI_RESULT(napi_get_reference_value(env_, emit_func_ref_, &emit_func));
    napi_valuetype emittype;
    CHECK_NAPI_RESULT(napi_typeof(env_, emit_func, &emittype));
    if (emittype == napi_function) {
      qDebug() << "emit func typeof func";
    } else {
      qDebug() << "emit func not typeof func";
    }
    napi_value jsthis;
    CHECK_NAPI_RESULT(napi_get_reference_value(env_, js_this_ref_, &jsthis));
    size_t argc = 2;
    napi_value argv[argc];
    CHECK_NAPI_RESULT(napi_create_string_latin1(env_, "clicked", 7, &argv[0]));
    CHECK_NAPI_RESULT(napi_get_boolean(env_, clicked, &argv[1]));
    CHECK_NAPI_RESULT(napi_call_function(env_, jsthis, emit_func, argc, argv, nullptr));
    CHECK_NAPI_RESULT(napi_close_handle_scope(env_, scope_));


//    napi_handle_scope scope;
//    CHECK_NAPI_RESULT(napi_open_handle_scope(env_, &scope));
////    napi_call_function(env_,
////                       js_this_value_,)
//    napi_value jsthis = js_this_value_;
//    napi_value result;
////    CHECK_NAPI_RESULT(napi_call_function(env_, js_this_value_,
////                                         emit_func_, 0, nullptr, &result));
//    napi_value emit_func;
//    CHECK_NAPI_RESULT(napi_get_named_property(env_, jsthis, "emit", &emit_func));
//    qDebug() << "emit func" << (emit_func == nullptr);
//    napi_valuetype emittype;
//    CHECK_NAPI_RESULT(napi_typeof(env_, emit_func, &emittype));
//    if (emittype == napi_function) {
//      qDebug() << "emit func typeof func";
//    } else {
//      qDebug() << "emit func not typeof func";
//    }
//    CHECK_NAPI_RESULT(napi_make_callback(env_, nullptr,
//                                         jsthis,
//                                         emit_func, 0,
//                                         nullptr, &result));
//    CHECK_NAPI_RESULT(napi_close_handle_scope(env_, scope));
  });
}

QPushButtonWrap::~QPushButtonWrap() {
  REMOVE_ALL_CONNECTIONS();
  CHECK_NAPI_RESULT(napi_delete_reference(env_, js_this_ref_));
  CHECK_NAPI_RESULT(napi_delete_reference(env_, emit_func_ref_));
  delete button_;
  CHECK_NAPI_RESULT(napi_delete_reference(env_, wrapper_));
}

/***** NAPI ******/

void QPushButtonWrap::Destructor(napi_env env, void* nativeObject, void* /*finalize_hint*/) {
  reinterpret_cast<QPushButtonWrap*>(nativeObject)->~QPushButtonWrap();
}

void QPushButtonWrap::Init(napi_env env, napi_value exports) {
  napi_property_descriptor properties[] = {
  };

  napi_value cons;
  CHECK_NAPI_RESULT(napi_define_class(env, "QPushButton", -1, New, nullptr,
                                      sizeof(properties) / sizeof(*properties),
                                      properties, &cons));

  CHECK_NAPI_RESULT(napi_create_reference(env, cons, 1, &constructor));
  CHECK_NAPI_RESULT(napi_set_named_property(env, exports, "QPushButton", cons));
}

napi_value QPushButtonWrap::New(napi_env env, napi_callback_info info) {
  bool is_constructor = IsConstructCall(env, info);

  if (is_constructor) {
    // TODO
    NAPI_PULL_FN_ARGS(2);

    QPushButtonWrap* obj = new QPushButtonWrap();

    napi_valuetype type[argc];
    CHECK_NAPI_RESULT(napi_typeof(env, args[0], &type[0]));
    CHECK_NAPI_RESULT(napi_typeof(env, args[1], &type[1]));
    if ((argc == 1 && type[0] == napi_string) ||
        (argc == 2 && type[0] == napi_string) // TODO || (argc == 2 && type[1] == napi_string)
        ) {
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

//    napi_create_async_work(env, resource, name, callback, completecb, (void*)data, &result);

//    napi_escapable_handle_scope scope;
//    CHECK_NAPI_RESULT(napi_open_escapable_handle_scope(env, &scope));
////    obj->js_this_value_ = jsthis;
//    CHECK_NAPI_RESULT(napi_escape_handle(env, scope, jsthis, &obj->js_this_value_));
//    CHECK_NAPI_RESULT(napi_close_escapable_handle_scope(env, scope));

    CHECK_NAPI_RESULT(napi_open_handle_scope(env, &obj->scope_));
    napi_value emit_func;
    CHECK_NAPI_RESULT(napi_get_named_property(env, jsthis, "emit", &emit_func));
    qDebug() << "emit func" << (emit_func == nullptr);
    napi_valuetype emittype;
    CHECK_NAPI_RESULT(napi_typeof(env, emit_func, &emittype));
    if (emittype == napi_function) {
      qDebug() << "emit func typeof func";
    } else {
      qDebug() << "emit func not typeof func";
    }
    napi_value argv[1];
    CHECK_NAPI_RESULT(napi_create_string_latin1(env, "clicked", 7, argv));
    CHECK_NAPI_RESULT(napi_make_callback(env, nullptr, jsthis,
                                         emit_func, 1, argv, nullptr));

    CHECK_NAPI_RESULT(napi_create_reference(env, emit_func, 1, &obj->emit_func_ref_));
    CHECK_NAPI_RESULT(napi_create_reference(env, jsthis, 1, &obj->js_this_ref_));

    CHECK_NAPI_RESULT(napi_close_handle_scope(env, obj->scope_));
//    CHECK_NAPI_RESULT(napi_call_function(env, jsthis,
//                                         obj->emit_func_, 1, argv, nullptr));

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
