import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item {
    anchors.fill: parent
//    width: parent.width
//    height: parent.height

//    Component.onCompleted: print(width)
    Flickable {
        anchors.fill: parent

        contentHeight: 10 / grid.columns * 210
        clip: true

        GridLayout {
            id: grid
            anchors.fill: parent

            columns: parent.width / 200
            rows: -1

            Repeater {
                model: 10

                Workflowpane {}
            }

        }
    }


}

