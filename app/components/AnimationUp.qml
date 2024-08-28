import QtQuick 2.2
import Ubuntu.Components 1.1

Column {
    width: childrenRect.width; height: childrenRect.height

    Icon {
        id: up0
        width: units.gu(4); height: units.gu(3)
        name: "go-up"
        color: UbuntuColors.orange
    }
    Icon {
        id: up1
        width: units.gu(4); height: units.gu(3)
        name: "go-up"
        color: UbuntuColors.orange
    }
    Icon {
        id: up2
        width: units.gu(4); height: units.gu(3)
        name: "go-up"
        color: UbuntuColors.orange
    }
    Icon {
        id: up3
        width: units.gu(4); height: units.gu(3)
        name: "go-up"
        color: UbuntuColors.orange
    }

    SequentialAnimation {
        running: true
        loops: Animation.Infinite

        UbuntuNumberAnimation { target: up3; properties: "opacity"; from: 1; to: 0; duration: 700 }
        UbuntuNumberAnimation { target: up2; properties: "opacity"; from: 1; to: 0; duration: 700 }
        UbuntuNumberAnimation { target: up1; properties: "opacity"; from: 1; to: 0; duration: 700 }
        UbuntuNumberAnimation { target: up0; properties: "opacity"; from: 1; to: 0; duration: 700 }
    }



}

