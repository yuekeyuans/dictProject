#include "myschemehandler.h"
#include <QWebEngineUrlRequestJob>
#include <QtScript/QScriptEngine>
#include <QFile>
#include <QDebug>

MySchemeHandler::MySchemeHandler(QObject *parent) : QWebEngineUrlSchemeHandler(parent)
{

}

void MySchemeHandler::requestStarted(QWebEngineUrlRequestJob * job){
    QUrl url = job->requestUrl ();
    QScriptEngine engine;
    QFile file(":/punycode.jsx");
    file.open (QFile::ReadOnly);
    QScriptValue js = engine.evaluate (file.readAll ());
    QScriptValue  decoder  = engine.globalObject().property("toUnicode");
    QScriptValueList valueList;
    valueList << url.host();
    QString host  = decoder.call (QScriptValue(), valueList).toString ();
    QString path = url.path().replace ("/", "");
    QString fragment = url.fragment ();
    file.close ();
    emit this->jumps(host, path, fragment);
}
