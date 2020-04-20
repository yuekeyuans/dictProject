#ifndef ENTRYWEBENGINEURLREQUESTINTERCEPTOR_H
#define ENTRYWEBENGINEURLREQUESTINTERCEPTOR_H

#include <QObject>
#include <QWebEngineUrlRequestInterceptor>

class EnTryWebEngineUrlRequestInterceptor : public QWebEngineUrlRequestInterceptor
{
    Q_OBJECT
public:
    explicit EnTryWebEngineUrlRequestInterceptor(QObject *parent = nullptr);
    void interceptRequest(QWebEngineUrlRequestInfo &info);

signals:

public slots:
};

#endif // ENTRYWEBENGINEURLREQUESTINTERCEPTOR_H
