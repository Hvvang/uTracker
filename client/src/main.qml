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

  Loader {
      id: loader
      objectName: "loader"
      anchors.fill: parent

      source: "qml/Authorization.qml"
  }


}
