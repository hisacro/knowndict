#include "youdaoapi.h"
//#include <QtNetwork/QNetworkReply>
//#include <QJsonDocument>
//#include <QJsonDocument>
//#include <QJsonParseError>

YoudaoAPI::YoudaoAPI(QObject *parent) :
    QObject(parent),
    urlPatten(QString("http://dict.youdao.com/jsonapi?client=mobile&q=%1&dicts=%2"))
{
    netManager = new QNetworkAccessManager();
    connect(netManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onNetworkReply(QNetworkReply*)));
}

void YoudaoAPI::searchWord(const QString &word)
{
    QString dicts="{\"dicts\":[[\"ec\",\"ce\",\"cj\",\"jc\",\"kc\",\"ck\",\"fc\",\"cf\"], \
            [\"baike\"],[\"pic_dict\"],[\"hh\"],[\"phrs\"], \
            [\"wordform\"],[\"ce_new\"], [\"auth_sents_part\"]\
            [\"blng_sents_part\"],[\"web_trans\"],[\"fanyi\"],[\"ec21\"],[\"ee\"],[\"special\"] \
            ],\"count\":99}";
    QUrl url(urlPatten.arg(word,dicts));
    netManager->get(QNetworkRequest(url));
}

void YoudaoAPI::search(const QString &word)
{
    searchWord(word);
}

