QT +=         \
  core        \
  widgets     \
  gui         \
  serialbus   \
  serialport  

QMAKE_CXXFLAGS +=                         \
  -std=c++20                              \
  -Wno-deprecated-copy                    \
  -Wno-deprecated-enum-enum-conversion    \
  -Wno-deprecated-declarations            \
  -Wno-unused-parameter


INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/include/modbus

HEADERS += $$PWD/include/*.h
HEADERS += $$PWD/include/modbus/*.h

SOURCES += $$PWD/src/*.cpp
SOURCES += $$PWD/src/*.c

FORMS += $$PWD/ui/*.ui

TARGET = PWB
target.path = $$PWD
INSTALLS += target
