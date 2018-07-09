import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0

Item {
    property string supplierID: ""
    property string name: ""
    property string address: ""
    property string email: ""
    property string phone: ""

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
                text: "Supplier Item: " + supplierID
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
                    x:parent.width/2-20
                    y:parent.height/2-15
                    width: 40
                    height: 30
                    source: "save.png"
                }
                onClicked: {
                    if(field1.text===""||field2.text===""||field3.text===""||field4.text===""){
                        warning3.visible=true
                    }else{
                        dboperator.editSupplierinfo(supplierID, field1.text, field2.text, field3.text, field4.text)
                        homeStackView.pop()
                        homeStackView.push("SupplierForm.qml")
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
        y: 50 + (parent.height-50)/10
        width: 200
        height: (parent.height-50)/10
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "name"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }


    TextField {
        id: field1
        x: parent.width/2-100
        y: 50+(parent.height-50)*2/10
        width: 200
        height: (parent.height-50)/10
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: name
    }

    Label {
        x: parent.width/2 - 100
        y: 50+(parent.height-50)*3/10
        width: 200
        height: (parent.height-50)/10
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "address"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }

    TextField {
        id: field2
        x: parent.width/2-100
        y: 50+(parent.height-50)*4/10
        width: 200
        height: (parent.height-50)/10
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: address
    }

    Label {
        x: parent.width/2 - 100
        y: 50+(parent.height-50)*5/10
        width: 200
        height: (parent.height-50)/10
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "Email"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }

    TextField {
        id: field3
        x: parent.width/2-100
        y: 50+(parent.height-50)*6/10
        width: 200
        height: (parent.height-50)/10
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: email
    }

    Label {
        x: parent.width/2 - 100
        y: 50+(parent.height-50)*7/10
        width: 200
        height: (parent.height-50)/10
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "Phone"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }

    TextField {
        id: field4
        x: parent.width/2-100
        y: 50+(parent.height-50)*8/10
        width: 200
        height: (parent.height-50)/10
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: phone
    }
}
