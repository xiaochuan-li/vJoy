QT       += core gui
include(qhotkey/qhotkey.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller.cpp \
    main.cpp \
    mainwindow.cpp \
    stick.cpp \

HEADERS += \
    controller.h \
    externDetector.h \
    mainwindow.h \
    stick.h \

FORMS += \
    mainwindow.ui

INCLUDEPATH += D:/software/opencv/install/include/ \
    ./include/
LIBS += D:/software/opencv/install/x64/vc16/lib/opencv_world452.lib \
    D:/C++/Qt_test/vJoy/lib/ViGEmClient.lib \
    setupapi.lib
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
msvc{
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
    }
RESOURCES += \
    statics.qrc


CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS_DEBUG += /MTd
}

CONFIG(release, debug|release) {
    QMAKE_CXXFLAGS_RELEASE += /MT /NODEFAULTLIB:msvcrt.lib
}
