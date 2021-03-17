import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQuick 2.14

Item {
    id: root
    width: 250
    height: view.childrenRect.height + 30

    property int colabsCounter: 0
    property var backColor: ["#4287f5", "#f5b042", "#f56042", "#f54242", "#b942f5", "#4257f5", "#f5429c"]

    ColumnLayout {
        id: view
        z: 2
        width: 225

        anchors.topMargin: 10
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

//        implicitHeight: taskTxt.height + tags.height + workers.height

        TextField {
            id: taskTxt

            text: taskTitle
            horizontalAlignment: Text.AlignLeft
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true

            selectByMouse: true
            background: Rectangle { color: "transparent"; }
            Keys.onReturnPressed:
                focus = false;
            onFocusChanged: {
                if (!focus)
                    client.updateTaskTitle(taskId, text);
            }
        }

        ColumnLayout {
            id: tags
            width: parent.width

            Flow {
                id: tagsFlow

                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 5

                Repeater {
                    id: rep
                    model: tagsModel

                    Item {
                        id: tag

                        width: name.width + 10
                        height: name.height + 4
                        Text {
                            z: 5
                            id: name

                            anchors.centerIn: parent
                            text: qsTr(modelData)
                            color: "white"
                        }

                        Rectangle {
                            id: tagBack
                            anchors.fill: parent
                            radius: 7
                            color: backColor[Math.ceil(Math.random() * (backColor.length - 1))]
                        }
                    }
                }
            }
        }

        ColumnLayout {
            id: workersView

            Repeater {
                id: colabsRepeater
                model: WorkersModel

                Row {
                    id: row
                    spacing: 5
                    Rectangle {
                        color: Material.color(Material.Pink)
                        width: 24
                        height: 24
                        radius: 50

                        Text {
                            anchors.centerIn: parent
                            text: colaborantIcon
                            color: "white"
                        }
                    }
                    Text {
                        text: qsTr("%1 %2").arg(colaborantName).arg(colaborantSurname)
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }

    }

    RoundButton {
        id: back

        anchors.fill: parent
        Material.background: "white"
        radius: 6

    }


}



