{
  "targets": [
    {
      "target_name": "hello",
      "sources": [
      	"hello.cc",
      	"src/QtCore/QPointWrap.cc",
      	"src/QtCore/QPointFWrap.cc",
      	"src/QtCore/QRectWrap.cc",
      	"src/QtCore/QSizeWrap.cc",
        "src/QtCore/myobject.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "<!@(node utils/find-qt5.js --cflags)"
      ],
      "libraries": [
      	"<!@(node utils/find-qt5.js --libs)"
      ]
    }
  ]
}