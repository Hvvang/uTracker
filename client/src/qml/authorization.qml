import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3

Window {
    id: root
    visible: true
    width: 640
    height: 480

    minimumHeight: authPanel.visible ? authPanel.height : registrationPanel.height
    minimumWidth: authPanel.visible ? authPanel.width : registrationPanel.width

    title: "uTracker Authorization"

    property bool error: true

    Item {
        id: authPanel
        height: 260
        width: 200
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        focus: true
        visible: false

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

        Label {
            color: "#7b7b7b"
            text: qsTr("Email")
            anchors.bottomMargin: 0
            font.pointSize: 12
            anchors.bottom: emailEntry.top
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

            validator: RegExpValidator { regExp:/\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*/ }

            KeyNavigation.tab: authBtn

            Material.accent: error ? "red" : "black"
            Material.foreground: error ? "red" : "black"
            Material.background: "white"
            Material.elevation: 4
            onTextChanged: {
                if (!emailEntry.acceptableInput)
                    error = true
                else {
                    error = false
                }
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

            KeyNavigation.tab: googleOAuthBtn

            Material.background: Material.Blue
            Material.foreground: "white"
            Material.elevation: 4

            onClicked: {
                console.log("Continue with email clicked");
                if (emailEntry.acceptableInput) {
                    print("Input acceptable\nemail: %1".arg(emailEntry.text))
                    authPanel.visible = false
                    registrationPanel.visible = true
                }
                else {
                    error = true
                    print("Input not acceptable")
                    emailEntry.forceActiveFocus()
                    errorlbl.text = "Incorrect email address"
                    errorlbl.visible = true
                }
            }
        }

        Label {
            id: errorlbl
            anchors.top: emailEntry.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            Material.foreground: "red"
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
        visible: true

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

            KeyNavigation.tab: authBtn

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
                anchors.leftMargin: 5

                id: loginBtn
                anchors.left: label.right
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: parent.top

                Button {
                    anchors.fill: parent
                    text: qsTr("Log in here");
                    font.weight: Font.DemiBold
                    font.capitalization: Font.MixedCase
                    padding: 0

                    background: Rectangle{}
                    Material.accent: "transparent"
                    Material.foreground: loginBtn.hover ? Material.Blue : "black"
                    Material.background: "transparent"

                    onHoveredChanged: loginBtn.hover = !loginBtn.hover;
                    onClicked: {
                        registrationPanel.visible = false
                        authPanel.visible = true
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



/*##^##
Designer {
    D{i:20;anchors_x:38;anchors_y:225}D{i:22;anchors_x:24;anchors_y:1}D{i:21;anchors_height:200;anchors_width:200;anchors_x:261;anchors_y:-60}
D{i:19;anchors_y:-16}
}
##^##*/
