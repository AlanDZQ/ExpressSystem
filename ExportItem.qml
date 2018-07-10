import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0

Item {
    id: exportItem
    property string eserialID: ""
    property string totalPrice: ""
    property string quality: ""
    property string userID: ""
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
                    if(totalPriceField.text===""||qualityField.text===""||userIDField.text===""
                            ||receiveNameField.text===""||receiveAddressField.text===""||receivePhoneField.text===""
                            ||remarkField.text===""){
                        warning3.visible=true
                    }else{
                        dboperator.editExport(eserialID,totalPriceField.text,qualityField.text,userIDField.text,
                                              receiveNameField.text,receiveAddressField.text,receivePhoneField.text,
                                              remarkField.text)
                        homeStackView.pop()
                        homeStackView.push("ExportForm.qml")
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
        var list = dboperator.searchExportGood(eserialID)
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
                                dboperator.delExportGood(eserialID, model1.get(view1.currentIndex).goodID)
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
                    width: exportItem.width/6
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
                    dboperator.editExportGood(eserialID, model1.get(view1.currentIndex).goodID, textField1.text)
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
            y: parent.height/2 - 75
            width: 250
            height: 50
            Material.accent: "#20B2AA"
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
                model4.clear()
                var list = dboperator.searchGoodW(comboBox2.currentText)
                for(var i = 0; i < list.length; i++){
                    model4.append({text: list[i].getGoodID})
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
                id: model4
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
            text: "Add Data"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                if(addField2.text===""||comboBox2.currentText===""||comboBox1.currentText==="")
                    addWarning1.visible = true
                else{
                    dboperator.addExportGood(eserialID, comboBox2.currentText, addField2.text)
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
                    dboperator.addEG(eserialID,  comboBox1.currentText, addField2.text,comboBox2.currentText)
                    addWarning1.visible = false
                    addPopup1.close()
                    refresh1()
                }
            }
        }

        Button {
            x: 341
            y: 204
            text: "Cancel"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                addPopup1.close()
            }
        }
    }

    Rectangle {
        color: "silver"
        x: exportItem.width/3
        width: 1
        height: exportItem.height
    }





















    ListModel {
        id: model2
        Component.onCompleted: refresh2()
    }

    function refresh2(){
        model2.clear()
        var list = dboperator.searchExportStatus(eserialID)
        for(var i = 0; i < list.length; i++){
            model2.append({"time": Qt.formatDateTime(list[i].getTime, "yyyy-MM-dd hh:mm:ss").toString(),
                           "status": list[i].getStatus})
        }
    }

    Component {
        id: delegate2
        Column {
            id: column2
            property int row: index
            Row {
                spacing: 1
                ItemDelegate {
                    width: view2.headerItem.itemAt(0).width
                    text: time
                }
                ItemDelegate {
                    width: view2.headerItem.itemAt(1).width
                    text: status
                    MouseArea {
                        anchors.fill: parent;
                        acceptedButtons: Qt.LeftButton | Qt.RightButton

                        onClicked: {
                            view2.currentIndex = column2.row
                            if (mouse.button === Qt.RightButton) {
                                contentMenu2.popup()
                            }else{
                                popup2.open()
                            }
                        }
                    }

                    Menu {
                        id: contentMenu2
                        MenuItem {
                            text: "Add"
                            onTriggered: {
                                addPopup2.open()
                            }
                        }
                        MenuItem {
                            text: "Delete"
                            onTriggered: {
                                dboperator.delExportStatus(eserialID, model2.get(view2.currentIndex).time)
                                refresh2()
                            }
                        }
                        MenuSeparator {}
                        MenuItem {
                            text: "Undo"
                            onTriggered: {
                                dboperator.undo()
                                refresh2()
                            }
                        }
                        MenuItem {
                            text: "Redo"
                            onTriggered: {
                                dboperator.redo()
                                refresh2()
                            }
                        }
                    }
                }
            }

            Rectangle {
                color: "silver"
                width: view2.headerItem.width
                height: 1
            }
        }
    }

    ListView {
        id: view2
        anchors.topMargin: 50
        anchors.leftMargin: exportItem.width*1/3
        anchors.fill: parent
        contentWidth: headerItem.width
        flickableDirection: Flickable.VerticalFlick
        highlightFollowsCurrentItem: true

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
                    width: exportItem.width/6
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
        model: model2
        delegate: delegate2
        ScrollIndicator.horizontal: ScrollIndicator { }
        ScrollIndicator.vertical: ScrollIndicator { }
    }


    Popup {
        id: popup2
        x: parent.width/2 - popup2.width/2
        y: parent.height/2 - popup2.height/2
        width: 530
        height: 300
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        Text {
            width: parent.width
            height: 40
            anchors.top: parent.top
            text: model2.get(view2.currentIndex).time
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
                    if(popup2.x + dlgX < 0){
                        popup2.x = 0
                    }
                    else if(popup2.x + dlgX > popup2.parent.width - popup2.width){
                        popup2.x = popup2.parent.width - popup2.width
                    }
                    else{
                        popup2.x = popup2.x + dlgX
                    }
                    if(popup2.y + dlgY < 0){
                        popup2.y = 0
                    }
                    else if(popup2.y + dlgY > popup2.parent.height - popup2.height){
                        popup2.y = popup2.parent.height - popup2.height
                    }
                    else{
                        popup2.y = popup2.y + dlgY
                    }
                }
            }
        }

        Label {
            id: warning2
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

        ComboBox {
            id: statusComboBox
            x: parent.width/2 - 125
            y: parent.height/2
            width: 250
            height: 50
            model: ["ORD", "REC", "DEL"]
            Material.accent: "#008080"
            displayText: model2.get(view2.currentIndex).status
        }

        Button {
            x: 103
            y: 204
            text: "ok"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                if(statusComboBox.currentText ==="")
                    warning2.visible = true
                else{
                    warning2.visible = false
                    dboperator.editExportStatus(eserialID, model2.get(view2.currentIndex).time,statusComboBox.currentText)
                    popup2.close()
                    refresh2()

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
                popup2.close()
            }
        }
    }


    Popup {
        id: addPopup2
        x: parent.width/2 - addPopup2.width/2
        y: parent.height/2 - addPopup2.height/2
        width: 530
        height: 300
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        Text {
            width: parent.width
            height: 40
            anchors.top: parent.top
            text:  "ADD NEW STATUS"
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
                    if(addPopup2.x + dlgX < 0){
                        addPopup2.x = 0
                    }
                    else if(addPopup2.x + dlgX > addPopup2.parent.width - addPopup2.width){
                        addPopup2.x = addPopup2.parent.width - addPopup2.width
                    }
                    else{
                        addPopup2.x = addPopup2.x + dlgX
                    }
                    if(addPopup2.y + dlgY < 0){
                        addPopup2.y = 0
                    }
                    else if(addPopup2.y + dlgY > addPopup2.parent.height - addPopup2.height){
                        addPopup2.y = addPopup2.parent.height - addPopup2.height
                    }
                    else{
                        addPopup2.y = addPopup2.y + dlgY
                    }
                }
            }
        }


        Label {
            id: addWarning2
            x: parent.width/2 - 125
            y: parent.height/2 - 75
            width: 250
            height: 50
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "TextField cannot be null"
            visible: false
        }


        TextField {
            id: addField3
            x: parent.width/2 - 125
            y: parent.height/2 - 50
            width: 250
            height: 50
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            placeholderText: "Enter the time (yyyy-MM-dd hh:mm:ss)"
        }

        RoundButton {
            id: roundButton1
            x: addField3.x + addField3.width + 10
            y: parent.height/2 - 50
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            text: "+"
            onClicked:{
                addField3.text = Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss")
            }
        }

        ComboBox {
            id: addStatusComboBox
            x: parent.width/2 - 125
            y: parent.height/2
            width: 250
            height: 50
            model: ["ORD", "REC", "DEL"]
            Material.accent: "#008080"
        }

        Button {
            x: 103
            y: 204
            text: "ok"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                if(addField3.text === ""||addStatusComboBox.currentText==="")
                    addWarning2.visible = true
                else{
                    dboperator.addExportStatus(eserialID, addField3.text, addStatusComboBox.currentText)
                    addWarning2.visible = false
                    addPopup2.close()
                    refresh2()
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
                addPopup2.close()
            }
        }
    }

    Rectangle {
        x: exportItem.width*2/3
        width: exportItem.width/3
        height: exportItem.height
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
            y: 50 + (parent.height-50)/15
            width: 200
            height: (parent.height-50)/15
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "Total Price"
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }


        TextField {
            id: totalPriceField
            x: parent.width/2-100
            y: 50+(parent.height-50)*2/15
            width: 200
            height: (parent.height-50)/15
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: totalPrice
        }

        Label {
            x: parent.width/2 - 100
            y: 50+(parent.height-50)*3/15
            width: 200
            height: (parent.height-50)/15
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "Quality"
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: qualityField
            x: parent.width/2-100
            y: 50+(parent.height-50)*4/15
            width: 200
            height: (parent.height-50)/15
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: quality
        }

        Label {
            x: parent.width/2 - 100
            y: 50+(parent.height-50)*5/15
            width: 200
            height: (parent.height-50)/15
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
            y: 50+(parent.height-50)*6/15
            width: 200
            height: (parent.height-50)/15
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: userID
        }

        Label {
            x: parent.width/2 - 100
            y: 50+(parent.height-50)*7/15
            width: 200
            height: (parent.height-50)/15
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "ReceiveName"
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: receiveNameField
            x: parent.width/2-100
            y: 50+(parent.height-50)*8/15
            width: 200
            height: (parent.height-50)/15
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: receiveName
        }

        Label {
            x: parent.width/2 - 100
            y: 50+(parent.height-50)*9/15
            width: 200
            height: (parent.height-50)/15
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "ReceiveAddress"
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: receiveAddressField
            x: parent.width/2-100
            y: 50+(parent.height-50)*10/15
            width: 200
            height: (parent.height-50)/15
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: receiveAddress
        }

        Label {
            x: parent.width/2 - 100
            y: 50+(parent.height-50)*11/15
            width: 200
            height: (parent.height-50)/15
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "ReceivePhone"
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: receivePhoneField
            x: parent.width/2-100
            y: 50+(parent.height-50)*12/15
            width: 200
            height: (parent.height-50)/15
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: receivePhone
        }

        Label {
            x: parent.width/2 - 100
            y: 50+(parent.height-50)*13/15
            width: 200
            height: (parent.height-50)/15
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "Remark"
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
        }

        TextField {
            id: remarkField
            x: parent.width/2-100
            y: 50+(parent.height-50)*14/15
            width: 200
            height: (parent.height-50)/15
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            text: remark
        }

    }

    Rectangle {
        color: "silver"
        x: exportItem.width*2/3
        width: 1
        height: exportItem.height
    }
}
