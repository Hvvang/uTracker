import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

Item {
    id: card

    property int cardId: 000000
    property string cardContent: "value"
    property int cardWidth: dp(100)
    property int cardHeight: dp(80)

    width: cardWidth
    height: cardHeight
    Card {
        anchors.centerIn: parent
        width: parent.width - dp(20)
        height: parent.height - dp(5)
        backgroundColor: "#fde8f5"
        Row {
            anchors.fill: parent
            anchors.margins: dp(20)
            spacing: dp(10)
            Text {
                id: infoText
                text: cardContent
                height: parent.height
                width: parent.width - (menuButton.width - parent.spacing / 2)
                color: "#7a163c"
                font.pixelSize: dp(19)
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
            }
            ActionBar {
                id: menuButton
                height: parent.height
                width: parent.height
//                onClicked: snackbar.open("That button is colored!")
                maxActionCount: 1
//                backgroundColor: "pink"

                actions: [
                    Action {
                        id: addPers
                        iconName: "navigation/chevron_right"
                        text: "More..."
                        hoverAnimation: true
                        onTriggered: {
//                            var cardIndex = layout.indexAt(mouseX, mouseY + control.globalPos)
//                            var cardItem = cardModel.get(index)
                            console.log("Request to server: Id of card: " + cardId)

                            // Waiting for response

                            var component;
                            var sprite;
                            component = Qt.createComponent("CardView.qml");
                            if (component.status === Component.Ready){
                                sprite = component.createObject(card, {text: "info:" + cardId});
                            }
                            sprite.show()
                        }
                    },
                    Action {
                        id: delPers
                        iconName: "navigation/chevron_right"
                        text: "Remove card"
                        hoverAnimation: true
                        onTriggered: {
                        }
                    }
                ]
            }
        }

    }
}
