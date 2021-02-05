import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.15


Item {
    id: root
    width: Screen.width * 0.12
    height: parent.height - header.height
    anchors.top: header.bottom


    ColumnLayout {
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.fill: parent
        spacing: 10


        RoundButton {
            id: newFlowBtn

            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.fillWidth: true
            Layout.rightMargin: root.width * 0.07
            Layout.leftMargin: root.width * 0.07
            Layout.preferredHeight: Screen.height * 0.05

            text: qsTr("\ue803    New Work Flow")
            font.capitalization: Font.MixedCase
            font.pointSize: 15
            font.family: "fontello"

            Material.background: Material.Blue
            Material.foreground: "white"
        }
        ColumnLayout {
            id: columnContainer
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.columnSpan: 0
            Layout.fillWidth: true
            spacing: 0

            property var currentPage: workFlowsBtn

            MenuButton {
                id: workFlowsBtn
                icon_text: "\uf16C"
                name_text: "Work Flows"
                description: "View work flows"
                selected: workFlowsBtn === columnContainer.currentPage
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        columnContainer.currentPage = workFlowsBtn
                        router.load(win, "qrc:/mainwindow/WorkFlows.qml")
                    }
                }
            }
            MenuButton {
                id: dailyPlaneBtn
                icon_text: "\ue807"
                name_text: "Daily plane"
                description: "View work for today"
                selected: dailyPlaneBtn === parent.currentPage

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        columnContainer.currentPage = dailyPlaneBtn
                        router.load(win, "qrc:/mainwindow/DailyPlane.qml")
                    }
                }
            }
            MenuButton {
                id: contactListBtn
                icon_text: "\ue804"
                name_text: "Contacts"
                description: "View contact list"
                selected: contactListBtn === parent.currentPage
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        columnContainer.currentPage = contactListBtn
                        router.load(win, "qrc:/mainwindow/Contacts.qml")
                    }
                }
            }
            MenuButton {
                id: calendarBtn
                icon_text: "\uf133"
                name_text: "Calendar"
                description: "View uncompleted tasks"
                selected: calendarBtn === parent.currentPage
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        columnContainer.currentPage = calendarBtn
                        router.load(win, "qrc:/mainwindow/Calendar.qml")
                    }
                }
            }
            MenuButton {
                id: statisticBtn
                icon_text: "\ue805"
                name_text: "Statistic"
                description: "View your progress statistic"
                selected: statisticBtn === parent.currentPage
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        columnContainer.currentPage = statisticBtn
                        router.load(win, "qrc:/mainwindow/Statistic.qml")
                    }
                }
            }
        }
        Item {
            Layout.fillHeight: true
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.columnSpan: 0
            Layout.fillWidth: true
            spacing: 0

            ControlButton {
//                        id: btn
                icon_text: "\uf1de"
                name_text: "Settings"

//                    onClicked: {
//                        selected = true
//                    }

            }
            ControlButton {
//                        id: btn
                icon_text: "\ue802"
                name_text: "What's new?"

//                    onClicked: {
//                        selected = true
//                    }

            }
            ControlButton {
//                        id: btn
                icon_text: "\uf128"
                name_text: "Support"

//                    onClicked: {
//                        selected = true
//                    }

            }
        }
    }
}
