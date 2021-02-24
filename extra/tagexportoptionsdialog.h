#ifndef TAGEXPORTOPTIONSDIALOG_H
#define TAGEXPORTOPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class TagExportOptionsDialog;
}

class TagExportOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    enum TagVal {
        EXPORT_TO_PARENT,
        EXPORT_TO_PLUGIN,
        EXPORT_ORIGNAL,
        EXPORT_FLAT,
    };

    explicit TagExportOptionsDialog(QWidget *parent = nullptr);
    ~TagExportOptionsDialog();
    TagVal getResult();

private:
    Ui::TagExportOptionsDialog *ui;
};

#endif // TAGEXPORTOPTIONSDIALOG_H
