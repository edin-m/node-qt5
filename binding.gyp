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
        "src/node_qt5_common.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "./QtCore",
        "./QtGui",
        "./QtWidgets",
        "./",
        "./src"
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
