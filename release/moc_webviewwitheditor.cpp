/****************************************************************************
** Meta object code from reading C++ file 'webviewwitheditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../webviewwitheditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'webviewwitheditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WebViewWithEditor_t {
    QByteArrayData data[17];
    char stringdata0[217];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WebViewWithEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WebViewWithEditor_t qt_meta_stringdata_WebViewWithEditor = {
    {
QT_MOC_LITERAL(0, 0, 17), // "WebViewWithEditor"
QT_MOC_LITERAL(1, 18, 5), // "jumps"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 6), // "toSave"
QT_MOC_LITERAL(4, 32, 19), // "emitViewModeChanged"
QT_MOC_LITERAL(5, 52, 17), // "getPlainTextValue"
QT_MOC_LITERAL(6, 70, 23), // "function<void(QString)>"
QT_MOC_LITERAL(7, 94, 17), // "setPlainTextValue"
QT_MOC_LITERAL(8, 112, 12), // "getHtmlValue"
QT_MOC_LITERAL(9, 125, 12), // "setHtmlValue"
QT_MOC_LITERAL(10, 138, 16), // "getMarkdownValue"
QT_MOC_LITERAL(11, 155, 16), // "setMarkdownValue"
QT_MOC_LITERAL(12, 172, 7), // "scaleUp"
QT_MOC_LITERAL(13, 180, 9), // "scaleDown"
QT_MOC_LITERAL(14, 190, 6), // "setUrl"
QT_MOC_LITERAL(15, 197, 3), // "url"
QT_MOC_LITERAL(16, 201, 15) // "viewModeChanged"

    },
    "WebViewWithEditor\0jumps\0\0toSave\0"
    "emitViewModeChanged\0getPlainTextValue\0"
    "function<void(QString)>\0setPlainTextValue\0"
    "getHtmlValue\0setHtmlValue\0getMarkdownValue\0"
    "setMarkdownValue\0scaleUp\0scaleDown\0"
    "setUrl\0url\0viewModeChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebViewWithEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       3,    0,  102,    2, 0x06 /* Public */,
       4,    0,  103,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,  104,    2, 0x0a /* Public */,
       5,    0,  107,    2, 0x2a /* Public | MethodCloned */,
       7,    1,  108,    2, 0x0a /* Public */,
       8,    1,  111,    2, 0x0a /* Public */,
       8,    0,  114,    2, 0x2a /* Public | MethodCloned */,
       9,    1,  115,    2, 0x0a /* Public */,
      10,    1,  118,    2, 0x0a /* Public */,
      10,    0,  121,    2, 0x2a /* Public | MethodCloned */,
      11,    1,  122,    2, 0x0a /* Public */,
      12,    0,  125,    2, 0x0a /* Public */,
      13,    0,  126,    2, 0x0a /* Public */,
      14,    1,  127,    2, 0x0a /* Public */,
      14,    0,  130,    2, 0x2a /* Public | MethodCloned */,
      16,    0,  131,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WebViewWithEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WebViewWithEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->jumps((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->toSave(); break;
        case 2: _t->emitViewModeChanged(); break;
        case 3: _t->getPlainTextValue((*reinterpret_cast< function<void(QString)>(*)>(_a[1]))); break;
        case 4: _t->getPlainTextValue(); break;
        case 5: _t->setPlainTextValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->getHtmlValue((*reinterpret_cast< function<void(QString)>(*)>(_a[1]))); break;
        case 7: _t->getHtmlValue(); break;
        case 8: _t->setHtmlValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->getMarkdownValue((*reinterpret_cast< function<void(QString)>(*)>(_a[1]))); break;
        case 10: _t->getMarkdownValue(); break;
        case 11: _t->setMarkdownValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->scaleUp(); break;
        case 13: _t->scaleDown(); break;
        case 14: _t->setUrl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->setUrl(); break;
        case 16: _t->viewModeChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WebViewWithEditor::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebViewWithEditor::jumps)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WebViewWithEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebViewWithEditor::toSave)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WebViewWithEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebViewWithEditor::emitViewModeChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WebViewWithEditor::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_WebViewWithEditor.data,
    qt_meta_data_WebViewWithEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WebViewWithEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebViewWithEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WebViewWithEditor.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int WebViewWithEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void WebViewWithEditor::jumps(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WebViewWithEditor::toSave()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WebViewWithEditor::emitViewModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
