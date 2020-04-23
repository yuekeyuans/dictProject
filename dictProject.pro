#-------------------------------------------------
#
# Project created by QtCreator 2020-01-04T15:31:27
#
#-------------------------------------------------

QT       += core gui  sql webenginewidgets script
QT       -= qml quick webengine printsupport positioning serialport quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dictProject
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

CONFIG+=resources_big

CONFIG += c++11

RC_ICONS = favoricon.ico

SOURCES += \
        DictSideBar/bodybarfilelist.cpp \
        DictSideBar/headerbar.cpp \
        DictSideBar/headerbarmenu.cpp \
        DictSideBar/headerbarsearch.cpp \
#        DictSideBar/main.cpp \
        DictSideBar/sidebar.cpp \
        DictSideBar/sidebaritem.cpp \
        DictSideBar/sidebaritemmodel.cpp \
        QXlsx/source/xlsxabstractooxmlfile.cpp \
        QXlsx/source/xlsxabstractsheet.cpp \
        QXlsx/source/xlsxcell.cpp \
        QXlsx/source/xlsxcellformula.cpp \
        QXlsx/source/xlsxcelllocation.cpp \
        QXlsx/source/xlsxcellrange.cpp \
        QXlsx/source/xlsxcellreference.cpp \
        QXlsx/source/xlsxchart.cpp \
        QXlsx/source/xlsxchartsheet.cpp \
        QXlsx/source/xlsxcolor.cpp \
        QXlsx/source/xlsxconditionalformatting.cpp \
        QXlsx/source/xlsxcontenttypes.cpp \
        QXlsx/source/xlsxdatavalidation.cpp \
        QXlsx/source/xlsxdatetype.cpp \
        QXlsx/source/xlsxdocpropsapp.cpp \
        QXlsx/source/xlsxdocpropscore.cpp \
        QXlsx/source/xlsxdocument.cpp \
        QXlsx/source/xlsxdrawing.cpp \
        QXlsx/source/xlsxdrawinganchor.cpp \
        QXlsx/source/xlsxformat.cpp \
        QXlsx/source/xlsxmediafile.cpp \
        QXlsx/source/xlsxnumformatparser.cpp \
        QXlsx/source/xlsxrelationships.cpp \
        QXlsx/source/xlsxrichstring.cpp \
        QXlsx/source/xlsxsharedstrings.cpp \
        QXlsx/source/xlsxsimpleooxmlfile.cpp \
        QXlsx/source/xlsxstyles.cpp \
        QXlsx/source/xlsxtheme.cpp \
        QXlsx/source/xlsxutility.cpp \
        QXlsx/source/xlsxworkbook.cpp \
        QXlsx/source/xlsxworksheet.cpp \
        QXlsx/source/xlsxzipreader.cpp \
        QXlsx/source/xlsxzipwriter.cpp \
        additem.cpp \
        data/appsqlite.cpp \
        data/appsqlite.cpp \
        data/dictmodel.cpp \
        data/entrymodel.cpp \
        data/dictmodel.cpp \
        data/setting.cpp \
        defaultpage.cpp \
        extra/createdictdialog.cpp \
    extra/dictinfodialog.cpp \
        extra/menuitemwidget.cpp \
        extra/myschemehandler.cpp \
        extra/sidebarselectdialog.cpp \
        helppage.cpp \
        importExport/export.cpp \
        importExport/exporttodicthtml.cpp \
        importExport/exporttoexcel.cpp \
        importExport/exporttohtml.cpp \
        importExport/exporttopdb.cpp \
        importExport/import.cpp \
        importExport/importfromexcel.cpp \
        loaddict.cpp \
        main.cpp \
        mainwindow.cpp \
        qt-json-master/json.cpp \
        webviewwitheditor.cpp

