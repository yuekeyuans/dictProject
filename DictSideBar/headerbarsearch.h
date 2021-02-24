#ifndef HEADERBARSEARCH_H
#define HEADERBARSEARCH_H

#include <QWidget>
#include <QIcon>

namespace Ui {
class HeaderBarSearch;
}

class HeaderBarSearch : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderBarSearch(QWidget *parent = nullptr);
    ~HeaderBarSearch();

public slots:
    void slotSearchFinished();
    void slotUpdate();

signals:
    void emitCompleteSearch();
    void emitAllTextSearch(bool);
    void emitShowParagraph(bool);
    void emitTextChanged(QString);
private:
    Ui::HeaderBarSearch *ui;
    bool isAllTextSearch = false;
    QIcon allTextSearchIcon_off{":/DictSideBar/res/img/item/allTextSearch_off.png"};
    QIcon allTextSearchIcon_on{":/DictSideBar/res/img/item/allTextSearch_on.png"};
    bool isShowParagraph = false;
    QIcon showParagraph_on{":/DictSideBar/res/img/item/showParagraph_on.png"};
    QIcon showParagraph_off{":/DictSideBar/res/img/item/showParagraph_off.png"};
};

#endif // HEADERBARSEARCH_H
