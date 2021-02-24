#include "additem.h"
#include "ui_additem.h"
#include "webviewwitheditor.h"
#include <QSqlQuery>
#include "data/entrymodel.h"
#include <QMessageBox>
#include <QThread>

addItem::addItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addItem)
{
    entry = new EntryModel();
    isAddEntry = true;

    ui->setupUi(this);
    editor = new WebViewWithEditor(this);
    ui->verticalLayout->addWidget(editor);

    connect(ui->saveButton, &QPushButton::clicked, this,  &addItem::save);
    connect(editor, &WebViewWithEditor::jumps, this, &addItem::emitJumpPage);
    connect(editor, &WebViewWithEditor::toSave, this, &addItem::save);
    connect(this, &addItem::emitViewModeChanged, editor, &WebViewWithEditor::slotViewModeChanged);
    connect(this, &addItem::emitViewModeChanged, [&](bool viewMode){ui->lineEdit->setEnabled (!viewMode);});
    connect(this, &addItem::emitSetHtmlValue, editor, &WebViewWithEditor::setHtmlValue);
    connect(this, &addItem::emitGetHtmlValue, editor, &WebViewWithEditor::getHtmlValueWithSet);
    connect(editor, &WebViewWithEditor::emitEntryChanged, this, &addItem::entryChanged);
    connect(this, &addItem::emitSideBarUpdated, editor, &WebViewWithEditor::slotUpdateEntryCount);
}

void addItem::save(){
    entry->entry = this->ui->lineEdit->text();
    editor->setEntry(this->entry);
    emit emitGetHtmlValue(this->entry);
}

void addItem::updatePage(){
    if(this->entry != nullptr){
        ui->lineEdit->setText(this->entry->entry);
        editor->setEntry(this->entry);
        emit emitSetHtmlValue(entry->html);
    }
}

void addItem::setDefaultValue (QString  val1,QString){
    updatePage ();
    if(val1 !=""){
        editor->slotJumpToAnchor (val1);
    }
}

void addItem::setEntryModel(EntryModel *entryModel)
{
    if (entry != nullptr && isAddEntry) {
        delete entry;
        entry = nullptr;
    }
    this->entry = entryModel == nullptr ? new EntryModel : entryModel;
    isAddEntry = entry->id == EntryModel::ENTRY_ID_NULL;
}

addItem::~addItem()
{
    delete ui;
    delete editor;
    if(entry != nullptr &&isAddEntry){
        delete entry;
        entry = nullptr;
    }
}
