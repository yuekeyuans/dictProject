#include "myschemehandler.h"
#include <QWebEngineUrlRequestJob>
#include <QtScript/QScriptEngine>
#include <QFile>

MySchemeHandler::MySchemeHandler(QObject *parent) : QWebEngineUrlSchemeHandler(parent)
{

}

void MySchemeHandler::requestStarted(QWebEngineUrlRequestJob * job){
    QUrl url = job->requestUrl ();
    QScriptEngine engine;
    QFile file(":/res/other/punycode.jsx");
    file.open (QFile::ReadOnly);
    QScriptValue js = engine.evaluate (file.readAll ());
    QScriptValue  decoder  = engine.globalObject().property("toUnicode");
    QScriptValueList valueList;
    valueList << url.host();
    QString b  = decoder.call (QScriptValue(), valueList).toString ();
    file.close ();
    emit this->jumps(b);
}
