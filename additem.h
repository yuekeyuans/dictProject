#ifndef ADDITEM_H
#define ADDITEM_H

#include <QWidget>
#include "webviewwitheditor.h"
#include "data/entrymodel.h"
#include "data/basewidget.h"

namespace Ui {
class addItem;
}

class addItem : public QWidget, public BaseWidget
{
    Q_OBJECT

public:
    explicit addItem(QWidget *parent = nullptr);
    ~addItem();
    bool hasEntry(QString);

public slots:
    void save();
    void deletePage();
    void setDefaultValue(QString val1 = "",QString = "");

signals:
    void entryChanged();
    void emitJumpPage(QString);

private:
    Ui::addItem *ui;
    WebViewWithEditor* editor;
    EntryModel* entry;
    void updatePage(int id = -1);
};

#endif // ADDITEM_H
