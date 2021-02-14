import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item {
    id: root

    property var workflowmodel: WorkflowsModel

    anchors.fill: parent

    Flickable {
        id: flick
        anchors.fill: parent
        width: parent.width
        height: parent.height

        contentHeight: workflowmodel.rowCount() / grid.columns * 210
        contentWidth: 1 / grid.columns * 210

        clip: true

        GridLayout {
            id: grid
            columnSpacing: 5
            rowSpacing: 5

            anchors.fill: parent
            onColumnsChanged: print("root.width is ", root.width)
            columns: root.width / 210
            rows: -1

            Repeater {
                model: workflowmodel

                onCountChanged: {
                    flick.contentHeight =  workflowmodel.rowCount() / grid.columns * 210
                }
                Workflowpane {
                    flowModel: flowColaborants
                }
            }

        }
    }


}

