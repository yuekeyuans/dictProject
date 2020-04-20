#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QNetworkProxyFactory>
#include "data/appsqlite.h"
#include "sidebar.h"'

AppSqlite* AppSqlite::_appSqlite = nullptr;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load(":/qnote_zh_CN.qm");
    qApp->installTranslator(&translator);

    QCoreApplication::setOrganizationName("yuekeyuan");
    QCoreApplication::setOrganizationDomain("yuekeyuan.com");
    QCoreApplication::setApplicationName("dictProject");
    a.setWindowIcon(QIcon(":/res/img/dict_ico.png"));

    MainWindow w;
    w.setWindowTitle("字典");
    w.show();

    return QApplication::exec();
}
