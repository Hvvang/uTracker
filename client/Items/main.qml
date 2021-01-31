import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

import "Buttons"
import "Windows"

Window {
    PageStack {
        id: pageStack
    }
    function checkValid () {
        var valid = false;
        if (!valid) {
            snackbar.open("Wrong login or password");
        }
    }

    function toSignUpPage () {
        console.log("SignUp")
        pageStack.push(Qt.resolvedUrl("Windows/SignUp.qml"))
    }

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
            placeholderContent: "Login or email"
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
                    Component.onCompleted: {
                        signIn.clicked.connect(checkValid);
                    }
                }
                S_Button_1 {
                    id:signUp
                    buttonType: "Type2"
                    buttonContent: "Sign Up"
                    width: (parent.width - dp(20)) / 2
                    Component.onCompleted: {
                        signUp.clicked.connect(toSignUpPage);
                    }
                }
            }
        }

    }
    Snackbar {
        id: snackbar
    }
}
