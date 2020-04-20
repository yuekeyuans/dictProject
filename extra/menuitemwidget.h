#ifndef MENUITEMWIDGET_H
#define MENUITEMWIDGET_H

#include <QWidget>
#include "data/entrymodel.h"
#include <QMouseEvent>

namespace Ui {
class MenuItemWidget;
}

enum WidgetType{
    TITLE,
    WITH_CHECKBOX,
    ALL_NO_CHECKBOX,
    ALL
};

class MenuItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuItemWidget(QWidget *parent = nullptr);
    explicit MenuItemWidget(QWidget* parent,
                            const WidgetType& type,
                            const QString& title = "", const bool isVisible = false,
                            const QString& content = "");

    ~MenuItemWidget();

private:
    Ui::MenuItemWidget *ui;
    QPoint mousePos;
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

signals:
    void itemClicked(const EntryModel&);

};

#endif // MENUITEMWIDGET_H
