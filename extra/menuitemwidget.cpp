#include "menuitemwidget.h"
#include "ui_menuitemwidget.h"

MenuItemWidget::MenuItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuItemWidget)
{
    ui->setupUi(this);
}

MenuItemWidget::MenuItemWidget(QWidget* parent, const WidgetType& type,
                               const QString& title, const bool isVisible,
                               const QString& content):MenuItemWidget(parent){
    int height = 60;
    if(type == WidgetType::TITLE){
        ui->checkBox->hide ();
        ui->content->hide();
        ui->line_2->hide ();
        height = 30;
    }else if(type == WidgetType::WITH_CHECKBOX){
        ui->content->hide();
        ui->line_2->hide ();
    }else if(type == WidgetType::ALL_NO_CHECKBOX){
        ui->checkBox->hide ();
    }
    this->setMaximumHeight (height);
    this->setMinimumHeight (height);
    ui->title->setText (title);
    ui->checkBox->setChecked (isVisible);
    ui->content->setText (content);
}


void MenuItemWidget::mouseReleaseEvent(QMouseEvent *ev){
    if(mousePos == QPoint(ev->x(),ev->y()) && ev->button () == Qt::LeftButton){
        EntryModel model;
        model.entry = ui->title->text ();
        model.load ();
        emit itemClicked (model);
    }
}
void MenuItemWidget::mousePressEvent(QMouseEvent *ev){
    mousePos = QPoint(ev->x(),ev->y());
}

MenuItemWidget::~MenuItemWidget()
{
    delete ui;
}
