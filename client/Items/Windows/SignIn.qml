import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

import "../Components"

Page {
    function checkValid () {
        var valid = true;
        if (!valid) {
            snackbar.open("Wrong login or password");
        } else {
            root.goMainWindow();
        }
    }

    function toSignUpPage () {
        console.log("SignUp")
        pageStack.push(Qt.resolvedUrl("SignUp.qml"))
    }
    anchors.fill: parent
    Column {
        spacing: dp(20)
        anchors.centerIn: parent
        Label {
            id: lable
            text: "uTracker"
            font.bold: true
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
        Column {
            spacing: dp(10)
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
            S_Button_1 {
                id:signInGoogle
                buttonContent: "Continue with Google"
                width: parent.width
                Component.onCompleted: {
//                    signIn.clicked.connect(signUpRequest);
                }
            }
        }

    }
}
