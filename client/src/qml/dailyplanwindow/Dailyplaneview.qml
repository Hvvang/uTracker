import QtQuick 2.8
import QtQuick.Window 2.12
import Qt.labs.settings 1.0
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item {
    id: root
    anchors.fill: parent

    ColumnLayout {
        anchors.fill: root
        anchors.margins: 10

        Text {
            id: header
            text: qsTr("Plan")
            font.pixelSize: 30
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

        }

        Text {
            text: qsTr("Create new task\nTo Start manage your day.")
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            visible: !(rep.count)
        }
        Flickable {
            id: flickable

            Layout.fillHeight: true
            Layout.fillWidth: true
            visible: (rep.count)
            contentHeight: view.height; contentWidth: view.width;
            clip: true

            ColumnLayout {
                id: view

                width: flickable.width

                Repeater {
                    id: rep
                    model: DailyPlanModel

                    RowLayout {
                        Layout.fillWidth: true

                        CheckBox {
                            id: statusBox
                            checked: dailyTaskStatus
                            onClicked: {
                                client.changeDailyTask(dailyTaskId, dailyTaskDescription, statusBox.checked);
                            }
                        }
                        TextField {
                            font.strikeout: statusBox.checked
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            placeholderText: "Enter description.."
                            wrapMode: "WrapAnywhere"
                            selectByMouse: true
                            text: dailyTaskDescription
                            onEditingFinished: client.changeDailyTask(dailyTaskId, text, statusBox.checked);
                        }
                        RoundButton {
                            text: qsTr("✖️");
                            font.pointSize: 16

                            Material.background: "transparent"
                            onClicked: client.removeDailyTask(dailyTaskId)
                        }
                    }
                }
            }

        }
        RowLayout {
            id: footer
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom


            Button {
                text: qsTr("Create New Task")
                Material.background: Material.Blue
                Material.foreground: "white"

                onClicked: client.createDailyTask();
            }
        }
    }
}

