import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item {
    id: root
    property string icon_text: ""
    property string name_text: ""
    property string description: ""
    property bool selected: false

    Layout.alignment: Qt.AlignTop
    Layout.fillWidth: true
    height: 40

    Button {
        id: button

        anchors.bottomMargin: -5
        anchors.topMargin: -5
        anchors.fill: parent

        RowLayout {
            anchors.rightMargin: 10
            anchors.leftMargin: 20
            anchors.fill: parent

            Text {
                id: iconText
                color: selected ? "#021cdb" : "black"
                text: qsTr(icon_text)
                Layout.preferredWidth: 20
                font.family: "fontello"
            }

            ColumnLayout {
                Layout.fillWidth: true
                Text {
                    id: nameText

                    text: qsTr(name_text)
                    Layout.fillWidth: true
                    font.pixelSize: 14
                    font.family: "fontello"
                }

                Text {
                    id: descText
                    text: qsTr(description)
                    Layout.fillWidth: false
                    font.pointSize: 10
                    font.family: "fontello"
                }
            }

        }

        Material.foreground: "black"
        Material.background: "transparent"

        Rectangle {
            color: "#55a7ff"
            anchors.topMargin: 5
            anchors.bottomMargin: 5
            anchors.fill: parent
            visible: selected
            opacity: 0.3


        }
    }
}
