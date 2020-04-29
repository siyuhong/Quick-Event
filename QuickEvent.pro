QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    event/quick.h \
    event/quickcontroller.h \
    example/dialog.h \
    example/student.h \
    example/testwork.h \
    event/quickapplication.h \
    event/quickevent.h \
    event/quickwork.h \
    example/userwork.h \
    example/orderwork.h

SOURCES += \
    event/quickcontroller.cpp \
    example/dialog.cpp \
    example/student.cpp \
    example/testwork.cpp \
    event/quickapplication.cpp \
    event/quickevent.cpp \
    event/quickwork.cpp \
    example/userwork.cpp \
    main.cpp \
    example/orderwork.cpp

FORMS += \
    example/dialog.ui

DISTFILES +=
