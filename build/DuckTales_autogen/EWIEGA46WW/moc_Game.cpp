/****************************************************************************
** Meta object code from reading C++ file 'Game.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Game.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.2. It"
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
struct qt_meta_tag_ZN2DT4GameE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN2DT4GameE = QtMocHelpers::stringData(
    "DT::Game",
    "reset",
    "",
    "start",
    "nextFrame",
    "gameEnd",
    "playMusic",
    "std::string",
    "name",
    "stopMusic",
    "resumable",
    "resumeMusic",
    "restoreLevelMusic",
    "timeExpired"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN2DT4GameE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x0a,    1 /* Public */,
       3,    0,   75,    2, 0x0a,    2 /* Public */,
       4,    0,   76,    2, 0x0a,    3 /* Public */,
       5,    0,   77,    2, 0x0a,    4 /* Public */,
       6,    1,   78,    2, 0x0a,    5 /* Public */,
       9,    1,   81,    2, 0x0a,    7 /* Public */,
       9,    0,   84,    2, 0x2a,    9 /* Public | MethodCloned */,
      11,    0,   85,    2, 0x0a,   10 /* Public */,
      12,    0,   86,    2, 0x0a,   11 /* Public */,
      13,    0,   87,    2, 0x0a,   12 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject DT::Game::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_ZN2DT4GameE.offsetsAndSizes,
    qt_meta_data_ZN2DT4GameE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN2DT4GameE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Game, std::true_type>,
        // method 'reset'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'start'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'nextFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'gameEnd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'playMusic'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::string &, std::false_type>,
        // method 'stopMusic'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'stopMusic'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resumeMusic'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'restoreLevelMusic'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'timeExpired'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void DT::Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Game *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->reset(); break;
        case 1: _t->start(); break;
        case 2: _t->nextFrame(); break;
        case 3: _t->gameEnd(); break;
        case 4: _t->playMusic((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 5: _t->stopMusic((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->stopMusic(); break;
        case 7: _t->resumeMusic(); break;
        case 8: _t->restoreLevelMusic(); break;
        case 9: _t->timeExpired(); break;
        default: ;
        }
    }
}

const QMetaObject *DT::Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DT::Game::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN2DT4GameE.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int DT::Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
