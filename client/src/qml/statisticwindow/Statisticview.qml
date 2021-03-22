import QtQuick 2.9
import QtQuick.Window 2.2
import QtCharts 2.2
import QtQuick.Layouts 1.3

Item {
    id: root
    anchors.fill: parent

    Flickable {
        id: flickable
        anchors.fill: parent

        contentHeight: view.height
        contentWidth: view.width
        clip: true

        GridLayout {
            id: view

            width: root.width
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 1

            Repeater {

                model: StatisticModel

                ChartView {
                    id: chart

                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

                    width: 600
                    localizeNumbers: true
                    Layout.minimumHeight: 500
                    Layout.minimumWidth: 500

                    title: qsTr(chartTitle)
//                    titleFont.bold: true
                    titleFont.pixelSize: 20;
                    titleFont.bold: true;


                    legend.visible: false
                    antialiasing: true
                    animationOptions: ChartView.AllAnimations

                    PieSeries {
                        id: pieSeries
                    }

                    HPieModelMapper {
                        id: mapper
                        series: pieSeries
                        model: chartSeries
                        labelsRow: 1
                        valuesRow: 2

                        firstColumn: 1
                        columnCount: entityChartCount

                    }
                    Component.onCompleted: {
                        pieSeries.at(mapper.columnCount - 1).exploded = true;
                        for (var i = 0; i < pieSeries.count; i++) {
                            pieSeries.at(i).labelPosition = PieSlice.LabelOutside;
                            pieSeries.at(i).labelVisible = true;
                            pieSeries.at(i).borderWidth = 3;
                        }
                    }
                }
            }
        }
    }
}
