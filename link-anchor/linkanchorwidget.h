#ifndef LINKANCHORWIDGET_H
#define LINKANCHORWIDGET_H

#include <QWidget>
#include <QListView>
#include <QDialog>
#include <QMessageBox>
#include <QStringListModel>
#include "data/entrymodel.h"

namespace Ui {
class LinkAnchorWidget;
}

class LinkAnchorWidget : public QDialog
{
    Q_OBJECT

public:
    explicit LinkAnchorWidget(QWidget *parent = nullptr);
    ~LinkAnchorWidget();

    QString getAnchor();
    QString getLink();
    QString getId();
    void setCurrentModel(EntryModel *);
    void updateLinks();
    void updateAchors(QString id);

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void linkClicked(const QModelIndex &);
    void anchorClicked(const QModelIndex &);
    void slotAllTextSearch();
    void slotAccept();

private:
    Ui::LinkAnchorWidget *ui;
    QStringListModel *linkModel{nullptr};
    QStringListModel *anchorModel{nullptr};
    EntryModel *currentModel{nullptr};
    QList<QMap<QString, QString>> *links{nullptr};
    QList<QMap<QString, QString>> *anchors{nullptr};
    QString currentLink{""};
    QString currentAnchor{""};
    QString currentId{EntryModel::ENTRY_ID_NULL};
    QString searchText{""};
    bool isAllTextSearch{false};
    QIcon allTextSearchIcon_off{":/DictSideBar/res/img/item/allTextSearch_off.png"};
    QIcon allTextSearchIcon_on{":/DictSideBar/res/img/item/allTextSearch_on.png"};

};

#endif // LINKANCHORWIDGET_H
