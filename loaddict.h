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
    WebViewWithEditor* editor{nullptr};

public slots:
    void load();
    void save();

signals:
    void emitJumpPage(EntryModel*, QString fragment);
    void emitViewModeChanged(bool);

private:
    Ui::LoadDict *ui;
};

#endif // LOADDICT_H
