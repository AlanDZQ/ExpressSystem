import QtQuick 2.11
import QtQuick.Controls 1.4 as C
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0

Item {
    ListView {
        id: peopleView
        anchors.topMargin: 50
        anchors.fill: parent
        contentWidth: headerItem.width
        flickableDirection: Flickable.HorizontalAndVerticalFlick

        header: Row {
            spacing: 1
            function itemAt(index) { return repeater.itemAt(index) }
            Repeater {
                id: repeater
                model: ["UserID", "Password", "Name", "Gender", "Age", "Privliege", "Salary", "Email", "Phone", "WagecardID"]
                Label {
                    text: modelData
                    color: "#ddffffff"
                    font.pixelSize: 20
                    padding: 10
                    width: 200
                    background: Rectangle { color: "#20B2AA"}
                }
            }
        }

        model: 100
        delegate: Column {
            id: delegate
            property int row: index
            Row {
                spacing: 1
                Repeater {
                    model: 10
                    ItemDelegate {
                        property int column: index
                        text: qsTr("%1x%2").arg(delegate.row).arg(column)
                        width: peopleView.headerItem.itemAt(column).width
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
        id: peopleToolBar
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
                y:parent.height/2-15
                width: 30
                height: 30
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
                y:parent.height/2-15
                width: 30
                height: 30
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
    }

    //删除col1中和itemData相等的值
    function remove(itemData) {
        var rowCount = listModel.count;
        for( var i = 0;i < rowCount;i++ ) {
            var data = listModel.get(i);
            if(data.value === itemData) {
                listModel.remove(i, 1);
            }
        }
    }
    //排序(这边我只用冒泡排了序号，后面的value2懒得一起排，也可以用ListModel.move来排序，这样可以一步到位)
    function sort(){
        var rowCount = listModel.count;
        for(var i = 0; i < rowCount; i++)
        {
            for(var j = 0; i + j < rowCount - 1; j++)
            {
                if(listModel.get(j).value > listModel.get(j+1).value)
                {
                    var temp = listModel.get(j).value;
                    listModel.get(j).value = listModel.get(j+1).value;
                    listModel.get(j+1).value = temp;
                }
            }
        }
    }
    //通过value查找value2
    function find(value1)
    {
        var rowCount = listModel.count;
        for( var i = 0;i < rowCount;i++ ) {
            var data = listModel.get(i);
            if(data.value === value1) {
                console.log(data.value2)
            }
        }
    }

}

