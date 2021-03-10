import QtQuick 2.8
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQml.Models 2.14
import QtQuick.Controls.Styles 1.4

import "../components"

Item {
    id: root
    anchors.fill: parent

    property int currentPanelIndexOnDragging: 0

    Flickable {
        id: headerFlick

        height: 44

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        contentWidth: rowView.childrenRect.width + 250
        clip: true
        interactive: false

        onContentXChanged: {
            panelsFlick.contentX = contentX
        }

        Row {
            id: headerView

            Repeater {
                id: panelHeaderRepeater
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
                        TextField {
                            id: panelheaderTitle
                            width: parent.width
                            text: qsTr(model.panelTitle)
                            horizontalAlignment: Text.AlignHCenter
                            font.weight: Font.DemiBold
                            font.pointSize: 15
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter

                            selectByMouse: true

                            background: Rectangle { color: "transparent"; }
                            onFocusChanged: {
                                if (!focus)
                                    client.updatePanelTitle(panelId, text);
                            }
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

                onClicked: {
                    client.newPanel(KanbanModel.flowId(), panelHeaderRepeater.count)
                }
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

            Repeater {
                model: KanbanModel

                ColumnLayout {
                    id: columnView

                    property int _sourceModelIndex: index
                    property var panelsModel: model
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                    Repeater {
                        id: rep
                        model: DelegateModel {
                            id: visualModel
                            model: panelModel

                            delegate: DropArea {
                                id: delegateRoot

                                width: task.width; implicitHeight: (isBlank) ? KanbanModel.getHeight() : task.height

                                property int sourceIndex: index
                                property int sourceModelIndex: columnView._sourceModelIndex

                                onDropped: {

                                    if (columnView._sourceModelIndex !== (drag.source as Taskview).panelIndex) {
                                        var sourcePanelIndex = (drag.source as Taskview).panelIndex;
                                        var sourceTaskIndex = (drag.source as Taskview).index;
                                        var targetPanelIndex = columnView._sourceModelIndex;
                                        var targetTaskIndex = task.index
                                        KanbanModel.swap(sourcePanelIndex, sourceTaskIndex, targetPanelIndex, targetTaskIndex);
                                    }
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
                                           forceActiveFocus()
//                                           if(mouse.button & Qt.RightButton) {
//                                               task.realModel.removeRows(task.index, 1);
//                                           }
//                                           if(mouse.button & Qt.LeftButton) {
//                                               task.colabsCounter += 1;
//                                           }
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

                        onClicked: {
                            client.newTask(panelId, visualModel.count)
                        }
                    }
                }

            }
        }


    }
}

