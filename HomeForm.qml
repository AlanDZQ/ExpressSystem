import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0

Item {
    property string userID: ""
    StackView {
        id: homeStackView
        x: toolBarLeft.width
        width: parent.width - toolBarLeft.width
        height: parent.height
        initialItem:
            Text {
            id: homeInfo
            color: "#6C6C6C"
            font.family: "Arial"
            font.pixelSize: 20
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            height: parent.height
            width: parent.width
            text:"Click left hand bar to do something"
        }
    }

    ToolBar {
        id: toolBarLeft
        x: 0
        y: 0
        width: 100
        height: window.height
        Material.background: "#008080"
        Material.accent: "#20B2AA"
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
            checkable: true
            autoExclusive: true
            onClicked: homeStackView.push("WarehouseForm.qml")
        }

        ToolButton {
            y: 100
            width:100
            height:50
            id: goodsButton
            text: qsTr("goods")
            autoExclusive: true
            checkable: true
            onClicked: homeStackView.push("GoodsForm.qml")
        }

        ToolButton {
            y: 150
            width:100
            height:50
            id: importButton
            text: qsTr("import")
            autoExclusive: true
            checkable: true
            onClicked: homeStackView.push("ImportForm.qml")
        }

        ToolButton {
            y: 200
            width:100
            height:50
            id: exportButton
            text: qsTr("export")
            autoExclusive: true
            checkable: true
            onClicked: homeStackView.push("ExportForm.qml")
        }

        ToolButton {
            y: 250
            width:100
            height:50
            id: peopleButton
            text: qsTr("people")
            autoExclusive: true
            checkable: true
            onClicked: homeStackView.push("PeopleForm.qml")
        }

        ToolButton {
            y: 300
            width:100
            height:50
            id: supplierButton
            text: qsTr("supplier")
            autoExclusive: true
            checkable: true
            onClicked: homeStackView.push("SupplierForm.qml")
        }

        ToolButton {
            y: parent.height-100
            width: 100
            height:50
            id: personButton
            Image {
                id: userImage
                x:40
                y:parent.height/2-10
                width: 20
                height: 20
                source: "user.png"
            }
            onClicked: homeStackView.push("PeopleItem.qml",{
                                          userID: userID
                                      })

        }

        ToolButton {
            y: parent.height-50
            width: 100
            height:50
            id: logoutButton
            Image {
                id: logoutImage
                x:40
                y:parent.height/2-10
                width: 20
                height: 20
                source: "logout.png"
            }
            onClicked:stackView.pop()
        }
    }
}
