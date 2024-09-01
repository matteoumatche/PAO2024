/****************************************************************************
** Meta object code from reading C++ file 'widgettemperatura.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../Desktop/PaO_prof_nuovo1/src/View/widgettemperatura.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widgettemperatura.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_View__WidgetTemperatura_t {
    const uint offsetsAndSize[10];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_View__WidgetTemperatura_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_View__WidgetTemperatura_t qt_meta_stringdata_View__WidgetTemperatura = {
    {
QT_MOC_LITERAL(0, 23), // "View::WidgetTemperatura"
QT_MOC_LITERAL(24, 11), // "simulazione"
QT_MOC_LITERAL(36, 0), // ""
QT_MOC_LITERAL(37, 15), // "Model::Sensore*"
QT_MOC_LITERAL(53, 7) // "sensore"

    },
    "View::WidgetTemperatura\0simulazione\0"
    "\0Model::Sensore*\0sensore"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_View__WidgetTemperatura[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x0a,    1 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void View::WidgetTemperatura::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WidgetTemperatura *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->simulazione((*reinterpret_cast< std::add_pointer_t<Model::Sensore*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject View::WidgetTemperatura::staticMetaObject = { {
    QMetaObject::SuperData::link<WidgetGrafico::staticMetaObject>(),
    qt_meta_stringdata_View__WidgetTemperatura.offsetsAndSize,
    qt_meta_data_View__WidgetTemperatura,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_View__WidgetTemperatura_t
, QtPrivate::TypeAndForceComplete<WidgetTemperatura, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Model::Sensore *, std::false_type>


>,
    nullptr
} };


const QMetaObject *View::WidgetTemperatura::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *View::WidgetTemperatura::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_View__WidgetTemperatura.stringdata0))
        return static_cast<void*>(this);
    return WidgetGrafico::qt_metacast(_clname);
}

int View::WidgetTemperatura::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WidgetGrafico::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
