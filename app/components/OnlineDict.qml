import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Components.ListItems 1.0 as ListItem

ListView {
    id: youdaoResult
    interactive: false
    anchors { left: parent.left; right: parent.right }
    height: contentItem.childrenRect.height
    clip: true
    visible: modelResultWord.count > 0

    Behavior on height { UbuntuNumberAnimation{} }

    function initial(data, dName,show) {
        dictName = dName
        modelResultWord.clear()
//        console.log(data);
        if (dName == "error") {
            modelResultWord.append({"value":data});
            return
        }

        for (var i=0; i<data.length; i++) {
            modelResultWord.append({"value":data[i]})
        }
        __isExpanded = show;
    }

    property string dictName: ""
    property bool __isExpanded: false

    model: ListModel { id: modelResultWord }
    delegate: Component {
        ListItem.Empty {
            height:  {
                if (__isExpanded) { return labelDetail.paintedHeight + units.gu(2) }
                else { return 0 }
            }
            visible: {
                if (__isExpanded) { return true }
                else { return false }
            }

            Label {
                id: labelDetail
                width: parent.width
                //                    Layout.fillWidth: true
                //                    height: contentHeight + units.gu(0.5);
                anchors { left: parent.left; right: parent.right; verticalCenter: parent.verticalCenter }
                //                    visible: index != 0
                text: value;
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere

                //                    wrapMode: Text.WordWrap
                //                    elide: Text.ElideRight
                //                    maximumLineCount: 1
            }

        }
    }

    header: Component {
        ListItem.Caption {
            id:dictLabel;
            text: dictName
            visible: modelResultWord.count > 0

            ListItem.ThinDivider { anchors.bottom: parent.bottom }
        }
//        Label {
//            anchors.left: dictLabel.right
////            anchors.centerIn: parent
//            text: {
//                if (__isExpanded) { return "Hide <<" }
//                else { return "Expand >>" }
//            }
    }

    footer: Component {
        ListItem.Base {
//            text: {
//                if (__isExpanded) { return "show less" }
//                else { return "show more" }
//            }
//            visible: modelResultWord.count > 2

            onClicked: { __isExpanded = !__isExpanded }

            Label {
                anchors.centerIn: parent
                text: {
                    if (__isExpanded) { return i18n.tr("Hide <<") }
                    else { return i18n.tr("Expand >>") }
                }
                color: UbuntuColors.darkAubergine
//                font.bold: true
            }
        }
    }

}
