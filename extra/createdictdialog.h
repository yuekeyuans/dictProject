#ifndef CREATEDICTDIALOG_H
#define CREATEDICTDIALOG_H

#include <QDialog>

namespace Ui {
class CreateDictDialog;
}

class CreateDictDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateDictDialog(QWidget *parent = nullptr);
    ~CreateDictDialog();

private:
    Ui::CreateDictDialog *ui;
};

#endif // CREATEDICTDIALOG_H
