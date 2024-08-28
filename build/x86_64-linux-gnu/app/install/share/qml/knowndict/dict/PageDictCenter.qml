import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Components.Popups 1.0
import Ubuntu.Components.ListItems 1.0 as ListItem

import "../components"

Page {
    id: pageDictCenter
    title: i18n.tr("Dictionaries")
    state: "default"
    states: [
        PageHeadState {
            name: "default"
            head: pageDictCenter.head
            actions: [
                Action {
                    iconName: "list-add"
                    onTriggered: {
                        mainStack.push(Qt.resolvedUrl("./ContentHubPicker.qml"), {pushOwner: pageDictCenter })
                    }

                }
                ,
                Action {
                    iconName: "info"
                    onTriggered: {
                        mainStack.push(Qt.resolvedUrl("../PageInfo.qml"), {pushOwner: pageDictCenter })
                    }

                }
            ]
        }
    ]

    // property to log who push me to stack ..
    property var pushOwner

    property var dictInfo
    function refreshDictList() {
        modelDict.clear()
        dictInfo = dictCenter.getAllDictInfo()
        for (var i=0; i<dictInfo.length; i++) {
            modelDict.append(dictInfo[i])
        }
    }

    function updateDictList() {
        refreshDictList()
        pushOwner.clearSearchResult()
    }

    Component.onCompleted: {
        refreshDictList()

//        print("dict info: ", dictInfo.length)
    }

    flickable: null

    /////////////////////////////  empty dictionary tips
//    property bool __hasDictionart: true
    Item {
        anchors.fill: parent
        visible: modelDict.count == 0

        Label {
            anchors { left: parent.left; right: parent.right; verticalCenter: parent.verticalCenter; margins: units.gu(3) }
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            horizontalAlignment: Text.AlignHCenter
            text: i18n.tr("No dictionary imported yet, please press the button up here to start importing")
        }

        AnimationUp {
            anchors { right: parent.right; margins: units.gu(6.4) }
        }
    }

    Flickable {
        id: scrollArea
        boundsBehavior: (contentHeight > height) ? Flickable.DragAndOvershootBounds : Flickable.StopAtBounds
        anchors.fill: parent
        contentWidth: width
        contentHeight: columnInnerArea.height + units.gu(3)
        clip: true

//        Label {
//            anchors {
//                top: parent.top; //topMargin: units.gu(1)
////                horizontalCenter: parent.horizontalCenter
//                left: parent.left; right: parent.right
//                margins: units.gu(1)
//            }
//            text: i18n.tr("No dictionary imported yet, please press the button on the top-right to start importing")
//            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
//            horizontalAlignment: Text.AlignHCenter
//            visible: modelDict.count == 0
//        }

        Column {
            id: columnInnerArea

//            spacing: units.gu(1)
            anchors {
                top: parent.top;
                //                topMargin: units.gu(1)
//                margins: units.gu(1)
                left: parent.left; right: parent.right
                //                leftMargin: units.gu(1); rightMargin: units.gu(1)
            }
            height: childrenRect.height

            Repeater {
                model: modelDict

                ListItem.Standard {
                    removable: true
                    confirmRemoval: true
                    text: dictname
                    control: Switch {
//                        checked: status == "1"
                        Component.onCompleted: {
                            if (status == "1") { checked = true }
                            else { checked = false }
                        }

                        onClicked: {
                            var tmpStatus = ""
                            if (checked) { tmpStatus = "1" }
                            else { tmpStatus = "0" }
                            print("dict activated: ", index, checked, tmpStatus)

                            if (dictCenter.updateDictionary(id, tmpStatus)) {
//                                refreshDictList()
//                                pageDictCenter.pushOwner.clearSearchResult()
                                updateDictList()
                            }
                            else {
                                checked = !checked
                                // TODO show error message
                            }
                        }
                    }

                    onItemRemoved: {
                        if (dictCenter.removeDictionary(id, filename)) {
//                            refreshDictList()
                            updateDictList()
                        }
                        else {
                            // TODO show error message
                            print("remove dictionary error!!")
                        }
                    }
                }
            } // Repeater

        } //columnInnerArea
    }

    ListModel { id: modelDict }

}
