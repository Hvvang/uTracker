import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item {
    id: root
    anchors.fill: parent
    anchors.centerIn: parent

    ColumnLayout {
        anchors.centerIn: parent
        width: registerwindow.childrenRect.width

        Text {
            id: logoLbl
            text: qsTr("UTRACKER")
            font.bold: true
            font.pointSize: 16
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        }

        Button {
            id: googleOAuthBtn
            text: "\uf0d5 Continue with Google"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.fillWidth: true
            highlighted: false
            font.pointSize: 12
            font.family: "fontello"

            KeyNavigation.tab: gitHubOAuthBtn

            Material.background: Material.Red
            Material.foreground: "white"
            Material.elevation: 4

            onClicked: {
                console.log("Continue with Google clicked");
                client.googleAuthorize();
            }
            Keys.onPressed: {
                if (event.key === Qt.Key_Enter - 1)
                    clicked();
            }
        }

        Button {
            id: gitHubOAuthBtn

            text: "\uf09b Continue with GitHub"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.fillWidth: true
            font.family: "fontello"

            font.pointSize: 13

            KeyNavigation.tab: email

            Material.background: "black"
            Material.foreground: "white"
            Material.elevation: 4

            onClicked: {
                snackbar.customOpen("Now this option is unfortunately unavailible 😕")
                console.log("Continue with GitHub clicked");
            }
            Keys.onPressed: {
                if (event.key === Qt.Key_Enter - 1)
                    clicked();
            }
        }

        Rectangle {
            id: spaceLine
            height: 1
            color: "#000000"
            Layout.bottomMargin: 20
            Layout.topMargin: 20
            Layout.fillWidth: true
        }

        TextField {
            id: email

            property bool emailError: true

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            font.pointSize: 14
            placeholderText: "Enter your Email address..."

            selectByMouse: true
            validator: RegExpValidator { regExp:/\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*/ }

            KeyNavigation.tab: password

            Material.accent: emailError ? "red" : "black"
            Material.foreground: emailError ? "red" : "black"
            Material.background: "white"
            Material.elevation: 4

            onTextChanged: {
                emailError = !email.acceptableInput
            }
        }

        TextField {
            id: password

            property bool passwordError: true

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            font.pointSize: 14
            placeholderText: qsTr("Enter your Password")
            selectByMouse: true

            KeyNavigation.tab: signInBtn

            echoMode: "Password"
            Material.accent: passwordError ? "red" : "black"
            Material.foreground: passwordError ? "red" : "black"
            Material.background: "white"
            Material.elevation: 4

            onTextChanged: {
                passwordError = (text.length < 6)
            }
        }

        Button {
            id: signInBtn
            text: qsTr("Continue with email")
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            Material.foreground: "white"
            Material.background: Material.Blue
            Material.elevation: 4

            KeyNavigation.tab: goTosignUpBtn
            Keys.onReturnPressed: clicked();
            onClicked: {
                print("Continue with email clicked!")
//                client.authorize("shemedvedd@gmail.com", "A112263a");

                var error = email.emailError || password.passwordError
                if (!error) {
                    client.authorize(email.text, password.text);
                }
                else {
                    if (email.emailError) {
                        snackbar.customOpen("Incorect email address!")
                        email.forceActiveFocus()
                    } else if (password.passwordError) {
                        snackbar.customOpen("Incorect password!")
                        password.forceActiveFocus()
                    }
                }
            }
        }

        Button {
            id: goTosignUpBtn

            text: qsTr("Create new account")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.fillWidth: true
            font.capitalization: Font.MixedCase

            KeyNavigation.tab: googleOAuthBtn

            Material.accent: "transparent"
            Material.foreground: goTosignUpBtn.hovered ? Material.Blue : "black"
            Material.background: "transparent"

            onClicked: {
                stack.push(registerwindow)
            }
        }


    }
}
