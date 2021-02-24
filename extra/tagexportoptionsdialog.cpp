#include "tagexportoptionsdialog.h"
#include "ui_tagexportoptionsdialog.h"

TagExportOptionsDialog::TagExportOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TagExportOptionsDialog)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->exportToPlugin->setChecked(true);
}

TagExportOptionsDialog::~TagExportOptionsDialog()
{
    delete ui;
}


TagExportOptionsDialog::TagVal TagExportOptionsDialog::getResult()
{
    if (ui->exportOriginal->isChecked()) {
        return EXPORT_ORIGNAL;
    } else if (ui->exportToParent->isChecked()) {
        return EXPORT_TO_PARENT;
    } else if (ui->exportToPlugin->isChecked()) {
        return EXPORT_TO_PLUGIN;
    } else if (ui->exportToParentWithoutTag) {
        return EXPORT_FLAT;
    }
    return EXPORT_FLAT;
}
