import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Controls 2.13

import "../workflowswindow"

Item {
    id: root

    anchors.fill: parent

    width: parent.width
    height: parent.height

    WorkflowDialog {
        id: dialog
    }
    InviteColaborantDialog {
        id: inviteDialog
    }

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

                anchors.margins: 10

                SplitView.minimumWidth: 50
                SplitView.fillWidth: true

                source: "qrc:/qml/workflowswindow/Workflowsview.qml"

                Connections {
                    target: client
                    function onSwitchMenu(source) {
                      workPanelLoader.source = source;
                    }
                }
            }

        }
    }

}
