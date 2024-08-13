/****************************************************************************
** Meta object code from reading C++ file 'sensorlistwidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../PaO/src/View/sensorlistwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sensorlistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SensorListWidget_t {
    const uint offsetsAndSize[14];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_SensorListWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_SensorListWidget_t qt_meta_stringdata_SensorListWidget = {
    {
QT_MOC_LITERAL(0, 16), // "SensorListWidget"
QT_MOC_LITERAL(17, 13), // "sensorClicked"
QT_MOC_LITERAL(31, 0), // ""
QT_MOC_LITERAL(32, 15), // "Model::Sensore*"
QT_MOC_LITERAL(48, 7), // "sensore"
QT_MOC_LITERAL(56, 12), // "sensorCloned"
QT_MOC_LITERAL(69, 13) // "sensorUpdated"

    },
    "SensorListWidget\0sensorClicked\0\0"
    "Model::Sensore*\0sensore\0sensorCloned\0"
    "sensorUpdated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SensorListWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x06,    1 /* Public */,
       5,    0,   35,    2, 0x06,    3 /* Public */,
       6,    0,   36,    2, 0x06,    4 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SensorListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SensorListWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sensorClicked((*reinterpret_cast< std::add_pointer_t<Model::Sensore*>>(_a[1]))); break;
        case 1: _t->sensorCloned(); break;
        case 2: _t->sensorUpdated(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SensorListWidget::*)(Model::Sensore * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorListWidget::sensorClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SensorListWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorListWidget::sensorCloned)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SensorListWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorListWidget::sensorUpdated)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject SensorListWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SensorListWidget.offsetsAndSize,
    qt_meta_data_SensorListWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_SensorListWidget_t
, QtPrivate::TypeAndForceComplete<SensorListWidget, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Model::Sensore *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *SensorListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SensorListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SensorListWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SensorListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SensorListWidget::sensorClicked(Model::Sensore * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SensorListWidget::sensorCloned()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SensorListWidget::sensorUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
