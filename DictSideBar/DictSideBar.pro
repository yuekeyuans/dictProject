#-------------------------------------------------
#
# Project created by QtCreator 2020-04-21T06:49:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DictSideBar
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        $$PWD/headerbar.cpp \
        $$PWD/headerbarmenu.cpp \
        $$PWD/headerbarsearch.cpp \
        $$PWD/main.cpp \
        $$PWD/sidebar.cpp \
        $$PWD/sidebaritem.cpp \
        $$PWD/sidebaritemmodel.cpp \
        $$PWD/widget.cpp \
        $$PWD/bodybarfilelist.cpp

HEADERS += \
        $$PWD/headerbar.h \
        $$PWD/headerbarmenu.h \
        $$PWD/headerbarsearch.h \
        $$PWD/sidebar.h \
        $$PWD/sidebaritem.h \
        $$PWD/sidebaritemmodel.h \
        $$PWD/widget.h \
        bodybarfilelist.h

FORMS += \
        $$PWD/headerbar.ui \
        $$PWD/headerbarmenu.ui \
        $$PWD/headerbarsearch.ui \
        $$PWD/sidebar.ui \
        $$PWD/widget.ui \
        $$PWD/bodybarfilelist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    $$PWD/res.qrc
