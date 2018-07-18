import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtQuick.Dialogs 1.0

Item {
    id:itemForm
    Component{
        id:highlightrec
        Rectangle{
            color: "#DCDCDC"
            radius: 5
            border.color: "#FFFFFF"
        }
    }

    ListModel {
        id: model1
        Component.onCompleted: refresh1()
    }

    function refresh1(){
        model1.clear()
        var list = dbconnection.openImportinfo()
        for(var i = 0; i < list.length; i++){
            model1.append({"iserialID": list[i].getIserialID,
                           "supplierID": list[i].getSupplierID,
                           "totalprice": list[i].getTotalprice.toString(),
                           "userID": list[i].getUserID,
                           "time": Qt.formatDateTime(list[i].getTime, "yyyy-MM-dd hh:mm:ss").toString()
                          })
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
                    text: iserialID
                    onClicked: {
                        view1.currentIndex = column1.row
                    }
                    onDoubleClicked: {
                        viewItem()
                    }
                }
                ItemDelegate {
                    width: view1.headerItem.itemAt(1).width
                    text: supplierID
                    onClicked: {
                        view1.currentIndex = column1.row
                    }
                    onDoubleClicked: {
                        viewItem()
                    }
                }
                ItemDelegate {
                    width: view1.headerItem.itemAt(2).width
                    text: totalprice
                    onClicked: {
                        view1.currentIndex = column1.row
                    }
                    onDoubleClicked: {
                        viewItem()
                    }
                }
                ItemDelegate {
                    width: view1.headerItem.itemAt(3).width
                    text: userID
                    onClicked: {
                        view1.currentIndex = column1.row
                    }
                    onDoubleClicked: {
                        viewItem()
                    }
                }
                ItemDelegate {
                    width: view1.headerItem.itemAt(4).width
                    text: time
                    onClicked: {
                        view1.currentIndex = column1.row
                    }
                    onDoubleClicked: {
                        viewItem()
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

    function viewItem(){
        if(!stackView.busy)
            homeStackView.push("ImportItem.qml",{
                                   iserialID: model1.get(view1.currentIndex).iserialID,
                                   supplierID: model1.get(view1.currentIndex).supplierID,
                                   totalprice: model1.get(view1.currentIndex).totalprice,
                                   userID: model1.get(view1.currentIndex).userID,
                                   time: model1.get(view1.currentIndex).time
                               })
    }

    ListView {
        id: view1
        anchors.topMargin: 50
        anchors.fill: parent
        contentWidth: headerItem.width
        flickableDirection: Flickable.HorizontalAndVerticalFlick
        highlightFollowsCurrentItem: true
        highlight: highlightrec
        header: Row {
            z: 2
            spacing: 1
            function itemAt(index) { return repeater1.itemAt(index) }
            Repeater {
                id: repeater1
                model: ["IserialID", "SupplierID", "Total Price", "UserID", "Time"]
                Label {
                    text: modelData
                    color: "#ffffffff"
                    font.pixelSize: 20
                    padding: 10
                    width: itemForm.width/5
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
        id: addPopup1
        x: parent.width/2 - addPopup1.width/2
        y: parent.height/2 - addPopup1.height/2
        width: 600
        height: 600
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        Text {
            width: parent.width
            height: 40
            anchors.top: parent.top
            text:  "ADD NEW ITEM"
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
            y: 50
            width: 250
            height: 50
            Material.accent: "#20B2AA"
            verticalAlignment: Text.AlignTop
            horizontalAlignment: Text.AlignHCenter
            clip: true
            color: "#20B2AA"
            text: "TextField cannot be null"
            visible: false
        }


        TextField {
            id: addField1
            x: parent.width/2 - 125
            y: parent.height/2 - 200
            width: 250
            height: 50
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            placeholderText: "Enter the IserialID"
        }

        TextField {
            id: addField2
            x: parent.width/2 - 125
            y: parent.height/2 - 150
            width: 250
            height: 50
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            placeholderText: "Enter the SupplierID"
        }

        TextField {
            id: addField3
            x: parent.width/2 - 125
            y: parent.height/2 - 100
            width: 250
            height: 50
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            placeholderText: "Enter the Total Price"
        }

        TextField {
            id: addField4
            x: parent.width/2 - 125
            y: parent.height/2 -50
            width: 250
            height: 50
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            placeholderText: "Enter the UserID"
        }

        TextField {
            id: addField5
            x: parent.width/2 - 125
            y: parent.height/2
            width: 250
            height: 50
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            placeholderText: "Enter the Time"
        }

        RoundButton {
            id: roundButton1
            x: addField5.x + addField5.width + 10
            y: parent.height/2
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            text: "+"
            onClicked:{
                addField5.text = Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss")
            }
        }

        Label {
            x: parent.width/2 - 125
            y: parent.height/2 + 50
            width: 100
            height: 25
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
            clip: true
            color: "#6C6C6C"
            text: "WarehouseID"
        }

        ComboBox {
            id: comboBox2
            x: parent.width/2 - 125
            y: parent.height/2 + 75
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
            y: parent.height/2 +50
            width: 100
            height: 25
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
            clip: true
            color: "#6C6C6C"
            text: "GoodID"
        }

        ComboBox {
            id: comboBox1
            x: parent.width/2 + 25
            y: parent.height/2 + 75
            width: 100
            height: 50
            model: ListModel {
                id: model2
            }
            Material.accent: "#008080"
        }

        TextField {
            id: addField6
            x: parent.width/2 - 125
            y: parent.height/2 + 125
            width: 250
            height: 50
            Material.accent: "#20B2AA"
            clip: true
            selectByMouse: true
            placeholderText: "Enter the amount"
        }

        Button {
            x: 50
            y: parent.height - 100
            text: "add data"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                if(addField1.text === ""||addField2.text===""||addField3.text===""||addField4.text===""||addField5.text===""||addField5.text===""||comboBox1.currentText==="")
                    addWarning1.visible = true
                else{
                    dboperator.addImportinfo(addField1.text, addField2.text, addField3.text, addField4.text, addField5.text)
                    addWarning1.visible = false
                    addPopup1.close()
                    refresh1()
                    overTimer.stop();
                    if (subWindow.visible === true) return;
                    info.text = "Add successfully!"
                    subWindow.opacity = 0.0;
                    subWindow.visible = true;
                    downAnimation.start();
                    showAnimation.start();
                    overTimer.start();
                }
            }
        }

        Button {
            x: 150
            y: parent.height - 100
            text: "Import Item"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                if(addField1.text === ""||addField2.text===""||addField3.text===""||addField4.text===""||addField5.text===""||addField5.text===""||comboBox1.currentText==="")
                    addWarning1.visible = true
                else{
                    dboperator.addImportFull(addField1.text, addField2.text, addField3.text, addField4.text, addField5.text, comboBox1.currentText,
                                             addField6.text, comboBox2.currentText)
                    addWarning1.visible = false
                    addPopup1.close()
                    refresh1()
                    overTimer.stop();
                    if (subWindow.visible === true) return;
                    info.text = "Add successfully!"
                    subWindow.opacity = 0.0;
                    subWindow.visible = true;
                    downAnimation.start();
                    showAnimation.start();
                    overTimer.start();
                }
            }
        }

        Button {
            x: parent.width - 150
            y: parent.height - 100

            text: "cancel"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                addPopup1.close()
            }
        }
    }

    Popup {
        id: deletePopup1
        x: parent.width/2 - deletePopup1.width/2
        y: parent.height/2 - deletePopup1.height/2
        width: 530
        height: 300
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        Text {
            width: parent.width
            height: 40
            anchors.top: parent.top
            text:  "DELETE ITEM"
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
                    if(deletePopup1.x + dlgX < 0){
                        deletePopup1.x = 0
                    }
                    else if(deletePopup1.x + dlgX > deletePopup1.parent.width - deletePopup1.width){
                        deletePopup1.x = deletePopup1.parent.width - deletePopup1.width
                    }
                    else{
                        deletePopup1.x = deletePopup1.x + dlgX
                    }
                    if(deletePopup1.y + dlgY < 0){
                        deletePopup1.y = 0
                    }
                    else if(deletePopup1.y + dlgY > deletePopup1.parent.height - deletePopup1.height){
                        deletePopup1.y = deletePopup1.parent.height - deletePopup1.height
                    }
                    else{
                        deletePopup1.y = deletePopup1.y + dlgY
                    }
                }
            }
        }


        Label {
            width: parent.width
            height: 100
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
            Material.accent: "#20B2AA"
            clip: true
            color: "#20B2AA"
            text: "Delete this item?"
        }

        Button {
            x: 103
            y: 204
            text: "Yes"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                dboperator.delImportinfo(model1.get(view1.currentIndex).iserialID)
                deletePopup1.close()
                refresh1()
                overTimer.stop();
                if (subWindow.visible === true) return;
                info.text = "Delete successfully!"
                subWindow.opacity = 0.0;
                subWindow.visible = true;
                downAnimation.start();
                showAnimation.start();
                overTimer.start();
            }
        }

        Button {
            x: 341
            y: 204
            text: "cancel"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                deletePopup1.close()
            }
        }
    }


    Popup{
        id:previewPopup
        x: parent.width/2 - previewPopup.width/2
        y: parent.height/2 - previewPopup.height/2
        width: 600
        height: 600
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        Text {
            width: parent.width
            height: 40
            anchors.top: parent.top
            text:  "PREVIEW"
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
                    if(previewPopup.x + dlgX < 0){
                        previewPopup.x = 0
                    }
                    else if(previewPopup.x + dlgX > previewPopup.parent.width - previewPopup.width){
                        previewPopup.x = previewPopup.parent.width - previewPopup.width
                    }
                    else{
                        previewPopup.x = previewPopup.x + dlgX
                    }
                    if(previewPopup.y + dlgY < 0){
                        previewPopup.y = 0
                    }
                    else if(previewPopup.y + dlgY > previewPopup.parent.height - previewPopup.height){
                        previewPopup.y = previewPopup.parent.height - previewPopup.height
                    }
                    else{
                        previewPopup.y = previewPopup.y + dlgY
                    }
                }
            }
        }

        ListModel {
            id: premodel
        }

        Component {
            id: predelegate
            Column {
                id: column1
                property int row: index
                Row {
                    spacing: 1
                    ItemDelegate {
                        width: preview.headerItem.itemAt(0).width
                        text: iserialID
                    }
                    ItemDelegate {
                        width: preview.headerItem.itemAt(1).width
                        text: supplierID
                    }
                    ItemDelegate {
                        width: preview.headerItem.itemAt(2).width
                        text: totalprice
                    }
                    ItemDelegate {
                        width: preview.headerItem.itemAt(3).width
                        text: userID
                    }
                    ItemDelegate {
                        width: preview.headerItem.itemAt(4).width
                        text: time
                    }
                }

                Rectangle {
                    color: "silver"
                    width: preview.headerItem.width
                    height: 1
                }
            }
        }

        ListView {
            id: preview
            anchors.topMargin: 50
            anchors.fill: parent
            contentWidth: headerItem.width
            flickableDirection: Flickable.HorizontalAndVerticalFlick
            highlightFollowsCurrentItem: true
            header: Row {
                z: 2
                spacing: 1
                function itemAt(index) { return prerepeater.itemAt(index) }
                Repeater {
                    id: prerepeater
                    model: ["IserialID", "SupplierID", "Total Price", "UserID", "Time"]
                    Label {
                        text: modelData
                        color: "#ffffffff"
                        font.pixelSize: 20
                        padding: 10
                        width: previewPopup.width/6
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
            model: premodel
            delegate: predelegate
            ScrollIndicator.horizontal: ScrollIndicator { }
            ScrollIndicator.vertical: ScrollIndicator { }
        }


        Button {
            x:100
            y: parent.height - 100
            text: "ReplaceDB"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                excelconnection.saveImportinfo(fileDialogIn.fileUrl)
                previewPopup.close()
                refresh1()
            }
        }


        Button {
            x: parent.width - 150
            y: parent.height - 100

            text: "cancel"
            Material.background: "#20B2AA"
            Material.foreground: "#FFFFFF"
            onClicked: {
                previewPopup.close()
            }
        }
    }



    ToolBar {
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
            onClicked: {
                addPopup1.open()
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
                deletePopup1.open()
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
            onClicked: {
                dboperator.undo()
                refresh1()
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
            onClicked: {
                dboperator.redo()
                refresh1()
            }
        }

        ToolButton {
            x: 240
            width: 60
            height: parent.height
            checkable: false
            autoExclusive: false
            focusPolicy: Qt.StrongFocus
            Image {
                x:parent.width/2-15
                y:parent.height/2-17
                width: 30
                height: 34
                source: "out.png"
            }
            onClicked: {
                fileDialogOut.open()
            }
        }

        FileDialog {
            id: fileDialogOut
            title: "Please choose a file"
            onAccepted: {
                console.log("You chose: " + fileDialogOut.fileUrl)
                excelconnection.dbtoExcel(5, fileDialogOut.fileUrl)
            }
            onRejected: {
                console.log("Canceled")
            }
            Component.onCompleted: visible = false
            selectExisting: false
        }

        ToolButton {
            x: 300
            width: 60
            height: parent.height
            checkable: false
            autoExclusive: false
            focusPolicy: Qt.StrongFocus
            Image {
                x:parent.width/2-15
                y:parent.height/2-17
                width: 30
                height: 34
                source: "in.png"
            }
            onClicked: {
                fileDialogIn.open()
            }
        }

        FileDialog {
            id: fileDialogIn
            title: "Please choose a file"
            onAccepted: {
                console.log("You chose: " + fileDialogIn.fileUrl)
                previewPopup.open()

                premodel.clear()
                var list = excelconnection.openImportinfo(fileDialogIn.fileUrl)
                for(var i = 0; i < list.length; i++){
                    premodel.append({"iserialID": list[i].getIserialID,
                                   "supplierID": list[i].getSupplierID,
                                   "totalprice": list[i].getTotalprice.toString(),
                                   "userID": list[i].getUserID,
                                   "time": Qt.formatDateTime(list[i].getTime, "yyyy-MM-dd hh:mm:ss").toString()
                                  })
                }

            }
            onRejected: {
                console.log("Canceled")
            }
            Component.onCompleted: visible = false
        }

        ToolButton {
            x: 360
            width: 60
            height: parent.height
            checkable: false
            autoExclusive: false
            focusPolicy: Qt.StrongFocus
            Image {
                x:parent.width/2-15
                y:parent.height/2-15
                width: 30
                height: 30
                source: "chart.png"
            }
            onClicked: {
                homeStackView.push("ImportChart.qml")
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
            onClicked: {
                search();
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
                search();
            }
        }

        ComboBox {
            id: sortBox
            x: parent.width - 360
            width: 150
            height: 50
            Material.accent: "#008080"
            Material.foreground: "#FFFFFF"
            model: ["IserialID", "SupplierID", "Total Price", "UserID", "Time"]
            onCurrentIndexChanged: {
                sort(currentIndex)
            }
        }
    }

    function sort(index){
        var keyWord
        switch(index){
        case 0: keyWord = "IserialID"
            break;
        case 1: keyWord = "SupplierID"
            break;
        case 2: keyWord = "TotalPrice"
            break;
        case 3: keyWord = "UserID"
            break;
        case 4: keyWord = "Time"
            break;
        }

        model1.clear()
        var list = dboperator.sortImport(keyWord)
        for(var i = 0; i < list.length; i++){
            model1.append({"iserialID": list[i].getIserialID,
                           "supplierID": list[i].getSupplierID,
                           "totalprice": list[i].getTotalprice.toString(),
                           "userID": list[i].getUserID,
                           "time": Qt.formatDateTime(list[i].getTime, "yyyy-MM-dd hh:mm:ss").toString()
                          })
        }
    }

    function search(){
        if (searchField.text === ""){
            refresh1()
        }else{
            model1.clear()
            var list = dboperator.searchImport(searchField.text)
            for(var i = 0; i < list.length; i++){
                model1.append({"iserialID": list[i].getIserialID,
                               "supplierID": list[i].getSupplierID,
                               "totalprice": list[i].getTotalprice.toString(),
                               "userID": list[i].getUserID,
                               "time": Qt.formatDateTime(list[i].getTime, "yyyy-MM-dd hh:mm:ss").toString()
                              })
            }
        }
    }
}
