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
    property int cardHeight: dp(100)

    width: cardWidth
    height:cardHeight
    Card {
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        backgroundColor: "pink"
        Text {
            id: infoText
            anchors.fill: parent
            text: cardContent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
