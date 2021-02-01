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
    actions: [
        Action {
            id: menu
            iconName: "navigation/menu"
            text: "Info"
            hoverAnimation: true
            onTriggered: {
                sidebarInfo.showing = !sidebarInfo.showing
            }
        }
    ]

    rightSidebar: PageSidebar {
        id: sidebarInfo
        title: "Table Info"

        width: dp(320)

        actionBar.maxActionCount: 1

        actions: [
            Action {
                id: addPers
                iconName: "navigation/chevron_right"
                text: "Add colab"
                hoverAnimation: true
                onTriggered: {
                }
            },
            Action {
                id: delPers
                iconName: "navigation/chevron_right"
                text: "Remove colab"
                hoverAnimation: true
                onTriggered: {
                }
            }
        ]
    }

    Snackbar {
        id: snackbar
    }
}
