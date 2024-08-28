
#include <QtCore>

#include "dict.h"

Dict::Dict(QObject *parent) :
    QObject(parent)
{
    hasDict = false ;
    dictinfo = new DictInfo;
    dictindex = new DictIndex;
    dictdata = new DictDataBlock;
    connect(dictinfo,SIGNAL(error_message(QString)),this,SLOT(get_error(QString)));
    connect(dictindex,SIGNAL(error_message(QString)),this,SLOT(get_error(QString)));
    connect(dictinfo,SIGNAL(warning_message(QString)),this,SLOT(get_warning(QString)));
    connect(dictindex,SIGNAL(warning_message(QString)),this,SLOT(get_warning(QString)));
}


bool Dict::load_from_path(const QString path)
{
    QDir director(path);
    QString basefilename;
    if(!director.exists()) {
        error_message(tr("The %1 is not exists").arg(path));
        return false;
    }

    foreach (QString filename, director.entryList(QDir::Files)) {
        if (filename.endsWith(IFO_EXTEND)) {
            basefilename=filename.left(filename.length()-QString(IFO_EXTEND).length());
            break;
        }
    }

    if (basefilename.isEmpty()) {
        error_message(tr("The directory:%1 not contain dict files.\n").arg(path));
        return false;
    }

    if (!(dictinfo->load_from_file(director.absoluteFilePath(basefilename+IFO_EXTEND),DictInfoType_NormDict))) {
        error_message(tr("Load the info file error from. %1\n").arg(path));
        return false;
    }

    if(!(dictindex->load_from_file(dictinfo,DictInfoType_NormDict))) {
        error_message(tr("Load the index file error from %1.\n").arg(path));
        return false;
    }

    if(!(dictdata->load_from_file(director.absoluteFilePath(basefilename+DICT_EXTEND),DictInfoType_NormDict))) {
        error_message(tr("Load the data file error from %1.\n").arg(path));
        return false;
    }

    hasDict = true ;
    return true;


}

void Dict::search(const QString &word)
{
//    qDebug() << "(dict) current thread : " << QThread::currentThreadId() ;
    bool status;
    WordList wordList = dictindex->search(word,status);
    emit searchFinished(dictinfo->bookname, wordList, status);
}

void Dict::getWordDetail(const QString &dictName, const QString &word, const qint32 &offset, const qint32 &size)
{
    if (dictName != dictinfo->bookname) {
        return ;
    }
    QString detail = dictdata->get_datablock(offset, size);
    QJsonObject jsonObj;
    jsonObj.insert("dict", dictName);
    jsonObj.insert("word", word);
    jsonObj.insert("detail", detail);
    emit getWordDetailFinished(jsonObj);
}





