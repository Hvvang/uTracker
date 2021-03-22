import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

import "../components"


Item {
    id: root
    width: Screen.width * 0.10

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
            Layout.preferredHeight: 58

            text: qsTr("\ue803    New Work Flow")
            font.capitalization: Font.MixedCase
            font.pointSize: 15
            font.family: "fontello"

            Material.background: Material.Blue
            Material.foreground: "white"

            onClicked: dialog.open()
        }
        ColumnLayout {
            id: columnContainer
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.columnSpan: 0
            Layout.fillWidth: true
            spacing: 0

            property var currentPage;

            Repeater {
                model: ListModel {
                    id: menuBtnModel
                    ListElement {icon_text: "\uf16C"; name_text: "Work Flows"; description: "View work flows"; selected: true}
                    ListElement {icon_text: "\ue807"; name_text: "Daily plan"; description: "View work for today"; selected: false}
                    ListElement {icon_text: "\ue804"; name_text: "Contacts"; description: "View contact list"; selected: false}
                    ListElement {icon_text: "\ue80c"; name_text: "Calendar"; description: "View uncompleted tasks"; selected: false}
                    ListElement {icon_text: "\ue805"; name_text: "Statistic"; description: "View your progress statistic"; selected: false}
                }

                delegate: Menubutton {
                    id: menuBtn

                    icon_text: model.icon_text
                    name_text: model.name_text
                    description: model.description
                    selected: columnContainer.currentPage ? menuBtn === columnContainer.currentPage : model.selected
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            columnContainer.currentPage = menuBtn
                            if (index == 0) {
                                client.getWorkflows();
                            } else if (index == 1) {
                                client.getDailyPlan();
                            } else if (index == 4) {
                                client.getStatistic();
                            }

                        }
                    }
                }
            }

        }
        Item {
            Layout.fillHeight: true
        }

        ColumnLayout {
            id: controlLayout
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.columnSpan: 0
            Layout.fillWidth: true
            spacing: 0

            property var currentPage;

            Repeater {
                model: ListModel {
                    id: controlBtnModel
                    ListElement {icon_text: "\uf1de"; name_text: "Settings"; selected: false}
                    ListElement {icon_text: "\ue802"; name_text: "What's new?"; selected: false}
                    ListElement {icon_text: "\uf128"; name_text: "Support"; selected: false}
                }

                delegate: Contolbutton {
                    id: contolBtn

                    icon_text: model.icon_text
                    name_text: model.name_text

                    selected: controlLayout.currentPage ? contolBtn === controlLayout.currentPage : model.selected
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            controlLayout.currentPage = contolBtn
                        }
                    }
                }
            }

        }
    }
}
