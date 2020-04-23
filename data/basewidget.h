#ifndef BASEWIDGET_H
#define BASEWIDGET_H
#include <memory>
#include <QString>
#include <QDebug>
class BaseWidget{
public:
    virtual void setDefaultValue(QString="", QString=""){
        qDebug() << "base widget";
    }
    ~BaseWidget(){}

};

#endif // BASEWIDGET_H
