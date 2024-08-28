import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Components.Popups 1.0
import Ubuntu.Content 1.1
import Ubuntu.Components.ListItems 1.0 as ListItem
import "../components"

Page {
    id: contentHubPicker
    title: i18n.tr("Import Dictionaries")
    flickable: null
//    anchors.fill: parent

    // property to log who push me to stack ..
    property var pushOwner

//    property string imgPath: ""

    property list<ContentItem> importItems
    property var activeTransfer
    property list<ContentPeer> peers

    // some variables to indicate the files are missing or not
    property bool isIFO: false
    property bool isIDX: false
    property bool isDICT: false

    signal filesPicked(string filePath)

    Component.onCompleted: {
//        PopupUtils.open(contentPickerDialog)
//        loaderContentHub.load()
//        timerContentPickerDialog.start()
//        mainStack.push(contentPickerDialog)
    }

    Timer {
        id: timerContentPickerDialog
        interval: 50; running: false; repeat: false; triggeredOnStart: false
        onTriggered: {
//            PopupUtils.close(componentPreviewSheet)
//            filesPicked(imgPath)
//            pageStack.pop()
            mainStack.push(contentPickerDialog)
        }
    }

    Timer {
        id: timerPop
        interval: 150; running: false; repeat: false; triggeredOnStart: false
        onTriggered: {
            pageStack.pop()
        }
    }

    function slotFilesPicked(path) {
//        PopupUtils.close(contentPickerDialog)
//
//        imgPath = path
//        loaderContentHub.unload()
//        mainView.addNotification(path, 3)
//        loaderPreview.load()
//        filesPicked(path)
//        pageStack.pop()

    }

    function slotCancelHub() {
        pageStack.pop()
    }

    //////////////////////////////////////////////////////////////////         content hub
    ContentPickerDialog{
        id: contentPickerDialog
        pickerParent: contentHubPicker
    }

    ContentTransferHint {
        anchors.fill: contentHubPicker
        activeTransfer: contentHubPicker.activeTransfer
    }

    Connections {
        target: contentPickerDialog.visible ? contentHubPicker.activeTransfer : undefined
        onStateChanged: {
            console.log("StateChanged: " + contentHubPicker.activeTransfer.state);
            if (contentHubPicker.activeTransfer.state === ContentTransfer.Charged
              /*      || contentHubPicker.activeTransfer.state === ContentTransfer.Collected*/) {
                contentHubPicker.importItems = contentHubPicker.activeTransfer.items;
//                console.log("importItems[0].: " + String(contentHubPicker.importItems[0].url) );
//                console.log("importItems[1].: " + JSON.stringify(importItems[1]) );
//                console.log("importItems[2].: " + JSON.stringify(importItems[2]) );
//                contentHubPicker.imgPath =
//                        String(contentHubPicker.importItems[0].url).replace("file://", "")
//                loaderPreview.load()
                isIFO = false
                isIDX = false
                isDICT = false
                modelImportItems.clear()
                for (var i=0; i<importItems.length; i++) {
                    modelImportItems.append({ "url": String(importItems[i].url) })
                    print("url: ", String(importItems[i].url))
                    var suffix = String(importItems[i].url).split(".").pop().toString()
                    if (suffix === "ifo" || suffix === "IFO") { isIFO = true }
                    if (suffix === "idx" || suffix === "IDX") { isIDX = true }
                    if (suffix === "dict" || suffix === "DICT") { isDICT = true }
                }
            }
            else if (contentHubPicker.activeTransfer.state === ContentTransfer.Aborted) {
//                timerPop.start()
            }
        }
    }

    ///////////////////////////////////////////////////////////
    //  UI for end users

    Flickable {
        id: scrollArea
        boundsBehavior: (contentHeight > height) ? Flickable.DragAndOvershootBounds : Flickable.StopAtBounds
        anchors.fill: parent; anchors.topMargin: units.gu(1)
        contentWidth: width
        contentHeight: columnInnerArea.height + units.gu(3)
        clip: true

        Column {
            id: columnInnerArea
            anchors { left: parent.left; right: parent.right }

            Column {
                anchors { left: parent.left; right: parent.right }
                spacing: units.gu(1)

                Label {
                    anchors { left: parent.left; right: parent.right; margins: units.gu(1) }
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    horizontalAlignment: Text.AlignHCenter
                    text: {
                        if (modelImportItems.count == 0) {
                            return i18n.tr("No file detected, please press the button below to import files. "
                                           + "Or if you don't know what to import, please read the instruction")
                        }
                        else {
                            if (isIFO && isIDX && isDICT) {
                                return i18n.tr("Dictionary files detected, please press the button below to proceed. ")
                            }
                            else {
                                return i18n.tr("Some files are missing, please make sure there are "
                                               + "one .ifo file, one .idx file and one .dict file. ")
                            }
                        }
                    }
                }

                Row {
                    //                anchors { left: parent.left; right: parent.right; margins: units.gu(1) }
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: childrenRect.width
                    height: childrenRect.height
                    spacing: units.gu(5)
                    visible: !isIFO || !isIDX || !isDICT

                    Button {
                        text: i18n.tr("Instruction")
                        onClicked: { mainStack.push(Qt.resolvedUrl("./PageHelpImport.qml")) }
                    }

                    Button {
                        color: UbuntuColors.orange
                        text: i18n.tr("Start Import")
                        onClicked: { mainStack.push(contentPickerDialog) }
                    }
                }

                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: UbuntuColors.orange
                    visible: isIFO && isIDX && isDICT
                    text: i18n.tr("Complete Import")

                    onClicked: {
                        var dictlist = new Array
                        for (var i=0; i<importItems.length; i++) {
                            dictlist.push(String(importItems[i].url).replace("file://", ""))
                        }
                        var result = dictCenter.importDict(dictlist)
                        if (result.error) {
                            print(result.error)
                        }
                        else {
                            pushOwner.refreshDictList()
                            mainStack.pop()
                        }
                    }
                }
            }

            Repeater {
                model: modelImportItems

                ListItem.Standard {
                    text: String(url).split("/").pop().toString()
                }
            }
        }

    }

    ListModel {
        id: modelImportItems
    }


}
