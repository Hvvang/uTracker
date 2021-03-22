import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.12
import QtQuick.Controls.Styles 1.3
import QtQuick.Controls.Material.impl 2.12

Item {
    id: root
    width: 200
    height: 200

    property var flowModel;

    ColumnLayout {
        z: 10
        id: wrapper
        spacing: 1
        anchors.fill: parent
        anchors.margins: 15

        Item {
            id: header
            height: 30
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

            Text {
                id: logo
                text: qsTr("\uf133 %1").arg(flowDeadline)
                font.family: "fontello"
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
                color: {
                    var currentTime = new Date();
                    var deadline = Date.fromLocaleString(Qt.locale(), flowDeadline, "dd-MM-yyyy")
//                    print(currentTime.getTime(),  deadline.getTime(), currentTime.getTime() > deadline.getTime())
                    print("diff: ", currentTime.getTime() -  deadline.getTime())
                    if (currentTime.getTime() > deadline.getTime()) {
                        return "red"
                    } else if (deadline.getTime() - currentTime.getTime() < 24263727 * 7) {
                        return "orange"
                    } else {
                      return "black";
                    }
                }

                font.pixelSize: 17
            }

            ToolButton {
                id: menuBtn
                text: qsTr("\ue806")
                font.family: "fontello"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right

                onClicked: {
                    contextMenu.popup()
                }
            }
        }

        Text {
            id: workflowTitle
            text: flowTitle
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
            verticalAlignment: Text.AlignTop
            font.pixelSize: 12
        }

        Item {
            id: progress
            height: 20
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true

            Text {
                id: percent
                text: qsTr("%1\%".arg(progressBar.value))
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 12
            }

            ProgressBar {
                id: progressBar
                to: 100
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: percent.bottom
                hoverEnabled: false
                indeterminate: flowProgress !== 100
                value: flowProgress
            }

        }

        Item {
            id: footer
            height: 40
            Layout.fillWidth: true

            Row {
                spacing: -20

                Repeater {
                    id: colabRepeater
                    model: flowModel

                    RoundButton {
                        width: 40
                        height: 40
                        text: qsTr("%1").arg(colaborantIcon)

                        Material.background: Material.Pink
                        Material.foreground: "white"
                    }

                }
                RoundButton {
                    width: 40
                    height: 40
                    visible: colabRepeater.count - 4 > 0
                    text: qsTr("+%1").arg(colabRepeater.count - 4)
                    font.pointSize: 10

                    Material.background: Material.Grey
                    Material.foreground: "black"
                }

                Rectangle {
                    id: tag

                    visible: !colabRepeater.count
                    width: txt.width + 10
                    height: txt.height + 10
                    Text {
                        id: txt
                        anchors.centerIn: parent
                        text: qsTr("personal");
                        color: Material.color(Material.Pink)
                    }
                    radius: 7
                    border.width: 1
                    border.color: Material.color(Material.Pink)
                    color: "transparent"
                }
            }
        }
    }


    RoundButton {
        id: back
        anchors.fill: parent

        Material.background: "white"
        radius: 7

        onClicked: {
            client.openWorkflow(flowId)
        }
    }

    Menu {
        id: contextMenu

        width: 100
        topPadding: 0
        bottomPadding: 0

        font.pixelSize: 13

        background: Pane {
            anchors.fill: parent
            Material.primary: Material.Grey
            Material.elevation: 6

        }

        MenuItem {
            text: "\ue80a  open"
            font.family: "fontello"
            onTriggered: back.clicked()
            height: 30
            width: parent.width
        }
        MenuItem {
            text: "\uf234  invite"
            font.family: "fontello"
            onTriggered: inviteDialog.open(flowId)
            height: 30
            width: parent.width
        }
        MenuItem {
            text: "\ue809  edit"
            font.family: "fontello"
            onTriggered: {
                dialog.open(flowId, flowTitle, flowDeadline)
            }
            height: 30
            width: parent.width
        }
        MenuItem {
            text: "\ue808  archive"
            font.family: "fontello"
            onTriggered: client.archiveWorkflow(flowId)
            height: 30
            width: parent.width
        }
    }
}
