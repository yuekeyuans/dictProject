#include "defaultpage.h"
#include "ui_defaultpage.h"
#include "data/setting.h"

DefaultPage::DefaultPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DefaultPage)
{
    ui->setupUi(this);

    buttons = new QList<QToolButton*>();

    connect(ui->createNewDict, &QToolButton::clicked, [=]{
        emit createNewDict();
    });
    connect(ui->openHelp, &QToolButton::clicked, [=]{
        emit openHelp();
    });
    updatePage();

}

DefaultPage::~DefaultPage()
{
    delete ui;
}

void DefaultPage::updatePage(){
    for(auto button: *buttons){
        buttons->removeOne(button);
        delete  button;
    }

    Setting settings;
    QList<QMap<QString, QString>> menu = settings.getSubMenu();
    QMap<QString, QString> i_map;
    foreach(i_map, menu){
        auto button = new QToolButton(this);
        button->setText(i_map.value("name"));
        ui->dictContainer->addWidget(button);
        buttons->append(button);
        connect(button, &QToolButton::clicked, [=]{
            emit this->openExistDict(i_map.values().first());
        });
        ui->dictContainer->addWidget(button);
    }
}
