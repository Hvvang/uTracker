import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Controls 2.13


Item {
    id: root

    anchors.fill: parent

    Headerpanel {
        id: header
    }

    Item {
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        SplitView {
            anchors.fill: parent
            orientation: Qt.Horizontal

            Material.background: "transparent"

            Maincontrolpanel {
                id: menu

                SplitView.minimumWidth: 200
                SplitView.maximumWidth: 400
            }

            Loader {
                id: workPanelLoader
                objectName: "panelLoader"

                anchors.margins: 10

                SplitView.minimumWidth: 50
                SplitView.fillWidth: true
                source: "Workflowsview.qml"

            }

        }
    }

}