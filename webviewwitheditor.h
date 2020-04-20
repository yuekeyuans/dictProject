#ifndef WEBVIEWWITHEDITOR_H
#define WEBVIEWWITHEDITOR_H

#include <QWidget>

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
};

#endif // WEBVIEWWITHEDITOR_H
