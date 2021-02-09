import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import ".."

Item {
    id: root
    visible: true
    anchors.fill: parent

    Popup {
        id: snackbar

        property string text
        property int duration: 2000

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

    StackView {
        id: stack
        initialItem: authwindow
        anchors.fill: parent
    }

    RegisterWidow {
        id: registerwindow
        visible: false
    }

    Authwindow {
        id: authwindow
        visible: false
    }

}

