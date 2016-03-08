/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 15),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 16),
QT_MOC_LITERAL(4, 45, 5),
QT_MOC_LITERAL(5, 51, 15),
QT_MOC_LITERAL(6, 67, 11),
QT_MOC_LITERAL(7, 79, 8),
QT_MOC_LITERAL(8, 88, 9),
QT_MOC_LITERAL(9, 98, 8),
QT_MOC_LITERAL(10, 107, 12),
QT_MOC_LITERAL(11, 120, 18),
QT_MOC_LITERAL(12, 139, 17),
QT_MOC_LITERAL(13, 157, 9),
QT_MOC_LITERAL(14, 167, 11),
QT_MOC_LITERAL(15, 179, 8),
QT_MOC_LITERAL(16, 188, 11),
QT_MOC_LITERAL(17, 200, 18),
QT_MOC_LITERAL(18, 219, 9)
    },
    "MainWindow\0settingsChanged\0\0"
    "showTransmission\0value\0showAddressBook\0"
    "showMailBox\0showMail\0showAbout\0saveData\0"
    "showSettings\0closeCurrentWidget\0"
    "startTransmission\0clearMail\0sendSuccess\0"
    "response\0sendFailure\0onConnectedChanged\0"
    "showClose\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06,
       3,    1,   90,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    0,   93,    2, 0x08,
       6,    0,   94,    2, 0x08,
       7,    0,   95,    2, 0x08,
       8,    0,   96,    2, 0x08,
       9,    0,   97,    2, 0x08,
      10,    0,   98,    2, 0x08,
      11,    0,   99,    2, 0x08,
      12,    0,  100,    2, 0x08,
      13,    0,  101,    2, 0x08,
      14,    1,  102,    2, 0x08,
      16,    1,  105,    2, 0x08,
      17,    0,  108,    2, 0x08,
      18,    1,  109,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->settingsChanged(); break;
        case 1: _t->showTransmission((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->showAddressBook(); break;
        case 3: _t->showMailBox(); break;
        case 4: _t->showMail(); break;
        case 5: _t->showAbout(); break;
        case 6: _t->saveData(); break;
        case 7: _t->showSettings(); break;
        case 8: _t->closeCurrentWidget(); break;
        case 9: _t->startTransmission(); break;
        case 10: _t->clearMail(); break;
        case 11: _t->sendSuccess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->sendFailure((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->onConnectedChanged(); break;
        case 14: _t->showClose((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::settingsChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::showTransmission)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::settingsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWindow::showTransmission(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
