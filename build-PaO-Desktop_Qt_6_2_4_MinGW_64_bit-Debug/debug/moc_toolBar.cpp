/****************************************************************************
** Meta object code from reading C++ file 'toolBar.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../PaO/src/View/toolBar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'toolBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_View__ToolBar_t {
    const uint offsetsAndSize[22];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_View__ToolBar_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_View__ToolBar_t qt_meta_stringdata_View__ToolBar = {
    {
QT_MOC_LITERAL(0, 13), // "View::ToolBar"
QT_MOC_LITERAL(14, 10), // "openSignal"
QT_MOC_LITERAL(25, 0), // ""
QT_MOC_LITERAL(26, 10), // "saveSignal"
QT_MOC_LITERAL(37, 12), // "saveAsSignal"
QT_MOC_LITERAL(50, 10), // "fileOpened"
QT_MOC_LITERAL(61, 10), // "setIsSaved"
QT_MOC_LITERAL(72, 5), // "value"
QT_MOC_LITERAL(78, 8), // "openSlot"
QT_MOC_LITERAL(87, 8), // "saveSlot"
QT_MOC_LITERAL(96, 10) // "saveAsSlot"

    },
    "View::ToolBar\0openSignal\0\0saveSignal\0"
    "saveAsSignal\0fileOpened\0setIsSaved\0"
    "value\0openSlot\0saveSlot\0saveAsSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_View__ToolBar[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    1 /* Public */,
       3,    0,   63,    2, 0x06,    2 /* Public */,
       4,    0,   64,    2, 0x06,    3 /* Public */,
       5,    0,   65,    2, 0x06,    4 /* Public */,
       6,    1,   66,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,   69,    2, 0x0a,    7 /* Public */,
       9,    0,   70,    2, 0x0a,    8 /* Public */,
      10,    0,   71,    2, 0x0a,    9 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void View::ToolBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ToolBar *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->openSignal(); break;
        case 1: _t->saveSignal(); break;
        case 2: _t->saveAsSignal(); break;
        case 3: _t->fileOpened(); break;
        case 4: _t->setIsSaved((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->openSlot(); break;
        case 6: _t->saveSlot(); break;
        case 7: _t->saveAsSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ToolBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ToolBar::openSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ToolBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ToolBar::saveSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ToolBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ToolBar::saveAsSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ToolBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ToolBar::fileOpened)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ToolBar::*)(const bool & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ToolBar::setIsSaved)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject View::ToolBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QToolBar::staticMetaObject>(),
    qt_meta_stringdata_View__ToolBar.offsetsAndSize,
    qt_meta_data_View__ToolBar,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_View__ToolBar_t
, QtPrivate::TypeAndForceComplete<ToolBar, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const bool &, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *View::ToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *View::ToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_View__ToolBar.stringdata0))
        return static_cast<void*>(this);
    return QToolBar::qt_metacast(_clname);
}

int View::ToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void View::ToolBar::openSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void View::ToolBar::saveSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void View::ToolBar::saveAsSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void View::ToolBar::fileOpened()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void View::ToolBar::setIsSaved(const bool & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
