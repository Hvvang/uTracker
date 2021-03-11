import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item {
    id: root

    property var workflowmodel: WorkflowsModel

    anchors.fill: parent

    onWidthChanged: {

        flick.contentHeight =  Math.round(workflowmodel.rowCount() / grid.columns) * 210
        flick.contentWidth =  grid.columns * 210
        grid.columns = root.width / 210 < WorkflowsModel.rowCount() ? root.width / 210 : WorkflowsModel.rowCount()
    }
    Flickable {
        id: flick
        anchors.fill: parent
        width: parent.width
        height: parent.height

        clip: true

        GridLayout {
            id: grid
            columnSpacing: 5
            rowSpacing: 5

            anchors.fill: parent

            Repeater {
                model: WorkflowsModel

                onCountChanged: {
                    grid.columns = root.width / 210 < WorkflowsModel.rowCount() ? root.width / 210 : WorkflowsModel.rowCount()
                    flick.contentHeight = Math.round(WorkflowsModel.rowCount() / grid.columns) * 210
                    flick.contentWidth =  grid.columns * 210
                }
                Workflowpane {
                    flowModel: flowColaborants
                }
            }

        }
    }
}

