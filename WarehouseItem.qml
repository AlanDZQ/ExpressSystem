import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0

Item {
    property string warehouseID: ""
    property string userID: ""
    property string address: ""

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
                text: "Warehouse Item: " + warehouseID
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
                    if(field1.text===""||field2.text===""){
                        warning3.visible=true
                    }else{
                        dboperator.editWarehouseinfo(warehouseID, field1.text,field2.text)
                        homeStackView.pop()
                        homeStackView.push("WarehouseForm.qml")
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
        y: 50 + (parent.height-50)/7
        width: 200
        height: (parent.height-50)/7
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "UserID"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }


    TextField {
        id: field1
        x: parent.width/2-100
        y: 50+(parent.height-50)*2/7
        width: 200
        height: (parent.height-50)/7
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: userID
    }

    Label {
        x: parent.width/2 - 100
        y: 50+(parent.height-50)*3/7
        width: 200
        height: (parent.height-50)/7
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "Address"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }

    TextField {
        id: field2
        x: parent.width/2-100
        y: 50+(parent.height-50)*4/7
        width: 200
        height: (parent.height-50)/7
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: address
    }
}
