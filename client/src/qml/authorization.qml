import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3

Item {
    id: root
    visible: true
    anchors.fill: parent

//    title: "uTracker Authorization"

    property string errorMessage: "qwerty"
    property bool error: false
    property var errorLabel: errorlbl

    onErrorChanged: {
        if (error)
            errorLabel.text = errorMessage;
    }

    StackView {
        id: stack
        initialItem: authPanel
        anchors.fill: parent
    }

    Item {
        id: authPanel
        height: 330
        width: 250
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        focus: true
        visible: true

        Label {
            id: logoLbl
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

            KeyNavigation.tab: gitHubOAuthBtn

            anchors.horizontalCenter: parent.horizontalCenter

            Material.background: Material.Red
            Material.foreground: "white"
            Material.elevation: 4

            onClicked: {
                console.log("Continue with Google clicked");
                GoogleAuth.click()
            }
            Keys.onPressed: {
                if (event.key === Qt.Key_Enter - 1)
                    clicked();
            }

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

            KeyNavigation.tab: emailEntry

            Material.background: "black"
            Material.foreground: "white"
            Material.elevation: 4

            onClicked: {
                console.log("Continue with GitHub clicked");
            }
            Keys.onPressed: {
                if (event.key === Qt.Key_Enter - 1)
                    clicked();
            }
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
            property bool error: true
            id: emailEntry
            width: 200
            font.pointSize: 14
            leftPadding: 5
            placeholderText: "Enter your Email address..."
            verticalAlignment: Text.AlignVCenter
            anchors.top: spaceLine.bottom
            anchors.topMargin: 40
            anchors.horizontalCenter: parent.horizontalCenter

            validator: RegExpValidator { regExp:/\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*/ }

            KeyNavigation.tab: passwordEntry

            Material.accent: emailEntry.error ? "red" : "black"
            Material.foreground: emailEntry.error ? "red" : "black"
            Material.background: "white"
            Material.elevation: 4
            onTextChanged: {
                emailEntry.error = !emailEntry.acceptableInput
                errorlbl.visible = false
            }

        }

        TextField {
            property bool error: true

            id: passwordEntry
            width: 200
            font.pointSize: 14
            anchors.horizontalCenterOffset: 0
            leftPadding: 5
            anchors.top: emailEntry.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: qsTr("Enter your Password")

            KeyNavigation.tab: authBtn

            echoMode: "Password"
            Material.accent: passwordEntry.error ? "red" : "black"
            Material.foreground: passwordEntry.error ? "red" : "black"
            Material.background: "white"
            Material.elevation: 4

            onTextChanged: {
                passwordEntry.error = (text.length < 6)
                errorlbl.visible = false
            }
        }

        Button {
            id: authBtn
            width: 200
            height: 40
            text: qsTr("Continue with email")
            font.pointSize: 13
            anchors.top: errorlbl.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            KeyNavigation.tab: newAccBtn

            Material.background: Material.Blue
            Material.foreground: "white"
            Material.elevation: 4

            onClicked: {
                console.log("Continue with email clicked");
                if (emailEntry.error || passwordEntry.error) {
                    print("Input not acceptable")
                    if (emailEntry.error) {
                        errorlbl.text = "Incorrect email address"
                        emailEntry.forceActiveFocus()
                    } else {
                        errorlbl.text = "Incorrect password"
                        passwordEntry.forceActiveFocus()
                    }
                    errorlbl.visible = true
                }
                else {
                    print("Input acceptable\nemail: %1".arg(emailEntry.text))
                    Auth.signIn(emailEntry.text, passwordEntry.text)
                }
            }
        }

        Label {
            id: errorlbl
            anchors.top: passwordEntry.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            Material.foreground: "red"
        }

        Rectangle {
            id: switcherPanel
            width: 200
            color: "#ffffff"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: authBtn.bottom
            anchors.bottom: parent.bottom

            Button {
                property bool hover: false
                id: newAccBtn
                text: qsTr("Create new account")
                font.capitalization: Font.MixedCase
                anchors.fill: parent

                KeyNavigation.tab: googleOAuthBtn

                background: Rectangle{}
                Material.accent: "transparent"
                Material.foreground: hover ? Material.Blue : "black"
                Material.background: "transparent"

                onHoveredChanged: hover = !hover;
                onClicked: {
                    errorLabel = error
                    root.error = false
                    stack.push(registrationPanel)
                }
            }
        }
        Keys.onPressed: {
            if ((event.key === Qt.Key_Return || event.key === Qt.Key_Enter)
                    && (authPanel.focus || emailEntry.focus || authBtn.focus))
                authBtn.clicked();
        }
    }

    Item {
        id: registrationPanel
        height: 266
        width: 250

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        visible: false

        Label {
            id: signUplbl
            text: qsTr("Create account")
            font.bold: true
            font.pointSize: 16
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            Material.foreground: "black"
            Material.elevation: 4
        }

        TextField {
            property bool emailError: true

            id: email
            width: 200
            font.pointSize: 14
            leftPadding: 5
            placeholderText: "Enter your Email address..."
            verticalAlignment: Text.AlignVCenter
            anchors.top: signUplbl.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            validator: RegExpValidator { regExp:/\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*/ }

            KeyNavigation.tab: passEntry

            Material.accent: emailError ? "red" : "black"
            Material.foreground: emailError ? "red" : "black"
            Material.background: "white"
            Material.elevation: 4

            onTextChanged: {
                emailError = !email.acceptableInput
            }
        }

        TextField {
            property bool passwordError: true

            id: passEntry
            width: 200
            font.pointSize: 14
            anchors.horizontalCenterOffset: 0
            leftPadding: 5
            anchors.top: email.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: qsTr("Enter your Password")

            KeyNavigation.tab: firstNameEntry

            echoMode: "Password"
            Material.accent: passwordError ? "red" : "black"
            Material.foreground: passwordError ? "red" : "black"
            Material.background: "white"
            Material.elevation: 4

            onTextChanged: {
                passwordError = (text.length < 6)
            }
        }
        TextField {
            property bool firstnameError: true

            id: firstNameEntry
            width: 200
            font.pointSize: 14
            leftPadding: 5
            placeholderText: "Enter your Name..."
            verticalAlignment: Text.AlignVCenter
            anchors.top: passEntry.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            KeyNavigation.tab: lastNameEntry

            Material.accent: firstnameError ? "red" : "black"
            Material.foreground: firstnameError ? "red" : "black"
            Material.background: "white"
            Material.elevation: 4

            onTextChanged: {
                firstnameError = (text.length < 1)
            }
        }
        TextField {
            property bool lastnameError: true

            id: lastNameEntry
            width: 200
            font.pointSize: 14
            leftPadding: 5
            placeholderText: "Enter your Last Name..."
            verticalAlignment: Text.AlignVCenter
            anchors.top: firstNameEntry.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            KeyNavigation.tab: signUpBtn

            Material.accent: lastnameError ? "red" : "black"
            Material.foreground: lastnameError ? "red" : "black"
            Material.background: "white"
            Material.elevation: 4

            onTextChanged: {
                lastnameError = (text.length < 1)
            }
        }

        Button {
            id: signUpBtn
            width: 200
            height: 40
            text: qsTr("Sign up")
            font.pointSize: 13
            anchors.top: error.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            Material.foreground: "white"
            Material.background: Material.Blue
            Material.elevation: 4

            KeyNavigation.tab: loginRouteButton

            onClicked: {
                print("Sign Up clicked!")
                var error = email.emailError || passEntry.passwordError || firstNameEntry.firstnameError || lastNameEntry.lastnameError
                if (!error) {
                    print("Register!")
                }
                else {
                    print("error");
                }
            }
        }

        Rectangle {
            id: loginRoutePanel
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 10
            anchors.top: signUpBtn.bottom

            Label {
                id: label
                text: qsTr("Already have an account?")
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.top: parent.top
            }

            Rectangle {

                property bool hover: false
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                anchors.leftMargin: 5

                id: loginBtn
                anchors.left: label.right
                anchors.right: parent.right

                Button {
                    id: loginRouteButton
                    anchors.fill: parent
                    text: qsTr("Log in here");
                    font.weight: Font.DemiBold
                    font.capitalization: Font.MixedCase
                    padding: 0

                    KeyNavigation.tab: email

                    background: Rectangle{}
                    Material.accent: "transparent"
                    Material.foreground: loginBtn.hover ? Material.Blue : "black"
                    Material.background: "transparent"

                    onHoveredChanged: loginBtn.hover = !loginBtn.hover;
                    onClicked: {
                        errorLabel = error
                        root.error = false
                        stack.pop()
                    }
                }
            }
        }

        Label {
            id: error
            width: 200
            anchors.top: lastNameEntry.bottom
            Material.foreground: "red"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
