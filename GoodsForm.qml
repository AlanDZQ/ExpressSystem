import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0

Item {
    Component{
        id:highlightrec
        Rectangle{
            color: "#DCDCDC"
            radius: 5
            border.color: "#FFFFFF"
        }
    }
    ListView {
        id: view
        anchors.topMargin: 50
        anchors.fill: parent
        contentWidth: headerItem.width
        flickableDirection: Flickable.HorizontalAndVerticalFlick
        highlightFollowsCurrentItem: true
        highlight: highlightrec

        header: Row {
            z: 2
            spacing: 1
            function itemAt(index) { return repeater.itemAt(index) }
            Repeater {
                id: repeater
                model: ["GoodID", "WarehouseID", "SupplierID", "Amount", "Price", "Desciption"]
                Label {
                    text: modelData
                    color: "#ffffffff"
                    font.pixelSize: 20
                    padding: 10
                    width: 200
                    background: Rectangle { color: "#20B2AA"}
                }
            }
        }
        headerPositioning: ListView.OverlayHeader

        model: dbconnection.openGoodinfo().length
        delegate: Column {
            id: delegate
            property int row: index
            Row {
                spacing: 1
                Repeater {
                    model: 6
                    ItemDelegate {
                        property int column: index
                        width: view.headerItem.itemAt(column).width
                        text: qsTr(getItem(delegate.row, column))
                        function getItem(i, j){
                            if(j===0)
                                return dbconnection.openGoodinfo()[i].getGoodID
                            if(j===1)
                                return dbconnection.openGoodinfo()[i].getWarehouseID
                            if(j===2)
                                return dbconnection.openGoodinfo()[i].getSupplierID
                            if(j===3)
                                return dbconnection.openGoodinfo()[i].getAmount.toString()
                            if(j===4)
                                return dbconnection.openGoodinfo()[i].getPrice.toString()
                            if(j===5)
                                return dbconnection.openGoodinfo()[i].getDescription
                        }
                        highlighted: ListView.isCurrentItem
                        onClicked: {
                            view.currentIndex = delegate.row
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
    ToolBar {
        id: goodsToolBar
        x: 0
        y: 0
        width: parent.width
        height: 50
        Material.background: "#20B2AA"

        ToolButton {
            id: plusButton
            width: 60
            height: parent.height
            checkable: false
            autoExclusive: false
            focusPolicy: Qt.StrongFocus
            Image {
                id: plusImage
                x:parent.width/2-15
                y:parent.height/2-15
                width: 30
                height: 30
                source: "plus.png"
            }
        }

        ToolButton {
            id: deleteButton
            x: 60
            width: 60
            height: parent.height
            checkable: false
            autoExclusive: false
            focusPolicy: Qt.StrongFocus
            Image {
                id: deleteImage
                x:parent.width/2-15
                y:parent.height/2-15
                width: 30
                height: 30
                source: "reduce.png"
            }
        }

        ToolButton {
            id: undoButton
            x: 120
            width: 60
            height: parent.height
            checkable: false
            autoExclusive: false
            focusPolicy: Qt.StrongFocus
            Image {
                id: undoImage
                x:parent.width/2-15
                y:parent.height/2-17
                width: 30
                height: 34
                source: "undo.png"
            }
        }

        ToolButton {
            id: redoButton
            x: 180
            width: 60
            height: parent.height
            checkable: false
            autoExclusive: false
            focusPolicy: Qt.StrongFocus
            Image {
                id: redoImage
                x:parent.width/2-15
                y:parent.height/2-17
                width: 30
                height: 34
                source: "redo.png"
            }
        }
        ToolButton {
            id: saveButton
            x: parent.width - 60
            width: 60
            height: parent.height
            checkable: false
            autoExclusive: false
            focusPolicy: Qt.StrongFocus
            Image {
                id:saveImage
                x:parent.width/2-20
                y:parent.height/2-15
                width: 40
                height: 30
                source: "save.png"
            }
        }

        TextField {
            id: searchField
            x: parent.width - 200
            height: 50
            placeholderText: "Search"
            clip: true
            Material.accent: "#FFFFFF"
            Material.foreground: "#008080"
            color: "#ffffffff"
            selectByMouse: true
            font.capitalization: Font.MixedCase
            onEditingFinished: {
                for(var child in view.contentItem.children) {
                    console.log(view.contentItem.children[child])
                }
            }
        }
    }
    function getIndex(index){
        if(index >= 12)
            return index + 1
        else
            return index
    }
}
