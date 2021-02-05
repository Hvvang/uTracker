import QtQuick 2.8
import QtQuick.Window 2.12
import Qt.labs.settings 1.0

Window {
  id: main
  width: 640
  height: 480
  property bool isAuthorized: false
  visible: true
//  onIsAuthorizedChanged: print("isAuthorized equal: ", main.isAuthorized);

//  Settings {
//    property alias isAuthorized: main.isAuthorized
//  }

  Loader {
      anchors.fill: parent
    source: "mainwindow/MainWindow.qml"
  }
}
