import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item {
    id: root
    anchors.fill: parent

    ColumnLayout {
        anchors.centerIn: parent

        Text {
            id: headerLbl
            text: qsTr("Create account")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            font.bold: true
            font.pointSize: 16
        }

        TextField {
            id: email

            property bool emailError: true

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            font.pointSize: 14
            placeholderText: "Enter your Email address..."


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

            KeyNavigation.tab: name

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
            id: name

            property bool firstnameError: true

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            font.pointSize: 14
            placeholderText: "Enter your Name..."

            KeyNavigation.tab: lastName

            Material.accent: firstnameError ? "red" : "black"
            Material.foreground: firstnameError ? "red" : "black"
            Material.background: "white"
            Material.elevation: 4

            onTextChanged: {
                firstnameError = (text.length < 1)
            }
        }
        TextField {
            id: lastName

            property bool lastnameError: true

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            font.pointSize: 14
            placeholderText: "Enter your Last Name..."
            verticalAlignment: Text.AlignVCenter

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
            text: qsTr("Sign up")
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            Material.foreground: "white"
            Material.background: Material.Blue
            Material.elevation: 4

            KeyNavigation.tab: goToLoginBtn

            onClicked: {
                print("Sign Up clicked!")
                var error = email.emailError || password.passwordError || name.firstnameError || lastName.lastnameError
                if (!error) {

                    print("Register button pressed!")
                    client.registrate(email.text, password.text, name.text, lastName.text);
                }
                else {
                    if (email.emailError) {
                        snackbar.customOpen("Incorect email address!")
                        email.forceActiveFocus()
                    } else if (password.passwordError) {
                        snackbar.customOpen("Incorect password!")
                        password.forceActiveFocus()
                    } else if (name.firstnameError) {
                        snackbar.customOpen("Name entry is empty!")
                        name.forceActiveFocus()
                    } else if (lastName.lastnameError) {
                        snackbar.customOpen("Surname entry is empty!")
                        lastName.forceActiveFocus()
                    }
                }
            }
        }

        RowLayout {
            id: loginRoutePanel

            Text {
                text: qsTr("Already have an account?")
            }

            Button {
                id: goToLoginBtn
                text: qsTr("Log in here");
                font.weight: Font.DemiBold
                font.capitalization: Font.MixedCase

                KeyNavigation.tab: email

                Material.accent: "transparent"
                Material.foreground: goToLoginBtn.hovered ? Material.Blue : "black"
                Material.background: "transparent"

                onClicked: {
                    stack.pop()
                }

            }
        }


    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
