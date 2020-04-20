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
    QString getName();
    QString getPath();
    void openFileDialog();
private:
    Ui::CreateDictDialog *ui;
    void checkInput();

};

#endif // CREATEDICTDIALOG_H