void YoudaoAPI::onNetworkReply(QNetworkReply *reply)
{
   QJsonObject retObj;
    if(reply->error() != QNetworkReply::NoError) {
        retObj.insert("error",QJsonValue(QString("network error:%1").arg(reply->errorString())));
//        retObj+= QString("\"error\",\"network error:%1\"").a
        searchFinished(retObj);
        return;
    }

//    searchFinished(QString(reply->readAll()));
    QJsonDocument jsonDoc;
    QJsonParseError jerror;


    jsonDoc = QJsonDocument::fromJson(reply->readAll(),&jerror);

    if(jerror.error != QJsonParseError::NoError) {
        retObj.insert("error",QJsonValue(QString("JSON parse error:%1").arg(jerror.errorString())));
        return;
    }

    QJsonObject rootObj;




    if (jsonDoc.isObject()) {
         rootObj = jsonDoc.object();

         //simple
         if (rootObj.contains("simple")) {
             QJsonObject simple = rootObj.value("simple").toObject();
             if (simple.contains("word")) {
                 QJsonObject word = simple.value("word").toArray().at(0).toObject();
//                 QJsonDocument t;
//                 t.setObject(word);
//                 qDebug()<<t.toJson();
                  QJsonArray explainArry;
                  if (word.contains("phone")) {
                     explainArry.append(QJsonValue(QString("[%1]").arg(word.value("phone").toString(""))));
                  }
                  if (word.contains("ukphone")) {
                      explainArry.append(QJsonValue(QString("[英]%1").arg(word.value("ukphone").toString(""))));
                  } if(word.contains("usphone")) {
                      explainArry.append(QJsonValue(QString("[美 ]%1").arg(word.value("usphone").toString(""))));
                  }
//                 explainArry.append(QString("[%1]").arg(word.value("phone").toString()));
                 retObj.insert("基本词典",QJsonValue(explainArry));
//                 explainArry.erase();
             }
         }

//         qDebug()<<retObj.toVariantMap();

         //ec
         if (rootObj.contains("ec")) {
             QJsonArray tempArry;
             QJsonObject ecObj = rootObj.value("ec").toObject();
             //source
             QString dictname;
             if (ecObj.contains("source")) {
                 QJsonObject sourceObj = ecObj.value("source").toObject();
                 //name
                 if (sourceObj.contains("name")) {
                     dictname = sourceObj.value("name").toString("");
                 }
             }

              //word
             if (ecObj.contains("word")) {
                 QJsonObject wordObj = ecObj.value("word").toArray().at(0).toObject();
                 if (wordObj.contains("phone")) {
                    tempArry.append(QJsonValue(QString("[%1]").arg(wordObj.value("phone").toString(""))));
                 }
                 if (wordObj.contains("ukphone")) {
                     tempArry.append(QJsonValue(QString("[英]%1").arg(wordObj.value("ukphone").toString(""))));
                 } if(wordObj.contains("usphone")) {
                     tempArry.append(QJsonValue(QString("[美 ]%1").arg(wordObj.value("usphone").toString(""))));
                 }

                 //trs
                 if(wordObj.contains("trs")) {
                     QJsonArray trsArry = wordObj.value("trs").toArray();
                     if (!trsArry.isEmpty()) {
                         for (int i=0; i < trsArry.size(); i++) {
                             QJsonObject tempObj = trsArry.at(i).toObject();
                             tempArry.append(QJsonValue(QString("%1.").arg(i+1)+tempObj.value("tr").toArray().at(0).toObject().value("l").toObject().value("i").toArray().at(0).toString("")));
                         }
                     }
                 } //end if(wordObj.contains("trs"))
             }  //end if (ecObj.contains("word"))

             retObj.insert("有道词典",QJsonValue(tempArry));
         } //  if (rootObj.contains("ec"))


         //e21
         if (rootObj.contains("ec21")) {
            QString dictName;
            QJsonArray tempArry;
            QJsonObject ec21Obj = rootObj.value("ec21").toObject();
            //source
            if (ec21Obj.contains("source")) {
                QJsonObject sourceObj = ec21Obj.value("source").toObject();
                //name
                if (sourceObj.contains("name"))
                    dictName = sourceObj.value("name").toString("");
                else
                    dictName = "";
            }

            //word
            if (ec21Obj.contains("word")) {
                QJsonArray wordArry = ec21Obj.value("word").toArray();
                for (int i=0; i < wordArry.size(); i++) {
                    QJsonObject wordObj=wordArry.at(i).toObject();
                    if (wordObj.contains("return-phrase")) {
                        QJsonValue retphrValue = wordObj.value("return-phrase").toObject().value("l").toObject().value("i");
                        if (retphrValue.isArray()) {
                            tempArry.append(QJsonValue(retphrValue.toArray().at(0).toString("")));
                        } else if (retphrValue.isString()) {
                            tempArry.append(QJsonValue(retphrValue.toString("")));
                        }
                    }

                    if (wordObj.contains("phone")) {
                        QString phone = wordObj.value("phone").toString("");
                        if (!phone.isEmpty())
                            tempArry.append(QJsonValue(phone));
                    }


                    if (wordObj.contains("trs")) {
                        QJsonArray trsArry = wordObj.value("trs").toArray();
                        for (int j = 0; j < trsArry.size(); j++) {
                            QJsonObject trObj = trsArry.at(j).toObject();
                            if (trObj.contains("pos")) {
                                tempArry.append(QJsonValue(trObj.value("pos").toString("")));
                            }

                            if (trObj.contains("tr")) {
                                QJsonArray subtr = trObj.value("tr").toArray();
                                for (int m = 0; m < subtr.size(); m++) {
                                    tempArry.append(QJsonValue(QString("%1.%2").arg(m+1).arg(subtr.at(m).toObject().value("l").toObject().value("i").toArray().at(0).toString(""))));
                                    QJsonObject temp=subtr.at(m).toObject();
                                    if (temp.contains("exam")) {
                                        QJsonArray exam=temp.value("exam").toArray();
                                        for (int iexam = 0; iexam < exam.size(); iexam ++) {
                                            tempArry.append(QJsonValue(exam.at(iexam).toObject().value("i")
                                                                       .toObject().value("f").toObject().value("l").toObject()
                                                                       .value("i").toString("")));
                                            tempArry.append(QJsonValue(exam.at(iexam).toObject().value("i")
                                                                       .toObject().value("n").toObject().value("l").toObject()
                                                                       .value("i").toString("")));
                                        }
                                    }
                                }
                            }
                        }
                    }

                    if (wordObj.contains("phrs")) { //短语
                        tempArry.append(QJsonValue(QString("短语")));
                        QJsonArray phrs = wordObj.value("phrs").toArray();
                        for (int iphrs = 0; iphrs < phrs.size(); iphrs++) {
                            QJsonObject subPhrs = phrs.at(iphrs).toObject();
                            if (subPhrs.contains("i")) {
                                QJsonArray iArry=subPhrs.value("i").toArray();
                                for (int ii = 0; ii < iArry.size(); ii++) {
                                    QJsonObject iiObj = iArry.at(ii).toObject();
                                    tempArry.append(QJsonValue(QString("%1.%2").arg(ii+1).arg(iiObj.value("phr").toObject()
                                                                                              .value("l").toObject().value("i").toString("") +
                                                                                              QString("  %1").arg(iiObj.value("des").toObject()
                                                                                              .value("l").toObject().value("i").toString("")))));
                                }
                            }
                        }
                    }

                }
            } //end word

            retObj.insert("21世纪大英汉词典",QJsonValue(tempArry));
         } //end e21

         //ee
         if (rootObj.contains("ee")) {
             QString dictname;
             QJsonArray tempArry;
             QJsonObject eeObj = rootObj.value("ee").toObject();

             //source
             if (eeObj.contains("source")) {
                 QJsonObject source = eeObj.value("source").toObject();
                 if (source.contains("name")) {
                     dictname = source.value("name").toString("");
                 } else {
                     dictname = "";
                 }
             }

             //word
             if (eeObj.contains("word")) {
                 QJsonObject wordArry = eeObj.value("word").toObject();
                 if (wordArry.contains("phone")) {
                     tempArry.append(QJsonValue(QString("%1").arg(wordArry.value("phone").toString(""))));
                 }
                 if (wordArry.contains("ukphone")) {
                     tempArry.append(QJsonValue(QString("[英]%1").arg(wordArry.value("ukphone").toString(""))));
                 }
                 if (wordArry.contains("usphone")) {
                     tempArry.append(QJsonValue(QString("[美]%1").arg(wordArry.value("usphone").toString(""))));
                 }
                 if (wordArry.contains("trs")) {
                     QJsonArray trsArry = wordArry.value("trs").toArray();
                     for (int j=0; j< trsArry.size(); j++) {
                         QJsonObject trObj = trsArry.at(j).toObject();
                         if (trObj.contains("pos"))
                             tempArry.append(QJsonValue(QString("%1").arg(trObj.value("pos").toString(""))));

                        if (trObj.contains("tr")) {
                            QJsonArray trArry = trObj.value("tr").toArray();
                            for (int i =0; i < trArry.size(); i++) {
                                QJsonObject subTrObj = trArry.at(i).toObject();
                                if (subTrObj.contains("l"))
                                    tempArry.append(QJsonValue(QString("%1.%2").arg(i+1).arg(subTrObj.value("l").toObject().value("i").toString(""))));
                                if (subTrObj.contains("exam"))
                                    tempArry.append(QJsonValue(subTrObj.value("exam").toObject().value("i").toObject().value("f").toObject().value("l").toArray().at(0).toObject().value("i").toString("")));

                                if (subTrObj.contains("similar-words")) {
                                    QString simString;
                                    QJsonArray simArry = subTrObj.value("similar-words").toArray();
                                    for (int m=0; m < simArry.size(); m++)
                                        simString += simArry.at(m).toObject().value("similar").toString("") + " / ";
                                    simString.remove(simString.length()-2,2);
                                    tempArry.append(QJsonValue(QString("同义词:%1").arg(simString)));
                                }
                            }
                        }
                     }

                 }
             } //end word

//             qDebug()<<tempArry.toVariantList();
             retObj.insert("英英释义",QJsonValue(tempArry));

         }

         //special
         if (rootObj.contains("special")) {
             QString dictname = "专业释义";
             QJsonArray tempArry;
              QString tempString;
             QJsonObject specialObj = rootObj.value("special").toObject();
             if (specialObj.contains("entries")) {
                 QJsonArray entriesArry = specialObj.value("entries").toArray();
                 for (int ientries = 0; ientries < entriesArry.size(); ientries ++ ) {
                     QJsonObject entryObj = entriesArry.at(ientries).toObject().value("entry").toObject();
                     tempArry.append(QString("%1.%2").arg(ientries+1).arg(entryObj.value("major").toString("")));
                     if (entryObj.contains("trs")) {
                         QJsonArray trs = entryObj.value("trs").toArray();
                         for (int j=0; j < trs.size(); j++) {
                             QJsonObject tr = trs.at(j).toObject().value("tr").toObject();
                             if (tr.contains("nat")) {
                                 QString natString = QString(tr.value("nat").toString(""));
                                 if (tr.contains("cite")) {
                                     int cite = tr.value("cite").toString("").toInt();
                                     if (cite > 0)
                                         natString += QString(" - 引用次数: <i>%1</i>").arg(cite);
                                 }
                                 tempArry.append(QJsonValue(natString));
                             }


                             if (tr.contains("engSent")) {
                                 tempArry.append(QJsonValue(QString(tr.value("engSent").toString(""))));
                             }

                             if (tr.contains("chnSent")) {
                                 tempArry.append(QJsonValue(QString(tr.value("chnSent").toString(""))));
                             }
                             if(tr.contains("docTitle")) {
                                 if (tr.contains("url"))
                                    tempArry.append(QJsonValue(QString("参考来源 - <a href=\"%1\">%2</a>")
                                                            .arg(tr.value("url").toString(""))
                                                            .arg(tr.value("docTitle").toString(""))));
                                 else
                                     tempArry.append(QJsonValue(QString("参考来源 - %1")
                                                             .arg(tr.value("docTitle").toString(""))));
                             }
                         }
                     }
                 }

             }

             if (!tempArry.isEmpty())
                 retObj.insert(dictname,QJsonValue(tempArry));
         }

         //blng_sents_part
         if (rootObj.contains("blng_sents_part")) {
             QJsonArray tempArry;
             QJsonObject blngObj = rootObj.value("blng_sents_part").toObject();
             if (blngObj.contains("sentence-pair")) {
                QJsonArray sentenceArry = blngObj.value("sentence-pair").toArray();
                for (int i=0; i < sentenceArry.size(); i++) {
                    QJsonObject sentObj = sentenceArry.at(i).toObject();
                    if (sentObj.contains("sentence")) {
                        tempArry.append(QJsonValue(QString("%1.%2").arg(i+1).arg(sentObj.value("sentence").toString(""))));
                        if (sentObj.contains("sentence-translation")) {
                            tempArry.append(QJsonValue(sentObj.value("sentence-translation").toString("")));
                        }
                    }
                }
             }

             if (!tempArry.isEmpty())
                 retObj.insert("双语例句",QJsonValue(tempArry));
         }

         //auth_sents_part
         if (rootObj.contains("auth_sents_part")) {
             QJsonObject topObj = rootObj.value("auth_sents_part").toObject();
             if (topObj.contains("sent")) {
                 QJsonArray sentArry = topObj.value("sent").toArray();
                 QJsonArray tempArry;
                 for (int i=0; i < sentArry.size(); i++) {
                     QJsonObject subSent = sentArry.at(i).toObject();
                     if (subSent.contains("foreign")) {
                         tempArry.append(QJsonValue(QString("%1.%2").arg(i+1).arg(subSent.value("foreign").toString(""))));
                         if (subSent.contains("source")) {
                             tempArry.append(QJsonValue(QString("来自:%1").arg(subSent.value("source").toString(""))));
                         }
                     }

                 }

                 if (!tempArry.isEmpty())
                     retObj.insert("权威例句",QJsonValue(tempArry));
             }
         }

         //web_trans
         if (rootObj.contains("web_trans")) {
             QJsonObject webObj = rootObj.value("web_trans").toObject();
             if (webObj.contains("web-translation")) {
                 QJsonArray tempArry,webArry=webObj.value("web-translation").toArray();
                 for (int i=0; i < webArry.size(); i++) {
                     QJsonObject subWeb = webArry.at(i).toObject();
                     static int index = 0;
                     if (subWeb.contains("@same") && subWeb.value("@same").toString("") == "true") {
                         if (subWeb.contains("trans")) {
                             QJsonArray trans = subWeb.value("trans").toArray();
                             for (int j=0; j < trans.size(); j++) {
                                 tempArry.append(QString("%1.%2").arg(j+1).arg(trans.at(j).toObject().value("value").toString("")));
                                 tempArry.append(QString(trans.at(j).toObject().value("summary").toObject().value("line").toArray().at(0).toString("")));
                             }
                         }
                     } //end if @same


                     else {
                        if (subWeb.contains("key"))
                            tempArry.append(QString("%1.%2").arg(++index).arg(subWeb.value("key").toString("")));
                        if (subWeb.contains("trans")) {
                            QJsonArray trans = subWeb.value("trans").toArray();
                            QString temp;
                            for (int m=0; m < trans.size(); m++)
                                temp += trans.at(m).toObject().value("value").toString("") +",";
                            temp.remove(temp.length()-1,1);
                            tempArry.append(temp);
                        }

                     }
                 }

                 if(!tempArry.isEmpty())
                     retObj.insert("网络释义",QJsonValue(tempArry));

             }
         }
    } else {
        retObj.insert("error",QJsonValue("Reply format error"));
    }
//    QJsonDocument document;
//    document.setObject(retObj);
//    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
//    QString json_str(byte_array);
//    qDebug()<<json_str;

    searchFinished(retObj);

}
