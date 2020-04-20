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
    void viewModeChanged();
    virtual void setDefaultValue(const QString& val1 = "", const QString& = ""){
        if(val1 != ""){
            updatePage (val1);
        }
    }


signals:
    void entryChanged();
    void jumps(QString);

private:
    Ui::addItem *ui;
    WebViewWithEditor* editor;
    EntryModel* entry;
    void updatePage(QString name);
};

#endif // ADDITEM_H
