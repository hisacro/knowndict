import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Components.ListItems 1.0 as ListItem
import Ubuntu.Components.Popups 1.0
import "./components"
import "./dict"
import "./pre_installed"

Page {
    id: pageEnablePreinstalled
    flickable: null
//    title: "pageEnablePreinstalleds"

    // property to log who push me to stack ..
    property var pushOwner
    function backToPushOwner() {
        try {
            pushOwner.checkDictionaries()
        }
        catch (err) {
            // TODO show errors
        }
        mainStack.pop()
//        timerPop.start()
    }
    Timer {
        id: timerPop
        interval: 300; repeat: false; running: false; triggeredOnStart: false
        onTriggered: {
//            mainStack.pop()
            backToPushOwner()
        }
    }

    Component.onCompleted: {
        PopupUtils.open(comShowPre)
    }

    ///////////////////////////////////////////////////////////////                 dialogs for pre-installed dictionaries
    Component {
        id: comShowPre
        Dialog {
            id: dia
            title: i18n.tr("Enable dictionaries")
            text: i18n.tr("The following dictionaries are pre-installed, due to some law issues, the dictionaries are disabled by default. User needs to enable them manually.")

            Label { text: i18n.tr("Langdao English-Chinese"); font.italic: true }
            Label { text: i18n.tr("Langdao Chinese-English"); font.italic: true }
            Label { text: i18n.tr("Youdao online API"); font.italic: true }

            Button {
                text: "Yes, enable it!";
                color: UbuntuColors.orange;
                onClicked: {
                    PopupUtils.close(dia); PopupUtils.open(comyes);
                }
            }
            Button { text: "No, I can do it myself."; onClicked: { PopupUtils.close(dia); PopupUtils.open(comno) } }

        }
    }

    Component {
        id: comyes
        Dialog {
            id: diayes
            title: i18n.tr("Enable dictionaries")
//            text: i18n.tr("importing ... ")

            Component.onCompleted: {
                timerImport.start()
            }

            Timer {
                id: timerImport
                interval: 200; repeat: false; running: false; triggeredOnStart: false
                onTriggered: {
                    // langdao Chinese-English
                    var dictlist0 = new Array
                    dictlist0.push(Qt.resolvedUrl("./pre_installed/langdao_ce/langdao-ce-gb.dict").replace("file://", ""))
                    dictlist0.push(Qt.resolvedUrl("./pre_installed/langdao_ce/langdao-ce-gb.idx").replace("file://", ""))
                    dictlist0.push(Qt.resolvedUrl("./pre_installed/langdao_ce/langdao-ce-gb.ifo").replace("file://", ""))
                    var result0 = dictCenter.importDict(dictlist0)
                    print("langdao Chinese-English imported: ", result0.no_error)
                    // langdao English-Chinese
                    var dictlist1 = new Array
                    dictlist1.push(Qt.resolvedUrl("./pre_installed/langdao_ec/langdao-ec-gb.dict").replace("file://", ""))
                    dictlist1.push(Qt.resolvedUrl("./pre_installed/langdao_ec/langdao-ec-gb.idx").replace("file://", ""))
                    dictlist1.push(Qt.resolvedUrl("./pre_installed/langdao_ec/langdao-ec-gb.ifo").replace("file://", ""))
                    var result1 = dictCenter.importDict(dictlist1)
                    print("langdao English-Chinese imported: ", result1.no_error)

                    aiImporting.running = false; aiImporting.visible = false
                    if (result0.no_error && result1.no_error) {
                        labelDone.visible = true
                        localSettings.isPreinstalledEnabled = true
                    }
                    else {
                        labelFail.visible = true
                    }
                    btnDone.visible = true
                }
            }

            ActivityIndicator { id:aiImporting; running: true }

            Label { id:labelDone; visible: false; text: i18n.tr("Dictionaries successfully imported :)") }
            Label { id:labelFail; visible: false; text: i18n.tr("Sth wrong during import.. :(") }

            Button {
                id:btnDone; visible: false; text: i18n.tr("OK"); color: UbuntuColors.orange;
                onClicked: {

                    if (labelFail.visible) { PopupUtils.close(diayes); PopupUtils.open(comno) }
                    else {
                        PopupUtils.close(diayes);
//                        pageEnablePreinstalled.backToPushOwner()
                        timerPop.start()
                    }

                }
            }

        }
    }

    Component {
        id: comno
        Dialog {
            id: diano
            title: i18n.tr("It's OK")
            text: i18n.tr("You still can enable it in Info page.")

            Button { text: "OK";
                onClicked: { PopupUtils.close(diano);
//                    pageEnablePreinstalled.backToPushOwner()
                    timerPop.start()
                }
            }

        }
    }

}
