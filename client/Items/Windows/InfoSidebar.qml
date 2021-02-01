import QtQuick 2.15
//import QtQuick.Layouts 1.1
import QtQuick.Controls 2.15
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

import "../Components"

PageSidebar {
        id: sidebarInfo
        title: "Table Info"

        width: dp(320)

        actionBar.maxActionCount: 1

        actions: [
            Action {
                id: addPers
                iconName: "navigation/chevron_right"
                text: "Add colab"
                hoverAnimation: true
                onTriggered: {
                }
            },
            Action {
                id: delPers
                iconName: "navigation/chevron_right"
                text: "Remove colab"
                hoverAnimation: true
                onTriggered: {
                }
            }
        ]
        data:
            Column {
                anchors.centerIn: parent
                width: parent.width - dp(20)
                height: parent.height - dp(40)
                spacing: dp(20)
                Column {
                    spacing: 5
                    id: colabComp
                    width: parent.width
                    height: (parent.height - dp(20)) / 2
                    Rectangle {
                        width: parent.width
                        height: parent.height / 10
                        color: "#fad2e0"
                        border.width: 2
                        border.color: "#f6a2bf"
                        radius: 5
                        Text {
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter

                            font.pixelSize: dp(24)
                            text: "Colaborators"
                        }
                    }
                    ListView {
//                        anchors.fill: parent
                        width: parent.width
                        height: parent.height * 0.9
                        spacing: dp(10)
                        flickableDirection: Flickable.VerticalFlick
                        boundsBehavior: Flickable.StopAtBounds
                        model: 15
                        clip: true
                        delegate: UserForms {
                            formContent: "intelek2al"
                            formWidth: parent.width
                            formHeight: 50
                        }

                    }
                }
//                Rectangle {
//                    height: 2
//                    color: "#f6a2bf"
//                    width: parent.width
//                } //separator

                Column {
                    spacing: 5
                    id: describComp
                    width: parent.width
                    height: (parent.height - dp(20)) / 2
                    Rectangle {
                        width: parent.width
                        height: parent.height / 10
                        color: "#fad2e0"
                        border.width: 2
                        border.color: "#f6a2bf"
                        radius: 5
                        Text {
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter

                            font.pixelSize: dp(24)
                            text: "Description"
                        }
                    }
                    ListView {
    //                        anchors.fill: parent
                        width: parent.width
                        height: parent.height * 0.9
                        spacing: dp(10)
                        flickableDirection: Flickable.VerticalFlick
                        boundsBehavior: Flickable.StopAtBounds
                        model: 15
                        clip: true
                        delegate: UserForms {
                            formContent: "intelek2al"
                            formWidth: parent.width
                        }

                    }
                }
            }
    }
