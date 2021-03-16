import QtQuick 2.8
import QtQuick.Window 2.12
import Qt.labs.settings 1.0
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

import QtQuick.Dialogs 1.2

import "../components"

Dialog {
    id: dialog

    title: "Edit Task"

    width: 500;
    height: 400

    modality: Qt.NonModal | Qt.Dialog | Qt.Popup

    contentItem: Item {
        anchors.fill: parent
        anchors.margins: 10

        Flickable {
            id: flick
            anchors.fill: parent
            contentHeight: view.childrenRect.height
            clip: true

            ColumnLayout {
                id: view

                width: parent.width

                Repeater {
                    model: TaskModel

                    RowLayout {
                        id: row
                        spacing: 10

                        TextField {
                            id: propertyTitle
                            placeholderText: "property"
                            wrapMode: Text.WrapAnywhere
                            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                            text: propertyName
                            selectByMouse: true

                            onEditingFinished: model.propertyName = text
                        }

                        Component {
                            id: checkboxComponent

                            ColumnLayout {
                                Repeater {
                                    id: checkboxRepeater

                                    model: propertyValue

                                    delegate: RowLayout {
                                        CheckBox {
                                            id: check
                                            checked: model.isDone
                                            onClicked: model.isDone = checked
                                        }
                                        TextField {
                                            Layout.fillWidth: true
                                            wrapMode: Text.WrapAnywhere
                                            selectByMouse: true
                                            text: model.description
                                            onEditingFinished: model.description = text
                                        }
                                        RoundButton {
                                            text: "x"
//                                                font.family: "fontello"
                                            Material.accent: "transparent"
                                            Material.background: "transparent"
                                            onClicked: {
                                                CheckboxModel.removeItem(index);
                                            }
                                        }
                                    }

                                }
                                Button {
                                    Layout.fillWidth: true
                                    text: qsTr("New Item")

                                    Material.background: "transparent"
                                    Material.foreground: Material.Pink

                                    onClicked: {
                                        CheckboxModel.addItem();
                                    }
                                }
                            }

                        }
                        Component {
                            id: entryComponent
                            TextField {
                                Layout.fillWidth: true
                                wrapMode: Text.WrapAnywhere
                                selectByMouse: true
                                placeholderText: "value"
                                text: model.propertyValue
                                onEditingFinished: model.propertyValue = text
                            }
                        }
                        Component {
                            id: tagsComponent

                            ColumnLayout {
                                Layout.fillWidth: true

                                Flow {
                                    spacing: 5

                                    Repeater {
                                        id: rep
                                        model: propertyValue

                                        Item {
                                            id: tag

                                            width: name.width + cross.width
                                            height: name.height + 4

                                            Text {
                                                id: name
                                                z: 5

                                                anchors.centerIn: parent
                                                text: modelData
                                                anchors.horizontalCenterOffset: -8
                                                wrapMode: Text.WrapAnywhere
                                            }

                                            RoundButton {
                                                id: cross
                                                z: 5
                                                width: 28
                                                height: 28
                                                text: qsTr("x")
                                                anchors.verticalCenter: parent.verticalCenter

                                                anchors.left: name.right
                                                Material.background: "transparent"

                                                onClicked: {
                                                    TaskModel.removeTag(index);
                                                }
                                            }


                                            Rectangle {
                                                id: tagBack
                                                anchors.fill: parent
                                                radius: 7
                                                color: "pink"
                                            }
                                        }
                                    }


                                }
                                TextField {
                                    Layout.fillWidth: true
                                    wrapMode: Text.WrapAnywhere
                                    selectByMouse: true
                                    placeholderText: "tag name"
                                    onEditingFinished: {
                                        if (text.length) {
                                            propertyValue = text;
                                            text = ""
                                        }
                                    }
                                    Keys.onReturnPressed: {
                                        editingFinished();
                                    }
                                }
                            }

                        }
                        Component {
                            id: dateComponent
                            ColumnLayout {
                                Layout.fillWidth: true
                                TextField {
                                    id: dateTitle
                                    placeholderText: "dd-mm-yyyy"
                                    wrapMode: Text.WrapAnywhere
                                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                                    Layout.fillWidth: true
                                    selectByMouse: true
                                    readOnly: true
                                    text: calendarLoader.date


                                }
                                Loader {
                                    id: calendarLoader

                                    property string date: propertyValue

                                    Layout.fillWidth: true
                                    Layout.preferredHeight: (sourceComponent) ? 200 : 0
                                    Layout.topMargin: -30

                                    sourceComponent: inputFocus ? datePickerComponent : null
                                    onDateChanged: model.propertyValue = date
                                    onSourceComponentChanged: {
                                         animation.running = true
                                    }
                                    NumberAnimation {
                                        id: animation
                                        target: calendarLoader.item
                                        property: "y"
                                        from: y
                                        to: y + 30
                                        duration: 1000
                                        easing.type: Easing.OutBack
                                    }
                                }
                            }
                        }
                        Loader {
                            id: load

                            property bool inputFocus: focus
                            function getComponent(propertyType) {
                                switch(propertyType) {
                                case 0:
                                    return entryComponent;
                                case 1:
                                    return dateComponent;
                                case 2:
                                    return checkboxComponent;
                                case 3:
                                    return tagsComponent;
                                }
                            }

                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                            sourceComponent: getComponent(propertyType)
                        }

                        RoundButton {
                            id: menuBtn
                            text: "\ue806"
                            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                            font.family: "fontello"

                            Material.background: "transparent"

                            onClicked: {
                                contextMenu.open()
                            }

                            Menu {
                                id: contextMenu

                                width: 130
                                topPadding: 0
                                bottomPadding: 0

                                font.pixelSize: 13

                                background: Pane {
                                    anchors.fill: parent
                                    Material.primary: Material.Grey
                                    Material.elevation: 6
                                }

                                MenuItem {
                                    text: "Remove"
                                    onTriggered: TaskModel.removeProperty(index);
                                    height: 30
                                    width: parent.width
                                }
                                MenuSeparator{}
                                MenuItem {
                                    text: "Text field"
                                    onTriggered: {
                                        model.propertyType = 0
                                    }
                                    height: 30
                                    width: parent.width
                                }
                                MenuItem {
                                    text: "Tags field"
                                    onTriggered: {
                                        model.propertyType = 3
                                    }
                                    height: 30
                                    width: parent.width
                                }
                                MenuItem {
                                    text: "Date field"
                                    onTriggered: {
                                        model.propertyType = 1
                                    }

                                    height: 30
                                    width: parent.width
                                }
                                MenuItem {
                                    text: "Checkboxes"
                                    onTriggered: model.propertyType = 2
                                    height: 30
                                    width: parent.width
                                }
                                MenuItem {
                                    text: "People"
                                    onTriggered: model.propertyType = 4
                                    height: 30
                                    width: parent.width
                                }
                            }
                        }
                    }
                }
                Button {
                    id: newPropertyBtn

                    text: qsTr("New Property")
                    Material.background: "transparent"
                    Material.foreground: Material.Pink
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                    onClicked: TaskModel.addProperty();
                }
                RowLayout {
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Button {
                        text: qsTr("Ok")
                        Material.foreground: "white"
                        Material.background: Material.Blue
                        implicitWidth: 120
                        onClicked: {
                            client.finishEditingTask();
                        }
                    }
                    Button {
                        text: qsTr("Cancel")
                        implicitWidth: 120
                        onClicked: {
                            dialog.close()

                        }
                    }
                }

            }

        }

    }

    Component {
        id: datePickerComponent

        DatePicker {
            id: datepicker

            Layout.fillWidth: true
            Component.onCompleted: {
                width = parent.parent.width
                set(Date.fromLocaleString(Qt.locale(), date, "dd-MM-yyyy"))
            }
            onClicked: {
                forceActiveFocus()
                parent.date = Qt.formatDate(datepicker.selectedDate, "dd-MM-yyyy")
            }

        }
    }

}
