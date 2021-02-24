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

public slots:
    void save();
    void setDefaultValue(QString val1 = "",QString = "");
    void setEntryModel(EntryModel *);

signals:
    void entryChanged();
    void emitJumpPage(EntryModel*, QString fragment);
    void emitViewModeChanged(bool);
    void emitSetHtmlValue(QString);
    void emitGetHtmlValue(EntryModel*);
    void emitSideBarUpdated();

private:
    Ui::addItem *ui;
    WebViewWithEditor* editor{nullptr};
    EntryModel* entry{nullptr};
    void updatePage();
    bool isViewMode{false};
    bool isAddEntry{false};
};

#endif // ADDITEM_H
