{
  "targets": [
    {
      "target_name": "node-qt",
      'dependencies': [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "sources": [
        "node-qt.cc",
        "src/QtCoreWrap/qpointwrap.cpp",
        "src/QtCoreWrap/qrectwrap.cpp",
        "src/QtCoreWrap/qsizewrap.cpp",
        "src/QtWidgetsWrap/qapplicationwrap.cpp",
        "src/QtWidgetsWrap/qwidgetwrap.cpp",
        "src/QtWidgetsWrap/qpushbuttonwrap.cpp",
        "src/QtWidgetsWrap/qlabelwrap.cpp",
        "src/QtWidgetsWrap/qhboxlayoutwrap.cpp",
        "src/node_qt5_common.cpp",
      #  "src/QtCoreWrap/wicked.cpp"
      #  "src/eventdispatcher.cpp"
      #  "qt_eventdispatcher_libuv/src/eventdispatcher_libuv.cpp",
      #  "qt_eventdispatcher_libuv/src/eventdispatcher_libuv_p.cpp",
      #  "qt_eventdispatcher_libuv/src/socknot_p.cpp",
      #  "qt_eventdispatcher_libuv/src/timers_p.cpp",
      #  "<!(moc qt_eventdispatcher_libuv/src/eventdispatcher_libuv.h -o qt_eventdispatcher_libuv/src/moc_eventdispatcher_libuv.cpp && echo qt_eventdispatcher_libuv/src/moc_eventdispatcher_libuv.cpp)"

         "src/qt-ed-mac/eventdispatcherlibuv.cpp",
         "src/qt-ed-mac/eventdispatcherlibuv/async_channel.cpp",
         "src/qt-ed-mac/eventdispatcherlibuv/libuv_api.cpp",
         "src/qt-ed-mac/eventdispatcherlibuv/socket_notifier.cpp",
         "src/qt-ed-mac/eventdispatcherlibuv/time_tracker.cpp",
         "src/qt-ed-mac/eventdispatcherlibuv/timer_notifier.cpp",
         "<!(moc src/qt-ed-mac/eventdispatcherlibuv.h -o src/qt-ed-mac/moc_eventdispatcherlibuv.cpp && echo src/qt-ed-mac/moc_eventdispatcherlibuv.cpp)"
      ],
      "include_dirs": [
      "./QtCore",
      "./QtCore/5.8.0",
      "./QtCore/5.8.0/QtCore",
        "./QtGui",
        "./QtGui/5.8.0",
        "./QtGui/5.8.0/QtGui",
        "./QtWidgets",
        "./",
        "./src",
        "/Users/edin-m/Qt/5.8/clang_64/mkspecs/macx-clang/"
      ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "xcode_settings": {
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "CLANG_CXX_LIBRARY": "libc++",
        "MACOSX_DEPLOYMENT_TARGET": "10.7"
      },
      'msvs_settings': {
          'VCCLCompilerTool': { 'ExceptionHandling': 1 },
      },
      'conditions': [
        ['OS=="mac"', {
          "libraries": [
            '-Wl,-rpath,/Users/edin-m/Qt/5.8/clang_64/lib',
            '-framework QtGui',
            '-framework QtCore',
            '-F/Users/edin-m/Qt/5.8/clang_64/lib -framework QtWidgets',
          ]
        }]
      ]
    }
  ]
}
