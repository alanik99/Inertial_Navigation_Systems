QT       += core gui printsupport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RTModel
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += *.cpp
HEADERS += *.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/NavLib/release/ -lNavLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/NavLib/debug/ -lNavLib

INCLUDEPATH += $$PWD/NavLib
DEPENDPATH += $$PWD/NavLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/NavLib/release/libNavLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/NavLib/debug/libNavLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/NavLib/release/NavLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/NavLib/debug/NavLib.lib
