/*
 * Flashback - Entertainment app for Ubuntu
 * Copyright (C) 2013, 2014 Nekhelesh Ramananthan <nik90@ubuntu.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Components.ListItems 1.0 as ListItem
import "./components"

Page {
    id: pageInfo

    flickable: null
    title: i18n.tr("About KnownDict")

    /////////////////////////////     main content
    Flickable {
        id: scrollArea
        boundsBehavior: (contentHeight > height) ? Flickable.DragAndOvershootBounds : Flickable.StopAtBounds
        anchors.fill: parent
        contentWidth: width
        contentHeight: columnInnerArea.height + units.gu(3)
        clip: true

        Column {
            id: columnInnerArea
            spacing: units.gu(2)
            anchors {
                top: parent.top;
                margins: units.gu(1)
                left: parent.left; right: parent.right
            }
            height: childrenRect.height

            SettingsItem {
                title: i18n.tr("Help")
                contents: [
                    ListItem.Standard {
                        text: i18n.tr("Show First Run Tutorial")
                        iconFrame: false
                        showDivider: false
                        progression: true
                        iconName: "help"
                        onClicked: mainStack.push(Qt.resolvedUrl("./PageHelp.qml"), {pushOwner: pageInfo });
                    }
                ]
            }

            SettingsItem {
                title: i18n.tr("Enable default dictionaries")
                visible: !localSettings.isPreinstalledEnabled
                contents: [
                    ListItem.Standard {
                        text: i18n.tr("Enable it")
                        iconFrame: false
                        showDivider: false
                        progression: true
                        onClicked: mainStack.push(Qt.resolvedUrl("./PageEnablePreinstalled.qml"), {pushOwner: pageInfo })
                    }
                ]
            }

            SettingsItem {
                title: i18n.tr("Author")
                contents: [
                    ListItem.Standard {
                        text: "hisacro <fsl@displ.nl>"
                    },

                    ListItem.Standard {
                        text: "Peter Putz <p.putz@yahoo.de>"
                    },

                    ListItem.Standard {
                        text: "Beny Fu <fuxixi1991@163.com>"
                    },

                    ListItem.Standard {
                        text: "Joey Chan <joeychan.ubuntu@gmail.com>"
                    }
                ]
            }

            SettingsItem {
                title: i18n.tr("Disclaimer")
                contents: [
                    //
                    ListItem.Standard {
                        text: i18n.tr("License with GPLv3")
                        showDivider: false
                    },

                    Label {
                        text: i18n.tr("Dictionaries/Online API used by this app is not/nendorsed or certified by their copyrights' owner.")
                        anchors { left: parent.left; right: parent.right; margins: units.gu(2) }
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    },

                    ListItem.Standard {
                        text: "<b>" + i18n.tr("Click here to report a bug") + "</b>"
                        showDivider: false
                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally("https://github.com/hisacro/knowndict/issues")
                        }
                    }
                ]
            }
        }
    }
}
