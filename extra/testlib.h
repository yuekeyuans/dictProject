#ifndef TESTLIB_H
#define TESTLIB_H

#include "testlib_global.h"
#include <QDebug>
class TESTLIBSHARED_EXPORT TestLib
{

public:
    TestLib() = default;
    void print(){
        qDebug() << "hello world";
    }
};

#endif // TESTLIB_H
