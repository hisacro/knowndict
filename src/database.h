#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore>
#include <QtSql/QtSql>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = 0);

    bool addDictionary(const QString &filename, const QString &dictname="", const QString &author=""
                       , const QString &email="", const QString &website="", const QString &date=""
                       , const QString &description="", const qint32 &wordcount=0, const QString &status="1");
    bool updateDictionary(const qint32 &id, const QString &status);
    bool removeDictionary(const qint32 &id);
    QJsonArray getDictionariesInfo();
    QStringList getDictionariesEnabled();
    bool isDictionaryExist(const QString &filename);

    bool addHistory(const QString &word);
    bool removeHistory(const qint32 &id);
    bool removeHistoryAll();
    QJsonArray getHistories();

signals:

public slots:

private:
    QSqlDatabase dbDict;

};

#endif // DATABASE_H
