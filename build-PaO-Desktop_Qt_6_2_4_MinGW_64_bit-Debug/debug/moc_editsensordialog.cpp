/****************************************************************************
** Meta object code from reading C++ file 'editsensordialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../PaO/src/View/editsensordialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editsensordialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EditSensorDialog_t {
    const uint offsetsAndSize[8];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_EditSensorDialog_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_EditSensorDialog_t qt_meta_stringdata_EditSensorDialog = {
    {
QT_MOC_LITERAL(0, 16), // "EditSensorDialog"
QT_MOC_LITERAL(17, 14), // "sensorModified"
QT_MOC_LITERAL(32, 0), // ""
QT_MOC_LITERAL(33, 34) // "std::map<std::string,std::str..."

    },
    "EditSensorDialog\0sensorModified\0\0"
    "std::map<std::string,std::string>&"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditSensorDialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void EditSensorDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EditSensorDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sensorModified((*reinterpret_cast< std::add_pointer_t<std::map<std::string,std::string>&>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EditSensorDialog::*)(std::map<std::string,std::string> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EditSensorDialog::sensorModified)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject EditSensorDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_EditSensorDialog.offsetsAndSize,
    qt_meta_data_EditSensorDialog,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_EditSensorDialog_t
, QtPrivate::TypeAndForceComplete<EditSensorDialog, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::map<std::string,std::string> &, std::false_type>



>,
    nullptr
} };


const QMetaObject *EditSensorDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditSensorDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EditSensorDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int EditSensorDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void EditSensorDialog::sensorModified(std::map<std::string,std::string> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
