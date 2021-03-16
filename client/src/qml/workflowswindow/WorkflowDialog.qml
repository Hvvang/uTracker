import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQml.Models 2.14

import "../components"

Item {
    id: root

    function open(flowId, flowTitle, flowDeadline) {
        if (flowId && flowTitle && flowDeadline) {
            m_flowId = flowId
            m_header = "Edit a workflow";
            m_title = flowTitle
            m_deadline = flowDeadline
            datepicker.selectedDate = Date.fromLocaleString(Qt.locale(), flowDeadline, "dd-MM-yyyy")
            m_footer = "Edit a workflow"
        } else {
            m_flowId = 0
            m_header = "Create a new workflow"
            m_title = ""
            title.text = ""
            m_deadline = Qt.formatDate(datepicker.selectedDate, "dd-MM-yyyy")
            m_footer = "Create a workflow"
        }
        popup.open();
    }
    property var m_flowId;
    property string m_header;
    property string m_icon: ""
    property string m_title;
    property string m_deadline;
    property string m_footer;
    property var m_colaborants: []

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
                id: title

                property bool titleError: true

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

                font.pointSize: 14
                placeholderText: "Enter workflow title"

                text: m_title

                KeyNavigation.tab: deadline

                onFocusChanged: if (focus) datepicker.visible = false

                Material.accent: titleError ? "red" : "black"
                Material.foreground: titleError ? "red" : "black"
                Material.background: "white"
                Material.elevation: 4

                onTextChanged: {
                    titleError = !text.length
                }
            }

            TextField {
                id: deadline

                property bool deadlineError: false

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

                font.pointSize: 15
                placeholderText: qsTr("Chose deadline")

                text: m_deadline

                KeyNavigation.tab: createBtn

                Material.accent: deadlineError ? "red" : "black"
                Material.foreground: deadlineError ? "red" : "black"
                Material.background: "white"
                Material.elevation: 4

                onTextChanged: {
                    var currentDate = new Date();

                    deadlineError = currentDate.getTime() > datepicker.selectedDate.getTime()
                }

                Text {
                    id: calendar_icon
                    width: 40
                    text: qsTr("\uf133")
                    font.family: "fontello"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                    font.pixelSize: 14
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        datepicker.visible = !datepicker.visible

                    }
                }
            }
            DatePicker {
                id: datepicker
                visible: deadline.focus || datepicker.focus
                Component.onCompleted: set(new Date()) // today
                onClicked:  {
                    datepicker.visible = false
                    deadline.text = Qt.formatDate(datepicker.selectedDate, "dd-MM-yyyy")
                }

            }
            Button {
                id: createBtn
                text: qsTr(m_footer)
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

                Material.foreground: "white"
                Material.background: Material.Blue
                Material.elevation: 4

                KeyNavigation.tab: discardBtn

                onClicked: {
                    var error = title.titleError || deadline.deadlineError;
                    if (!error) {
                        if (m_flowId) {
                            client.editWorkflow(m_flowId, title.text, deadline.text);
                        } else {
                            client.createWorkflow(title.text, deadline.text);
                        }
                        popup.close();
                    }
                    else {
                        if (title.titleError) {
                            snackbar.customOpen("Title can`t be empty")
                            title.forceActiveFocus()
                        } else if (deadline.deadlineError) {
                            snackbar.customOpen("Deadline can`t be set in past")
                            deadline.forceActiveFocus()
                        }
                    }
                }
            }

            Button {
                id: discardBtn

                text: qsTr("Discard")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.fillWidth: true
                font.capitalization: Font.MixedCase

                KeyNavigation.tab: title

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
