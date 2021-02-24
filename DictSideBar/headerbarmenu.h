#ifndef HEADERBARMENU_H
#define HEADERBARMENU_H

#include <QWidget>
#include <QIcon>
#include <QMenu>
#include <QPushButton>
#include "extra/dictinfodialog.h"

namespace Ui {
class HeaderBarMenu;
}

class HeaderBarMenu : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderBarMenu(QWidget *parent = nullptr);
    ~HeaderBarMenu();

private:
    Ui::HeaderBarMenu *ui;
    QIcon view_off{":/DictSideBar/res/img/view-off.png"};
    QIcon view_on{":/DictSideBar/res/img/view-ons.png"};
    QIcon showTagIcon{":/DictSideBar/res/img/view-off.png"};
    bool isView{false};

public slots:
    void slotUpdate();
    void slotShowInfo();

public: signals:
    void searchButtonClicked();
    void emitAddEntry();
    void emitDeleteEntry();
    void emitViewHidden(bool);

    void emitTagAdd();
    void emitTagExpandAll();
    void emitTagFoldAll();

private slots:

private:
    void createTageMemu();
    bool isShowTag{true};
};

#endif // HEADERBARMENU_H
