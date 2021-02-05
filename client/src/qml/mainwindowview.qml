import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.15

Item {
    id: root

    anchors.fill: parent

    HeaderPanel {
        id: header
    }

    MainControlPanel {
        id: menu
    }

    Item {
        id: workPanel
        anchors.top: header.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: menu.right

        anchors.margins: 10

        Loader {
            id: workPanelLoader
            objectName: "panelLoader"
            anchors.fill: parent
            source: "/mainwindow/WorkFlows.qml"

        }

    }
}
