#ifndef YOUDAOAPI_H
#define YOUDAOAPI_H

#include <QObject>
#include <QtNetwork>
#include <QtCore>

class YoudaoAPI : public QObject
{
    Q_OBJECT
public:
    explicit YoudaoAPI(QObject *parent = 0);

    Q_INVOKABLE void searchWord(const QString &word);

signals:
    void searchFinished(const QJsonObject &detail);
    void error(const QString &error);
    void warnning(const QString &warnning);

public slots:
    void search(const QString &word);

private slots:
    void onNetworkReply(QNetworkReply *);

private:
    QNetworkAccessManager *netManager;
    QString urlPatten;

};

#endif // YOUDAOAPI_H
