#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QNetworkProxyFactory>
#include "globalsetting.h"
#include "data/appsqlite.h"
#include "data/setting.h"
#include <QUuid>
#include <QWebSocketServer>

AppSqlite* AppSqlite::_appSqlite = nullptr;

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_UseOpenGLES);
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load(":/qnote_zh_CN.qm");
    qApp->installTranslator(&translator);

    QCoreApplication::setOrganizationName("yuekeyuan");
    QCoreApplication::setOrganizationDomain("yuekeyuan.com");
    QCoreApplication::setApplicationName("dictProject");
    a.setWindowIcon(QIcon(":/res/img/dict_ico.png"));
    Setting setting;

//#ifdef COMPILE_IN_CODING
    setting.setData("exePath", "");
//#else
//    QString appPath = QCoreApplication::applicationDirPath() + "/";
//    setting.setData("exePath", appPath);
//#endif
    QString c{""};

    MainWindow w;

    //注册信息
    w.RegisterShellFileType (".dict","dict.project", "dict.project");

    //打开文件
    if(argc > 1){
        w.openDict (qApp->arguments ().at (1));
    }

    w.setWindowTitle("字典");
    w.show();

    return QApplication::exec();
}
