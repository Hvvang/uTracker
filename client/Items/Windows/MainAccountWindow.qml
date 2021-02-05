import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import Material 0.3
import Material.ListItems 0.1 as ListItem

Page {

    function createNewDesk() {
        console.log("Request to create new desk");
    }

    property var userSection: [
        {
            title: "Profile",
            id: -1
        }
    ]
    property var desksSection: [
        {
            title: "Desk 1",
            id: 1
        },
        {
            title: "Desk 2",
            id: 2
        },
        {
            title: "Desk 3",
            id: 3
        },
        {
            title: "Desk 4",
            id: 4
        }
    ]
    property var sections: [userSection, desksSection]
    property var sectionsTitles: ["User information", "Desks"]
    property var selectedComponent: undefined

    id: rootAccount
    visible: true
    width: 1920
    height: 1080

    title: "uTracker"
    backgroundColor: "#dab6c2"
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

        overlayColor: "#307a163c"
        onEnabledChanged: smallLoader.active = enabled

        Flickable {
            anchors.fill: parent

            contentHeight: Math.max(content.implicitHeight, height)

            Column {
                id: content
                anchors.fill: parent

                Repeater {
                    model: sections

                    delegate: Column {
                        width: parent.width

                        ListItem.Subheader {
                            text: sectionsTitles[index]
                            textColor:"#7a163c"
                            showDivider: true
                            elevation: 1
                        }

                        Repeater {
                            model: sections[index]
                            delegate: ListItem.Standard {
                                text: modelData.title
                                selected: modelData.id === selectedComponent.id
                                onClicked: {
                                    selectedComponent = modelData
                                    console.log(modelData.title)
                                    navDrawer.close()
                                }
                            }
                        }
                    }
                }
                Button {
                    text: "New desk +"
                    height: dp(40)
                    width: parent.width
                    onClicked: createNewDesk();
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
