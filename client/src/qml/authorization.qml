import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3

Window {
    id: root
    visible: true
    width: 640
    height: 480
    minimumHeight: flowView.height
    minimumWidth: flowView.width

    title: "uTracker Authorization"
//    Material.theme: Material.Light
//    Material.accent: Material.Purple

    Rectangle {
        id: flowView
        height: 246
        width: 200
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Label {
            id: logoLbl
            x: 101
            text: qsTr("UTRACKER")
            font.bold: true
            font.pointSize: 16
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            Material.foreground: "black"
            Material.elevation: 4
        }

        Button {
            id: googleOAuthBtn
            width: 200
            height: 40
            text: "\uf0d5 Continue with Google"
            anchors.top: logoLbl.bottom
            highlighted: false
            font.pointSize: 12
            font.family: "fontello"

            anchors.horizontalCenter: parent.horizontalCenter

            Material.background: Material.Red
            Material.foreground: "white"

            Material.elevation: 4

        }
        Button {
            id: gitHubOAuthBtn
            width: 200
            height: 40
            text: "\uf09b Continue with GitHub"
            font.family: "fontello"

            font.pointSize: 13
            anchors.top: googleOAuthBtn.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter

            Material.background: "white"
            Material.elevation: 4
        }

        Rectangle {
            id: spaceLine
            width: 200
            height: 1
            color: "#000000"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: gitHubOAuthBtn.bottom
            anchors.topMargin: 20
        }

        TextField {
            id: emailEntry
            width: 200
            font.pointSize: 14
            leftPadding: 5
            placeholderText: "Enter your Email address..."
            verticalAlignment: Text.AlignVCenter
            anchors.top: spaceLine.bottom
            anchors.topMargin: 40
            anchors.horizontalCenter: parent.horizontalCenter

            Material.accent: "black"
            Material.background: "white"
            Material.elevation: 4
        }
//        TextField {
//            id: passEntry
//            width: 200
//            font.pointSize: 14
//            anchors.horizontalCenterOffset: 0
//            anchors.topMargin: 4
//            leftPadding: 5
//            anchors.top: emailEntry.bottom
//            anchors.horizontalCenter: parent.horizontalCenter
//            placeholderText: qsTr("Enter your Password")

//            echoMode: "Password"
//            Material.accent: "black"
//            Material.background: "white"
//            Material.elevation: 4
//        }

        Button {
            id: authBtn
            width: 200
            height: 40
            text: qsTr("Continue with email")
            font.pointSize: 13
            anchors.top: emailEntry.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            Material.background: Material.Blue
            Material.foreground: "white"
            Material.elevation: 4
        }

        Label {
            color: "#7b7b7b"
            text: qsTr("Email")
            anchors.bottomMargin: 0
            font.pointSize: 12
            anchors.bottom: emailEntry.top
        }





    }
}

/*##^##
Designer {
    D{i:4;anchors_width:200}D{i:1;anchors_height:236}
}
##^##*/
