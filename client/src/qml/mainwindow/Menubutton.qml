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

        onClicked: print("clicked")

        Text {
            id: iconText
            color: selected ? "#021cdb" : "black"
            text: qsTr(icon_text)
            anchors.leftMargin: 20
            anchors.left: parent.left
            font.pixelSize: 15
            font.family: "fontello"
            anchors.verticalCenter: parent.verticalCenter
        }

        Material.foreground: "black"
        Material.background: "transparent"


        Rectangle {
            id: rectangle
            color: "#00000000"
            anchors.topMargin: 10
            anchors.leftMargin: 20
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: iconText.right


            Text {
                id: nameText

                text: qsTr(name_text)
                font.pixelSize: 14
                verticalAlignment: Text.AlignVCenter
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                font.family: "fontello"
            }

            Text {
                id: descText
                text: qsTr(description)
                font.pointSize: 10
                anchors.left: parent.left
                anchors.top: nameText.bottom
                font.family: "fontello"
            }
        }

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
