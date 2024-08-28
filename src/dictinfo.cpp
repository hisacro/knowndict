#include "dictinfo.h"
#include "QTextStream"

#define NORM_DICT_MAGIC_DATA "StarDict's dict ifo file"
#define TREE_DICT_MAGIC_DATA "StarDict's treedict ifo file"
#define RES_DB_MAGIC_DATA "StarDict's storage ifo file"

#define WORDCOUNT                   "wordcount"
#define FILECOUNT                       "filecount"
#define SYNWORDCOUNT            "synwordcount"
#define BOOKNAME                      "bookname"
#define AUTHOR                             "author"
#define EMAIL                                 "email"
#define WEBSITE                             "website"
#define DATE                                    "date"
#define DESCRIPITION                    "description"
#define INDEXFILESIZE                   "idxfilesize"
#define SAMETYPESEQ                    "sametypesequence"
#define DICTTYPE                            "dicttype"
#define VERSION                             "version"

DictInfo::DictInfo()
{
    ifofilename.clear();
    bookname.clear();
    author.clear();
    email.clear();
    website.clear();
    date.clear();
    description.clear();
    sametypesequence.clear();
    dicttype.clear();
    version=QString("");
    wordcount=0;
    filecount=0;
    synwordcount=0;
    index_file_size=0;
}

bool DictInfo::load_from_file(QString info_file_name,DictInfoType info_type)
{
    ifofilename = info_file_name;
    infotype = info_type;

    QFile *file = new QFile(ifofilename);
    if(!(file->open(QIODevice::ReadOnly))) {
        error_message(tr("Faild to open info file:%1.Error: %2").arg(ifofilename,file->errorString()));
        return false;
    }
    QTextStream *text = new QTextStream(file);

    QByteArray magic_data=NORM_DICT_MAGIC_DATA;
    if(infotype == DictInfoType_NormDict)
        magic_data = QByteArray(NORM_DICT_MAGIC_DATA);
    else if (infotype == DictInfoType_ResDb)
        magic_data = QByteArray(RES_DB_MAGIC_DATA);
    else if(infotype == DictInfoType_TreeDict)
        magic_data = QByteArray(TREE_DICT_MAGIC_DATA);
    else {
        file->close();
        return false;
    }

    QString buffer;
    if((buffer=text->readLine()).isEmpty()) {
        error_message(tr("Faild to read info file:%1.").arg(ifofilename));
        file->close();
        return false;
    }

    if(!(buffer.startsWith(magic_data))) {
        warning_message(tr("Load '%1' failed: Incorrect magic data.").arg(ifofilename));
        if(buffer.startsWith(QString(NORM_DICT_MAGIC_DATA))) {
            warning_message(tr("File '%1' is an index-based dictionary.").arg(ifofilename));
        } else if(buffer.startsWith(QString(RES_DB_MAGIC_DATA))) {
//            infotype=DictInfoType_ResDb;
            warning_message(tr("File '%1' is a resource database.").arg(ifofilename));
        } else if(buffer.startsWith(QString(TREE_DICT_MAGIC_DATA))) {
//            infotype=DictInfoType_TreeDict;
            warning_message(tr("File '%1' is a tree dictionary. ").arg(ifofilename));
        }
        else {
            error_message(tr("File '%1' is not a StarDict dictionary or it's broken.").arg(ifofilename));
        }
        file->close();
        delete file;
        delete text;
        return false;
    }

    buffer.clear();
    buffer=text->readLine().simplified();
    if(!(buffer.startsWith("version"))) {
        error_message(tr("Load %1 failed: \"version\" must be the first option.").arg(ifofilename));
        file->close();
        delete file;
        delete text;
        return false;
    }
    while(!(buffer.isEmpty())) {
        read_key(buffer);
        buffer.clear();
        buffer=text->readLine().simplified();
    }

    delete file;
    delete text;
    return true;
}

#define IF_DE(_P,_K)\
    else if(key.startsWith(QString(_P)))\
        _K=key.mid(QString(_P).length()+1)
#define IF_DE_INT(_P,_K)\
    else if(key.startsWith(QString(_P)))\
        _K=key.mid(QString(_P).length()+1).toInt()

void DictInfo::read_key(const QString key)
{
    if(key.startsWith(QString(WORDCOUNT)))
        wordcount=key.mid(QString(WORDCOUNT).length()+1).toInt();
    IF_DE_INT(FILECOUNT,filecount);
    IF_DE_INT(SYNWORDCOUNT,synwordcount);
    IF_DE(BOOKNAME,bookname);
    IF_DE(AUTHOR,author);
    IF_DE(EMAIL,email);
    IF_DE(WEBSITE,website);
    IF_DE(DATE,date);
    IF_DE(DESCRIPITION,description);
    IF_DE_INT(INDEXFILESIZE,index_file_size);
    IF_DE(SAMETYPESEQ,sametypesequence);
    IF_DE(DICTTYPE,dicttype);
    IF_DE(VERSION,version);
    else
        warning_message(QString("Unspecified key in %1").arg(ifofilename));
}

#undef IF_DE_INT
#undef IF_DE

void DictInfo::clear()
{
    ifofilename.clear();
    wordcount = 0;
    filecount = 0;
    synwordcount = 0;
    bookname.clear();
    author.clear();
    email.clear();
    website.clear();
    date.clear();
    description.clear();
    index_file_size = 0;
    sametypesequence.clear();
    dicttype.clear();
    version.clear();
}
