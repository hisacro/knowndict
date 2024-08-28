#ifndef DICTCENTER_H
#define DICTCENTER_H

#include <QtCore>
#include <QtSql/QtSql>

#include "dict.h"
#include "database.h"

class DictCenter : public QObject
{
    Q_OBJECT
public:
    explicit DictCenter(QObject *parent = 0);
    ~DictCenter() {
        dictThread.quit();
        dictThread.wait();
    }

    // function search word, for qml use only
    Q_INVOKABLE void searchWords(const QString &word) ;

    // function get a word's detail, for qml use only
    Q_INVOKABLE void getWordDetail(const QString &dictName, const QString &word
                                   , const qint32 &offset, const qint32 &size) ;

    // function import dictionary files, for qml use only
    // arg: a file list of necessary dictionary files
    Q_INVOKABLE QJsonObject importDict(const QStringList &dictFiles) ;


    ////////////////////////////////////////////////////////////////////////
    // operations for dict
    //
    ////////////////////////////////////////////////////////////////////////
    // function get one dict info, for qml use only
    // name, type, words count, etc..
    Q_INVOKABLE QJsonArray getAllDictInfo() ;

    // function update one dict's status, for qml use only
    // to enable or disable a dict
    Q_INVOKABLE bool updateDictionary(const qint32 &id, const QString &status);

    // function remove one dict, for qml use only
    // remove a dict, includes its database data & files
    Q_INVOKABLE bool removeDictionary(const qint32 &id, const QString &fileName);


    ////////////////////////////////////////////////////////////////////////
    // operations for history
    //
    ////////////////////////////////////////////////////////////////////////

    // function add one word's history, for qml use only
    //
    Q_INVOKABLE bool addHistory(const QString &word);

    // function remove one word's history, for qml use only
    //
    Q_INVOKABLE bool removeHistory(const qint32 &id);

    // function remove all words' history, for qml use only
    //
    Q_INVOKABLE bool removeHistoryAll();

    // function get all words' history, for qml use only
    // include word & time
    Q_INVOKABLE QJsonArray getHistories();

private:
    // a QThread for searching dictionaries, searching hard/flash drive may be slow
    QThread dictThread;

    // an database instant, store dicts' necessary info
    Database dictDB;

    // a list of dictionary instant
    QHash<QString, Dict*> dictList;

    // function initial all dictionaries
    void initial() ;

signals:
    // error signals

    // search result signals
    void startSearchWords(const QString &word);
    void searchWordsResult(QJsonArray wordList, const QString &dictName) ;

    // get one word's detail signals
    void startGetWordDetail(const QString &dictName, const QString &word
                            , const qint32 &offset, const qint32 &size) ;
    void getWordDetailResult(QJsonObject wordDetail) ;

public slots:

private slots:
    // a slot for search words in another thread

    // a slot to receive search words result
    void slotSearchWordsResult(QString dictName, const WordList &wordList, const bool &status);

    // a slot to receive one word's detail result
    void slotGetWordDetailResult(QJsonObject wordDetail);

};

#endif // DICTCENTER_H
