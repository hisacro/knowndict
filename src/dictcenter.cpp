#include "dictcenter.h"

DictCenter::DictCenter(QObject *parent) :
    QObject(parent)
{
    initial();
//    qDebug() << "(dictcenter) current thread : " << QThread::currentThreadId() ;
//    QString path("./stardict-oxford-gb-2.4.2");
//    Dict *dict = new Dict;

//    dict->load_from_path(path);

////    connect(this, SIGNAL(startSearch(QString)), dict2, SLOT(search(QString)), Qt::QueuedConnection);
//    connect(dict, SIGNAL(searchFinished(QString, WordList,bool)), this, SLOT(slotSearchWordsResult(QString, WordList,bool)), Qt::QueuedConnection);
//    connect(this, SIGNAL(startSearchWords(QString)), dict, SLOT(search(QString)), Qt::QueuedConnection);
////    dictThread = new QThread(this);
//    dict->moveToThread(&dictThread);
//    dictList.insert(QCryptographicHash::hash(dict->get_bookname().toUtf8(), QCryptographicHash::Md5).toHex(), dict);
//    qDebug() << "dictList.uniqueKeys() : " << dictList.uniqueKeys() ;
//    dictThread.start();


//    QDir dir("/home/cy/qtproject/ditcionary/dic/langdao-ec/");
//    QStringList filelist;
//    foreach (QFileInfo info, dir.entryInfoList(QDir::Files))
//    {
////        qDebug() << info.absoluteFilePath() ;
//        filelist << info.absoluteFilePath() ;
//    }
//    importDict(filelist) ;


}

void DictCenter::searchWords(const QString &word)
{
    emit startSearchWords(word);
}

void DictCenter::getWordDetail(const QString &dictName, const QString &word
                               , const qint32 &offset, const qint32 &size)
{
    emit startGetWordDetail(dictName, word, offset, size);
}

