import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0

Item {
    ToolBar {
        id: toolBarTop
        x: 0
        y: 0
        width: window.width
        Material.background: "#20B2AA"
        ToolButton {
            x : parent.width - 300
            width: 200
            id: personButton
            text: qsTr("Personal Center")
        }

        ToolButton {
            x : parent.width - 100
            width: 100
            id: logoutButton
            text: qsTr("Log out")
            onClicked:stackView.pop()
        }
    }

    ToolBar {
        id: toolBarLeft
        x: 0
        y: 0
        width: 100
        height: window.height
        Material.background: "#008080"
        Label {
            y: 20
            width:100
            height:30
            id: logo
            x: 0
            text: qsTr("Logistics")
            horizontalAlignment: Text.AlignHCenter
            lineHeight: 0.4
            font.weight: Font.Bold
            font.family: "Arial"
            font.bold: true
            font.italic: true
            font.underline: true
            font.strikeout: true
            font.pointSize: 14
        }

        ToolButton {
            y: 50
            width:100
            height:50
            id: warehouseButton
            text: qsTr("stock")
            onClicked: stackView.push("WarehouseForm.qml")
        }

        ToolButton {
            y: 100
            width:100
            height:50
            id: goodsButton
            text: qsTr("goods")
            onClicked: stackView.push("GoodsForm.qml")
        }

        ToolButton {
            y: 150
            width:100
            height:50
            id: importButton
            text: qsTr("import")
            onClicked: stackView.push("ImportForm.qml")
        }

        ToolButton {
            y: 200
            width:100
            height:50
            id: exportButton
            text: qsTr("export")
            onClicked: stackView.push("ExportForm.qml")
        }

        ToolButton {
            y: 250
            width:100
            height:50
            id: peopleButton
            text: qsTr("people")
            onClicked: stackView.push("PeopleForm.qml")
        }
    }
}
