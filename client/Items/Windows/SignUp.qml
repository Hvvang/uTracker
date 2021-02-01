import QtQuick 2.4
import QtQuick.Controls.Material 2.3
import Material 0.3
import Material.ListItems 0.1 as ListItem

import "../Components"



Page {
    id: signUpPage
    function signUpRequest () {
        console.log("requested")
        snackbar.open("Account created successfully");
        signUpPage.pop()
    }

    Column {
        spacing: dp(10)
        anchors.centerIn: parent
        Label {
            id: lable
            text: "uTracker"
            font.bold: true
            font.pixelSize: 100 * Units.dp
        }
        S_Input_1 {
            id: inputLogin
            property bool error: true
            placeholderContent: "Entry Your Login"
            inputWidth: lable.width
            KeyNavigation.tab: inputEmail
            KeyNavigation.backtab: inputEmail
            input {
                focus: true
                onTextChanged: {
                    inputLogin.error = (input.text.length < 4)
//                    console.log("login: " + error)
                    logLableLogin.toLogLable()
                }
                validator: RegExpValidator { regExp:/\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*/ }
            }
        }
        Label {
            id: logLableLogin

            function toLogLable() {
                var message = "";
                if (inputLogin.error && inputLogin.input.text.length !== 0) {
                    message += "Login must be great then 4 symbols"
                }
                logLableLogin.text = message
            }
            width: text !== "" ? inputLogin.width : 0
            horizontalAlignment: Text.Center
            visible: !(!inputLogin.error && !inputEmail.error && !inputPassword.error && !inputPasswordConfirm.error)
            text: ""
            color: "red"
        }
        S_Input_1 {
            id: inputEmail
            property bool error: true
            placeholderContent: "Entry Your Email"
            inputWidth: lable.width
            input {
                onTextChanged: {
                    if (!input.acceptableInput)
                        inputEmail.error = true
                    else {
                        inputEmail.error = false
                    }
//                    console.log("email: " + error)
                    logLableMail.toLogLable()
                }
                validator: RegExpValidator { regExp:/\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*/ }
            }
            KeyNavigation.tab: inputPassword
        }
        Label {
            id: logLableMail

            function toLogLable() {
                var message = "";
                if (inputEmail.error && inputEmail.input.text.length !== 0) {
                    message += "Wrong email"
                }
                logLableMail.text = message
            }
            width: text !== "" ? inputEmail.width : 0
            horizontalAlignment: Text.Center
            visible: !(!inputLogin.error && !inputEmail.error && !inputPassword.error && !inputPasswordConfirm.error)
            color: "red"
        }
        S_Input_1 {
            id: inputPassword
            property bool error: true
            placeholderContent: "Password"
            inputWidth: lable.width
            input.echoMode: TextInput.Password
            KeyNavigation.tab: inputPasswordConfirm
            input {
                onTextChanged: {
                    inputPassword.error = (input.text.length < 7)
//                    console.log("pass: " + error)
                    logLablePassword.toLogLable()
                    inputPasswordConfirm.error = (inputPassword.input.text != inputPasswordConfirm.input.text) ||
                            (inputPasswordConfirm.input.text.length <= 0)
                }
            }
        }
        Label {
            id: logLablePassword

            function toLogLable() {
                var message = "";
                if (inputPassword.error && inputPassword.input.text.length !== 0) {
                    message += "Password must contain more then 7 symbols"
                }
                logLablePassword.text = message
            }
            width: text !== "" ? inputPassword.width : 0
            horizontalAlignment: Text.Center
            visible: !(!inputLogin.error && !inputEmail.error && !inputPassword.error && !inputPasswordConfirm.error)
            text: ""
            color: "red"
        }
        S_Input_1 {
            id: inputPasswordConfirm

            property bool error: true
            placeholderContent: "Password Confirm"
            inputWidth: lable.width
            input.echoMode: TextInput.Password
            input {
                onTextChanged: {
                    inputPasswordConfirm.error = (inputPassword.input.text != inputPasswordConfirm.input.text) ||
                            (inputPasswordConfirm.input.text.length <= 0)
//                    console.log("pass confirm: " + error)
//                    console.log("GENERAL: " + error)
                    logLableConfirm.toLogLable()
                }
            }
        }

        Label {
            id: logLableConfirm

            function toLogLable() {
                var message = ""
                if (!inputPassword.error && inputPassword.input.text.length !== 0
                         && inputPasswordConfirm.error && inputPasswordConfirm.input.text.length !== 0) {
                    message += "Passwords do not match"
                }
                logLableConfirm.text = message
            }
            width: text !== "" ? inputPasswordConfirm.width : 0
            horizontalAlignment: Text.Center
            visible: !(!inputLogin.error && !inputEmail.error && !inputPassword.error && !inputPasswordConfirm.error)
            text: ""
            color: "red"
        }

        S_Button_1 {
            id:signUn
            buttonEnabled: !inputLogin.error && !inputEmail.error && !inputPassword.error && !inputPasswordConfirm.error
            buttonContent: "Sign Up"
            width: parent.width
            Component.onCompleted: {
                signUn.clicked.connect(signUpRequest);
            }
        }
    }

}
