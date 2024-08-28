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
                    text: i18n.tr("A. Prepare StarDict dictionary files")
                    fontSize: "large"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }

                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("1. KnownDict supports dictionaries in StarDict dictionary format. Use your favorite search engine to find some. A selection of dictionaries is available at")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                    ListItem.Standard {
                        text: "<b>" + i18n.tr("tuxor1337.frama.io/firedict/dictionaries.html") + "</b>"
                        showDivider: false
                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally("https://tuxor1337.frama.io/firedict/dictionaries.html")
                        }

                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("2. Download and uncompress the zip.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("3. Rename and uncompress dict: mv NAME.dict.dz NAME.dict.gz && gzip -d NAME.dict.gz" )
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("4. Select the corresponding three files for import: NAME.dict, NAME.idx and NAME.ifo - source listed has same name stardict* for all the databases, rename accordingly for multiple imports" )
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
                    text: i18n.tr("B. Copy files to device")
                    fontSize: "large"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("1. Unlock your device and connect it to your PC via USB.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("2. Copy the folder which contains the dictionary files to your devices. Remember the folder's name and location, you will need it in next step.")
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
                    text: i18n.tr("C. In-app import")
                    fontSize: "large"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("1. Due to security reasons, files must be explicitly imported by user.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("2. The button next to 'Instruction', is the entry of importing dictionary files.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("3. When a dialog comes out to ask you what app to choose, please choose 'File Manager'.")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Label {
                    anchors { left: parent.left; right: parent.right }
                    text: i18n.tr("4. Now, select the files which you copied to your device, this app will guide you to complete the rest import process. Enjoy!")
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: UbuntuColors.orange
                    text: i18n.tr("Start Import")
                    onClicked: { pageStack.pop() }
                }
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
        onClicked: { pageStack.pop() }

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
    } // bottom indicator
}
