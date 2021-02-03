import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import QtQuick.Controls 2.15
import Material 0.3
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.3

Item {
    id: cardList

    property int cardListWidth: dp(300)
    property int cardListHeight: dp(1080)

    width: cardListWidth
    height:cardListHeight

//    function showModelItems(model, layoutItem, delegateItem) {
//        for (var item = 0; item < model.count; item++) {
//            var component;
//            var sprite;
//            component = Qt.createComponent(delegateItem);
//            console.log(model.get(item).text)
//            if (component.status === Component.Ready){
//                sprite = component.createObject(layoutItem, {cardContent: model.get(item).text});
//            }
//        }

//    }

    ListModel {
        id: cardModel
        ListElement {
            text: "Task1"
        }
        ListElement {
            text: "Task2"
        }
        ListElement {
            text: "Task3"
        }

    }

    Card {
        id: card
        width: parent.width
        height: (layout.height + dp(77)) < parent.height ? (layout.height + dp(77)) : parent.height
//        anchors.fill: pa  rent
        backgroundColor: "pink"

        Column {
            spacing: dp(7)
            id: listGroup
            anchors.fill: parent
            View {
                width: parent.width
                height: dp(70)
                elevation: 1
                z:1
//                            radius: 5
                Rectangle {
                    anchors.fill: parent
                    color: "#80f6a2bf"
//                                border.width: 2
//                                border.color: "#f6a2bf"
//                                radius: parent.radius
                    Text {
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
//                                horizontalAlignment: Text.AlignHCenter
                        anchors.leftMargin: dp(15)
                        color: "#7a163c"
                        font.pixelSize: dp(24)
                        text: "List something"
                        font.bold: true
                    }
                }
            }
            Item {
                height: card.height - dp(77)
                width: parent.width
                Flickable {
                    anchors.fill: parent
                    contentWidth: parent.width
                    contentHeight: layout.height
                    ScrollBar.vertical: ScrollBar { }
                    ColumnLayout {
        //                implicitHeight: dp(100)
                        id: layout
                        clip: true

                        anchors { // the column should have a real size so make it fill the parent horizontally
                            left: parent.left;
                            right: parent.right;
                        }
        //                Component.onCompleted:  {
        ////                    console.log(cardModel.count)
        //                    showModelItems(cardModel, layout, "CardItem.qml");
        //                }
                        Repeater {
                            model:11
                            delegate: CardItem {
                                Layout.maximumHeight: dp(100)
                                cardContent: model.text + parent.index
                                cardWidth: layout.width
                            }
                        }

        //                MouseArea {
        //                    id: coords
        //                    anchors.fill: parent
        //                    onReleased: {
        //                        if (layout.draggedItemIndex !== -1) {
        //                            var draggedIndex = layout.draggedItemIndex
        //                            layout.draggedItemIndex = -1
        //                            dndModel.move(draggedIndex,dndGrid.indexAt(mouseX, mouseY),1)
        //                        }
        //                    }
        //                    onPressed: {
        //                        dndGrid.draggedItemIndex = dndGrid.indexAt(mouseX, mouseY)
        //                    }
        //                }
                    }

                }
            }
        }

    }

}

