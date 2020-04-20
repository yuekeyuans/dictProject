/****************************************************************************
** Meta object code from reading C++ file 'defaultpage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../defaultpage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'defaultpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DefaultPage_t {
    QByteArrayData data[7];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DefaultPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DefaultPage_t qt_meta_stringdata_DefaultPage = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DefaultPage"
QT_MOC_LITERAL(1, 12, 13), // "createNewDict"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "openExistDict"
QT_MOC_LITERAL(4, 41, 8), // "dictName"
QT_MOC_LITERAL(5, 50, 8), // "openHelp"
QT_MOC_LITERAL(6, 59, 10) // "updatePage"

    },
    "DefaultPage\0createNewDict\0\0openExistDict\0"
    "dictName\0openHelp\0updatePage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DefaultPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,
       5,    0,   38,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void DefaultPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DefaultPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createNewDict(); break;
        case 1: _t->openExistDict((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->openHelp(); break;
        case 3: _t->updatePage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DefaultPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DefaultPage::createNewDict)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DefaultPage::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DefaultPage::openExistDict)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DefaultPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DefaultPage::openHelp)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DefaultPage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_DefaultPage.data,
    qt_meta_data_DefaultPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DefaultPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DefaultPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DefaultPage.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "BaseWidget"))
        return static_cast< BaseWidget*>(this);
    return QWidget::qt_metacast(_clname);
}

int DefaultPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DefaultPage::createNewDict()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DefaultPage::openExistDict(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DefaultPage::openHelp()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
