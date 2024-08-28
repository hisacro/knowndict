#include "dictdatablock.h"

DictDataBlock::DictDataBlock()
{
    dictfile = new QFile(dictfilename);
}

bool DictDataBlock::load_from_file(QString basename, DictInfoType infotype)
{
    clear();
    QString dict_orign=basename;
    QString dict_dz     =basename+".dz";
    if(QFile::exists(dict_orign) & QFile::exists(dict_dz)) {
        warning_message(tr("Two dict files exist!Load origin file first."));
        dictfilename=dict_orign;
    } else if(QFile::exists(dict_orign))
        dictfilename=dict_orign;
    else if (QFile::exists(dict_dz)) {  //.dict.dz file unzip it
        dictfilename = dict_dz+".cache";
        QFile dict_dz(dictfilename);
        if(dict_dz.open(QIODevice::ReadWrite)) {
            error_message(tr("The cache file '%1' cannot open or creat").arg(dictfilename));
            return false;
        }
        dict_dz.close();

    }
    else {
        error_message(tr("No dict file found according to %1").arg(basename));
        return false;
    }
    dictinfotype=infotype;
    dictfile->setFileName(dictfilename);
    return true;
}

QString DictDataBlock::get_datablock(worditem_t worditem)
{
    if(!(dictfile->open(QIODevice::ReadOnly))) {
        error_message(tr("Faild to open dict file: %1.Error: %2").arg(dictfilename,dictfile->errorString()));
        return NULL;
    }
    quint32 offset,length;
    offset=worditem.offset;
    length=worditem.size;
    dictfile->seek(offset);
    QByteArray data=dictfile->read(length);
    if(data.isEmpty()) {
        error_message(tr("Data block is empty."));
        dictfile->close();
        return NULL;
    }
    dictfile->close();
    return QString(data);
}

QString DictDataBlock::get_datablock(const qint32 &offset, const qint32 &size)
{
    if(!(dictfile->open(QIODevice::ReadOnly))) {
        error_message(tr("Faild to open dict file: %1.Error: %2").arg(dictfilename,dictfile->errorString()));
        return NULL;
    }
    quint32 offSet,length;
    offSet=offset;
    length=size;
    dictfile->seek(offSet);
    QByteArray data=dictfile->read(length);
    if(data.isEmpty()) {
        error_message(tr("Data block is empty."));
        dictfile->close();
        return NULL;
    }
    dictfile->close();
    return QString(data);
}

void DictDataBlock::clear()
{
    dictfilename.clear();
//    delete dictfile;
}
