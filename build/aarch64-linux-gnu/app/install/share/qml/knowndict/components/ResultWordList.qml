import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Components.ListItems 1.0 as ListItem

ListView {
    id: lvResultWordList
    interactive: false
    anchors { left: parent.left; right: parent.right }
    height: contentItem.childrenRect.height
    clip: true
    visible: modelResultWord.count > 0

    Behavior on height { UbuntuNumberAnimation{} }

    function initial(data, dName) {
        dictName = dName
        modelResultWord.clear()
        for (var i=0; i<data.length; i++) {
            modelResultWord.append(data[i])
        }
    }

    property string dictName: ""
    property bool __isExpanded: false

    /*
      element detail in model:
      {
        dict: <dict name>
        word: <current word candidate>
        offset: for searching detail use
        size: for searching detail use
      }
    */
    model: ListModel { id: modelResultWord }
    delegate: Component {
        ListItem.Base {
//            text: word
            height:  {
                if (index < 1) { return units.gu(14) }
                else if (index < 2) { return units.gu(6) }
                else if (__isExpanded) { return units.gu(6) }
                else { return 0 }
            }
            visible: {
                if (index < 2) { return true }
                else if (__isExpanded) { return true }
                else { return false }
            }

            Component.onCompleted: {
                dictCenter.getWordDetail(dictName, word, offset, size)
            }

            property bool __hasDetail: false
            Connections {
                target: index === 0 && !__hasDetail ? dictCenter : null
                ignoreUnknownSignals: true

                onGetWordDetailResult: {
//                    console.log("qml, word detail: ", JSON.stringify(wordDetail))
                    if (wordDetail.dict === dictName && wordDetail.word === word) {
                        labelDetail.text = wordDetail.detail
                        __hasDetail = true
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    dictCenter.addHistory(word)
                    mainStack.push(Qt.resolvedUrl("../search/PageDetail.qml"))
                    mainStack.currentPage.setData(dictName, word, offset, size)
                }
            }

            Column {
                anchors {
//                    left: parent.left;
//                    leftMargin: units.gu(1)
//                    top: parent.top;
                    topMargin: units.gu(1.8)
                    fill: parent
                }
                spacing: units.gu(0.8)

                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: word
                    elide: Text.ElideRight
                }

                Label {
                    id: labelDetail
                    anchors { left: parent.left; right: parent.right }
                    visible: index == 0
                    text: ""
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    elide: Text.ElideRight
                    maximumLineCount: 3
                }
            }
        }
    }

    header: Component {
        ListItem.Caption {
            text: dictName
            visible: modelResultWord.count > 0

            ListItem.ThinDivider { anchors.bottom: parent.bottom }
        }
    }

    footer: Component {
        ListItem.Base {
//            text: {
//                if (__isExpanded) { return "show less" }
//                else { return "show more" }
//            }
            visible: modelResultWord.count > 2
            height: visible ? units.gu(6) : 0

            onClicked: { __isExpanded = !__isExpanded }

            Label {
                anchors.centerIn: parent
                text: {
                    if (__isExpanded) { return "show less" }
                    else { return "show more" }
                }
                font.bold: true
            }
        }
    }

}

