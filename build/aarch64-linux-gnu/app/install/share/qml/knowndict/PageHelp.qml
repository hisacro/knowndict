import QtQuick 2.2
//import QtQml.Models 2.1
import Ubuntu.Components 1.1
import Ubuntu.Components.ListItems 1.0 as ListItem
//import Ubuntu.Components.Popups 1.0
//import "../components"



Page {
    id: pageHelp
//    title: i18n.tr("Help")
    flickable: null

    // property to log who push me to stack ..
    property var pushOwner

    function backToPushOwner() {
        localSettings.isFirstUse = false
        pageStack.pop()
        if (!localSettings.isPreinstalledEnabled) {
            try {
                pushOwner.showPreinstalled()
            }
            catch (er) {
                // TODO show error
            }
        }
    }

    VisualItemModel {
        id: itemModel

        //////////////////////////////////////////////////             tutorial 1
        Item {
            width: view.width; height: view.height
            Column {
                anchors.fill: parent
                anchors.margins: units.gu(2)
                spacing: units.gu(1)

                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("Welcome to<br>KnownDict")
                    fontSize: "large"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Image {
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "./images/knowndict.png"
                    width: units.gu(15); height: width
                    fillMode: Image.PreserveAspectFit
                }

                Item { width: units.gu(2); height: width }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("KnownDict is a dictonary app for Ubuntu Touch. You can install many different dictionaries.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("This is a special version for Chinese, or those who want to learn Chinese. There are 2 Chinese/English dictionaries ship with this app.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("Warning: due to some law issues, the dictionaries ship with this app are disabled by default. User needs to enable them manually.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    font.bold: true
                }
                Item { width: units.gu(2); height: width }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("Swipe left to continue.")
                    font.italic: true
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }

            }
        }

        //////////////////////////////////////////////////             tutorial 2
        Item {
            width: view.width; height: view.height
            Column {
                anchors.fill: parent
                anchors.margins: units.gu(2)
                spacing: units.gu(1)

                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("Offline usage")
                    fontSize: "large"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("1. This app support StarDict dictionary format file.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("2. To import StarDict dictionary, there's another instruction in setting page to show how to import.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }

            }
        }

        //////////////////////////////////////////////////             tutorial 3
        Item {
            width: view.width; height: view.height
            Column {
                anchors.fill: parent
                anchors.margins: units.gu(2)
                spacing: units.gu(1)

                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("Online usage")
                    fontSize: "large"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("1. This special version ship with Youdao Dictionary online API, it can translate all other languages to Chinese or Chinese to all other languages.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("2. Youdao API is also disabled by default, user needs to enable it manually.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("3. To use Youdao online dictionary, there's a bottom area in the search page to enter Youdao Online Dictionary.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }

            }
        }

        //////////////////////////////////////////////////             tutorial 4
        Item {
            width: view.width; height: view.height
            Column {
                anchors.fill: parent
                anchors.margins: units.gu(2)
                spacing: units.gu(1)

                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("Setting Page")
                    fontSize: "large"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("1. Normally, users are no need to care about their settings, default setting will work fine for most cases.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("2. To enter setting page, press 'Back' button in search page then press the 'setting' button.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("3. In setting page, following functions can be operated by user:")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                //
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("  *. press the 'Plus' button to import new dictionary")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("  *. press the 'Switch' button to enable/disable dictionary")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("  *. swipe from left to delete one dictionary")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }

            }
        }

        //////////////////////////////////////////////////             tutorial 5
        Item {
            width: view.width; height: view.height
            Column {
                anchors.fill: parent
                anchors.margins: units.gu(2)
                spacing: units.gu(1)

                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("Enjoy !")
                    fontSize: "large"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }

                Image {
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "./images/face.jpg"
                }


            }

            Button {
                anchors { centerIn: parent }
                color: UbuntuColors.orange
                text: i18n.tr("Start using KnownDict")
                onClicked: { backToPushOwner() }
            }
        }
    }

    ListView {
        id: view
        anchors { fill: parent; bottomMargin: units.gu(6); topMargin: units.gu(1) }
        model: itemModel
        preferredHighlightBegin: 0; preferredHighlightEnd: 0
        highlightRangeMode: ListView.StrictlyEnforceRange
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem;
        cacheBuffer: 999999
    }

    MouseArea {
        width: units.gu(8); height: units.gu(7)
        anchors.bottom: parent.bottom
        onClicked: { backToPushOwner() }

        Label{ /*anchors.horizontalCenter: parent.horizontalCenter;*/
            anchors.centerIn: parent
            text: i18n.tr("Skip")
            font.italic: true
        }
    }

    // bottom indicator
    Item {
        width: pageHelp.width; height: units.gu(6) 
        anchors { top: view.bottom; bottom: parent.bottom }

        Row {
            anchors.centerIn: parent
            spacing: units.gu(1.8)

            Repeater {
                model: itemModel.count

                Rectangle {
                    width: units.gu(1) ; height: width
                    radius: width
                    color: view.currentIndex == index ? "blue" : "white"

                    MouseArea {
                        width: units.gu(2); height: width
                        anchors.centerIn: parent
                        onClicked: view.currentIndex = index
                    }
                }
            }
        }
    }
}
