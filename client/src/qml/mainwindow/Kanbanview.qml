import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQml.Models 2.14

Item {
    id: root
    anchors.fill: parent
    anchors.margins: 10

    height: parent.height
    width: parent.width

    property int currentPanelIndexOnDragging: 0

    Flickable {
        id: headerFlick

        height: 44

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        contentWidth: rowView.childrenRect.width + 250
        clip: true

        onContentXChanged: {
            panelsFlick.contentX = contentX
        }

        Row {
            id: headerView

            Repeater {

                model: KanbanModel

                Item {
                    id: panel
                    width: 250
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom

                    Item {
                        id: header
                        width: panel.width
                        height: 44
                        Text {
                            text: qsTr(model.panelTitle)
                            font.weight: Font.DemiBold
                            font.pointSize: 15
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }
            }
            RoundButton {
                id: newPanelBtn

                width: 250

                Material.background: Material.Blue
                Material.foreground: "white"

                Material.elevation: 6
                text: qsTr("New Panel");
                font.capitalization: Font.MixedCase
                font.weight: Font.Medium

                radius: 6
            }
        }
    }

    Flickable {
        id: panelsFlick
        anchors.top: headerFlick.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        contentHeight: rowView.childrenRect.height
        contentWidth: rowView.childrenRect.width + 250
        clip:true

        onContentXChanged: {
            headerFlick.contentX = contentX
        }


        RowLayout {
            id: rowView
//            anchors.fill: parent

            Repeater {
                id: repeater
//                Layout.alignment: Qt.AlignLeft | Qt.AlignTop


                model: KanbanModel

                ColumnLayout {
                    id: columnView

                    property int _sourceModelIndex: index
                    property var panelsModel: model
                    anchors.top: parent.top
                    anchors.topMargin: 0

                    Repeater {
                        id: rep
                        model: DelegateModel {

                            id: visualModel

                            model: panelModel

                            delegate: DropArea {
                                id: delegateRoot

                                width: task.width; height: (isBlank) ? KanbanModel.getHeight() : task.height

                                property int sourceIndex: index
                                property int sourceModelIndex: columnView._sourceModelIndex

                                onDropped: {

                                    if (columnView._sourceModelIndex !== (drag.source as Taskview).panelIndex) {
                                        var sourcePanelIndex = (drag.source as Taskview).panelIndex;
                                        var sourceTaskIndex = (drag.source as Taskview).index;
                                        var targetPanelIndex = columnView._sourceModelIndex;
                                        var targetTaskIndex = task.index
//                                            drag.drop()
                                        KanbanModel.swap(sourcePanelIndex, sourceTaskIndex, targetPanelIndex, targetTaskIndex);
                                    }

//                                        print(columnView._sourceModelIndex, (drag.source as Taskview).panelIndex)
                                }

                                onExited: {
                                    root.currentPanelIndexOnDragging = columnView._sourceModelIndex
                                }

                                onEntered: function(drag) {

                                    if (root.currentPanelIndexOnDragging !== columnView._sourceModelIndex) {
                                        KanbanModel.removeBlank(root.currentPanelIndexOnDragging);
                                    }


                                    delegateRoot.height = KanbanModel.getHeight()
                                    delegateRoot.width = (drag.source as Taskview).width


                                    if ((task as Taskview).realModel === (drag.source as Taskview).realModel)
                                        panelModel.move((drag.source as Taskview).index, (task as Taskview).index, 1);
                                    else {
                                        panelModel.test((task as Taskview).index)
                                    }

                                }


                                 Rectangle {
                                     id: dropBack
                                     anchors.fill: delegateRoot
                                     radius: 6
                                     smooth: true
                                     anchors.margins: 10
                                     color: delegateRoot.containsDrag ? "#d3d2d2" : "transparent";
                                 }

                                Taskview {
                                    id: task

                                    property int index: model.index
                                    property int panelIndex: delegateRoot.sourceModelIndex
                                    property var realModel: panelModel

                                    visible: !isBlank

                                    MouseArea {
                                       id: dragArea
                                       anchors.fill: parent

                                       drag.target: parent

                                       acceptedButtons: Qt.LeftButton | Qt.RightButton
                                       onClicked: {
                                           if(mouse.button & Qt.RightButton) {
                                               task.realModel.removeRows(task.index, 1);
                                           }
                                       }
                                       onPressed: KanbanModel.setHeight(drag.target.height)
                                       onReleased: {
                                           parent.Drag.drop()
                                           KanbanModel.setHeight(0)
                                       }
                                    }
                                    states: [
                                       State {
                                           when: task.Drag.active

                                           ParentChange {
                                               target: task
                                               parent: root
                                           }


                                           AnchorChanges {
                                               target: task
                                               anchors.horizontalCenter: undefined
                                               anchors.verticalCenter: undefined
                                           }
                                       }
                                    ]

                                    Drag.active: dragArea.drag.active
                                    Drag.hotSpot.x: task.width / 2
                                    Drag.hotSpot.y: task.height / 2

                                }
                            }

                        }
                    }

                    RoundButton {
                        id: newTaskBtn

                        Material.background: "white"
                        Material.foreground: "black"
                        Material.elevation: 6
                        text: qsTr("New Task");
                        font.capitalization: Font.MixedCase
                        font.weight: Font.Medium
                        Layout.fillWidth: true
                        radius: 6
                    }
                }

            }
        }


    }
}

