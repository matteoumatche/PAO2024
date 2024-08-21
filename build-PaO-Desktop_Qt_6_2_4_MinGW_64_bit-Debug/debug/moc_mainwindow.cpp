/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../PaO/src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[44];
    char stringdata0[271];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 9), // "addSensor"
QT_MOC_LITERAL(21, 0), // ""
QT_MOC_LITERAL(22, 4), // "name"
QT_MOC_LITERAL(27, 4), // "type"
QT_MOC_LITERAL(32, 2), // "id"
QT_MOC_LITERAL(35, 19), // "showNewSensorDialog"
QT_MOC_LITERAL(55, 12), // "openJsonFile"
QT_MOC_LITERAL(68, 12), // "saveJsonFile"
QT_MOC_LITERAL(81, 14), // "saveJsonFileAs"
QT_MOC_LITERAL(96, 14), // "reloadJsonFile"
QT_MOC_LITERAL(111, 11), // "cloneSensor"
QT_MOC_LITERAL(123, 15), // "Model::Sensore*"
QT_MOC_LITERAL(139, 6), // "sensor"
QT_MOC_LITERAL(146, 12), // "modifySensor"
QT_MOC_LITERAL(159, 12), // "deleteSensor"
QT_MOC_LITERAL(172, 21), // "onSearchButtonClicked"
QT_MOC_LITERAL(194, 26), // "onClearSearchButtonClicked"
QT_MOC_LITERAL(221, 16), // "onSensorSelected"
QT_MOC_LITERAL(238, 11), // "std::string"
QT_MOC_LITERAL(250, 8), // "sensorID"
QT_MOC_LITERAL(259, 11) // "dataUpdated"

    },
    "MainWindow\0addSensor\0\0name\0type\0id\0"
    "showNewSensorDialog\0openJsonFile\0"
    "saveJsonFile\0saveJsonFileAs\0reloadJsonFile\0"
    "cloneSensor\0Model::Sensore*\0sensor\0"
    "modifySensor\0deleteSensor\0"
    "onSearchButtonClicked\0onClearSearchButtonClicked\0"
    "onSensorSelected\0std::string\0sensorID\0"
    "dataUpdated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   92,    2, 0x08,    1 /* Private */,
       6,    0,   99,    2, 0x08,    5 /* Private */,
       7,    0,  100,    2, 0x08,    6 /* Private */,
       8,    0,  101,    2, 0x08,    7 /* Private */,
       9,    0,  102,    2, 0x08,    8 /* Private */,
      10,    0,  103,    2, 0x08,    9 /* Private */,
      11,    1,  104,    2, 0x08,   10 /* Private */,
      14,    1,  107,    2, 0x08,   12 /* Private */,
      15,    1,  110,    2, 0x08,   14 /* Private */,
      16,    0,  113,    2, 0x08,   16 /* Private */,
      17,    0,  114,    2, 0x08,   17 /* Private */,
      18,    1,  115,    2, 0x0a,   18 /* Public */,
      21,    0,  118,    2, 0x0a,   20 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addSensor((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 1: _t->showNewSensorDialog(); break;
        case 2: _t->openJsonFile(); break;
        case 3: _t->saveJsonFile(); break;
        case 4: _t->saveJsonFileAs(); break;
        case 5: _t->reloadJsonFile(); break;
        case 6: _t->cloneSensor((*reinterpret_cast< std::add_pointer_t<Model::Sensore*>>(_a[1]))); break;
        case 7: _t->modifySensor((*reinterpret_cast< std::add_pointer_t<Model::Sensore*>>(_a[1]))); break;
        case 8: _t->deleteSensor((*reinterpret_cast< std::add_pointer_t<Model::Sensore*>>(_a[1]))); break;
        case 9: _t->onSearchButtonClicked(); break;
        case 10: _t->onClearSearchButtonClicked(); break;
        case 11: _t->onSensorSelected((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 12: _t->dataUpdated(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Model::Sensore *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Model::Sensore *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Model::Sensore *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
