import QtQuick 2.8
import QtQuick.Window 2.12
import Qt.labs.settings 1.0



Window {
  id: main
  width: 640
  height: 480
  visible: true

  Loader {
      width: parent.width
      height: parent.height
      anchors.fill: parent
      source: "qml/mainwindow/Kanbanview.qml"
  }
}
