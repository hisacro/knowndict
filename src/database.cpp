#include "database.h"
#include <QtSql/QtSql>

Database::Database(QObject *parent) :
    QObject(parent)
{
//    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
//    qDebug() << QStandardPaths::writableLocation(QStandardPaths::DataLocation) ;
    QDir dbDir ;
    dbDir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/Database") ;
    dbDir.setPath(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/Database");

    dbDict = QSqlDatabase::addDatabase("QSQLITE");
    dbDict.setDatabaseName(dbDir.absolutePath() + "/dict.sqlite");

    if (!dbDict.open())
    {
        qDebug() << dbDict.lastError().text();
    }

    QSqlQuery q(dbDict);
    if (!q.exec(QLatin1String("CREATE TABLE IF NOT EXISTS dictionary "
                               " (id  INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT"
                               ", filename  TEXT  NOT NULL UNIQUE"
                               ", dictname  TEXT   NULL "
                               ", author  TEXT   NULL "
                               ", email  TEXT   NULL "
                               ", website  TEXT   NULL "
                               ", date  TEXT   NULL "
                               ", description  TEXT   NULL "
                               ", wordcount  INTEGER  NULL "
                               ", status  char(1)  NULL DEFAULT '0' );")))
    {
        qDebug() << "create dictionary table error: " << q.lastError().text();
    }
    if (!q.exec(QLatin1String("CREATE TABLE IF NOT EXISTS history  (id  INTEGER  NOT NULL PRIMARY KEY AUTOINCREMENT, word  TEXT NULL, time  INTEGER  NULL );")))
    {
        qDebug() << "create history table error: " << q.lastError().text() ;
    }

}

bool Database::addDictionary(const QString &filename, const QString &dictname, const QString &author
                             , const QString &email, const QString &website, const QString &date
                             , const QString &description, const qint32 &wordcount, const QString &status)
{
    QSqlQuery q(dbDict);
    q.prepare("insert into dictionary (filename, dictname, author, email, website, date, description, wordcount, status) values(?, ?, ?, ?, ?, ?, ?, ?, ?)");
    q.addBindValue(filename);
    q.addBindValue(dictname);
    q.addBindValue(author);
    q.addBindValue(email);
    q.addBindValue(website);
    q.addBindValue(date);
    q.addBindValue(description);
    q.addBindValue(wordcount);
    q.addBindValue(status);
    if (!q.exec())
    {
        qDebug() << "insert dictionary error: " << q.lastError().text() ;
        return false ;
    }
    return true ;
}

bool Database::updateDictionary(const qint32 &id, const QString &status)
{
    QSqlQuery q(dbDict);
    q.prepare("update dictionary set status=? where id=? ");
    q.addBindValue(status);
    q.addBindValue(id);

    if (!q.exec())
    {
        qDebug() << "update dictionary error: " << q.lastError().text() ;
        return false ;
    }
    return true ;
}

bool Database::removeDictionary(const qint32 &id)
{
    QSqlQuery q(dbDict);
    q.prepare("delete from dictionary where id=? ");
    q.addBindValue(id);

    if (!q.exec())
    {
        qDebug() << "delete dictionary error: " << q.lastError().text() ;
        return false ;
    }
    return true ;
}

QJsonArray Database::getDictionariesInfo()
{
    QJsonArray jsonArr ;
    QSqlQuery q(dbDict);
    q.prepare("select * from dictionary ");

    if (!q.exec())
    {
        qDebug() << "get dictionary info error: " << q.lastError().text() ;
        return jsonArr ;
    }

    while (q.next()) {
        QJsonObject jsonObj;
        jsonObj.insert("id", q.value("id").toInt());
        jsonObj.insert("filename", q.value("filename").toString());
        jsonObj.insert("dictname", q.value("dictname").toString());
        jsonObj.insert("author", q.value("author").toString());
        jsonObj.insert("email", q.value("email").toString());
        jsonObj.insert("website", q.value("website").toString());
        jsonObj.insert("date", q.value("date").toString());
        jsonObj.insert("description", q.value("description").toString());
        jsonObj.insert("wordcount", q.value("wordcount").toLongLong());
        jsonObj.insert("status", q.value("status").toString());
        jsonArr.append(QJsonValue(jsonObj));
    }
//    qDebug() << "jsonArr: " << jsonArr.toVariantList() ;
    return jsonArr ;
}

QStringList Database::getDictionariesEnabled()
{
    QStringList dictlist ;
    QSqlQuery q(dbDict);
    q.prepare("select filename from dictionary where status='1' ");

    if (!q.exec())
    {
        qDebug() << "get dictionary Enabled error: " << q.lastError().text() ;
        return dictlist ;
    }

    while (q.next()) {
        dictlist.append(q.value(0).toString());
    }
    return dictlist ;
}

bool Database::isDictionaryExist(const QString &filename)
{
    QSqlQuery q(dbDict);
    q.prepare("select * from dictionary where filename=? ");
    q.addBindValue(filename);

    if (!q.exec())
    {
        qDebug() << "select * from dictionary where filename=? : " << q.lastError().text() ;
        return false ;
    }
    if (q.next())
    {
        return true ;
    }
    else { return false ; }
}

bool Database::addHistory(const QString &word)
{
    qint64 timeValue = QDateTime::currentMSecsSinceEpoch() ;
    QSqlQuery q(dbDict);
    q.prepare("insert into history (word, time) values(?, ?)");
    q.addBindValue(word);
    q.addBindValue(timeValue);
    if (!q.exec())
    {
        qDebug() << "insert history error: " << q.lastError().text() ;
        return false ;
    }
    return true ;
}

bool Database::removeHistory(const qint32 &id)
{
    QSqlQuery q(dbDict);
    q.prepare("delete from history where id=? ");
    q.addBindValue(id);

    if (!q.exec())
    {
        qDebug() << "delete history error: " << q.lastError().text() ;
        return false ;
    }
    return true ;
}

bool Database::removeHistoryAll()
{
    QSqlQuery q(dbDict);
    q.prepare("delete from history");

    if (!q.exec())
    {
        qDebug() << "delete all history error: " << q.lastError().text() ;
        return false ;
    }
    return true ;
}

QJsonArray Database::getHistories()
{
    QJsonArray jsonArr ;
    QSqlQuery q(dbDict);
    q.prepare("select * from history ORDER BY time DESC LIMIT 20 ");

    if (!q.exec())
    {
        qDebug() << "get history info error: " << q.lastError().text() ;
        return jsonArr ;
    }

    while (q.next()) {
        QJsonObject jsonObj;
        jsonObj.insert("id", q.value("id").toInt());
        jsonObj.insert("word", q.value("word").toString());
        jsonObj.insert("time", q.value("time").toLongLong());
        jsonArr.append(QJsonValue(jsonObj));
    }
    return jsonArr ;
}
