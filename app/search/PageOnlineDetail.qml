import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Components.ListItems 1.0 as ListItem
import Ubuntu.Components.Popups 1.0
import "../components"
import "../dict"

Page {
    id: pageSearch
    title: i18n.tr("Online search results")
    flickable: null
    property string __word: ""
    function setData(word) {
        __word = word;
        youdaoDict.searchWord(word);
    }

    Connections {
        target: youdaoDict
        onSearchFinished:{
            loadingIndicator.visible = false
            addResultToList(detail["基本词典"],"基本词典",true);
            addResultToList(detail["有道词典"],"有道词典",true);
            addResultToList(detail["21世纪大英汉词典"],"21世纪大英汉词典",false);
            addResultToList(detail["英英释义"],"英英释义",false);
            addResultToList(detail["专业释义"],"专业释义",false);
            addResultToList(detail["网络释义"],"网络释义",false);
            addResultToList(detail["权威例句"],"权威例句",false);
        }
    }

    Item {
        id: loadingIndicator
        anchors { left: parent.left; right: parent.right; verticalCenter: parent.verticalCenter }
        height: visible ? units.gu(6) : 0

        Row {
            anchors.centerIn: parent
//            width: childrenRect.width; height: childrenRect.height
            spacing: units.gu(2)

            ActivityIndicator {  running: true }

            Label { text: i18n.tr("Loading..."); anchors.verticalCenter: parent.verticalCenter }
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
        } // columnInnerArea
    }

     property var dictArray: []
    function addResultToList(wList, dName,show) {
        if (wList === undefined) {
            return
        }
        print("dictArray.length: ", dictArray.length)
        var isExist = false
        for (var i=0; i<dictArray.length; i++) {
            if(dictArray[i].dictName === dName) {
                dictArray[i].initial(wList, dName,show)
                isExist = true
                break
            }
        }
        if (!isExist) {
            var component = Qt.createComponent("../components/OnlineDict.qml");
            var obj = component.createObject(columnInnerArea);
            obj.initial(wList, dName,show)
            dictArray.push(obj)
        }
    }
}

