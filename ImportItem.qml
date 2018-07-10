import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0

Item {
    id: importItem
    property string iserialID: ""
    property string supplierID: ""
    property string totalprice: ""
    property string userID: ""
    property string time: ""

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
                text: "Import Item: " + iserialID
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
                    if(supplierIDField.text===""||totalpriceField.text===""||userIDField.text===""||timeField.text===""){
                        warning3.visible=true
                    }else{
                        dboperator.editImportinfo(iserialID,supplierIDField.text,totalpriceField.text,userIDField.text,
                                              timeField.text)
                        homeStackView.pop()
                        homeStackView.push("ImportForm.qml")
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



    ListModel {
        id: model1
        Component.onCompleted: refresh1()
    }

    function refresh1(){
        model1.clear()
        var list = dboperator.searchImportGood(iserialID)
        for(var i = 0; i < list.length; i++){
            model1.append({"goodID": list[i].getGoodID,
                           "amount": list[i].getAmount.toString()})
        }
    }

    Component {
        id: delegate1
        Column {
            id: column1
            property int row: index
            Row {
                spacing: 1
                ItemDelegate {
                    width: view1.headerItem.itemAt(0).width
                    text: goodID
                }
                ItemDelegate {
                    width: view1.headerItem.itemAt(1).width
                    text: amount
                    MouseArea {
                        anchors.fill: parent;
                        acceptedButtons: Qt.LeftButton | Qt.RightButton

                        onClicked: {
                            view1.currentIndex = column1.row
                            if (mouse.button === Qt.RightButton) {
                                contentMenu1.popup()
                            }else{
                                popup1.open()
                            }
                        }
                    }

                    Menu {
                        id: contentMenu1
                        MenuItem {
                            text: "Add"
                            onTriggered: {
                                addPopup1.open()
                            }
                        }
                        MenuItem {
                            text: "Delete"
                            onTriggered: {
                                dboperator.delImportGoodinfo(iserialID, model1.get(view1.currentIndex).goodID)
                                refresh1()
                            }
                        }
                        MenuSeparator {}
                        MenuItem {
                            text: "Undo"
                            onTriggered: {
                                dboperator.undo()
                                refresh1()
                            }
                        }
                        MenuItem {
                            text: "Redo"
                            onTriggered: {
                                dboperator.redo()
                                refresh1()
                            }
                        }
                    }
                }
            }

            Rectangle {
                color: "silver"
                width: view1.headerItem.width
                height: 1
            }
        }
    }

    ListView {
        id: view1
        anchors.topMargin: 50
        anchors.fill: parent
        contentWidth: headerItem.width
        flickableDirection: Flickable.VerticalFlick
        highlightFollowsCurrentItem: true

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
                    width: importItem.width/4
                    background: Rectangle { color: "#20B2AA"}
                    MouseArea {
                        property point clickPoint: "0,0"

                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton
                        onPressed: {
                            clickPoint  = Qt.point(mouse.x, mouse.y)
                            parent.parent.parent.parent.flickableDirection = Flickable.VerticalFlick
                        }
                        onReleased: parent.parent.parent.parent.flickableDirection = Flickable.HorizontalAndVerticalFlick
                        onPositionChanged: {
                            var offset = Qt.point(mouse.x - clickPoint.x, mouse.y - clickPoint.y)
                            setDlgPoint(offset.x, offset.y)
                        }
                        function setDlgPoint(dlgX) {
                            if(width>=50||dlgX>0)
                                parent.width = parent.width + dlgX/100
                        }
                    }
                }
            }
        }
        headerPositioning: ListView.OverlayHeader
        model: model1
        delegate: delegate1
        ScrollIndicator.horizontal: ScrollIndicator { }
        ScrollIndicator.vertical: ScrollIndicator { }
    }

    Popup {
        id: popup1
        x: parent.width/2 - popup1.width/2
        y: parent.height/2 - popup1.height/2
        width: 530
        height: 300
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        Text {
            width: parent.width
            height: 40
            anchors.top: parent.top
            text:  model1.get(view1.currentIndex).goodID
            color: "#6C6C6C"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            MouseArea {
                property point clickPoint: "0,0"

                anchors.fill: parent
                acceptedButtons: Qt.LeftButton
                onPressed: {
                    clickPoint  = Qt.point(mouse.x, mouse.y)
                }
                onPositionChanged: {
                    var offset = Qt.point(mouse.x - clickPoint.x, mouse.y - clickPoint.y)
                    setDlgPoint(offset.x, offset.y)
                }
                function setDlgPoint(dlgX ,dlgY)
                {
                    //设置窗口拖拽不能超过父窗口
                    if(popup1.x + dlgX < 0){
                        popup1.x = 0
                    }
                    else if(popup1.x + dlgX > popup1.parent.width - popup1.width){
                        popup1.x = popup1.parent.width - popup1.width
                    }
                    else{
                        popup1.x = popup1.x + dlgX
                    }
                    if(popup1.y + dlgY < 0){
                        popup1.y = 0
                    }
                    else if(popup1.y + dlgY > popup1.parent.height - popup1.height){
                        popup1.y = popup1.parent.height - popup1.height
                    }
                    else{
                        popup1.y = popup1.y + dlgY
                    }
                }
            }
        }


        Label {
            id: warning1
            x: parent.width/2 - 125
            y: parent.height/2 - 50
            width: 250
            height: 50
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "TextField cannot be null"
            visible: false
        }


        TextField {
            id: textField1
            x: parent.width/2 - 125
            y: parent.height/2
            width: 250
            height: 50
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: model1.get(view1.currentIndex).amount
        }

        Button {
            x: 103
            y: 204
            text: "ok"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                if(textField1.text === "")
                    warning1.visible = true
                else{
                    warning1.visible = false
                    dboperator.editImportGoodinfo(iserialID, model1.get(view1.currentIndex).goodID, textField1.text)
                    popup1.close()
                    refresh1()
                }
            }
        }

        Button {
            x: 341
            y: 204
            text: "cancel"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                popup1.close()
            }
        }
    }


    Popup {
        id: addPopup1
        x: parent.width/2 - addPopup1.width/2
        y: parent.height/2 - addPopup1.height/2
        width: 530
        height: 300
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        Text {
            width: parent.width
            height: 40
            anchors.top: parent.top
            text:  "ADD NEW GOOD"
            color: "#6C6C6C"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            MouseArea {
                property point clickPoint: "0,0"

                anchors.fill: parent
                acceptedButtons: Qt.LeftButton
                onPressed: {
                    clickPoint  = Qt.point(mouse.x, mouse.y)
                }
                onPositionChanged: {
                    var offset = Qt.point(mouse.x - clickPoint.x, mouse.y - clickPoint.y)
                    setDlgPoint(offset.x, offset.y)
                }
                function setDlgPoint(dlgX ,dlgY)
                {
                    //设置窗口拖拽不能超过父窗口
                    if(addPopup1.x + dlgX < 0){
                        addPopup1.x = 0
                    }
                    else if(addPopup1.x + dlgX > addPopup1.parent.width - addPopup1.width){
                        addPopup1.x = addPopup1.parent.width - addPopup1.width
                    }
                    else{
                        addPopup1.x = addPopup1.x + dlgX
                    }
                    if(addPopup1.y + dlgY < 0){
                        addPopup1.y = 0
                    }
                    else if(addPopup1.y + dlgY > addPopup1.parent.height - addPopup1.height){
                        addPopup1.y = addPopup1.parent.height - addPopup1.height
                    }
                    else{
                        addPopup1.y = addPopup1.y + dlgY
                    }
                }
            }
        }


        Label {
            id: addWarning1
            x: parent.width/2 - 125
            y: parent.height/2 - 100
            width: 250
            height: 50
            Material.accent: "#20B2AA"
            horizontalAlignment: Text.AlignHCenter
            clip: true
            color: "#20B2AA"
            text: "TextField cannot be null"
            visible: false
        }

        Label {
            x: parent.width/2 - 125
            y: parent.height/2 - 100
            width: 100
            height: 50
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
            clip: true
            color: "#6C6C6C"
            text: "WarehouseID"
        }

        ComboBox {
            id: comboBox2
            x: parent.width/2 - 125
            y: parent.height/2-50
            width: 100
            height: 50
            model: ListModel {
                id: model3
            }
            Material.accent: "#008080"
            Component.onCompleted: {
                model3.clear()
                var list = dbconnection.openWarehouseinfo()
                for(var i = 0; i < list.length; i++){
                    model3.append({text: list[i].getWarehouseID})
                }
            }
            onCurrentTextChanged: {
                model2.clear()
                var list = dboperator.searchGoodW(comboBox2.currentText)
                for(var i = 0; i < list.length; i++){
                    model2.append({text: list[i].getGoodID})
                }
            }
        }

        Label {
            x: parent.width/2 + 25
            y: parent.height/2 - 100
            width: 100
            height: 50
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
            clip: true
            color: "#6C6C6C"
            text: "GoodID"
        }

        ComboBox {
            id: comboBox1
            x: parent.width/2 + 25
            y: parent.height/2 - 50
            width: 100
            height: 50
            model: ListModel {
                id: model2
            }
            Material.accent: "#008080"
        }


        TextField {
            id: addField2
            x: parent.width/2 - 125
            y: parent.height/2
            width: 250
            height: 50
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            placeholderText: "Enter the amount"
        }

        Button {
            x: 103
            y: 204
            text: "Add data"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                if(addField2.text===""||comboBox2.currentText===""||comboBox1.currentText==="")
                    addWarning1.visible = true
                else{
                    dboperator.addImportGoodinfo(iserialID, comboBox1.currentText, addField2.text)
                    addWarning1.visible = false
                    addPopup1.close()
                    refresh1()
                }
            }
        }

        Button {
            x: 200
            y: 204
            text: "Add Good"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                if(addField2.text===""||comboBox2.currentText===""||comboBox1.currentText==="")
                    addWarning1.visible = true
                else{
                    dboperator.addIG(iserialID, comboBox1.currentText, addField2.text, comboBox2.currentText)
                    addWarning1.visible = false
                    addPopup1.close()
                    refresh1()
                }
            }
        }

        Button {
            x: 341
            y: 204
            text: "cancel"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                addPopup1.close()
            }
        }
    }


    Rectangle {
        x: importItem.width/2
        width: importItem.width/2
        height: importItem.height
        color: "#FAFAFA"

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
            y: 50 + (parent.height-50)/11
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
            id: supplierIDField
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
            text: "Totalprice"
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: totalpriceField
            x: parent.width/2-100
            y: 50+(parent.height-50)*4/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: totalprice
        }

        Label {
            x: parent.width/2 - 100
            y: 50+(parent.height-50)*5/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "UserID"
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: userIDField
            x: parent.width/2-100
            y: 50+(parent.height-50)*6/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: userID
        }

        Label {
            x: parent.width/2 - 100
            y: 50+(parent.height-50)*7/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "Time"
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: timeField
            x: parent.width/2-100
            y: 50+(parent.height-50)*8/11
            width: 200
            height: (parent.height-50)/11
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: time
        }

    }

    Rectangle {
        color: "silver"
        x: importItem.width/2
        width: 1
        height: importItem.height
    }
}
