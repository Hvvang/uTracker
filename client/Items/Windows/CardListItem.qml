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
        ListElement {
            text: "Task4"
        }
        ListElement {
            text: "Task5"
        }
        ListElement {
            text: "Task1"
        }
        ListElement {
            text: "Task2"
        }
        ListElement {
            text: "Task3"
        }
        ListElement {
            text: "Task4"
        }
        ListElement {
            text: "Task5"
        }
        ListElement {
            text: "Task1"
        }
        ListElement {
            text: "Task2"
        }
        ListElement {
            text: "Task3"
        }
        ListElement {
            text: "Task4"
        }
        ListElement {
            text: "Task5"
        }

    }

    Card {
        id: cardBack
        width: parent.width
        height: (layout.contentHeight + dp(77)) < parent.height ? (layout.contentHeight + dp(77)) : parent.height
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
                height: cardBack.height - dp(77)
                width: parent.width

                ListView {
                    id:layout
                    width: parent.width
                    height: parent.height
                    model:cardModel
                    flickableDirection: Flickable.VerticalFlick
                    boundsBehavior: Flickable.StopAtBounds
                    ScrollBar.vertical: ScrollBar{
                        property real globalPos: control.position * layout.contentHeight
                        id: control
                        hoverEnabled: true
                        active: layout.height < layout.contentHeight && (hovered || pressed)
                        size: 0.3
                        contentItem: Rectangle {
                                implicitWidth: 3
                                implicitHeight: 100
                                radius: width / 2
                                color: !(layout.height < layout.contentHeight) ? "#007a163c" :
                                                         (control.pressed || control.hovered ? "#807a163c" : "#407a163c")
                        }
                    }

                    anchors {
                        left: parent.left;
                        right: parent.right;
                    }
                    delegate: CardItem {
                        id:card
                        cardContent: model.text
                        cardWidth: layout.width

                        states: [
                            State {
                                name: "inDrag"
                                when: index == layout.draggedItemIndex
                                PropertyChanges { target: border; opacity: 1 }
                                PropertyChanges { target: card; parent: dndContainer }
                                PropertyChanges { target: card; anchors.centerIn: undefined }
                                PropertyChanges { target: card; x: coords.mouseX - card.width / 2 }
                                PropertyChanges { target: card; y: coords.mouseY - card.height / 2 }
                            }
                        ]
                        Rectangle {
                            id: border
                            anchors.fill: parent
                            radius: 5
                            color: "transparent"
                            border.color: "#ffffff"
                            border.width: 6
                            opacity: 0
                        }
                    }
                    property int draggedItemIndex: -1
                            interactive: false
                    Item {
                        id: dndContainer
                        anchors.fill: parent
                    }

                    MouseArea {
                        id: coords
                        anchors.fill: parent

                        onReleased: {
                            if (layout.draggedItemIndex !== -1) {
                                var draggedIndex = layout.draggedItemIndex
                                layout.draggedItemIndex = -1
                                cardModel.move(draggedIndex,layout.indexAt(mouseX, mouseY + control.globalPos),1)
                            }
                        }
                        onPressed: {
                            layout.draggedItemIndex = layout.indexAt(mouseX, mouseY + control.globalPos)
                        }

                    }
                }

            }
        }

    }

}

