#include "utils.h"
#include <QTime>
#include <QDateTime>
#include <QtNumeric>
#include <QUuid>
#include <algorithm>
#include <string>
#include <QRandomGenerator>
using namespace std;

const QList<QChar> Utils::CHARS ={
    '0','1','2','3','4','5','6','7','8','9',
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    '_','-',
};

Utils::Utils(QObject *parent) : QObject(parent)
{
}

QString Utils::getUid (){

    QDateTime time;

    auto isd1 = QRandomGenerator::global ()->generate (); //生成随机数，即唯一标识
    auto isd2 = QRandomGenerator::global ()->generate ();
    QString uid = QString::number(time.currentMSecsSinceEpoch());
    return transform(uid.toLongLong()) + transform(isd1);
}


QString Utils::transform(qlonglong data){
    QString  b = "";
    int number = CHARS.length ();
    while((data / number) != 0){
        auto cs = (data % number);
        b = b+ CHARS.at (cs);
        data = data / number;
    }
    if(data !=  0){
        auto  cs = data;
        b = b + CHARS.at (cs);
    }
    return b;
}
