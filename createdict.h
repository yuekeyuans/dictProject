#ifndef DEFAULTPAGE_H
#define DEFAULTPAGE_H

#include <QWidget>
#include <QToolButton>


namespace Ui {
class DefaultPage;
}

class DefaultPage : public QWidget
{
    Q_OBJECT

public:
    explicit DefaultPage(QWidget *parent = nullptr);
    ~DefaultPage();

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
