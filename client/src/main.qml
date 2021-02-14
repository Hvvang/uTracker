import QtQuick 2.8
import QtQuick.Window 2.12
import Qt.labs.settings 1.0
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3




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


}
