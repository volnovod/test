/****************************************************************************
** Meta object code from reading C++ file 'CombatModuleWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CombatModuleWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CombatModuleWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CombatModuleWidget_t {
    QByteArrayData data[16];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CombatModuleWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CombatModuleWidget_t qt_meta_stringdata_CombatModuleWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CombatModuleWidget"
QT_MOC_LITERAL(1, 19, 16), // "setAngelPitchYaw"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 5), // "pitch"
QT_MOC_LITERAL(4, 43, 3), // "yaw"
QT_MOC_LITERAL(5, 47, 12), // "setAlignment"
QT_MOC_LITERAL(6, 60, 13), // "Qt::Alignment"
QT_MOC_LITERAL(7, 74, 1), // "f"
QT_MOC_LITERAL(8, 76, 14), // "setEditControl"
QT_MOC_LITERAL(9, 91, 1), // "c"
QT_MOC_LITERAL(10, 93, 21), // "setVerticalVisibility"
QT_MOC_LITERAL(11, 115, 22), // "setVerticalOrientation"
QT_MOC_LITERAL(12, 138, 24), // "setHorizontalOrientation"
QT_MOC_LITERAL(13, 163, 10), // "setLimiter"
QT_MOC_LITERAL(14, 174, 2), // "up"
QT_MOC_LITERAL(15, 177, 4) // "down"

    },
    "CombatModuleWidget\0setAngelPitchYaw\0"
    "\0pitch\0yaw\0setAlignment\0Qt::Alignment\0"
    "f\0setEditControl\0c\0setVerticalVisibility\0"
    "setVerticalOrientation\0setHorizontalOrientation\0"
    "setLimiter\0up\0down"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CombatModuleWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x0a /* Public */,
       5,    1,   54,    2, 0x0a /* Public */,
       8,    1,   57,    2, 0x0a /* Public */,
      10,    1,   60,    2, 0x0a /* Public */,
      11,    0,   63,    2, 0x0a /* Public */,
      12,    0,   64,    2, 0x0a /* Public */,
      13,    2,   65,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,   14,   15,

       0        // eod
};

void CombatModuleWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CombatModuleWidget *_t = static_cast<CombatModuleWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setAngelPitchYaw((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->setAlignment((*reinterpret_cast< Qt::Alignment(*)>(_a[1]))); break;
        case 2: _t->setEditControl((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setVerticalVisibility((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setVerticalOrientation(); break;
        case 5: _t->setHorizontalOrientation(); break;
        case 6: _t->setLimiter((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject CombatModuleWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CombatModuleWidget.data,
      qt_meta_data_CombatModuleWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CombatModuleWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CombatModuleWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CombatModuleWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CombatModuleWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
