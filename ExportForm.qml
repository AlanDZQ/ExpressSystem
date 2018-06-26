import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0

Item {
    ListView {
        id: view
        anchors.topMargin: 50
        anchors.fill: parent
        contentWidth: headerItem.width
        flickableDirection: Flickable.HorizontalAndVerticalFlick

        header: Row {
            spacing: 1
            function itemAt(index) { return repeater.itemAt(index) }
            Repeater {
                id: repeater
                model: ["EserialID", "Total Price", "Quality", "UserID", "Time", "Receive Name", "Receive Address", "Receive Phone", "Status", "Remark"]
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

        model: dbconnection.openExportinfo().length
        delegate: Column {
            id: delegate
            property int row: index
            Row {
                spacing: 1
                Repeater {
                    model: 10
                    ItemDelegate {
                        property int column: index
                        width: view.headerItem.itemAt(column).width
                        text: qsTr(getItem(delegate.row, column))
                        function getItem(i, j){
                            if(j===0)
                                return dbconnection.openExportinfo()[i].getEserialID
                            if(j===1)
                                return dbconnection.openExportinfo()[i].getTotalprice.toString()
                            if(j===2)
                                return dbconnection.openExportinfo()[i].getQuality.toString()
                            if(j===3)
                                return dbconnection.openExportinfo()[i].getUserID
                            if(j===4)
                                return dbconnection.openExportinfo()[i].getTime.toString()
                            if(j===5)
                                return dbconnection.openExportinfo()[i].getReceivename
                            if(j===6)
                                return dbconnection.openExportinfo()[i].getReceiveaddress
                            if(j===7)
                                return dbconnection.openExportinfo()[i].getReceivephone
                            if(j===8)
                                return dbconnection.openExportinfo()[i].getStatus
                            if(j===9)
                                return dbconnection.openExportinfo()[i].getRremark
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
        id: exportToolBar
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
        }
    }
}
