#include "loaddict.h"
#include "ui_loaddict.h"
#include "webviewwitheditor.h"
#include <QtSql>
#include "data/appsqlite.h"
#include "data/dictmodel.h"
#include "QMessageBox"

LoadDict::LoadDict(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadDict)
{
    editor = new WebViewWithEditor(this);
    ui->setupUi(this);
    ui->container->addWidget(editor);
    connect(ui->save, &QPushButton::clicked, this, &LoadDict::save);
    connect(editor, &WebViewWithEditor::jumps, this, &LoadDict::emitJumpPage);
    connect(editor, &WebViewWithEditor::toSave, this, &LoadDict::save);
    connect(this, &LoadDict::emitViewModeChanged, editor, &WebViewWithEditor::slotViewModeChanged);

}

void LoadDict::load(){
    DictModel dictModel;
    dictModel.load();
    ui->title->setText(dictModel.title);
    editor->setHtmlValue(dictModel.html);
}

void LoadDict::save(){
    this->editor->getHtmlValue([&](QString html) {
        QSqlQuery query;
        query.prepare("update dict set html = :html");
        query.bindValue(":html", html);
        query.exec();
        QMessageBox::about(this, tr("tips"), tr("succeed saving"));
    });
}

LoadDict::~LoadDict()
{
    delete ui;
    delete editor;
}
