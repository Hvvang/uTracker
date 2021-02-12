import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item {
    id: root

    property var workflowmodel: WorkflowsModel

    anchors.fill: parent
    width: parent.width
    height: parent.height

    Flickable {
        anchors.fill: parent
        width: parent.width
        height: parent.height

        Component.onCompleted: print(workflowmodel.rowCount())
        contentHeight: workflowmodel.rowCount() / grid.columns * 250


        clip: true

        GridLayout {
            id: grid

            anchors.fill: parent

            columns: root.width / 200
            rows: -1

            Repeater {
                model: workflowmodel

                Workflowpane {
                    flowModel: flowColaborants
                }
            }

        }
    }


}

