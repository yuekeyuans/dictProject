#include "headerbarsearch.h"
#include "ui_headerbarsearch.h"
#include <QDebug>

HeaderBarSearch::HeaderBarSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderBarSearch)
{
    ui->setupUi(this);
    connect (ui->allTextSearchButton, &QToolButton::clicked, [=]{
        ui->allTextSearchButton->setIcon (isAllTextSearch ? allTextSearchIcon_off: allTextSearchIcon_on);
        isAllTextSearch = !isAllTextSearch;
        if(isAllTextSearch){
            ui->showParagraph->setIcon (showParagraph_on);
            isShowParagraph = true;
            emit emitShowParagraph(isShowParagraph);
        }
        emit emitAllTextSearch(isAllTextSearch);
    });
    connect (ui->showParagraph, &QToolButton::clicked,[=]{
        ui->showParagraph->setIcon (isShowParagraph ? showParagraph_off:showParagraph_on);
        isShowParagraph = !isShowParagraph;
        emit emitShowParagraph(isShowParagraph);
    });
    connect(ui->searchTextEdit, &QLineEdit::textChanged, this, &HeaderBarSearch::emitTextChanged );
    connect (ui->searchTextEdit, &QLineEdit::editingFinished, this, &HeaderBarSearch::slotSearchFinished);
    connect(ui->returnButton, &QToolButton::clicked, [&]{
        ui->searchTextEdit->setText ("");
        this->slotSearchFinished ();
    });
}

void HeaderBarSearch::slotSearchFinished (){    
    if(ui->searchTextEdit->text () == ""){
        ui->showParagraph->setIcon (showParagraph_off);
        isShowParagraph = false;
        ui->allTextSearchButton->setIcon (allTextSearchIcon_off);
        isAllTextSearch = false;
        emit emitCompleteSearch();
        emit emitTextChanged ("");
        emit emitShowParagraph(isShowParagraph);
        emit emitAllTextSearch (isAllTextSearch);
    }
}

void HeaderBarSearch::slotUpdate (){

}

HeaderBarSearch::~HeaderBarSearch()
{
    delete ui;
}
