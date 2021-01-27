import QtQuick 2.8
import QtQuick.Window 2.12
import Qt.labs.settings 1.0

Window {
  id: main
//  visible: true
//  width: 640
//  height: 480

  property bool isAuthorized: false

  Settings {
    property alias isAuthorized: main.isAuthorized
  }

  Loader {
    source: isAuthorized ? "mainwindow/qml/appview.qml" : "auth/qml/authorization.qml"
  }
}
