QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dictionary.cpp \
    main.cpp \
    mainwindow.cpp \
    myswipegesture.cpp \
    offercreator.cpp \
    settings.cpp \
    training.cpp \
    translation.cpp

HEADERS += \
    dictionary.h \
    mainwindow.h \
    myswipegesture.h \
    offercreator.h \
    settings.h \
    training.h \
    translation.h

FORMS += \
    dictionary.ui \
    mainwindow.ui \
    offercreator.ui \
    settings.ui \
    training.ui \
    translation.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../api/release/ -lapi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../api/debug/ -lapi

INCLUDEPATH += $$PWD/../api
DEPENDPATH += $$PWD/../api

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../api/release/libapi.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../api/debug/libapi.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../api/release/api.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../api/debug/api.lib
