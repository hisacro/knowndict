import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Components.ListItems 1.0 as ListItem
import Ubuntu.Components.Popups 1.0
import "../components"
import "../dict"
import "../pre_installed"

Page {
    id: pageSearch
    title: i18n.tr("KnownDict")

    Component.onCompleted: {
        checkDictionaries()
        timerFirstUse.start()
    }

    function checkDictionaries() {
        var dicts = dictCenter.getAllDictInfo()
        if (dicts.length == 0) {
            __hasDictionart = false
            pageSearch.state = "default"
        }
        else {
            __hasDictionart = true
            pageSearch.state = "search"
        }
    }

    // for first time use
    Timer {
        id: timerFirstUse
        interval: 50; repeat: false; running: false; triggeredOnStart: false
        onTriggered: {
            if (localSettings.isFirstUse) {
                mainStack.push(Qt.resolvedUrl("../PageHelp.qml"), {pushOwner: pageSearch })
            }
        }
    }
    function showPreinstalled() {
        mainStack.push(Qt.resolvedUrl("../PageEnablePreinstalled.qml"), {pushOwner: pageSearch })
    }
    //////////////////// end

    flickable: null
    state: "search"
    states: [
        PageHeadState {
            name: "default"
            head: pageSearch.head
            actions: [
                Action {
                    iconName: "search"
                    onTriggered: pageSearch.state = "search"
                }
                ,
                Action {
                    iconName: "settings"
                    onTriggered: {
                        mainStack.push(Qt.resolvedUrl("../dict/PageDictCenter.qml"), {pushOwner: pageSearch })
                    }
                }
            ]
        },
        PageHeadState {
            id: headerState
            name: "search"
            head: pageSearch.head
//            actions: [
//                Action {
//                    id: acSearchStart
//                    iconName: "search"
//                    onTriggered: {
//                        // TODO  start search session
//                    }
//                }
//            ]
            backAction: Action {
                id: acleaveSearch
                text: i18n.tr("back")
                iconName: "back"
                onTriggered: pageSearch.state = "default"
            }
            contents: TextField {
                id: tfSearchWord
                anchors {
                    right: pageSearch.state == "search" ? parent.right : undefined
                    rightMargin: units.gu(1)
                }
                visible: pageSearch.state == "search"
                inputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase
                placeholderText: i18n.tr("Please input a word")

                onTextChanged: {
                    if (text === "") {
                        var historyArr = dictCenter.getHistories()
//                        print("dictCenter.getHistories(): ", historyArr.length)
                        lvHistory.setData(historyArr)
                    }
//                    else {
//                    }
                    timerSearch.stop()
                    timerSearch.start()
                }

                onFocusChanged: {
                    if (text === "") {
                        var historyArr = dictCenter.getHistories()
//                        print("dictCenter.getHistories(): ", historyArr.length)
                        lvHistory.setData(historyArr)
                    }
                }

                Keys.onReturnPressed: { if (tfSearchWord.text != "") {dictCenter.searchWords(tfSearchWord.text)} }
                Keys.onEnterPressed: { if (tfSearchWord.text != "") {dictCenter.searchWords(tfSearchWord.text)} }
            }
        }
    ]

    Timer {
        id: timerSearch; interval: 700; running: false; repeat: false; triggeredOnStart: false
        onTriggered: {
            if (tfSearchWord.text != "") {
                dictCenter.searchWords(tfSearchWord.text)
            }
        }
    }

    ////////////////////////////////////
    //   property & function & connection for adding search result to this page
    ////////////////////////////////////
    property var dictArray: []

    function addResultToList(wList, dName) {
        print("dictArray.length: ", dictArray.length)
        var isExist = false
        for (var i=0; i<dictArray.length; i++) {
            if(dictArray[i].dictName === dName) {
                dictArray[i].initial(wList, dName)
                isExist = true
                break
            }
        }
        if (!isExist) {
            var component = Qt.createComponent("../components/ResultWordList.qml");
            var obj = component.createObject(columnInnerArea);
            obj.initial(wList, dName)
            dictArray.push(obj)
        }
    }

    Connections {
        target: dictCenter
        onSearchWordsResult: {
            addResultToList(wordList, dictName)
        }

    }

    function clearSearchResult() {
        for (var i=0; i<dictArray.length; i++) {
            dictArray[i].destroy()
        }
        dictArray = []
    }

    /////////////////////////////  empty dictionary tips
    property bool __hasDictionart: true
    Item {
        anchors.fill: parent
        visible: !__hasDictionart && pageSearch.state == "default"

        Label {
            anchors { left: parent.left; right: parent.right; verticalCenter: parent.verticalCenter; margins: units.gu(3) }
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            horizontalAlignment: Text.AlignHCenter
            text: i18n.tr("No dictionary found, please the press Setting button to start importing. ")
        }

        AnimationUp {
            anchors { right: parent.right; margins: units.gu(1.5) }
        }
    }

    /////////////////////////////     main content
    Flickable {
        id: scrollArea
        boundsBehavior: (contentHeight > height) ? Flickable.DragAndOvershootBounds : Flickable.StopAtBounds
        anchors {
            left: parent.left; right: parent.right
            bottom: liOnlineEntry.top; top: parent.top
        }

        contentWidth: width
        contentHeight: columnInnerArea.height + units.gu(6)
        clip: true
        visible: tfSearchWord.text != ""

        Column {
            id: columnInnerArea

//            spacing: units.gu(1)
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

    //////////////////////////////////////////////                       online search entry
    ListItem.Standard {
        id: liOnlineEntry
        visible:tfSearchWord.text !== "" && pageSearch.state === "search"
        iconSource:Qt.resolvedUrl("../images/search-online.png");
        anchors{
            bottom: parent.bottom; bottomMargin: Qt.inputMethod.keyboardRectangle.height
        }

        text:i18n.tr("search via online dictionary >>");

        onClicked: {
            if (tfSearchWord.text != "") {
                mainStack.push(Qt.resolvedUrl("../search/PageOnlineDetail.qml"));
                mainStack.currentPage.setData(tfSearchWord.text);
                dictCenter.addHistory(tfSearchWord.text)
            }
        }

    }

    ////////////////////////////////////////////////             search history listview
    ListView {
        id: lvHistory
        anchors { left: parent.left; right: parent.right }
        height: contentItem.childrenRect.height
        clip: true
        visible: tfSearchWord.text === "" && pageSearch.state === "search"

        Component.onCompleted: {
            var historyArr = dictCenter.getHistories()
            lvHistory.setData(historyArr)
        }

        function setData(historyArr) {
            modelHistory.clear()
            for (var i=0; i<historyArr.length; i++) {
                modelHistory.append(historyArr[i])
            }
        }

        model: ListModel { id: modelHistory }
        delegate: Component {
            ListItem.Standard {
                text: word

                onClicked: { tfSearchWord.text = word }
            }
        }

        header: Component {
            ListItem.Caption {
                text: i18n.tr("History")

                ListItem.ThinDivider { anchors.bottom: parent.bottom }
            }
        }

    } // lvHistory


}

