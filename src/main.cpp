#include <QtGui>
#include <QtCore>
#include <QtQuick>

#include "dictcenter.h"
#include "youdaoapi.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qSetMessagePattern("%{file}- %{line}: %{function} M: %{message}");

    app.setApplicationName("knowndict.hisacro");

    QQuickView *viewer = new QQuickView();

    qRegisterMetaType<WordList>("WordList");

    DictCenter dictCenter;
    YoudaoAPI youdaoDict;
    viewer->engine()->rootContext()->setContextProperty("dictCenter", &dictCenter);
    viewer->engine()->rootContext()->setContextProperty("youdaoDict",&youdaoDict);

    viewer->setResizeMode(QQuickView::SizeRootObjectToView);
//    viewer->setSource(QUrl("./qml/splash.qml"));
//    viewer->show();
//    QElapsedTimer t;
//    t.start();
//    while(t.elapsed()<100)
//    {
//        QCoreApplication::processEvents();
//    }
    viewer->setSource(QUrl("./share/qml/knowndict/knowndict.qml"));
//    viewer->setSource(QUrl("/home/beny/Ubuntu4Phone/mainline/app/knowndict.qml"));
    viewer->show();

    return app.exec();
}
