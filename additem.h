#ifndef ADDITEM_H
#define ADDITEM_H

#include <QWidget>

namespace Ui {
class addItem;
}

class addItem : public QWidget
{
    Q_OBJECT

public:
    explicit addItem(QWidget *parent = nullptr);
    ~addItem();

private:
    Ui::addItem *ui;
};

#endif // ADDITEM_H
