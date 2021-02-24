#include "webchannelobject.h"
#include <QDebug>
#include "link-anchor/linkanchorwidget.h"

WebChannelObject::WebChannelObject(QObject *parent) : QObject(parent)
{

}

void WebChannelObject::slotGetLinkAndAnchor(QString text)
{
    LinkAnchorWidget links;
    if (links.exec() == QDialog::Accepted) {
        if (text == "") {
            text = tr("链接");
        }
        auto link = links.getLink();
        auto anchor = links.getAnchor();
        auto linkId = links.getId();
        if (entryModel != nullptr) {
            if (entryModel->entry == link) {
                if (anchor == "") {
                    return;
                }else{
                    emit emitGetLinkAndAnchors(text, "#" + anchor.trimmed());
                }
            } else {
                emit emitGetLinkAndAnchors(text, "entry://" + link.trimmed () + "/" + linkId +  "#" + anchor.trimmed());
            }
        }else{
            emit emitGetLinkAndAnchors(text, "entry://" + link.trimmed ()+ "/" + linkId +"#" + anchor.trimmed());
        }
    }
}

void WebChannelObject::setCurrentEntry(const EntryModel* model)
{
    this->entryModel = model;
}
