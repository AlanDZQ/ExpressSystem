import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0

Item {
    id: exportItem
    property string goodID: ""
    property string warehouseID: ""
    property string supplierID: ""
    property string amount: ""
    property string price: ""
    property string description: ""
    property string location: ""

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
                text: "Good Item: " + goodID + " at Warehouse: " + warehouseID
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                focusPolicy: Qt.StrongFocus
                width: 60
                height: parent.height
                Image {
                    id: viewImage
                    x:parent.width/2-20
                    y:parent.height/2-15
                    width: 40
                    height: 30
                    source: "save.png"
                }
                onClicked: {
                    if(field2.text===""||field3.text===""
                            ||field4.text===""||field5.text===""||field6.text===""){
                        warning3.visible=true
                    }else{
                        dboperator.editGoodinfo(goodID,warehouseID,field2.text,field3.text,field4.text,field5.text,field6.text)
                        homeStackView.pop()
                        homeStackView.push("GoodsForm.qml")
                        overTimer.stop();
                        if (subWindow.visible === true) return;
                        info.text = "Saved successfully!"
                        subWindow.opacity = 0.0;
                        subWindow.visible = true;
                        downAnimation.start();
                        showAnimation.start();
                        overTimer.start();
                    }
                }
            }
        }
    }


        Label {
            id: warning3
            x: parent.width/2 - 100
            y: 50
            width: 200
            height: 50
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "TextField cannot be null"
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
            visible: false
        }


        Label {
            x: parent.width/2 - 100
            y: 50+(parent.height-50)/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "SupplierID"
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: field2
            x: parent.width/2-100
            y: 50+(parent.height-50)*2/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: supplierID
        }

        Label {
            x: parent.width/2 - 100
            y: 50+(parent.height-50)*3/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "Amount"
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: field3
            x: parent.width/2-100
            y: 50+(parent.height-50)*4/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: amount
        }

        Label {
            x: parent.width/2 - 100
            y: 50+(parent.height-50)*5/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "Price"
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: field4
            x: parent.width/2-100
            y: 50+(parent.height-50)*6/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: price
        }

        Label {
            x: parent.width/2 - 100
            y: 50+(parent.height-50)*7/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "Description"
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: field5
            x: parent.width/2-100
            y: 50+(parent.height-50)*8/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: description
        }

        Label {
            x: parent.width/2 - 100
            y: 50+(parent.height-50)*9/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "Location"
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: field6
            x: parent.width/2-100
            y: 50+(parent.height-50)*10/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: location
        }
}
