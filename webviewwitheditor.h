#ifndef WEBVIEWWITHEDITOR_H
#define WEBVIEWWITHEDITOR_H

#include <QWidget>
#include "QWebEngineView"
#include "extra/myschemehandler.h"
using namespace std;

namespace Ui {
class WebViewWithEditor;
}

class WebViewWithEditor : public QWidget
{
    Q_OBJECT

public:
    explicit WebViewWithEditor(QWidget *parent = nullptr);
    ~WebViewWithEditor();

private:
    Ui::WebViewWithEditor *ui;
    QWebEngineView* m_webView;
    MySchemeHandler* mySchemeHandler;
    double scaleFactor = 1;
    bool isViewMode = false;
    QString html = "";

public slots:
    void getPlainTextValue(function<void (QString)> = nullptr);
    void setPlainTextValue(QString);
    void getHtmlValue(function<void (QString)> = nullptr);
    void setHtmlValue(QString);
    void getMarkdownValue(function<void (QString)> = nullptr);
    void setMarkdownValue(QString);
    void scaleUp();
    void scaleDown();
    void setUrl(QString url = nullptr);
    void viewModeChanged();

public: signals:
    void jumps(QString);
    void toSave();
    void emitViewModeChanged();
};

#endif // WEBVIEWWITHEDITOR_H
