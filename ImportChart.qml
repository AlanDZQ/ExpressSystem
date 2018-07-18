import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtCharts 2.0

Item {

    ToolBar {
        z:2
        width: parent.width
        height: 50
        Material.background: "#20B2AA"
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTr("‹")
                font.bold: true
                font.pointSize: 20
                onClicked: homeStackView.pop()

            }
            Label {
                text: "IMPORT CHART"
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
        }
    }



    SwipeView {
        id: swipeView
        y : 50
        width: parent.width
        height: parent.height - 50
        currentIndex: 0
        Item {
            ChartView {
                id: chartView1
                title:"TotalPrice-ISerialID"
                width: parent.width
                height: parent.height
                anchors.fill: parent
                antialiasing: true
                theme: ChartView.ChartThemeLight
                animationOptions:ChartView.SeriesAnimations
                BarSeries {
                    BarSet {
                        label: "TotalPrice"
                        color: "#20B2AA"
                        values: totalPrice()
                    }

                    axisX: BarCategoryAxis {
                        titleText: "ISerialID"
                        categories: xAxisList()
                    }
                }
                Rectangle{
                    id: shadow
                    color: "#20B2AA"
                    opacity: 0.6
                    visible: false
                }
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    acceptedButtons: Qt.AllButtons

                    onPressed: {shadow.x = mouseX; shadow.y = mouseY; shadow.visible = true; swipeView.interactive = false}
                    onMouseXChanged: {shadow.width = mouseX - shadow.x}
                    onMouseYChanged: {shadow.height = mouseY - shadow.y}
                    onReleased: {
                        chartView1.zoomIn(Qt.rect(shadow.x, shadow.y, shadow.width, shadow.height))
                        shadow.visible = false
                        swipeView.interactive = true
                    }
                    onClicked: {
                        if (mouse.button === Qt.RightButton) {
                            contentMenu1.popup()
                        }
                    }
                }
            }
            Menu {
                id: contentMenu1
                MenuItem {
                    text: "Zoom Resize"
                    onTriggered: {
                        chartView1.zoomReset()
                    }
                }
            }
        }

        Item {
            ChartView {
                id: chartView2
                title:"Spend($)-Time"
                width: parent.width
                height: parent.height
                anchors.fill: parent
                antialiasing: true
                theme: ChartView.ChartThemeLight
                animationOptions:ChartView.SeriesAnimations
                axes: [
                    DateTimeAxis{
                        id: xAxis
                        format: "yyyy/MM/dd"
                        titleText: "Time"
                        min: xAxisTime().timeList[0]
                        max: xAxisTime().timeList[xAxisTime().timeList.length - 1]
                    },
                    ValueAxis{
                        id: yAxis
                        min: 0.0
                        max: 10000
                    }
                ]

                Component.onCompleted: {
                    var xlist = xAxisTime()
                    var series = chartView2.createSeries(ChartView.SeriesTypeLine, "Spend Money", xAxis, yAxis);
                    for(var i = 0; i < xlist.timeList.length; i++){
                        series.append(xlist.timeList[i], xlist.valueList[i])
                    }
                }

                Rectangle{
                    id: shadow2
                    color: "#20B2AA"
                    opacity: 0.6
                    visible: false
                }
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    acceptedButtons: Qt.AllButtons

                    onPressed: {shadow2.x = mouseX; shadow2.y = mouseY; shadow2.visible = true; swipeView.interactive = false}
                    onMouseXChanged: {shadow2.width = mouseX - shadow2.x}
                    onMouseYChanged: {shadow2.height = mouseY - shadow2.y}
                    onReleased: {
                        chartView2.zoomIn(Qt.rect(shadow2.x, shadow2.y, shadow2.width, shadow2.height))
                        shadow2.visible = false
                        swipeView.interactive = true
                    }
                    onClicked: {
                        if (mouse.button === Qt.RightButton) {
                            contentMenu2.popup()
                        }
                    }
                }
                Menu {
                    id: contentMenu2
                    MenuItem {
                        text: "Zoom Resize"
                        onTriggered: {
                            chartView2.zoomReset()
                        }
                    }
                }
            }
        }
    }

    PageIndicator {
        id: indicator
        count: swipeView.count
        currentIndex: swipeView.currentIndex

        anchors.bottom: swipeView.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    function totalPrice(){
        var totalPriceList = []
        var list = xAxisList()
        for(var i = 0; i < list.length; i++){
            totalPriceList[i] = dboperator.searchImport(list[i])[0].getTotalprice.toString()
        }
        return totalPriceList
    }
    function xAxisList(){
        var xAxisList = []
        var list = dboperator.sortImport("iserialID")
        for(var i = 0; i < list.length; i++){
            xAxisList[i]=list[i].getIserialID
        }
        return xAxisList
    }
    function xAxisTime(){
        var timeList = []
        var valueList = []
        var list = dboperator.sortImport("Time")
        for(var i = 0; i < list.length; i++){
            if(i>0 && Qt.formatDateTime(list[i].getTime, "yyyy-MM-dd")!==Qt.formatDateTime(list[i-1].getTime, "yyyy-MM-dd"))
            {
                timeList[timeList.length] = list[i].getTime
                valueList[valueList.length] = (list[i].getTotalprice)
            }
            else if (i>0 && Qt.formatDateTime(list[i].getTime, "yyyy-MM-dd")===Qt.formatDateTime(list[i-1].getTime, "yyyy-MM-dd"))
                valueList[valueList.length-1] += list[i].getTotalprice
            else{
                timeList[timeList.length] = list[i].getTime
                valueList[valueList.length] = (list[i].getTotalprice)
            }

        }
        return {
            timeList: timeList,
            valueList: valueList
        }
    }
}
