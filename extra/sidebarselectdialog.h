#ifndef SIDEBARSELECTDIALOG_H
#define SIDEBARSELECTDIALOG_H

#include <QDialog>

namespace Ui {
class SideBarSelectDialog;
}

class SideBarSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SideBarSelectDialog(QWidget *parent = nullptr);
    ~SideBarSelectDialog();

private:
    Ui::SideBarSelectDialog *ui;
};

#endif // SIDEBARSELECTDIALOG_H
