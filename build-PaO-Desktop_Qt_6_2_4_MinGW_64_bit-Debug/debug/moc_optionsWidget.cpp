/****************************************************************************
** Meta object code from reading C++ file 'optionsWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../PaO/src/View/optionsWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'optionsWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_View__optionsWidget_t {
    const uint offsetsAndSize[16];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_View__optionsWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_View__optionsWidget_t qt_meta_stringdata_View__optionsWidget = {
    {
QT_MOC_LITERAL(0, 19), // "View::optionsWidget"
QT_MOC_LITERAL(20, 14), // "onCloneClicked"
QT_MOC_LITERAL(35, 0), // ""
QT_MOC_LITERAL(36, 15), // "Model::Sensore*"
QT_MOC_LITERAL(52, 1), // "s"
QT_MOC_LITERAL(54, 15), // "onModifyClicked"
QT_MOC_LITERAL(70, 15), // "onDeleteClicked"
QT_MOC_LITERAL(86, 15) // "onSimulaClicked"

    },
    "View::optionsWidget\0onCloneClicked\0\0"
    "Model::Sensore*\0s\0onModifyClicked\0"
    "onDeleteClicked\0onSimulaClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_View__optionsWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,
       5,    1,   41,    2, 0x06,    3 /* Public */,
       6,    1,   44,    2, 0x06,    5 /* Public */,
       7,    0,   47,    2, 0x06,    7 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void View::optionsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<optionsWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onCloneClicked((*reinterpret_cast< std::add_pointer_t<Model::Sensore*>>(_a[1]))); break;
        case 1: _t->onModifyClicked((*reinterpret_cast< std::add_pointer_t<Model::Sensore*>>(_a[1]))); break;
        case 2: _t->onDeleteClicked((*reinterpret_cast< std::add_pointer_t<Model::Sensore*>>(_a[1]))); break;
        case 3: _t->onSimulaClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (optionsWidget::*)(Model::Sensore * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&optionsWidget::onCloneClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (optionsWidget::*)(Model::Sensore * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&optionsWidget::onModifyClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (optionsWidget::*)(Model::Sensore * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&optionsWidget::onDeleteClicked)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (optionsWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&optionsWidget::onSimulaClicked)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject View::optionsWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_View__optionsWidget.offsetsAndSize,
    qt_meta_data_View__optionsWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_View__optionsWidget_t
, QtPrivate::TypeAndForceComplete<optionsWidget, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Model::Sensore *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Model::Sensore *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Model::Sensore *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *View::optionsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *View::optionsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_View__optionsWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int View::optionsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void View::optionsWidget::onCloneClicked(Model::Sensore * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void View::optionsWidget::onModifyClicked(Model::Sensore * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void View::optionsWidget::onDeleteClicked(Model::Sensore * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void View::optionsWidget::onSimulaClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
