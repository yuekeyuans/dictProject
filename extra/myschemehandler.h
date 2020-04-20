#ifndef MYSCHEMEHANDLER_H
#define MYSCHEMEHANDLER_H

#include <QObject>
#include <QWebEngineUrlSchemeHandler>
#include <QtScript/QScriptEngine>

class MySchemeHandler : public QWebEngineUrlSchemeHandler
{
    Q_OBJECT
public:
    explicit MySchemeHandler(QObject *parent = nullptr);
    void requestStarted(QWebEngineUrlRequestJob *) override;
    QString decode(QString str);
    QScriptValue  decoder;

signals:
    void jumps(QString);

public slots:
};

#endif // MYSCHEMEHANDLER_H
