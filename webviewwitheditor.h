#ifndef WEBVIEWWITHEDITOR_H
#define WEBVIEWWITHEDITOR_H

#include <QWidget>
#include "QWebEngineView"
#include "extra/myschemehandler.h"
#include "data/entrymodel.h"
#include "data/setting.h"
#include "globalsetting.h"
#include <QWebChannel>
#include <QMessageBox>
#include <QMenu>
#include "data/appsqlite.h"
#include <link-anchor/webchannelobject.h>

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
    static double scaleFactor;
    const QString DEFAULT_URL = SUMMERNOTE_PATH;
    void setEntry(const EntryModel* entry);

private:
    Ui::WebViewWithEditor *ui;
    QWebEngineView* m_webView{nullptr};
    MySchemeHandler* mySchemeHandler{nullptr};
    bool isViewMode{false};
    QString html{""};
    Setting* setting{nullptr};
    QString defaultPath{""};
    QWebChannel *channel;
    WebChannelObject *webChannelObject;
    QMenu* webMenu{nullptr};
    QShortcut *saveShortCut{nullptr};

    double getScale(int);
    int getPos(double);

public slots:
    void getHtmlValue(function<void (QString)> fun);
    void getHtmlValueWithSet(EntryModel * = nullptr);
    void setHtmlValue(QString);
    void scalePage(double = 1.0);
    void setUrl(QString url = "");
    void slotViewModeChanged(bool isView);
    void slotJumpToAnchor(QString = "");
    void slotUpdateEntryCount();

public: signals:
    void jumps(EntryModel*, QString);
    void emitEntryChanged();
    void toSave();
};

#endif // WEBVIEWWITHEDITOR_H
