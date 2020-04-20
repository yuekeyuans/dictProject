#ifndef LOADDICT_H
#define LOADDICT_H

#include <QWidget>

namespace Ui {
class LoadDict;
}

class LoadDict : public QWidget
{
    Q_OBJECT

public:
    explicit LoadDict(QWidget *parent = nullptr);
    ~LoadDict();

private:
    Ui::LoadDict *ui;
};

#endif // LOADDICT_H
