#include "linkanchorwidget.h"
#include "ui_linkanchorwidget.h"
#include <QDebug>
#include <QMessageBox>

LinkAnchorWidget::LinkAnchorWidget(QWidget *parent) :
    QDialog (parent),
    ui(new Ui::LinkAnchorWidget)
{
    ui->setupUi(this);
    linkModel = new QStringListModel(this);
    anchorModel = new QStringListModel(this);
    ui->anchorListView->setModel(anchorModel);
    ui->linkListView->setModel(linkModel);

    connect(ui->okbutton, &QPushButton::clicked, this, &LinkAnchorWidget::slotAccept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui->linkListView, &QListView::clicked, this, &LinkAnchorWidget::linkClicked);
    connect(ui->anchorListView, &QListView::clicked, this, &LinkAnchorWidget::anchorClicked);
    connect(ui->allTextSearch, &QToolButton::clicked, this, &LinkAnchorWidget::slotAllTextSearch);
    connect(ui->searchBox, &QLineEdit::textChanged, [=](const QString &text) {
        this->searchText = text;
        this->updateLinks();
    });
    updateLinks();
}

QString LinkAnchorWidget::getLink()
{
    return this->currentLink;
}

QString LinkAnchorWidget::getId()
{
    return this->currentId;
}

QString LinkAnchorWidget::getAnchor()
{
    return this->currentAnchor;
}

void LinkAnchorWidget::linkClicked(const QModelIndex &index)
{
    int row = index.row();
    auto mp = links->at(row);
    currentLink = mp.values().first();
    currentId = mp.keys().first();
    updateAchors(mp.keys().first());
}

void LinkAnchorWidget::slotAccept()
{
    if (currentLink == "" & currentAnchor == "") {
        QMessageBox::information(this, tr("tips"), tr("please select when submit"));
        return;
    }
    this->accept();
}

void LinkAnchorWidget::anchorClicked(const QModelIndex &index)
{
    int row = index.row();
    auto mp = anchors->at(row);
    currentAnchor = mp.keys().first();
}

void LinkAnchorWidget::slotAllTextSearch()
{
    ui->allTextSearch->setIcon(isAllTextSearch ? allTextSearchIcon_off : allTextSearchIcon_on);
    isAllTextSearch = !isAllTextSearch;
    updateLinks();
}

void LinkAnchorWidget::updateLinks()
{
    if (links != nullptr) {
        links->clear();
        delete links;
        links = nullptr;
    }
    ui->linkListView->reset();
    ui->anchorListView->reset();

    EntryModel model;
    links = model.loadNames(searchText, isAllTextSearch);
    QStringList lks;
    for (auto mp : *links) {
        lks << mp.values().first();
    }
    linkModel->setStringList(lks);

    if (currentModel != nullptr) {
        QString currentId = currentModel->id;
        int row = 0;
        for (int i = 0; i < links->length(); i++) {
            if (links->at(i).keys().first() == currentId) {
                row = i;
                break;
            }
        }
        ui->linkListView->setCurrentIndex(linkModel->index(row));
        updateAchors(currentId);
    }
}

void LinkAnchorWidget::setCurrentModel(EntryModel *model)
{
    this->currentModel = model;
}

void LinkAnchorWidget::updateAchors(QString id)
{
    if (anchors != nullptr) {
        anchors->clear();
        delete anchors;
        anchors = nullptr;
    }
    ui->anchorListView->reset();
    EntryModel model;
    anchors = model.loadAchors(id);
    QStringList aks;
    for (auto ak : *anchors) {
        aks << ak.keys().first();
    }
    anchorModel->setStringList(aks);
}

void LinkAnchorWidget::closeEvent(QCloseEvent *)
{
    reject();
}

LinkAnchorWidget::~LinkAnchorWidget()
{
    delete ui;
    delete linkModel;
    delete anchorModel;
    if (links != nullptr) {
        links->clear();
        delete links;
        links = nullptr;
    }
    if (anchors != nullptr) {
        anchors->clear();
        delete anchors;
        anchors = nullptr;
    }
}

