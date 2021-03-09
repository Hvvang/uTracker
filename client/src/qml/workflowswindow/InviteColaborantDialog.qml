import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQml.Models 2.14

import "../components"

Item {
    id: root

    property int index;

    function open(index) {
        contact.text = "";
        root.index = index
        popup.open();
    }

    property string m_header: "Invite to colaborate"

    height: layout.childrenRect.height + 40
    anchors.centerIn: parent

    Popup {
        id: popup
        width: 220

        ColumnLayout {
            id: layout
            width: 200
            anchors.centerIn: parent

            Text {
                id: headerLbl
                text: qsTr("%1").arg(m_header)
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                font.bold: true
                font.pointSize: 16
            }

            TextField {
                id: contact

                property bool contactError: true

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

                font.pointSize: 14
                placeholderText: "Enter contact email"

                selectByMouse: true
                rightPadding: 30

                KeyNavigation.tab: inviteBtn

                Material.accent: contactError ? "red" : "black"
                Material.foreground: contactError ? "red" : "black"
                Material.background: "white"
                Material.elevation: 4

                onTextChanged: {
                    contactError = !text.length
                }

                Text {
                    id: search_icon
                    width: 40

                    text: qsTr("\ue80d")
                    font.family: "fontello"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 7
                    anchors.top: parent.top
                    font.pixelSize: 14
                }
            }

            Button {
                id: inviteBtn
                text: qsTr("Invite contact")
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

                Material.foreground: "white"
                Material.background: Material.Blue
                Material.elevation: 4

                KeyNavigation.tab: discardBtn

                onClicked: {
                    print("Create new workflow clicked!")

                    if (!contact.titleError) {
                        print("Invite new button pressed!");
                        client.inviteContact(contact.text, root.index);
                        popup.close();
                    }
                    else {
                        snackbar.customOpen("Contact entry can`t be empty")
                        contact.forceActiveFocus()
                    }
                }
            }

            Button {
                id: discardBtn

                text: qsTr("Discard")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.fillWidth: true
                font.capitalization: Font.MixedCase

                KeyNavigation.tab: contact

                Material.accent: "transparent"
                Material.foreground: discardBtn.hovered ? Material.Blue : "black"
                Material.background: "transparent"

                onClicked: {
                    popup.close()
                }
            }


        }

        enter: Transition {
            NumberAnimation { property: "opacity"; from: 0.0; to: 1.0 }
        }
        exit: Transition {
            NumberAnimation { property: "opacity"; from: 1.0; to: 0.0 }
        }
        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
    }

}
