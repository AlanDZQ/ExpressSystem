import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0

Item {
    property string eserialID: ""
    property string totalPrice: ""
    property string quality: ""
    property string userID: ""
    property string time: ""
    property string receiveName: ""
    property string receiveAddress: ""
    property string receivePhone: ""
    property string remark: ""

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
                text: "Export Item: " + eserialID
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
        }
    }

    Component{
        id:highlightrec
        Rectangle{
            color: "#DCDCDC"
            radius: 5
            border.color: "#FFFFFF"
        }
    }

    ListView {
        id: view1
        anchors.topMargin: 50
        anchors.rightMargin: parent.width - view1.headerItem.width
        anchors.fill: parent
        contentWidth: headerItem.width
        flickableDirection: Flickable.HorizontalAndVerticalFlick
        highlightFollowsCurrentItem: true
        highlight: highlightrec

        header: Row {
            z: 2
            spacing: 1
            function itemAt(index) { return repeater1.itemAt(index) }
            Repeater {
                id: repeater1
                model: ["GoodID", "Amount"]
                Label {
                    text: modelData
                    color: "#ffffffff"
                    font.pixelSize: 20
                    padding: 10
                    width: 100
                    background: Rectangle { color: "#20B2AA"}
                }
            }
        }
        headerPositioning: ListView.OverlayHeader

        model: dboperator.searchExportGood("eserialid", eserialID).length
        delegate: Column {
            id: delegate1
            property int row: index
            Row {
                spacing: 1
                Repeater {
                    model: 2
                    ItemDelegate {
                        property int column: index
                        width: view1.headerItem.itemAt(column).width
                        text: qsTr(getItem(delegate1.row, column, dboperator.searchExportGood("eserialid", eserialID)))
                        function getItem(i, j, list){
                            if(j===0)
                                return list[i].getGoodID
                            if(j===1)
                                return list[i].getAmount.toString()
                        }
                        highlighted: ListView.isCurrentItem
                        onClicked: {
                            view1.currentIndex = delegate1.row
                        }
                    }
                }
            }
            Rectangle {
                color: "silver"
                width: parent.width
                height: 1
            }
        }

        ScrollIndicator.horizontal: ScrollIndicator { }
        ScrollIndicator.vertical: ScrollIndicator { }
    }

    ListView {
        id: view2
        anchors.topMargin: 50
        anchors.leftMargin: view1.width
        anchors.rightMargin:  parent.width - view1.headerItem.width - view2.headerItem.width
        anchors.fill: parent
        contentWidth: headerItem.width
        flickableDirection: Flickable.HorizontalAndVerticalFlick
        highlightFollowsCurrentItem: true
        highlight: highlightrec

        header: Row {
            z: 2
            spacing: 1
            function itemAt(index) { return repeater2.itemAt(index) }
            Repeater {
                id: repeater2
                model: ["Time", "Status"]
                Label {
                    text: modelData
                    color: "#ffffffff"
                    font.pixelSize: 20
                    padding: 10
                    width: 100
                    background: Rectangle { color: "#20B2AA"}
                }
            }
        }
        headerPositioning: ListView.OverlayHeader

        model: dboperator.searchExportStatus("eserialid", eserialID).length
        delegate: Column {
            id: delegate2
            property int row: index
            Row {
                spacing: 1
                Repeater {
                    model: 2
                    ItemDelegate {
                        property int column: index
                        width: view2.headerItem.itemAt(column).width
                        text: qsTr(getItem(delegate2.row, column, dboperator.searchExportStatus("eserialid", eserialID)))
                        function getItem(i, j, list){
                            if(j===0)
                                return list[i].getTime.toString()
                            if(j===1)
                                return list[i].getStatus
                        }
                        highlighted: ListView.isCurrentItem
                        onClicked: {
                            view2.currentIndex = delegate2.row
                        }
                    }
                }
            }
            Rectangle {
                color: "silver"
                width: parent.width
                height: 1
            }
        }

        ScrollIndicator.horizontal: ScrollIndicator { }
        ScrollIndicator.vertical: ScrollIndicator { }
    }


}
