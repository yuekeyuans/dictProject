#ifndef MENUITEMWIDGET_H
#define MENUITEMWIDGET_H

#include <QWidget>

namespace Ui {
class MenuItemWidget;
}

class MenuItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuItemWidget(QWidget *parent = nullptr);
    ~MenuItemWidget();

private:
    Ui::MenuItemWidget *ui;
};

#endif // MENUITEMWIDGET_H
