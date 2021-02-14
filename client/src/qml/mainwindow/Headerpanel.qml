import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.3

Item {
    id: root
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    height: 50

    RowLayout {
        id: controlWrapper
        anchors.bottom: footerline.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        RowLayout {
            id: logoWrapper
            Layout.leftMargin: 20
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            Label {
                id: logoLbl
                text: qsTr("Utracker");
                font.pointSize: 15
                font.weight: Font.DemiBold

                MouseArea {
                   anchors.fill: parent
                   onClicked: print("Go home")
                }
            }
        }

        Item {
            id: routeWrapper
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true

            RowLayout {
                id: routeRow
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillWidth: true
                Layout.fillHeight: true

                Repeater {
                    id: rep

                    model: 3 // route.size

                    Row {
                        Text {
                            id: routeText
                            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                            text: qsTr("Route %1").arg(model.index);
                            color: model.index < rep.count - 1 && !mouseArea.containsMouse ? "#8a8a8a" : "black"
                            font.family: "fontello"
                            MouseArea {
                                id: mouseArea
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: print("go to Route with lvl index %1".arg(index))
                            }
                        }
                        Text {
                            id: sign
                            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                            text: qsTr("%1").arg(model.index < rep.count - 1 ? " \ue800 " : "");
                            color: "#8a8a8a"
                            font.family: "fontello"
                        }
                    }
                }

            }



        }

        RowLayout {
            id: profileWrapper
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            spacing: 10

            Button {
                id: helpBtnWrapper

                text: qsTr("Help \ue801")
                Material.foreground: "#8a8a8a";
                Material.background: "#ededed";
                font.family: "fontello"

            }
            Button {
                id: upgradeBtnWrapper

                text: qsTr("Upgrade")
                Material.foreground: "white";
                Material.background: Material.Blue;
            }
            RoundButton {
                id: profileBtn

                text: qsTr(client.letter)
                font.weight: Font.Black
                Material.foreground: "white";
                Material.background: Material.Pink;

                onClicked: {
                    contextMenu.x = profileBtn - 100

                    contextMenu.y = 100
                    contextMenu.popup()
                }
            }
        }
    }

    Rectangle {
        id: footerline
        anchors.right: parent.right
        anchors.left: parent.left
        height: 0.7
        anchors.bottom: parent.bottom
        color: "#c4c3c2"
        border.color: "transparent"
        radius: 10
    }
    DropShadow {
        verticalOffset: 1
        radius: 7.0
        anchors.bottomMargin: -2
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: footerline.bottom
        samples: 17
        color: "#cc000000"
        source: footerline
    }

    Menu {
        id: contextMenu



        width: 100
        topMargin: 0
        dim: true
        topPadding: 0
        bottomPadding: 0

        font.pixelSize: 13

        background: Pane {
            anchors.fill: parent
            Material.primary: Material.Grey
            Material.elevation: 6

        }

        MenuItem {
            text: "\ue807  Profile"
            font.family: "fontello"
            onTriggered: back.clicked()
            height: 30
            width: parent.width
        }
        MenuSeparator {}
        MenuItem {
            text: "\ue80b  Log out"
            font.family: "fontello"
            onTriggered: back.clicked()
            height: 30
            width: parent.width
        }
    }
}
