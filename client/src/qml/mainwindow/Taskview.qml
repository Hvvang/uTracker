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
//    implicitHeight: view.childrenRect.height + 30
    property int colabsCounter: 0

    ColumnLayout {
        id: view
        z: 2
        width: 225

        anchors.topMargin: 10
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        Item {
            id: header
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            height: taskTxt.height
            width: parent.width

            Row {
                id: row1

                anchors.fill: header

                Text {
                    id: icon
                    text: qsTr("😄")
                    font.pointSize: 17
                }
                Text {
                    id: taskTxt

//                    text: qsTr("Some task # %1 with some title".arg(model.index))
                    text: taskTitle
                    anchors.leftMargin: 5
                    anchors.left: icon.right
                    anchors.right: parent.right
                    font.pointSize: 17
                    horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
            }
        }
        ColumnLayout {
            id: tags
            width: parent.width

            Flow {
                id: tagsFlow

                anchors.fill: tags
                spacing: 5

                Repeater {
                    id: rep
//                    model: ["common", "feature", "high priority", "important"]
                    model: 0

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
                            color: Material.color(Material.Pink)
                        }
                    }
                }
            }
        }

        Item {
            id: workers
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            height: workersView.height
            width: parent.width

            ColumnLayout {
                id: workersView

                Repeater {
                    id: colabsRepeater
                    model: root.colabsCounter

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
                                text: qsTr("A")
                            }
                        }
                        Text {
                            text: qsTr("FirstName LastName")
                            anchors.verticalCenter: parent.verticalCenter
                        }
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
        onClicked: {
            print("emit open task signal")
            root.colabsCounter += 1
        }
    }
}


