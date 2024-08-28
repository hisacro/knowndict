#ifndef DICTDATABLOCK_H
#define DICTDATABLOCK_H

#include <QObject>
#include <QFile>
#include "dictindex.h"

class DictDataBlock : public QObject
{
    Q_OBJECT
public:
    explicit DictDataBlock();
    ~DictDataBlock() {
        delete dictfile;
    }

    bool load_from_file(QString,DictInfoType);
    QString get_datablock(worditem_t);
    // override
    QString get_datablock(const qint32 &offset, const qint32 &size);
    void clear();
signals:
    void error_message(QString );
    void warning_message(QString );
public slots:

private:
    QString dictfilename;
    DictInfoType dictinfotype;
    QFile *dictfile;
};

#endif // DICTDATABLOCK_H
