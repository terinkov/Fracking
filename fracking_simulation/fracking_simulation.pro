QT       += core gui
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ScoresWidget.cpp \
    frackingsettingswidget.cpp \
    graphics_parameters_widget.cpp \
    graphicswidget.cpp \
    interface_graphics_handler.cpp \
    main.cpp \
    mainwindow.cpp \
    parameters.cpp \
    startwidget.cpp

HEADERS += \
    ScoresWidget.h \
    frackingsettingswidget.h \
    graphics_parameters_widget.h \
    graphicswidget.h \
    interface_graphics_handler.h \
    mainwindow.h \
    parameters.h \
    startwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
