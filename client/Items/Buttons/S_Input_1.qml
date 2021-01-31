import QtQuick 2.9
import QtQuick.Controls 2.4


Rectangle {
    id: root
    enum ButtonType {
        StandartType,
        SquareType
    }
    enum ButtonColor {
        MainColor,
        ExtraColor
    }

    property string typeButton: "StandartType"
    property string colorButton: "MainColor"
    property string content: "value"
    property int buttonWidth: 125
    property int buttonHeight: 30

//    signal clicked

    width: buttonWidth
    height: buttonHeight
    border.width: typeButton == "StandartType" ? 2 : 2
    border.color: colorButton == "MainColor" ? "#f6a2bf" : "#ffb4b0"
    radius: typeButton == "StandartType" ? height / 2 : 5

    Rectangle {
        id:content
        anchors.fill: parent
        anchors.margins: parent.border.width
        radius: parent.radius
//        color:
//        color: colorButton == "MainColor" ? (!mouseArea.containsMouse ? "#fad2e0" : "#ffdad8") : (!mouseArea.containsMouse ? "#ffdad8" : "#fad2e0")
        Item {
            width: parent.width - parent.radius
            height: parent.height - parent.radius
            anchors.fill: parent
            TextInput {
                text: "Hello"
                anchors.fill: parent

                verticalAlignment: TextInput.AlignVCenter
                wrapMode: TextInput.NoWrap
            }
        }

//        MouseArea{
//            id: mouseArea
//            anchors.fill: parent
//            hoverEnabled: true
//        }
    //        onClick: {}
    }

}
