import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

//    height:
//    ListModel {
//        id: model
//        ListElement {
//            text: "Plan"
////            tasks: ["Task1", "Task2"]
//        }
//        ListElement {
//            text: "Prccess"
////            tasks: ["Task3", "Task4"]
//        }
//        ListElement {
//            text: "Done"
////            tasks: ["Task5"]
//        }
//    }



Item {
    id: deskItem
    property int listWidgth: dp(300)


    width: listWidgth
    Card {
        anchors.centerIn: parent
        width: parent.width - dp(20)
        height: parent.height - dp(20)
        backgroundColor: "pink"
        Row {
            width: deskItem.width - dp(20)
            height: deskItem.height - dp(20)
            spacing: dp(20)
            anchors {
                top: parent.top
                left: parent.left
                margins: dp(10)
            }
            CardItem{}
            CardItem{}
            CardItem{}
            CardListItem{}

        }
    }
}



