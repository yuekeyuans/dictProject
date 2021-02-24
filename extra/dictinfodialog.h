#ifndef DICTINFODIALOG_H
#define DICTINFODIALOG_H

#include <QDialog>

namespace Ui {
class DictInfoDialog;
}

class DictInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DictInfoDialog(QWidget *parent = nullptr);
    ~DictInfoDialog();

    void args(QString, QString, QString, QString, QString, QString);
private:
    Ui::DictInfoDialog *ui;
    QString name;
    QString path;
    QString size;
    QString count;
    QString showCount;
    QString hideCount;
    QString readableFilesize( long filesize);
};

#endif // DICTINFODIALOG_H
