QT       += core gui svg multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = "Edgware Road Signal Box"

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
    blocksection.cxx \
    dispatcher.cxx \
    framelever.cxx \
    interlocking.cxx \
    leverframe.cxx \
    main.cpp \
    ermainwindow.cxx \
    points.cpp \
    pointsindicator.cxx \
    signal.cxx \
    signalindicator.cxx \
    trackcircuit.cxx \
    traindescriber.cxx

HEADERS += \
    blocksection.hxx \
    dispatcher.hxx \
    ermainwindow.hxx \
    framelever.hxx \
    global_params.hxx \
    interlocking.hxx \
    leverframe.hxx \
    points.hxx \
    pointsindicator.hxx \
    scaling.hxx \
    service.hxx \
    signal.hxx \
    signalindicator.hxx \
    trackcircuit.hxx \
    traindescriber.hxx

FORMS += \
    ermainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    erresources.qrc
