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

    ui->setupUi(this);
    editor = new WebViewWithEditor(this);
    ui->verticalLayout->addWidget(editor);

    connect(ui->saveButton, &QPushButton::clicked, this,  &addItem::save);
    connect(editor, &WebViewWithEditor::jumps, this, &addItem::emitJumpPage);
    connect(editor, &WebViewWithEditor::toSave, this, &addItem::save);
    //connect(editor, &WebViewWithEditor::emitViewModeChanged, this, &addItem::viewModeChanged);
}

void addItem::save(){
    this->editor->getHtmlValue([&](QString html){
        bool isInsert = entry->id == -1;
        entry->html = html;
        entry->entry = ui->lineEdit->text();
        if(entry->entry == ""){
            QMessageBox::about (this,"tips","complete the infomation");
            return;
        }
        entry->insertOrUpdate();
        emit this->entryChanged();
        QMessageBox::about(this, tr("tips"),
                           isInsert?tr("insert succeed"):tr("update succeed"));
    });
}

void addItem::updatePage(int id){
    if(entry != nullptr){
        delete entry;
        entry = nullptr;
    }
    if(id == -1){
        entry = new EntryModel();
    }else{
        EntryModel model{id};
        entry = model.copyLoad();
    }
    ui->lineEdit->setText(entry->entry);
    editor->setHtmlValue(entry->html);
}

void addItem::deletePage(){
    entry->deleted();
    emit entryChanged();
    updatePage();
}

void addItem::setDefaultValue (QString  val1,QString val2){
    updatePage (val1 == "" ? -1:val1.toInt ());
}

bool addItem::hasEntry(QString name){
    EntryModel model{name};
    return model.checkExist();
}

addItem::~addItem()
{
    delete ui;
    delete editor;
    if(entry != nullptr){
        delete entry;
    }
}
