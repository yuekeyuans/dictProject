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

signals:
    void jumps(QString, QString, QString);

public slots:

private:
    QString decode(QString str);
};

#endif // MYSCHEMEHANDLER_H
