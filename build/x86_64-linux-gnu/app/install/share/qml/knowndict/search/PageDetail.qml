import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Components.ListItems 1.0 as ListItem
import Ubuntu.Components.Popups 1.0
import "../components"
import "../dict"

Page {
    id: pageSearch
    title: i18n.tr("Detail")
    flickable: null
    state: "default"
    states: [
        PageHeadState {
            name: "default"
            head: pageSearch.head
            actions: [
//                Action {
//                    iconName: "search"
//                    onTriggered: pageSearch.state = "search"
//                }
//                ,
//                Action {
//                    iconName: "attachment"
//                    onTriggered: {
//                        mainStack.push(Qt.resolvedUrl("../dict/PageDictCenter.qml"))
//                    }
//                }
            ]
        }
    ]

    property string __word: ""
    property string __detail: ""
    property string __dictName: ""

    function setData(dictName, word, offset, size) {
        __word = word
        __dictName = dictName
        __detail = ""
        dictCenter.getWordDetail(dictName, word, offset, size)
    }

    Connections {
        target: dictCenter

        onGetWordDetailResult: {
            __detail = wordDetail.detail
        }
    }


    Flickable {
        id: scrollArea
        boundsBehavior: (contentHeight > height) ? Flickable.DragAndOvershootBounds : Flickable.StopAtBounds
        anchors.fill: parent
        contentWidth: width
        contentHeight: columnInnerArea.height + units.gu(3)
        clip: true

        Column {
            id: columnInnerArea

            spacing: units.gu(1)
            anchors {
                top: parent.top;
                //                topMargin: units.gu(1)
                margins: units.gu(1)
                left: parent.left; right: parent.right
                //                leftMargin: units.gu(1); rightMargin: units.gu(1)
            }
            height: childrenRect.height

            Label {
                id: labelWord
                anchors { left: parent.left; right: parent.right }
                text: __word
                elide: Text.ElideRight
                fontSize: "large"
            }

            Label {
                id: labelDetail
                anchors { left: parent.left; right: parent.right }
                text: __detail
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            Label {
                id: labelDictName
                anchors { left: parent.left; right: parent.right }
                text: __dictName
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                opacity: 0.7
            }

            ListItem.ThinDivider{}

            ListItem.Standard {
                visible:__word != ""
//                width:contentWidth
//                height: contentHeight
                anchors{
                    topMargin: units.gu(1);
                    rightMargin: units.gu(1);
                }
                icon:Qt.resolvedUrl("../images/search-online.png");

        //        anchors.top:pageSearch.buttom;
                text:i18n.tr("search via online dictionary >>");
//                color: UbuntuColors.green
                MouseArea {
                    anchors.fill: parent;
                    onClicked: {
                        if (__word != "") {
                            mainStack.push(Qt.resolvedUrl("../search/PageOnlineDetail.qml"));
                            mainStack.currentPage.setData(__word);
                        }
                    }
                }
            }


        } // columnInnerArea
    }
}

