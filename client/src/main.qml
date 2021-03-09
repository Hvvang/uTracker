import QtQuick 2.8
import QtQuick.Window 2.12
import Qt.labs.settings 1.0
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

import "./qml/workflowswindow/."
import "qml/components"

Window {
  id: main
  width: 640
  height: 480
  visible: true

  title: "Utracker"

  Popup {
    id: snackbar

    Connections {
        target: client
        function onNotification(msg) {
          snackbar.customOpen(msg);
        }
    }

    property string text
    property int duration: 2000

    onTextChanged: customOpen(text);

    y: parent.height - 44
    width: parent.width
    height: 44

    background: Rectangle {
        color: "#323232"
    }

    contentItem: Text {
        text: snackbar.text
        color: "white"
    }

    function customOpen(text) {
        snackbar.text = text
        open()
        timer.restart();
    }

    Timer {
        id: timer

        interval: snackbar.duration
        onTriggered: {
            if (!running) {
                snackbar.close()
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
        NumberAnimation { duration: 300 }
    }
}

  Loader {
      id: loader

      Connections {
          target: client
          function onSwitchWindow(window) {
            loader.source = window;
          }
      }
      anchors.fill: parent

      source: "qml/authwindow/Authorization.qml"
//      source: "qml/mainwindow/Mainwindowview.qml"
  }


  /*
  Component.onCompleted: dialog.open()
    Dialog {
        id: dialog

        title: "Edit Task"

        contentItem: Item {
            Flickable {
                anchors.fill: parent
                contentHeight: view.childrenRect.height
                clip: true

                ColumnLayout {
                    id: view

                    anchors.fill: parent


                    Repeater {
                        model: 10

                        RowLayout {
                            id: row
                            spacing: 10

                            TextField {
                                id: propertyTitle
                                placeholderText: "property"
                                wrapMode: Text.WrapAnywhere
                                Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                                selectByMouse: true
                            }


                            Component {
                                id: checkboxComponent

                                ColumnLayout {
                                    Repeater {
                                        id: checkboxRepeater

                                        model: 2

                                        delegate: RowLayout {
                                            CheckBox {
                                                id: check
                                            }
                                            TextField {
                                                Layout.fillWidth: true
                                                wrapMode: Text.WrapAnywhere
                                                selectByMouse: true
                                                text: "qwerty"
                                            }
                                            RoundButton {
                                                text: "x"
//                                                font.family: "fontello"
                                                Material.accent: "transparent"
                                                Material.background: "transparent"
                                                onClicked: {
//                                                    checkboxRepeater.model.remove(index)
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
                                            checkboxRepeater.model += 1
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
                                            model: []

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
//                                        width: parent.width
                                        wrapMode: Text.WrapAnywhere
                                        selectByMouse: true
                                        placeholderText: "tag name"
                                        Keys.onReturnPressed: {
                                            if (text.length) {
                                                var new_model = new Array
                                                for (var item in rep.model) {
                                                    new_model.push(rep.model[item])
                                                }
                                                new_model.push(text)
                                                rep.model = new_model;
                                                text = ""
                                            }


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

                                        property string date: ""

                                        Layout.fillWidth: true
                                        Layout.preferredHeight: (sourceComponent) ? 200 : 0
                                        Layout.topMargin: -30

                                        sourceComponent: inputFocus ? datePickerComponent : null

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

                                Layout.fillWidth: true
                                Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                                sourceComponent: tagsComponent
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
                                        onTriggered: {}
                                        height: 30
                                        width: parent.width
                                    }
                                    MenuSeparator{}
                                    MenuItem {
                                        text: "Text field"
                                        onTriggered: load.sourceComponent = entryComponent
                                        height: 30
                                        width: parent.width
                                    }
                                    MenuItem {
                                        text: "Tags field"
                                        onTriggered: load.sourceComponent = tagsComponent
                                        height: 30
                                        width: parent.width
                                    }
                                    MenuItem {
                                        text: "Date field"
                                        onTriggered: load.sourceComponent = dateComponent
                                        height: 30
                                        width: parent.width
                                    }
                                    MenuItem {
                                        text: "Checkboxes"
                                        onTriggered: load.sourceComponent = checkboxComponent
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

                    }
                }

            }

        }

        width: parent.width / 1.5 > 400 ? parent.width / 1.5 : 400
        height: parent.height / 1.5
        anchors.centerIn: parent

        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: console.log("Ok clicked")
        onRejected: console.log("Cancel clicked")

        Component {
            id: datePickerComponent

//            width: parent.width
            DatePicker {
                id: datepicker
//                width: parent.parent.width
                Layout.fillWidth: true
                onWidthChanged: print(width)
                Component.onCompleted: {
                    width = parent.parent.width
                    print(width, parent.parent.width)
                    set(new Date) // today
                }
                onClicked: {
                    forceActiveFocus()
                    parent.date = Qt.formatDate(datepicker.selectedDate, "dd-MM-yyyy")
                }

            }
        }

    }

*/

}
