#ifndef DICTINDEX_H
#define DICTINDEX_H

#include <QtCore>
#include <QObject>
#include <QVector>
#include "dictinfo.h"
#include <QString>

#define MAX_WORD_LENGTH 100 //max word length in index file
#define MAX_SEARCH  5

#define MAX_CACHE 30

struct worditem_t {
    QString word;
    quint32 offset;
    quint32 size;
//    bool operator ==(worditem_t src){
//        if(word.startsWith(src.word))
//            return true;
//        else
//            return false;
//    }
};

struct cacheitem_t {
    QString word[MAX_CACHE];
    qint32 offset[MAX_CACHE];          //seek for the file
    qint32 get_cache(QString wo);
    void cache(QString wo,qint32 offst);
};

typedef QList<worditem_t> WordList;

class DictIndex : public QObject
{
    Q_OBJECT
public:
    explicit DictIndex();
    ~DictIndex() {
        if(index_file->isOpen())
            index_file->close();
        delete index_file;
    }

    bool load_from_file(DictInfo *dictinfo,DictInfoType);
    WordList search(QString word,bool& status);
    bool search(QString word, WordList &explain);
signals:
    void error_message(QString);
    void warning_message(QString);
public slots:

private:
    QFile *index_file;
    qint32 wordcount;
    cacheitem_t cache;
};

#endif // DICTINDEX_H
