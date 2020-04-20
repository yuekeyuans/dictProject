/****************************************************************************
** Meta object code from reading C++ file 'additem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../additem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'additem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_addItem_t {
    QByteArrayData data[9];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_addItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_addItem_t qt_meta_stringdata_addItem = {
    {
QT_MOC_LITERAL(0, 0, 7), // "addItem"
QT_MOC_LITERAL(1, 8, 12), // "entryChanged"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 5), // "jumps"
QT_MOC_LITERAL(4, 28, 4), // "save"
QT_MOC_LITERAL(5, 33, 10), // "deletePage"
QT_MOC_LITERAL(6, 44, 15), // "viewModeChanged"
QT_MOC_LITERAL(7, 60, 15), // "setDefaultValue"
QT_MOC_LITERAL(8, 76, 4) // "val1"

    },
    "addItem\0entryChanged\0\0jumps\0save\0"
    "deletePage\0viewModeChanged\0setDefaultValue\0"
    "val1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_addItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   58,    2, 0x0a /* Public */,
       5,    0,   59,    2, 0x0a /* Public */,
       6,    0,   60,    2, 0x0a /* Public */,
       7,    2,   61,    2, 0x0a /* Public */,
       7,    1,   66,    2, 0x2a /* Public | MethodCloned */,
       7,    0,   69,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    2,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,

       0        // eod
};

void addItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<addItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->entryChanged(); break;
        case 1: _t->jumps((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->save(); break;
        case 3: _t->deletePage(); break;
        case 4: _t->viewModeChanged(); break;
        case 5: _t->setDefaultValue((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->setDefaultValue((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->setDefaultValue(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (addItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&addItem::entryChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (addItem::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&addItem::jumps)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject addItem::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_addItem.data,
    qt_meta_data_addItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *addItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *addItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_addItem.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "BaseWidget"))
        return static_cast< BaseWidget*>(this);
    return QWidget::qt_metacast(_clname);
}

int addItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void addItem::entryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void addItem::jumps(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
