#ifndef LOADDICT_H
#define LOADDICT_H

#include <QWidget>
#include <webviewwitheditor.h>
#include <data/basewidget.h>

namespace Ui {
class LoadDict;
}

class LoadDict : public QWidget, public BaseWidget
{
    Q_OBJECT
public:
    explicit LoadDict(QWidget *parent = nullptr);
    ~LoadDict();
    void setDefaultValue(const QString& val1, const QString& val2){
    }
    WebViewWithEditor* editor;

public slots:
    void load();
    void save();
    void viewModeChanged();

signals:
    void jumps(QString);

private:
    Ui::LoadDict *ui;

};

#endif // LOADDICT_H
