import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3

Item {
    id: root
    visible: true
    anchors.fill: parent

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

