#include "webviewwitheditor.h"
#include "ui_webviewwitheditor.h"

WebViewWithEditor::WebViewWithEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebViewWithEditor)
{
    ui->setupUi(this);
}

WebViewWithEditor::~WebViewWithEditor()
{
    delete ui;
}
