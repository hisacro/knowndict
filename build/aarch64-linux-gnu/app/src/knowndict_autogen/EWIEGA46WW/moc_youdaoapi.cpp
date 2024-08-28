/****************************************************************************
** Meta object code from reading C++ file 'youdaoapi.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../src/youdaoapi.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'youdaoapi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_YoudaoAPI_t {
    QByteArrayData data[11];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_YoudaoAPI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_YoudaoAPI_t qt_meta_stringdata_YoudaoAPI = {
    {
QT_MOC_LITERAL(0, 0, 9), // "YoudaoAPI"
QT_MOC_LITERAL(1, 10, 14), // "searchFinished"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 6), // "detail"
QT_MOC_LITERAL(4, 33, 5), // "error"
QT_MOC_LITERAL(5, 39, 8), // "warnning"
QT_MOC_LITERAL(6, 48, 6), // "search"
QT_MOC_LITERAL(7, 55, 4), // "word"
QT_MOC_LITERAL(8, 60, 14), // "onNetworkReply"
QT_MOC_LITERAL(9, 75, 14), // "QNetworkReply*"
QT_MOC_LITERAL(10, 90, 10) // "searchWord"

    },
    "YoudaoAPI\0searchFinished\0\0detail\0error\0"
    "warnning\0search\0word\0onNetworkReply\0"
    "QNetworkReply*\0searchWord"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_YoudaoAPI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       5,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   53,    2, 0x0a /* Public */,
       8,    1,   56,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      10,    1,   59,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonObject,    3,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, 0x80000000 | 9,    2,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void YoudaoAPI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<YoudaoAPI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->searchFinished((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 1: _t->error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->warnning((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->search((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->onNetworkReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->searchWord((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (YoudaoAPI::*)(const QJsonObject & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&YoudaoAPI::searchFinished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (YoudaoAPI::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&YoudaoAPI::error)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (YoudaoAPI::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&YoudaoAPI::warnning)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject YoudaoAPI::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_YoudaoAPI.data,
    qt_meta_data_YoudaoAPI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *YoudaoAPI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *YoudaoAPI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_YoudaoAPI.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int YoudaoAPI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void YoudaoAPI::searchFinished(const QJsonObject & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void YoudaoAPI::error(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void YoudaoAPI::warnning(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
