import QtQuick 2.2
import Qt.labs.settings 1.0
import Ubuntu.Components 1.1

import "search"
import "dict"
import "components"
import "js"
import "pre_installed"



MainView {
    // objectName for functional testing purposes (autopilot-qt5)
    objectName: "mainView"
    id: mainView

    // Note! applicationName needs to match the "name" field of the click manifest
    applicationName: "knowndict.hisacro"

    /*
     This property enables the application to change orientation
     when the device is rotated. The default is false.
    */
    //automaticOrientation: true

    // Removes the old toolbar and enables new features of the new header.
    useDeprecatedToolbar: false

    width: units.gu(100)
    height: units.gu(75)

    Settings {
        id: localSettings

        property bool isFirstUse: true
        property bool isPreinstalledEnabled: false

        ///////////////////////////  background settings
        property color headColor
        property color bgColor
        property color footColor

        property string bgImage
    }

    //////////////////////////////////////////////////////////////////         main PageStack
    PageStack {
        id: mainStack
        anchors.fill: parent

        Component.onCompleted: {
            timerFirstPush.start()
        }

        Timer {
            id: timerFirstPush
            interval: 50; repeat: false; running: false; triggeredOnStart: false
            onTriggered: {
                mainStack.push(Qt.resolvedUrl("./search/PageSearch.qml"))
//                mainStack.push(Qt.resolvedUrl("./PageHelp.qml"))
            }
        }
    }
}