HEADERS += \
        DictSideBar/bodyBarfilelist.h \
        DictSideBar/headerbar.h \
        DictSideBar/headerbarmenu.h \
        DictSideBar/headerbarsearch.h \
        DictSideBar/sidebar.h \
        DictSideBar/sidebaritem.h \
        DictSideBar/sidebaritemmodel.h \
        QXlsx/header/xlsxabstractooxmlfile.h \
        QXlsx/header/xlsxabstractooxmlfile_p.h \
        QXlsx/header/xlsxabstractsheet.h \
        QXlsx/header/xlsxabstractsheet_p.h \
        QXlsx/header/xlsxcell.h \
        QXlsx/header/xlsxcell_p.h \
        QXlsx/header/xlsxcellformula.h \
        QXlsx/header/xlsxcellformula_p.h \
        QXlsx/header/xlsxcelllocation.h \
        QXlsx/header/xlsxcellrange.h \
        QXlsx/header/xlsxcellreference.h \
        QXlsx/header/xlsxchart.h \
        QXlsx/header/xlsxchart_p.h \
        QXlsx/header/xlsxchartsheet.h \
        QXlsx/header/xlsxchartsheet_p.h \
        QXlsx/header/xlsxcolor_p.h \
        QXlsx/header/xlsxconditionalformatting.h \
        QXlsx/header/xlsxconditionalformatting_p.h \
        QXlsx/header/xlsxcontenttypes_p.h \
        QXlsx/header/xlsxdatavalidation.h \
        QXlsx/header/xlsxdatavalidation_p.h \
        QXlsx/header/xlsxdatetype.h \
        QXlsx/header/xlsxdocpropsapp_p.h \
        QXlsx/header/xlsxdocpropscore_p.h \
        QXlsx/header/xlsxdocument.h \
        QXlsx/header/xlsxdocument_p.h \
        QXlsx/header/xlsxdrawing_p.h \
        QXlsx/header/xlsxdrawinganchor_p.h \
        QXlsx/header/xlsxformat.h \
        QXlsx/header/xlsxformat_p.h \
        QXlsx/header/xlsxglobal.h \
        QXlsx/header/xlsxmediafile_p.h \
        QXlsx/header/xlsxnumformatparser_p.h \
        QXlsx/header/xlsxrelationships_p.h \
        QXlsx/header/xlsxrichstring.h \
        QXlsx/header/xlsxrichstring_p.h \
        QXlsx/header/xlsxsharedstrings_p.h \
        QXlsx/header/xlsxsimpleooxmlfile_p.h \
        QXlsx/header/xlsxstyles_p.h \
        QXlsx/header/xlsxtheme_p.h \
        QXlsx/header/xlsxutility_p.h \
        QXlsx/header/xlsxworkbook.h \
        QXlsx/header/xlsxworkbook_p.h \
        QXlsx/header/xlsxworksheet.h \
        QXlsx/header/xlsxworksheet_p.h \
        QXlsx/header/xlsxzipreader_p.h \
        QXlsx/header/xlsxzipwriter_p.h \
        additem.h \
        data/appsqlite.h \
        data/appsqlite.h \
        data/basewidget.h \
        data/dictmodel.h \
        data/entrymodel.h \
        data/router.h \
        data/dictmodel.h \
        data/setting.h \
        defaultpage.h \
        extra/createdictdialog.h \
        extra/dictinfodialog.h \
        extra/menuitemwidget.h \
        extra/myschemehandler.h \
        extra/sidebarselectdialog.h \
        extra/testlib.h \
        extra/testlib_global.h \
        helppage.h \
        importExport/export.h \
        importExport/exporttodicthtml.h \
        importExport/exporttoexcel.h \
        importExport/exporttohtml.h \
        importExport/exporttopdb.h \
        importExport/import.h \
        importExport/importfromexcel.h \
        loaddict.h \
        mainwindow.h \
        qt-json-master/json.h \
        sqlitesource.h \
        webviewwitheditor.h

FORMS += \
        DictSideBar/bodybarfilelist.ui \
        DictSideBar/filelist.ui \
        DictSideBar/headerbar.ui \
        DictSideBar/headerbarmenu.ui \
        DictSideBar/headerbarsearch.ui \
        DictSideBar/sidebar.ui \
        DictSideBar/widget.ui \
        additem.ui \
        defaultpage.ui \
        extra/createdictdialog.ui \
        extra/dictinfodialog.ui \
        extra/menuitemwidget.ui \
        extra/sidebarselectdialog.ui \
        helppage.ui \
        loaddict.ui \
        mainwindow.ui \
        webviewwitheditor.ui

QTQUICK_COMPILER_SKIPPED_RESOURCES += page.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    DictSideBar/res.qrc \
    page.qrc \
    res.qrc \
    translator.qrc

TRANSLATIONS += qnote_zh_CN.ts

DISTFILES += \
    DictSideBar/res/img/ \
    res/

# NOTE: You can fix value of QXlsx path of source code.
  QXLSX_PARENTPATH=./QXlsx/
  QXLSX_HEADERPATH=./QXlsx/header/
  QXLSX_SOURCEPATH=./QXlsx/source/

include(qt-json-master/qt-json.pri)
include(./QXlsx/QXlsx.pri)

#SUBDIRS += \
#    QXlsx/QXlsx.pro

SUBDIRS += \
    DictSideBar/DictSideBar.pro

