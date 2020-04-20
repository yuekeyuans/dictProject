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
    editor = new WebViewWithEditor(this);
    ui->setupUi(this);
    ui->verticalLayout->addWidget(editor);

    connect(ui->saveButton, &QPushButton::clicked, this,  &addItem::save);
    connect(editor, &WebViewWithEditor::jumps, this, &addItem::jumps);
    connect(editor, &WebViewWithEditor::toSave, this, &addItem::save);
    connect(editor, &WebViewWithEditor::emitViewModeChanged, this, &addItem::viewModeChanged);
}

void addItem::save(){
    this->editor->getHtmlValue([&](QString html){
        bool isInsert = entry->id == -1;
        entry->html = html;
        entry->entry = ui->lineEdit->text();
        entry->insertOrUpdate();
        emit this->entryChanged();
        QMessageBox::about(this, tr("tips"),
                           isInsert?tr("insert succeed"):tr("update succeed"));
    });

}

void addItem::updatePage(QString name = nullptr){
    if(entry != nullptr){
        delete entry;
        entry = nullptr;
    }
    if(name == "" || name.trimmed() == "" || name == nullptr){
        entry = new EntryModel();
        ui->lineEdit->setText(entry->entry);
        editor->setHtmlValue(entry->html);
        return;
    }
    if(entry != nullptr){
        delete entry;
        entry = nullptr;
    }
    EntryModel model;
    model.entry = name;
    entry = model.copyLoad();
    ui->lineEdit->setText(entry->entry);
    editor->setHtmlValue(entry->html);
}

void addItem::deletePage(){
    entry->deleted();
    emit entryChanged();
    updatePage("");
}

bool addItem::hasEntry(QString name){
    EntryModel model;
    model.entry = name;
    return model.checkExist();
}

addItem::~addItem()
{
    delete ui;
    delete editor;
}

void addItem::viewModeChanged (){
    EntryModel model;
    model.entry = ui->lineEdit->text ();
    model.load ();
    editor->setHtmlValue (model.html);
}
