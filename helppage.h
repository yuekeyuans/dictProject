#ifndef HELPPAGE_H
#define HELPPAGE_H

#include <QWidget>
#include <QWebEngineView>
#include <data/basewidget.h>
namespace Ui {
class HelpPage;
}

class HelpPage : public QWidget, public BaseWidget
{
    Q_OBJECT

public:
    explicit HelpPage(QWidget *parent = nullptr);
    ~HelpPage();
    void setDefaltValue(const QString& page, const QString& val2){
        if(page == "help_md"){
            this->m_webView->load(QUrl("qrc:/res/usage/markdown.html"));
        }else if(page == "help_importExport"){
            this->m_webView->load(QUrl("qrc:/res/usage/importExport.html"));
        }else{
            this->m_webView->load(QUrl("qrc:/res/usage/guide.html"));
        }
    }

private:
    Ui::HelpPage *ui;
    QWebEngineView* m_webView;
};

#endif // HELPPAGE_H
