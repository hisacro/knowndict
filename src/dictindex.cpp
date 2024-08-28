#include "dictindex.h"
#include <QFile>
#include <QDataStream>

DictIndex::DictIndex()
{
    index_file = new QFile(this);

}

qint32 cacheitem_t::get_cache(QString wo)
{
    for (int i=0;i<=MAX_CACHE-1;i++) {
        if (word[i].isEmpty())
            continue;
        if (wo.startsWith(word[i]))
            return offset[i];
    }

    return -1;
}

void cacheitem_t::cache(QString wo, qint32 offst)
{
    int i = 0;
    if (wo.isEmpty())
        return;
    for (i=0;i<=MAX_CACHE-1;i++) {
        if(word[i].startsWith(wo))
            break;
    }

    if(i >= MAX_CACHE) {
        for(int j=0;j<=MAX_CACHE-2;j++) {
            word[j]=word[j+1];
            offset[j]=offset[j+1];
        }
        word[MAX_CACHE-1]=wo;
        offset[MAX_CACHE-1]=offst;
    }
}

static QString readword(QDataStream &src)
{
    char temp[MAX_WORD_LENGTH];
    char *p=temp;
    src.readRawData(p,1);
    while(*p && p <= (temp + MAX_WORD_LENGTH)) {
        p++;
        src.readRawData(p,1);
    }
    return QString(temp);
}

bool DictIndex::load_from_file(DictInfo *dictinfo,DictInfoType info_type)
{
    QString idx_name=dictinfo->get_ifofilename().replace(".ifo",".idx");
    index_file->setFileName(idx_name);
    if(!(index_file->open(QIODevice::ReadOnly))) {
        error_message(tr("Faild to open index file: %1.Error: %2").arg(idx_name,index_file->errorString()));
       delete index_file;
        return false;
    }
    wordcount=dictinfo->get_wordcount();
    return true;
}

WordList DictIndex::search(QString word, bool& status)
{
        index_file->seek(0);
        QDataStream index_stream(index_file);
        WordList  worditems;
        worditem_t temp;
        int i=1;
        int nCount=0;
        qint32 offset,size;
        int oft=cache.get_cache(word);
        if(oft >=0)
            index_file->seek(oft);
        for(i=1;i<=wordcount;i++) {
            temp.word=readword(index_stream);
            index_stream>>offset>>size;
            if(temp.word.startsWith(word)) {
               temp.offset=offset;
               temp.size=size;
               worditems.append(temp);
               nCount++;
               if(nCount>=MAX_SEARCH)
                   break;
            }

            if(!(worditems.isEmpty())) {
                if(!(word.isEmpty()))
                    if(!(temp.word.startsWith(word.at(0))))
                        break;
            }
        }
        if(worditems.isEmpty())
            status=false;
        else {
            status=true;
            cache.cache(word,index_file->pos());
        }
        return worditems;

}


bool DictIndex::search(QString word, WordList &explain)
{
    bool st;
    WordList w;
    w=search(word,st);
    explain = w;
    return st;
}
