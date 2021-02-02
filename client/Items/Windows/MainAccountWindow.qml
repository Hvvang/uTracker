import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

Page {
    id: rootAccount
    visible: true
    width: 1920
    height: 1080

    title: "uTracker"
    backgroundColor: "pink"
    actionBar.decorationColor:"#7a163c"
    actions: [
        Action {
            id: info
            iconName: "navigation/menu"
            text: "Info"
            hoverAnimation: false
            onTriggered: {
                sidebarInfo.showing = !sidebarInfo.showing
            }
        }
    ]

    rightSidebar: InfoSidebar {
        id: sidebarInfo
    }
    backAction: navDrawer.action
    NavigationDrawer {
        id: navDrawer

        enabled: true

        onEnabledChanged: smallLoader.active = enabled

        Flickable {
            anchors.fill: parent

            contentHeight: Math.max(content.implicitHeight, height)

            Column {
                id: content
                anchors.fill: parent

                Repeater {
                    model: 3

                    delegate: Column {
                        width: parent.width

                        ListItem.Subheader {
                            text: "Text"
                        }

                        Repeater {
                            model: 3
                            delegate: ListItem.Standard {
                                text: "3"
                                selected: [0]
                                onClicked: selectedComponent = [0]
                            }
                        }
                    }
                }
            }
        }
    }

    Item {
        anchors.fill: parent
        Flickable {
            id: flickable
            anchors.fill: parent
            clip: true
            contentHeight: Math.max(example.implicitHeight + 40, height)
            Loader {
                id: example
                anchors.fill: parent
                asynchronous: true
                visible: status == Loader.Ready
                // selectedComponent will always be valid, as it defaults to the first component
                source: {
                        return Qt.resolvedUrl("DeskItem.qml")
                }
            }

            ProgressCircle {
                anchors.centerIn: parent
                visible: example.status == Loader.Loading
            }
        }
        Scrollbar {
            flickableItem: flickable
        }
    }



    Snackbar {
        id: snackbar
    }
}
