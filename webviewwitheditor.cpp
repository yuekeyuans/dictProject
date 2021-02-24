#include "webviewwitheditor.h"
#include "ui_webviewwitheditor.h"
#include "QWebEngineView"
#include "QWebEngineSettings"
#include "QWebEngineCallback"
#include "QShortcut"
#include <QAction>
#include <QWebEngineProfile>
#include "extra/myschemehandler.h"
#include <QWebEngineUrlScheme>
#include <QTextDocument>
#include <data/entrymodel.h>
#include <QNetworkProxyFactory>
#include "data/dictmodel.h"
#include <QMenu>

double WebViewWithEditor::scaleFactor = 1.0;

WebViewWithEditor::WebViewWithEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebViewWithEditor)
{
    ui->setupUi(this);

    mySchemeHandler = new MySchemeHandler(this);
    setting = new Setting();
    defaultPath = setting->getData ("exePath");
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::AutoLoadImages, true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::HyperlinkAuditingEnabled, true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::JavascriptCanPaste, true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::WebGLEnabled, true);
    QWebEngineSettings::defaultSettings()->setUnknownUrlSchemePolicy(QWebEngineSettings::AllowAllUnknownUrlSchemes);
    QWebEngineProfile::defaultProfile()->installUrlSchemeHandler("entry",mySchemeHandler);

    m_webView = new QWebEngineView();

    ui->container->addWidget(m_webView);
    setUrl ();

    channel = new QWebChannel(this);
    webChannelObject = new WebChannelObject(this);
    channel->registerObject("WebChannelObject", webChannelObject);
    m_webView->page()->setWebChannel(channel);

    scaleFactor = setting->getScaleFactor ();
    ui->scaleCount->setText (QString::number (int(scaleFactor * 100)) + "%");
    ui->scaleSlider->setValue (getPos (scaleFactor));

    //保存
    saveShortCut = new QShortcut(QKeySequence(tr("ctrl+s")), this);
    connect(saveShortCut, &QShortcut::activated, this, &WebViewWithEditor::toSave);

    connect(mySchemeHandler, &MySchemeHandler::jumps, [&](QString ,QString path, QString fragment){
        if(path != EntryModel::ENTRY_ID_NULL){
            EntryModel model;
            model.id = path;
            model.load ();
            if(model.id != -1){
                emit jumps(&model, fragment);
            }
        }
    });

    connect(m_webView, &QWebEngineView::loadFinished, this, [=]{
        this->setHtmlValue(html);
    });

    connect(ui->scaleSlider, &QSlider::valueChanged, [&](int val) {
        scaleFactor = getScale (val);
        setting->setScaleFactor (scaleFactor);
        scalePage(scaleFactor);
        ui->scaleCount->setText (QString::number (int(scaleFactor * 100)) + "%");
    });

    m_webView->setContextMenuPolicy(Qt::CustomContextMenu);
    webMenu = new QMenu(this);
    connect(m_webView, &QWidget::customContextMenuRequested, this, [&] {
        webMenu->clear();
        if(m_webView->hasSelection ()){
            webMenu->addAction(tr("cut"));
            webMenu->addAction(tr("copy"));
            webMenu->addAction(tr("delete"));
        }
        webMenu->addAction(tr("paste"));
        webMenu->addAction(tr("paste with format"));
        webMenu->addAction(tr("save"));
        webMenu->exec(QCursor::pos ());
    });
}

//直接写
double WebViewWithEditor::getScale(int x){
    return 0.05*x;
}

int WebViewWithEditor::getPos(double x){
    return int(x * 20);
}

void WebViewWithEditor::setUrl (QString url){
    if(url == ""){
        m_webView->load (QUrl(defaultPath +  DEFAULT_URL));
    }else{
        m_webView->load (QUrl(url));
    }
}

void WebViewWithEditor::getHtmlValue(function<void (QString)> fun){
    m_webView->page()->runJavaScript("getHtmlContent()",[=](const QVariant &v)
    {
        if(fun != nullptr){
            fun(v.toString());
        }
    });
}

void WebViewWithEditor::getHtmlValueWithSet(EntryModel *entry)
{
    m_webView->page()->runJavaScript("getHtmlContent()", [=](const QVariant &v){
        bool isInsert = (entry->id == EntryModel::ENTRY_ID_NULL);
            entry->html = v.toString ();
                if (entry->entry == "") {
                    QMessageBox::about(this, tr("tips"), tr("complete the infomation"));
                    return;
                }
                if (!entry->entry.contains("|")) { // 单个entry
                    bool res = entry->insertOrUpdate();
                    if (res) {
                        emit emitEntryChanged();
                        QMessageBox::about(this,
                                           tr("tips"),
                                           isInsert ? tr("insert succeed") : tr("update succeed"));
                    } else {
                        QMessageBox::about(this,
                                           tr("tips"),
                                           isInsert ? tr("insert fail, please use proper name")
                                                    : tr("update fail, please use proper name"));
                    }
                } else {
                    auto entries = entry->entry.split("|");
                    for (auto en : entries) {
                        if (en.trimmed() == "") {
                            continue;
                        }
                        en = en.trimmed();
                        EntryModel model;
                        model.entry = en;
                        model.html = entry->html;
                        bool res = model.insertOrUpdate();
                        if (res) {
                            emit emitEntryChanged();
                            QMessageBox::about(this, tr("tips"), isInsert ? tr("succeed1") : tr("succeed2"));
                        } else {
                            QMessageBox::about(this,
                                               tr("tips"),
                                               isInsert ? tr("insert fail, please use proper name")
                                                        : tr("update fail, please use proper name"));
                        }
                    }
                }
    });
}


void WebViewWithEditor::setHtmlValue(QString value){
    this->html = value;
    value = value.replace ("\n", "").replace ("\r", "").replace("'", "\"");
    QString function = "setHtmlContent('" + value + "')";
    m_webView->page()->runJavaScript(function);
    this->scalePage (setting->getScaleFactor ());
    this->slotUpdateEntryCount();
}

void WebViewWithEditor::scalePage(double scale){
    QString function = "setScaleFactor(" + QString::number(scale) + ")";
    m_webView->page()->runJavaScript(function);
}

void WebViewWithEditor::slotViewModeChanged (bool isView){
    if(isView == isViewMode) return;
    isViewMode = isView;
    m_webView->page()->runJavaScript(isViewMode ? "viewMode()": "editMode()");
}

void WebViewWithEditor::setEntry(const EntryModel* entry)
{
    this->webChannelObject->setCurrentEntry(entry);
}

void WebViewWithEditor::slotJumpToAnchor(QString anchor)
{
    if (anchor != "") {
        m_webView->page()->runJavaScript("window.location.hash='" + anchor.trimmed() + "'");
    }
}

void WebViewWithEditor::slotUpdateEntryCount()
{
    if (SDB == nullptr) {
        ui->entryCount->setText(tr("please open dict"));
        return;
    }
    EntryModel model;
    int count = model.getTotalCount();
    if (count == -1) {
        ui->entryCount->setText(tr("please open dict"));
    }else{
        ui->entryCount->setText(tr("当前共有 ") + QString::number(count) + tr("词条"));
    }
}

WebViewWithEditor::~WebViewWithEditor()
{
    delete ui;
    delete mySchemeHandler;
    delete m_webView;
    delete webMenu;
    delete channel;
    delete webChannelObject;
    delete setting;
    delete saveShortCut;
}
