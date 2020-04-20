#ifndef ENTRYWEBENGINEURLREQUESTINTERCEPTOR_H
#define ENTRYWEBENGINEURLREQUESTINTERCEPTOR_H

#include <QObject>

class EnTryWebEngineUrlRequestInterceptor : public QObject
{
    Q_OBJECT
public:
    explicit EnTryWebEngineUrlRequestInterceptor(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ENTRYWEBENGINEURLREQUESTINTERCEPTOR_H
