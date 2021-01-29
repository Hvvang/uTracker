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

    signal clicked

    width: buttonWidth
    height: buttonHeight
    border.width: typeButton == "StandartType" ? 2 : 2
    border.color: colorButton == "MainColor" ? "#f6a2bf" : "#ffb4b0"
    radius: typeButton == "StandartType" ? height/2 : 5

    Rectangle {
        anchors.fill: parent
        anchors.margins: parent.border.width
        id: button
        radius: parent.radius
        color: colorButton == "MainColor" ? (!mouseArea.containsMouse ? "#fad2e0" : "#ffdad8") : (!mouseArea.containsMouse ? "#ffdad8" : "#fad2e0")
        Text {
            id: text
//            clip: true
            elide: Text.ElideRight
            anchors.fill: parent
            text: qsTr(root.content)
            font.pixelSize: 14
            color: colorButton == "MainColor" ? "#7a163c" : "#7a163c"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    console.log("Clicked");
//                    parent.parent.color: "#eea3a0";
                }

                enabled: active
                hoverEnabled: true
            }
        }
    //        onClick: {}
    }

}
//Rectangle {
//    id: root
//    property string content: "value"
//    Button {
//        anchors.centerIn: parent
//        id: button
//        text: qsTr(content)
//    }
//}


//        EXAMPLE


//Rectangle {
//    id: root
//    color: "transparent"
//    height: 100
//    width: 200

//    property string text
//    property color bgColor: "transparent"
//    property color bgColorSelected: "#14aaff"
//    property color textColor: "white"
//    property alias enabled: mouseArea.enabled
//    property bool active: true
//    property alias horizontalAlign: text.horizontalAlignment

//    signal clicked

//    Rectangle {
//        anchors { fill: parent; margins: 1 }
//        color: mouseArea.pressed ? bgColorSelected : bgColor

//        Text {
//            id: text
//            clip: true
//            text: root.text
//            anchors { fill: parent; margins: scaledMargin }
//            font.pixelSize: fontSize
//            color: textColor
//            horizontalAlignment: Text.AlignLeft
//            verticalAlignment: Text.AlignVCenter
//        }

//        MouseArea {
//            id: mouseArea
//            anchors.fill: parent
//            onClicked: {
//                root.clicked()
//            }
//            enabled: active
//        }
//    }
//}
