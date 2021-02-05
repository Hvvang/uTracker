import QtQuick 2.15
import QtQuick.Window 2.11
import QtQuick.Controls 1.3 as Controls
import QtQuick.Controls 2.15
import Material 0.3
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.3


Dialog {
    id: cardView
    width: dp(500)
    title: "Use Google's location service?"
    text: "Let Google help apps determine location. This means sending anonymous location data to Google, even when no apps are running."
    hasActions: true
    positiveButtonText: "agree"
    negativeButtonText: "disagree"
}
