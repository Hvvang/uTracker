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
                text: qsTr("A")
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
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
            id: flowTitle
            text: qsTr("What is Lorem Ipsum?
Lorem Ipsum is simply dummy text of the printing and typesetting industry.")
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
                value: 25
            }

        }

        Item {
            id: footer
            height: 40
            Layout.fillWidth: true

            Row {
                spacing: -20

                Repeater {
                    model: 4

                    RoundButton {
                        width: 40
                        height: 40
                        text: "A"

                        Material.background: Material.Pink
                        Material.foreground: "white"
                    }
                }
                RoundButton {
                    width: 40
                    height: 40
                    text: "+6"
                    font.pointSize: 10

                    Material.background: Material.Grey
                    Material.foreground: "black"
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
            client.openWorkflow(model.index)
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
            onTriggered: back.clicked()
            height: 30
            width: parent.width
        }
        MenuItem {
            text: "\ue809  edit"
            font.family: "fontello"
            onTriggered: back.Material.background = Material.Yellow
            height: 30
            width: parent.width
        }
        MenuItem {
            text: "\ue808  archive"
            font.family: "fontello"
            onTriggered: back.Material.background = Material.Red
            height: 30
            width: parent.width
        }
    }
}
