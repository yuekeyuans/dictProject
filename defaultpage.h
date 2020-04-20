#ifndef DEFAULTPAGE_H
#define DEFAULTPAGE_H

#include <QWidget>
#include <QToolButton>
#include "data/basewidget.h"


namespace Ui {
class DefaultPage;
}

class DefaultPage : public QWidget, public BaseWidget
{
    Q_OBJECT

public:
    explicit DefaultPage(QWidget *parent = nullptr);
    ~DefaultPage();
//    void setDefaultValue(QString val1, QString val2){
//        qDebug() << val1;
//    }

signals:
    void createNewDict();
    void openExistDict(QString dictName);
    void openHelp();

public slots:
    void updatePage();

private:
    Ui::DefaultPage *ui;
    QList<QToolButton*>* buttons;

};

#endif // DEFAULTPAGE_H
