/****************************************************************************
** Meta object code from reading C++ file 'Imap.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Imap.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Imap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Imap_t {
    QByteArrayData data[15];
    char stringdata[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Imap_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Imap_t qt_meta_stringdata_Imap = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 18),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 9),
QT_MOC_LITERAL(4, 35, 14),
QT_MOC_LITERAL(5, 50, 16),
QT_MOC_LITERAL(6, 67, 9),
QT_MOC_LITERAL(7, 77, 1),
QT_MOC_LITERAL(8, 79, 15),
QT_MOC_LITERAL(9, 95, 9),
QT_MOC_LITERAL(10, 105, 12),
QT_MOC_LITERAL(11, 118, 11),
QT_MOC_LITERAL(12, 130, 3),
QT_MOC_LITERAL(13, 134, 10),
QT_MOC_LITERAL(14, 145, 3)
    },
    "Imap\0directoriesFetched\0\0pipeReady\0"
    "fetchCompleted\0connectedChanged\0"
    "printLine\0s\0connectionReady\0readyRead\0"
    "disconnected\0sendCommand\0cmd\0Directory*\0"
    "dir\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Imap[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06,
       3,    0,   60,    2, 0x06,
       4,    0,   61,    2, 0x06,
       5,    0,   62,    2, 0x06,
       6,    1,   63,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       8,    0,   66,    2, 0x08,
       9,    0,   67,    2, 0x08,
      10,    0,   68,    2, 0x08,
      11,    2,   69,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 13,   12,   14,

       0        // eod
};

void Imap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Imap *_t = static_cast<Imap *>(_o);
        switch (_id) {
        case 0: _t->directoriesFetched(); break;
        case 1: _t->pipeReady(); break;
        case 2: _t->fetchCompleted(); break;
        case 3: _t->connectedChanged(); break;
        case 4: _t->printLine((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->connectionReady(); break;
        case 6: _t->readyRead(); break;
        case 7: _t->disconnected(); break;
        case 8: _t->sendCommand((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< Directory*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Directory* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Imap::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Imap::directoriesFetched)) {
                *result = 0;
            }
        }
        {
            typedef void (Imap::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Imap::pipeReady)) {
                *result = 1;
            }
        }
        {
            typedef void (Imap::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Imap::fetchCompleted)) {
                *result = 2;
            }
        }
        {
            typedef void (Imap::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Imap::connectedChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (Imap::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Imap::printLine)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject Imap::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Imap.data,
      qt_meta_data_Imap,  qt_static_metacall, 0, 0}
};


const QMetaObject *Imap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Imap::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Imap.stringdata))
        return static_cast<void*>(const_cast< Imap*>(this));
    return QObject::qt_metacast(_clname);
}

int Imap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Imap::directoriesFetched()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Imap::pipeReady()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Imap::fetchCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Imap::connectedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Imap::printLine(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
