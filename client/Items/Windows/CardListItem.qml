import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

Item {
    id: cardList

    property int cardWidth: dp(300)
    property int cardHeight: dp(300)

    width: cardWidth
    height:cardHeight

    function showModelItems(model, layoutItem, delegateItem) {
        for (var item = 0; item < model.count; item++) {
            var component;
            var sprite;
            component = Qt.createComponent(delegateItem);
            console.log(model.get(item).text)
            if (component.status === Component.Ready){
                sprite = component.createObject(layoutItem, {cardContent: model.get(item).text});
            }
        }

    }

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
        width: parent.width
        height: layout.height
        backgroundColor: "pink"

        Flickable {
//             clip: true;
            contentWidth: parent.width
            contentHeight: layout.height


            Column {
                id: layout
                spacing: dp(5)
                anchors { // the column should have a real size so make it fill the parent horizontally
                    left: parent.left;
                    right: parent.right;
                }
                Component.onCompleted:  {
//                    console.log(cardModel.count)
                    showModelItems(cardModel, layout, "CardItem.qml");
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

