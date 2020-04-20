#ifndef BASEWIDGET_H
#define BASEWIDGET_H
#include <memory>
#include <QString>
#include <QDebug>
class BaseWidget{
public:
    virtual void setDefaultValue(const QString& val1 = "", const QString& val2 = ""){}
    ~BaseWidget(){}

};

#endif // BASEWIDGET_H
