/****************************************************************************
** Meta object code from reading C++ file 'ContactsDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/ContactsDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ContactsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ContactsDialog_t {
    QByteArrayData data[11];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ContactsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ContactsDialog_t qt_meta_stringdata_ContactsDialog = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ContactsDialog"
QT_MOC_LITERAL(1, 15, 20), // "editContactTriggered"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 8), // "Contact*"
QT_MOC_LITERAL(4, 46, 8), // "saveData"
QT_MOC_LITERAL(5, 55, 13), // "passSelection"
QT_MOC_LITERAL(6, 69, 10), // "reloadData"
QT_MOC_LITERAL(7, 80, 11), // "editContact"
QT_MOC_LITERAL(8, 92, 1), // "c"
QT_MOC_LITERAL(9, 94, 10), // "addContact"
QT_MOC_LITERAL(10, 105, 13) // "deleteContact"

    },
    "ContactsDialog\0editContactTriggered\0"
    "\0Contact*\0saveData\0passSelection\0"
    "reloadData\0editContact\0c\0addContact\0"
    "deleteContact"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ContactsDialog[] = {

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
       1,    1,   49,    2, 0x06 /* Public */,
       4,    0,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   53,    2, 0x08 /* Private */,
       6,    0,   54,    2, 0x08 /* Private */,
       7,    1,   55,    2, 0x08 /* Private */,
       9,    0,   58,    2, 0x08 /* Private */,
      10,    0,   59,    2, 0x08 /* Private */,

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

void ContactsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ContactsDialog *_t = static_cast<ContactsDialog *>(_o);
        Q_UNUSED(_t)
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
            typedef void (ContactsDialog::*_t)(Contact * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ContactsDialog::editContactTriggered)) {
                *result = 0;
            }
        }
        {
            typedef void (ContactsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ContactsDialog::saveData)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject ContactsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ContactsDialog.data,
      qt_meta_data_ContactsDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ContactsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ContactsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ContactsDialog.stringdata0))
        return static_cast<void*>(const_cast< ContactsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ContactsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void ContactsDialog::editContactTriggered(Contact * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ContactsDialog::saveData()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
