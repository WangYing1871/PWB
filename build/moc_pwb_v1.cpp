/****************************************************************************
** Meta object code from reading C++ file 'pwb_v1.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/pwb_v1.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pwb_v1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSpwb_v1ENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSpwb_v1ENDCLASS = QtMocHelpers::stringData(
    "pwb_v1",
    "switch_channel0",
    "",
    "switch_channel1",
    "switch_channel2",
    "switch_channel3",
    "set_channel0",
    "set_channel1",
    "set_channel2",
    "set_channel3",
    "start",
    "stop",
    "update"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSpwb_v1ENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x0a,    1 /* Public */,
       3,    1,   83,    2, 0x0a,    3 /* Public */,
       4,    1,   86,    2, 0x0a,    5 /* Public */,
       5,    1,   89,    2, 0x0a,    7 /* Public */,
       6,    0,   92,    2, 0x0a,    9 /* Public */,
       7,    0,   93,    2, 0x0a,   10 /* Public */,
       8,    0,   94,    2, 0x0a,   11 /* Public */,
       9,    0,   95,    2, 0x0a,   12 /* Public */,
      10,    0,   96,    2, 0x0a,   13 /* Public */,
      11,    0,   97,    2, 0x0a,   14 /* Public */,
      12,    0,   98,    2, 0x0a,   15 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject pwb_v1::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSpwb_v1ENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSpwb_v1ENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSpwb_v1ENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<pwb_v1, std::true_type>,
        // method 'switch_channel0'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'switch_channel1'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'switch_channel2'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'switch_channel3'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'set_channel0'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'set_channel1'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'set_channel2'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'set_channel3'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'start'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'update'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void pwb_v1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        auto *_t = static_cast<pwb_v1 *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->switch_channel0((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->switch_channel1((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->switch_channel2((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->switch_channel3((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->set_channel0(); break;
        case 5: _t->set_channel1(); break;
        case 6: _t->set_channel2(); break;
        case 7: _t->set_channel3(); break;
        case 8: _t->start(); break;
        case 9: _t->stop(); break;
        case 10: _t->update(); break;
        default: ;
        }
    }
}

const QMetaObject *pwb_v1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pwb_v1::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSpwb_v1ENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int pwb_v1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
