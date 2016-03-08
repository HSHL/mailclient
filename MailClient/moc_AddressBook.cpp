/****************************************************************************
** Meta object code from reading C++ file 'AddressBook.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "AddressBook.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AddressBook.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AddressBook_t {
    QByteArrayData data[11];
    char stringdata[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AddressBook_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AddressBook_t qt_meta_stringdata_AddressBook = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 20),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 8),
QT_MOC_LITERAL(4, 43, 8),
QT_MOC_LITERAL(5, 52, 13),
QT_MOC_LITERAL(6, 66, 10),
QT_MOC_LITERAL(7, 77, 11),
QT_MOC_LITERAL(8, 89, 1),
QT_MOC_LITERAL(9, 91, 10),
QT_MOC_LITERAL(10, 102, 13)
    },
    "AddressBook\0editContactTriggered\0\0"
    "Contact*\0saveData\0passSelection\0"
    "reloadData\0editContact\0c\0addContact\0"
    "deleteContact\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddressBook[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06,
       4,    0,   52,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    0,   53,    2, 0x08,
       6,    0,   54,    2, 0x08,
       7,    1,   55,    2, 0x08,
       9,    0,   58,    2, 0x08,
      10,    0,   59,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AddressBook::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AddressBook *_t = static_cast<AddressBook *>(_o);
        switch (_id) {
        case 0: _t->editContactTriggered((*reinterpret_cast< Contact*(*)>(_a[1]))); break;
        case 1: _t->saveData(); break;
        case 2: _t->passSelection(); break;
        case 3: _t->reloadData(); break;
        case 4: _t->editContact((*reinterpret_cast< Contact*(*)>(_a[1]))); break;
        case 5: _t->addContact(); break;
        case 6: _t->deleteContact(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AddressBook::*_t)(Contact * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AddressBook::editContactTriggered)) {
                *result = 0;
            }
        }
        {
            typedef void (AddressBook::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AddressBook::saveData)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject AddressBook::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AddressBook.data,
      qt_meta_data_AddressBook,  qt_static_metacall, 0, 0}
};


const QMetaObject *AddressBook::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddressBook::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddressBook.stringdata))
        return static_cast<void*>(const_cast< AddressBook*>(this));
    return QWidget::qt_metacast(_clname);
}

int AddressBook::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void AddressBook::editContactTriggered(Contact * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AddressBook::saveData()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
