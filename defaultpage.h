#ifndef DEFAULTPAGE_H
#define DEFAULTPAGE_H

#include <QWidget>

namespace Ui {
class DefaultPage;
}

class DefaultPage : public QWidget
{
    Q_OBJECT

public:
    explicit DefaultPage(QWidget *parent = nullptr);
    ~DefaultPage();

private:
    Ui::DefaultPage *ui;
};

#endif // DEFAULTPAGE_H