QJsonObject DictCenter::importDict(const QStringList &dictFiles)
{
    // get filename, check if this exist in database, if exist, return
    QString filename;
    foreach (QString file, dictFiles)
    {
        if (file.contains("ifo", Qt::CaseInsensitive))
        {
            QFileInfo info(file);
            filename = info.baseName();
            if (dictDB.isDictionaryExist(filename))
            {
                qDebug() << "dictionary already existed  " ;
                QJsonObject jsonObj;
                jsonObj.insert("error", QString("db_dict_exist"));
                return jsonObj ;
            }
            break ;
        }
    }

    // 0. dict files already be imported into cache folder by content-hub
    QFileInfo dictFileInfo(dictFiles[0]) ;
    QString tmpPath = dictFileInfo.absolutePath() ;

    // 1. try load them by using Dict class
    Dict *dict = new Dict;
    bool loadStatus = dict->load_from_path(tmpPath);

    // 2. if no errors occur,
    //    2.1 copy them to app's data folder
    //    2.2 add them to database
    //    2.3 return true
    if (loadStatus)
    {
        //preload dict's info
        QString dictname = dict->get_bookname() ; QString author = dict->get_author();
        QString email = dict->get_email() ; QString website = dict->get_website() ;
        QString date = dict->get_date() ; QString description = dict->get_description() ;
        qint64 wordcount = qint64(dict->get_wordcount()) ;

        // copy files to new folder
        QDir dictDir ;
        dictDir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/dictionary/" + filename) ;
        dictDir.setPath(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/dictionary/" + filename);
        foreach (QString file, dictFiles)
        {
            QFileInfo info(file);
            if (!QFile::copy(file, dictDir.absolutePath() + "/" + info.fileName()) )
            {
                qDebug() << "copy dict file error : " << file ;
            }
        }

        // add to database
        if (!dictDB.addDictionary(filename, dictname, author, email, website, date, description, wordcount) )
        {
            qDebug() << "dictDB.addDictionary() error  " ;
            QJsonObject jsonObj;
            jsonObj.insert("error", QString("db_addDict_fail"));
            return jsonObj ;
        }

        // finish work
        delete dict ;
        initial();
        QJsonObject jsonObj;
        jsonObj.insert("no_error", QString("dictionary imported"));
        return jsonObj ;
    }

    // 3. else emit error signal & return false
    else
    {
        qDebug() << "dict->load_from_path(tmpPath) error  " ;
        // emit
        QJsonObject jsonObj;
        jsonObj.insert("error", QString("dict_load_fail"));
        return jsonObj ;
    }
}

QJsonArray DictCenter::getAllDictInfo()
{
    return dictDB.getDictionariesInfo() ;
}

bool DictCenter::updateDictionary(const qint32 &id, const QString &status)
{
    if (dictDB.updateDictionary(id, status))
    {
        initial();
        return true ;
    }
    else
    {
        return false ;
    }
}

bool DictCenter::removeDictionary(const qint32 &id, const QString &fileName)
{
    if (dictDB.removeDictionary(id))
    {
        QDir dictDir ;
        dictDir.setPath(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/dictionary/" + fileName) ;
        dictDir.removeRecursively() ;
        return true ;
//        if (dictDir.removeRecursively() )
//        {
//            return true ;
//        }
//        else { return false ; }
        initial();
    }
    else { return false ; }
}

bool DictCenter::addHistory(const QString &word)
{
    return dictDB.addHistory(word) ;
}

bool DictCenter::removeHistory(const qint32 &id)
{
    return dictDB.removeHistory(id) ;
}

bool DictCenter::removeHistoryAll()
{
    return dictDB.removeHistoryAll() ;
}

QJsonArray DictCenter::getHistories()
{
    return dictDB.getHistories() ;
}

void DictCenter::initial()
{
    dictThread.quit();
    dictThread.wait();
    QHash<QString, Dict*>::const_iterator i;
    for (i = dictList.constBegin(); i != dictList.constEnd(); ++i) {
        delete i.value() ;
    }
    dictList.clear();
    // 0. get dict name list from db, ignore disabed dict
    QStringList dictEnabledList = dictDB.getDictionariesEnabled() ;
    qDebug() << "dictEnabledList: " << dictEnabledList ;

    foreach (QString dictName, dictEnabledList)
    {
            // 1. load folders from the name list one by one
        QString path(QStandardPaths::writableLocation(QStandardPaths::DataLocation)
                     + "/dictionary/" + dictName );
        Dict *dict = new Dict;
        dict->load_from_path(path);

        // connections for search words list
        connect(dict, SIGNAL(searchFinished(QString, WordList,bool)), this, SLOT(slotSearchWordsResult(QString, WordList,bool)), Qt::QueuedConnection);
        connect(this, SIGNAL(startSearchWords(QString)), dict, SLOT(search(QString)), Qt::QueuedConnection);

        // connections for word's detail
        connect(dict, SIGNAL(getWordDetailFinished(QJsonObject)), this, SLOT(slotGetWordDetailResult(QJsonObject)), Qt::QueuedConnection);
        connect(this, SIGNAL(startGetWordDetail(QString,QString,qint32,qint32)), dict, SLOT(getWordDetail(QString,QString,qint32,qint32)), Qt::QueuedConnection);

        dict->moveToThread(&dictThread);
        dictList.insert(QCryptographicHash::hash(dict->get_bookname().toUtf8(), QCryptographicHash::Md5).toHex(), dict);
    }
    dictThread.start();


}

void DictCenter::slotSearchWordsResult(QString dictName, const WordList &wordList, const bool &status)
{
    qDebug() << "status ? " << status ;
    QJsonArray jsonArr;
    foreach (worditem_t word, wordList) {
        QJsonObject jsonObj;
        jsonObj.insert("dict", dictName);
        jsonObj.insert("word", word.word);
        jsonObj.insert("offset", qint64(word.offset));
        jsonObj.insert("size", qint64(word.size));
        jsonArr.append(QJsonValue(jsonObj));
    }
    emit searchWordsResult(jsonArr, dictName);
}

void DictCenter::slotGetWordDetailResult(QJsonObject wordDetail)
{
    emit getWordDetailResult(wordDetail) ;
}

