/****************************************************************************
** Meta object code from reading C++ file 'dictcenter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../src/dictcenter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dictcenter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DictCenter_t {
    QByteArrayData data[29];
    char stringdata0[357];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DictCenter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DictCenter_t qt_meta_stringdata_DictCenter = {
    {
QT_MOC_LITERAL(0, 0, 10), // "DictCenter"
QT_MOC_LITERAL(1, 11, 16), // "startSearchWords"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 4), // "word"
QT_MOC_LITERAL(4, 34, 17), // "searchWordsResult"
QT_MOC_LITERAL(5, 52, 8), // "wordList"
QT_MOC_LITERAL(6, 61, 8), // "dictName"
QT_MOC_LITERAL(7, 70, 18), // "startGetWordDetail"
QT_MOC_LITERAL(8, 89, 6), // "offset"
QT_MOC_LITERAL(9, 96, 4), // "size"
QT_MOC_LITERAL(10, 101, 19), // "getWordDetailResult"
QT_MOC_LITERAL(11, 121, 10), // "wordDetail"
QT_MOC_LITERAL(12, 132, 21), // "slotSearchWordsResult"
QT_MOC_LITERAL(13, 154, 8), // "WordList"
QT_MOC_LITERAL(14, 163, 6), // "status"
QT_MOC_LITERAL(15, 170, 23), // "slotGetWordDetailResult"
QT_MOC_LITERAL(16, 194, 11), // "searchWords"
QT_MOC_LITERAL(17, 206, 13), // "getWordDetail"
QT_MOC_LITERAL(18, 220, 10), // "importDict"
QT_MOC_LITERAL(19, 231, 9), // "dictFiles"
QT_MOC_LITERAL(20, 241, 14), // "getAllDictInfo"
QT_MOC_LITERAL(21, 256, 16), // "updateDictionary"
QT_MOC_LITERAL(22, 273, 2), // "id"
QT_MOC_LITERAL(23, 276, 16), // "removeDictionary"
QT_MOC_LITERAL(24, 293, 8), // "fileName"
QT_MOC_LITERAL(25, 302, 10), // "addHistory"
QT_MOC_LITERAL(26, 313, 13), // "removeHistory"
QT_MOC_LITERAL(27, 327, 16), // "removeHistoryAll"
QT_MOC_LITERAL(28, 344, 12) // "getHistories"

    },
    "DictCenter\0startSearchWords\0\0word\0"
    "searchWordsResult\0wordList\0dictName\0"
    "startGetWordDetail\0offset\0size\0"
    "getWordDetailResult\0wordDetail\0"
    "slotSearchWordsResult\0WordList\0status\0"
    "slotGetWordDetailResult\0searchWords\0"
    "getWordDetail\0importDict\0dictFiles\0"
    "getAllDictInfo\0updateDictionary\0id\0"
    "removeDictionary\0fileName\0addHistory\0"
    "removeHistory\0removeHistoryAll\0"
    "getHistories"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DictCenter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    2,   97,    2, 0x06 /* Public */,
       7,    4,  102,    2, 0x06 /* Public */,
      10,    1,  111,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    3,  114,    2, 0x08 /* Private */,
      15,    1,  121,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      16,    1,  124,    2, 0x02 /* Public */,
      17,    4,  127,    2, 0x02 /* Public */,
      18,    1,  136,    2, 0x02 /* Public */,
      20,    0,  139,    2, 0x02 /* Public */,
      21,    2,  140,    2, 0x02 /* Public */,
      23,    2,  145,    2, 0x02 /* Public */,
      25,    1,  150,    2, 0x02 /* Public */,
      26,    1,  153,    2, 0x02 /* Public */,
      27,    0,  156,    2, 0x02 /* Public */,
      28,    0,  157,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QJsonArray, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int,    6,    3,    8,    9,
    QMetaType::Void, QMetaType::QJsonObject,   11,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 13, QMetaType::Bool,    6,    5,   14,
    QMetaType::Void, QMetaType::QJsonObject,   11,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int,    6,    3,    8,    9,
    QMetaType::QJsonObject, QMetaType::QStringList,   19,
    QMetaType::QJsonArray,
    QMetaType::Bool, QMetaType::Int, QMetaType::QString,   22,   14,
    QMetaType::Bool, QMetaType::Int, QMetaType::QString,   22,   24,
    QMetaType::Bool, QMetaType::QString,    3,
    QMetaType::Bool, QMetaType::Int,   22,
    QMetaType::Bool,
    QMetaType::QJsonArray,

       0        // eod
};

void DictCenter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DictCenter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startSearchWords((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->searchWordsResult((*reinterpret_cast< QJsonArray(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->startGetWordDetail((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const qint32(*)>(_a[3])),(*reinterpret_cast< const qint32(*)>(_a[4]))); break;
        case 3: _t->getWordDetailResult((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 4: _t->slotSearchWordsResult((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const WordList(*)>(_a[2])),(*reinterpret_cast< const bool(*)>(_a[3]))); break;
        case 5: _t->slotGetWordDetailResult((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 6: _t->searchWords((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->getWordDetail((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const qint32(*)>(_a[3])),(*reinterpret_cast< const qint32(*)>(_a[4]))); break;
        case 8: { QJsonObject _r = _t->importDict((*reinterpret_cast< const QStringList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QJsonObject*>(_a[0]) = std::move(_r); }  break;
        case 9: { QJsonArray _r = _t->getAllDictInfo();
            if (_a[0]) *reinterpret_cast< QJsonArray*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->updateDictionary((*reinterpret_cast< const qint32(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->removeDictionary((*reinterpret_cast< const qint32(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->addHistory((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->removeHistory((*reinterpret_cast< const qint32(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: { bool _r = _t->removeHistoryAll();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 15: { QJsonArray _r = _t->getHistories();
            if (_a[0]) *reinterpret_cast< QJsonArray*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DictCenter::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DictCenter::startSearchWords)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DictCenter::*)(QJsonArray , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DictCenter::searchWordsResult)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DictCenter::*)(const QString & , const QString & , const qint32 & , const qint32 & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DictCenter::startGetWordDetail)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DictCenter::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DictCenter::getWordDetailResult)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DictCenter::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DictCenter.data,
    qt_meta_data_DictCenter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DictCenter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DictCenter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DictCenter.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DictCenter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void DictCenter::startSearchWords(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DictCenter::searchWordsResult(QJsonArray _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DictCenter::startGetWordDetail(const QString & _t1, const QString & _t2, const qint32 & _t3, const qint32 & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DictCenter::getWordDetailResult(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
