#ifndef WEBCHANNELOBJECT_H
#define WEBCHANNELOBJECT_H

#include <QObject>
#include <data/entrymodel.h>

class WebChannelObject : public QObject
{
    Q_OBJECT
public:
    explicit WebChannelObject(QObject *parent = nullptr);
    void setCurrentEntry(const EntryModel* );

signals:
    void emitGetLinkAndAnchors(QString, QString);

public slots:
    void slotGetLinkAndAnchor(QString);

private:
    const EntryModel *entryModel{nullptr};
};

#endif // WEBCHANNELOBJECT_H
