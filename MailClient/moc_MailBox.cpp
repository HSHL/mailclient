/****************************************************************************
** Meta object code from reading C++ file 'MailBox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MailBox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MailBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MailBox_t {
    QByteArrayData data[21];
    char stringdata[272];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MailBox_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MailBox_t qt_meta_stringdata_MailBox = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 16),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 9),
QT_MOC_LITERAL(4, 36, 5),
QT_MOC_LITERAL(5, 42, 19),
QT_MOC_LITERAL(6, 62, 23),
QT_MOC_LITERAL(7, 86, 7),
QT_MOC_LITERAL(8, 94, 8),
QT_MOC_LITERAL(9, 103, 11),
QT_MOC_LITERAL(10, 115, 14),
QT_MOC_LITERAL(11, 130, 16),
QT_MOC_LITERAL(12, 147, 19),
QT_MOC_LITERAL(13, 167, 21),
QT_MOC_LITERAL(14, 189, 15),
QT_MOC_LITERAL(15, 205, 5),
QT_MOC_LITERAL(16, 211, 16),
QT_MOC_LITERAL(17, 228, 9),
QT_MOC_LITERAL(18, 238, 1),
QT_MOC_LITERAL(19, 240, 21),
QT_MOC_LITERAL(20, 262, 8)
    },
    "MailBox\0directoriesReady\0\0showClose\0"
    "value\0reloadDirectoryTree\0"
    "currentDirectoryChanged\0current\0"
    "previous\0reloadMails\0replyTriggered\0"
    "forwardTriggered\0deleteMailTriggered\0"
    "markAsUnseenTriggered\0mailContextMenu\0"
    "point\0showTransmission\0printLine\0s\0"
    "refreshMailsTriggered\0showMail\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MailBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06,
       3,    1,   90,    2, 0x06,
       3,    0,   93,    2, 0x26,

 // slots: name, argc, parameters, tag, flags
       5,    0,   94,    2, 0x0a,
       6,    2,   95,    2, 0x0a,
       9,    0,  100,    2, 0x0a,
      10,    0,  101,    2, 0x0a,
      11,    0,  102,    2, 0x0a,
      12,    0,  103,    2, 0x0a,
      13,    0,  104,    2, 0x0a,
      14,    1,  105,    2, 0x0a,
      16,    1,  108,    2, 0x0a,
      17,    1,  111,    2, 0x0a,
      19,    0,  114,    2, 0x0a,
      20,    0,  115,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::QModelIndex,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   15,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MailBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MailBox *_t = static_cast<MailBox *>(_o);
        switch (_id) {
        case 0: _t->directoriesReady(); break;
        case 1: _t->showClose((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->showClose(); break;
        case 3: _t->reloadDirectoryTree(); break;
        case 4: _t->currentDirectoryChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 5: _t->reloadMails(); break;
        case 6: _t->replyTriggered(); break;
        case 7: _t->forwardTriggered(); break;
        case 8: _t->deleteMailTriggered(); break;
        case 9: _t->markAsUnseenTriggered(); break;
        case 10: _t->mailContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 11: _t->showTransmission((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->printLine((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->refreshMailsTriggered(); break;
        case 14: _t->showMail(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MailBox::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MailBox::directoriesReady)) {
                *result = 0;
            }
        }
        {
            typedef void (MailBox::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MailBox::showClose)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject MailBox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MailBox.data,
      qt_meta_data_MailBox,  qt_static_metacall, 0, 0}
};


const QMetaObject *MailBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MailBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MailBox.stringdata))
        return static_cast<void*>(const_cast< MailBox*>(this));
    return QWidget::qt_metacast(_clname);
}

int MailBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void MailBox::directoriesReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MailBox::showClose(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
