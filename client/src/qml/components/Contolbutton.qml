import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item {
    id: root
    property string icon_text: ""
    property string name_text: ""
    property bool selected: false

    Layout.alignment: Qt.AlignTop
    Layout.fillWidth: true
    height: 30


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

                text: qsTr(icon_text)
                Layout.preferredWidth: 20
                font.pixelSize: 13
                font.family: "fontello"
            }

            Text {
                id: nameText

                text: qsTr(name_text)
                Layout.fillWidth: true
                font.pixelSize: 12
                font.family: "fontello"
            }


        }



        Material.foreground: "black"
        Material.background: "transparent"

        Rectangle {
            color: "#55a7ff"
            anchors.fill: parent
            visible: selected
            opacity: 0.3

            anchors.bottomMargin: 5
            anchors.topMargin: 5

        }

    }
    Rectangle {
        height: 1
        color: "#d9d9d9"
        anchors.bottomMargin: 0
        anchors.bottom: parent.bottom
        width: parent.width
    }
}

