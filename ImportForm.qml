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
                model: ["IserialID", "SupplierID", "Total Price", "UserID", "Time"]
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

        model: dbconnection.openImportinfo().length

        delegate: Column {
            id: delegate
            property int row: index
            Row {
                id: row
                spacing: 1
                Repeater {
                    id: repeater2
                    model: 7
                    ItemDelegate {
                        id:itemDelegate
                        property int column: index
                        width: view.headerItem.itemAt(column).width
                        text: qsTr(getItem(delegate.row, column, dbconnection.openImportinfo()))
                        function getItem(i, j, list){
                            if(j===0)
                                return list[i].getIserialID
                            if(j===1)
                                return list[i].getSupplierID
                            if(j===2)
                                return list[i].getTotalprice.toString()
                            if(j===3)
                                return list[i].getUserID
                            if(j===4)
                                return list[i].getTime.toString()
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
        id: importToolBar
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
            onClicked:{
                console.log(view.contentItem.children[getIndex(view.currentIndex+1)].children[0].children[0].text)
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
            id: viewButton
            x: parent.width - 60
            width: 60
            height: parent.height
            checkable: false
            autoExclusive: false
            focusPolicy: Qt.StrongFocus
            Image {
                id: viewImage
                x:parent.width/2-15
                y:parent.height/2-15
                width: 30
                height: 30
                source: "view.png"
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
            }
        }

        ComboBox {
            id: sortBox
            x: parent.width - 400
            width: 150
            height: 50
            Material.accent: "#008080"
            Material.foreground: "#FFFFFF"
            model: ["DefaultSort", "IserialID", "SupplierID", "GoodID", "Amount", "Total Price", "UserID", "Time"]
        }
    }

    function getIndex(index){
        if(index >= 12)
            return index + 1
        else
            return index
    }
}
