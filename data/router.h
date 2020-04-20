#ifndef ROUTER_H
#define ROUTER_H

#include <QtCore>
#include <data/basewidget.h>

class Router
{
public:
    Router() = default;
    explicit Router(QString name, int order, BaseWidget* widget){
        this->name = name;
        this->order = order;
        this->widget = widget;
    }

    QString name;
    int order;
    BaseWidget* widget;
};

#endif // ROUTER_H
