/****************************************************************************
** Meta object code from reading C++ file 'obraz.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "obraz.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'obraz.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Ui_Obraz_t {
    QByteArrayData data[8];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ui_Obraz_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ui_Obraz_t qt_meta_stringdata_Ui_Obraz = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Ui_Obraz"
QT_MOC_LITERAL(1, 9, 10), // "closeEvent"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 12), // "QCloseEvent*"
QT_MOC_LITERAL(4, 34, 5), // "event"
QT_MOC_LITERAL(5, 40, 15), // "mousePressEvent"
QT_MOC_LITERAL(6, 56, 12), // "QMouseEvent*"
QT_MOC_LITERAL(7, 69, 2) // "ev"

    },
    "Ui_Obraz\0closeEvent\0\0QCloseEvent*\0"
    "event\0mousePressEvent\0QMouseEvent*\0"
    "ev"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ui_Obraz[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       5,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void Ui_Obraz::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Ui_Obraz *_t = static_cast<Ui_Obraz *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 1: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Ui_Obraz::*_t)(QCloseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Ui_Obraz::closeEvent)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Ui_Obraz::*_t)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Ui_Obraz::mousePressEvent)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Ui_Obraz::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Ui_Obraz.data,
      qt_meta_data_Ui_Obraz,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Ui_Obraz::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ui_Obraz::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ui_Obraz.stringdata0))
        return static_cast<void*>(const_cast< Ui_Obraz*>(this));
    return QWidget::qt_metacast(_clname);
}

int Ui_Obraz::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_Ui__Obraz_t {
    QByteArrayData data[12];
    char stringdata0[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ui__Obraz_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ui__Obraz_t qt_meta_stringdata_Ui__Obraz = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Ui::Obraz"
QT_MOC_LITERAL(1, 10, 10), // "closeEvent"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "QCloseEvent*"
QT_MOC_LITERAL(4, 35, 5), // "event"
QT_MOC_LITERAL(5, 41, 15), // "mousePressEvent"
QT_MOC_LITERAL(6, 57, 12), // "QMouseEvent*"
QT_MOC_LITERAL(7, 70, 2), // "ev"
QT_MOC_LITERAL(8, 73, 13), // "pause_changed"
QT_MOC_LITERAL(9, 87, 6), // "_value"
QT_MOC_LITERAL(10, 94, 8), // "run_stop"
QT_MOC_LITERAL(11, 103, 14) // "ustaw_wielkosc"

    },
    "Ui::Obraz\0closeEvent\0\0QCloseEvent*\0"
    "event\0mousePressEvent\0QMouseEvent*\0"
    "ev\0pause_changed\0_value\0run_stop\0"
    "ustaw_wielkosc"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ui__Obraz[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   45,    2, 0x08 /* Private */,
      10,    0,   48,    2, 0x08 /* Private */,
      11,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Ui::Obraz::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Obraz *_t = static_cast<Obraz *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 1: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->pause_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->run_stop(); break;
        case 4: _t->ustaw_wielkosc(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Obraz::*_t)(QCloseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Obraz::closeEvent)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Obraz::*_t)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Obraz::mousePressEvent)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Ui::Obraz::staticMetaObject = {
    { &Ui_Obraz::staticMetaObject, qt_meta_stringdata_Ui__Obraz.data,
      qt_meta_data_Ui__Obraz,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Ui::Obraz::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ui::Obraz::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ui__Obraz.stringdata0))
        return static_cast<void*>(const_cast< Obraz*>(this));
    return Ui_Obraz::qt_metacast(_clname);
}

int Ui::Obraz::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Ui_Obraz::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Ui::Obraz::closeEvent(QCloseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Ui::Obraz::mousePressEvent(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE