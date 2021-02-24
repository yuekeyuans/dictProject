#ifndef HEADERBAR_H
#define HEADERBAR_H

#include <QWidget>
#include "DictSideBar/headerbarsearch.h"
#include "DictSideBar/headerbarmenu.h"

namespace Ui {
class HeaderBar;
}

class HeaderBar : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderBar(QWidget *parent = nullptr);
    ~HeaderBar();
signals:
    void emitAllTextSearch(bool);
    void emitShowParagraph(bool);
    void emitViewHidden(bool);
    void emitTextChanged(QString);
    void emitAddEntry();
    void emitDeleteEntry();
    void emitUpdateHeaderBar();
    void emitTagAdd();
    void emitTagsExpandAll();
    void emitTagsFoldAll();

public slots:
    void slotUpdate();


private:
    Ui::HeaderBar *ui;
    HeaderBarSearch* barSearch{nullptr};
    HeaderBarMenu* barMenu{nullptr};
};

#endif // HEADERBAR_H
