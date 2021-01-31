import QtQuick 2.9
import QtQuick.Window 2.11
import Material 0.3
import Material.ListItems 0.1 as ListItem

import "Buttons"

Window {
    theme {
        primaryColor: "#fad2e0"
        accentColor: "#ffdad8"
//        borderColor: "#f6a2bf"
        tabHighlightColor: "white"
    }
    minimumWidth: 1000
    minimumHeight: 680
//    minimum: 680
    visible: true
    width: 1920
    height: 1080
    title: qsTr("uTracker")

    Column {
        spacing: dp(20)
        anchors.centerIn: parent
        Label {
            id: lable
            text: "uTracker"
//            font.bold: true
            font.pixelSize: 100 * Units.dp
        }
        S_Input_1 {
            id: inputNickname
            placeholderContent: "Nickname or email"
            inputWidth: lable.width
        }
        S_Input_1 {
            id: inputPassword
            placeholderContent: "Password"
            inputWidth: lable.width
            input.echoMode: TextInput.Password
        }
        Item {
            id: signButtons
            height: 40 * Units.dp
            width: inputPassword.width
            Row {
                anchors.fill: parent
                spacing: dp(20)
                S_Button_1 {
                    id:signIn
                    buttonContent: "Sign In"
                    width: (parent.width - dp(20)) / 2
                }
                S_Button_1 {
                    id:signUp
                    buttonType: ""
                    buttonContent: "Sign Up"
                    width: (parent.width - dp(20)) / 2

                }
            }
        }


    }
}
