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
#include <QThread>

WebViewWithEditor::WebViewWithEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebViewWithEditor)
{
    mySchemeHandler = new MySchemeHandler(this);
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

    //jumpStack = new JumpStack(this);

    m_webView = new QWebEngineView(this);
    ui->setupUi(this);
    ui->container->addWidget(m_webView);
    setUrl();

    connect(mySchemeHandler, &MySchemeHandler::jumps, this ,&WebViewWithEditor::jumps);

    // 快捷键
    //保存
    QShortcut  *saveShortCut = new QShortcut(QKeySequence(tr("ctrl+s")), this);
    connect(saveShortCut, &QShortcut::activated, this, &WebViewWithEditor::toSave);
    //放大
    QShortcut  *scaleUp= new QShortcut(QKeySequence(tr("ctrl++")), this);
    connect(scaleUp, &QShortcut::activated, this, &WebViewWithEditor::scaleUp);
    //缩小
    QShortcut  *scaleDown= new QShortcut(QKeySequence(tr("ctrl+-")), this);
    connect(scaleDown, &QShortcut::activated, this, &WebViewWithEditor::scaleDown);
    //正常
    QShortcut *scaleNormal = new QShortcut(QKeySequence(tr("ctrl+0")), this);
    connect(scaleNormal, &QShortcut::activated, [=]{
        this->scaleFactor = 1.0;
        m_webView->page()->runJavaScript("setScaleFactor(0)");
    });

    connect(ui->scaleUp, &QToolButton::clicked, [=]{this->scaleUp();});
    connect(ui->scaleDown, &QToolButton::clicked, [=]{this->scaleDown();});

    connect(ui->viewMode, &QToolButton::clicked, this, &WebViewWithEditor::viewModeChanged);

    connect(m_webView, &QWebEngineView::loadFinished, this, [=]{ this->setHtmlValue(html);});
    connect(ui->nextEntry, &QToolButton::clicked, [=]{m_webView->forward();});
    connect(ui->prevEntry, &QToolButton::clicked, [=]{m_webView->back();});
}

void WebViewWithEditor::setUrl(QString url){
    if(url == nullptr){
        m_webView->load(QUrl("qrc:/simditor/demo.html"));
    }else{
        m_webView->load(QUrl(url));
    }
}

WebViewWithEditor::~WebViewWithEditor()
{
    delete ui;
}

void WebViewWithEditor::getHtmlValue(function<void (QString)> fun){
    m_webView->page()->runJavaScript("getHtmlContent()",[=](const QVariant &v)
    {
        auto html = v.toString();
        if(fun != nullptr){
            fun(html);
        }
    });
}

void WebViewWithEditor::setHtmlValue(QString value){
    this->html = value;
    QString function = "setHtmlContent('" + value + "')";
    m_webView->page()->runJavaScript(function);
}

void WebViewWithEditor::getPlainTextValue(function<void (QString)> fun){
    m_webView->page()->runJavaScript("getPlainTextContent()",[&](const QVariant &v)
    {
        QString plainText = v.toString();
        if(fun != nullptr){
            fun(plainText);
        }
    });
}

void WebViewWithEditor::setPlainTextValue(QString value){
    QString function = "setPlainTextContent('" + value + "')";
    m_webView->page()->runJavaScript(function);
}

void WebViewWithEditor::getMarkdownValue(function<void (QString)> fun){
    m_webView->page()->runJavaScript("getMarkdownContent()",[&](const QVariant &v)
    {
        QString markdownFile = v.toString();
        if(fun != nullptr){
            fun(markdownFile);
        }
    });
}

void WebViewWithEditor::setMarkdownValue(QString value){
    QString function = "setMarkdownContent('" + value + "')";
    m_webView->page()->runJavaScript(function);
}

void WebViewWithEditor::scaleUp(){
    this->scaleFactor += 0.1;
    QString function = "setScaleFactor(" + QString::number(this->scaleFactor) + ")";
    m_webView->page()->runJavaScript(function);
}

void WebViewWithEditor::scaleDown(){
    this->scaleFactor -= 0.1;
    QString function = "setScaleFactor(" + QString::number(this->scaleFactor) + ")";
    m_webView->page()->runJavaScript(function);
}

void WebViewWithEditor::viewModeChanged (){
    isViewMode = !isViewMode;
    m_webView->page()->runJavaScript("getHtmlContent()",[=](const QVariant &v){
        html = v.toString();
        if(isViewMode){
            emit toSave();
            QThread::currentThread ()->usleep (200);
            m_webView->setUrl(QUrl("qrc:/simditor/demo_desplay.html"));
        }else{
            m_webView->setUrl(QUrl("qrc:/simditor/demo.html"));
            emit emitViewModeChanged();
        }
    });
}
