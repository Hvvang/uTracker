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
                //                 model: 3
                CardItem {
                anchors.horizontalCenter: parent.horizontalCenter
                }
                //                 delegate: CardItem {

                //                 }
                CardItem {

                }
                CardItem {

                }
                CardItem {

                }
                CardItem {

                }
                CardItem {

                }
                CardItem {

                }
                CardItem {

                }
                CardItem {

                }
            }
        }
    }

}
