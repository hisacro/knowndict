#ifndef DICT_H
#define DICT_H

#include <QObject>
#include "dictinfo.h"
#include "dictindex.h"
#include "dictdatablock.h"

#define IFO_EXTEND ".ifo"
#define IDX_EXTEND ".idx"
#define DICT_EXTEND ".dict"

#define D_GET_METHOD_TEMPL(type, field) \
    type get_##field(void) const \
    { \
        return dictinfo->field;\
    }

#define D_IS_METHOD_TEMPL(type, field) \
    bool is_##field(void) const \
    { \
        return true; \
    }

#define D_ALL_METHOD_TEMPL(type, field, default_val) \
    D_GET_METHOD_TEMPL(type, field) \
    D_IS_METHOD_TEMPL(type, field)

class Dict : public QObject
{
    Q_OBJECT
public:
    explicit Dict(QObject *parent = 0);
    ~Dict() {
        delete dictdata;
        delete dictindex;
        delete dictinfo;
    }

 /*
 * function name:load_from_path
 * input variable:path. find and load the dictionary files from @path
 * output variable: return whether the load is successful.
*/
    bool load_from_path(const QString path);                                              //load both .ifo file and .idx file,prepare the data file.

    WordList search(const QString &word,bool &status)      //search the words(return the QList) begin with the @word    // status is a vaiable out of class, to get the status of search
    {
        return dictindex->search(word,status);
    }

    QString get_datablock(const worditem_t &w) {                                    //get the datablock contains the explain of @w
        return dictdata->get_datablock(w);
    }

    //functions to get the dictionary attributes
    D_ALL_METHOD_TEMPL(QString,ifofilename,"")
    D_ALL_METHOD_TEMPL(qint32, wordcount, 0)
    D_ALL_METHOD_TEMPL(qint32, filecount, 0)
    D_ALL_METHOD_TEMPL(qint32, synwordcount, 0)
    D_ALL_METHOD_TEMPL(QString, bookname, "")
    D_ALL_METHOD_TEMPL(QString, author, "")
    D_ALL_METHOD_TEMPL(QString, email, "")
    D_ALL_METHOD_TEMPL(QString, website, "")
    D_ALL_METHOD_TEMPL(QString, date, "")
    D_ALL_METHOD_TEMPL(QString, description, "")
    D_ALL_METHOD_TEMPL(qint32, index_file_size, 0)
    D_ALL_METHOD_TEMPL(QString, sametypesequence, "")
    D_ALL_METHOD_TEMPL(QString, dicttype, "")
    D_ALL_METHOD_TEMPL(QString, version, "")
    D_ALL_METHOD_TEMPL(DictInfoType, infotype, DictInfoType_NormDict)

public slots:
    //search the words(return the QList) begin with the @word
    void search(const QString &word);

    // slot, get one word's detail
    void getWordDetail(const QString &dictName, const QString &word
                       , const qint32 &offset, const qint32 &size) ;


signals:
    void error_message(QString);                                                                    //error messages signals.
    void warning_message(QString);                                                              //warning messahes signals.
    void searchFinished(QString dictName, WordList wordList, bool status);
    void getWordDetailFinished(QJsonObject wordDetail);

private slots:
    void get_error(QString e)
    {
        error_message(e);
    }

    void get_warning(QString w)
    {
        warning_message(w);
    }

private:
    DictInfo *dictinfo;
    DictIndex *dictindex;
    DictDataBlock *dictdata;

    bool hasDict;

};

#endif // DICT_H
