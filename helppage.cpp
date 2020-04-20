#include "helppage.h"
#include "ui_helppage.h"
#include <QWebEngineView>

HelpPage::HelpPage(QWidget *parent) :
    QWidget(parent),BaseWidget (),
    ui(new Ui::HelpPage)
{
    this->m_webView = new QWebEngineView(this);
    ui->setupUi(this);
    ui->container->addWidget(m_webView);
}

HelpPage::~HelpPage()
{
    delete ui;
    delete m_webView;
}
