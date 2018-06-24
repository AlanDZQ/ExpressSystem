import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.0
import DBConnection 1.0
import QtQuick.Controls.Material 2.0

ApplicationWindow { 

    DBConnection {
        id: dbconnection
    }

    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("System")
    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&New...") }
            Action {
                text: qsTr("&Open...")
                onTriggered: fileDialog.visible = true;
            }
            Action { text: qsTr("&Save") }
            Action { text: qsTr("Save &As...") }
            MenuSeparator { height: 20 }
            Action { text: qsTr("&Quit")
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: qsTr("&Edit")
            Action { text: qsTr("&Cut")
                onTriggered: nameField.cut()
            }
            Action { text: qsTr("&Copy")
                onTriggered: nameField.copy()}
            Action { text: qsTr("&Paste")
                onTriggered: nameField.paste()}
        }
        Menu {
            title: qsTr("&Help")
            Action { text: qsTr("&About")}
        }
    }

    Drawer {
        id: menu
        width: window.width * 0.40
        height: window.height
        edge: Qt.RightEdge
        Column {
            anchors.fill: parent
            ItemDelegate {
                text: qsTr("Page 1")
                width: parent.width
                onClicked: {
                    stackView.push("Page1Form.ui.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Page 2")
                width: parent.width
                onClicked: {
                    stackView.push("Page2Form.ui.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "LoginForm.qml"
        anchors.fill: parent
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
        }
        onRejected: {
            console.log("Canceled")
        }
        Component.onCompleted: visible = false
    }

    Timer{
            id: overTimer
            interval: 1000
            repeat: false
            onTriggered: {
                upAnimation.start();
                hideAnimation.start();
            }
        }

    PropertyAnimation{
            id: showAnimation
            target: subWindow
            properties:"opacity"
            from: 0.0
            to: 1.0
            duration: 500
        }

        PropertyAnimation{
            id: hideAnimation
            target: subWindow
            properties:"opacity"
            from: 1.0
            to: 0.0
            duration: 300
            onStopped: {
                subWindow.visible = false;
            }
        }

        PropertyAnimation{
            id: downAnimation
            target: subWindow
            properties:"y"
            duration: 300
        }

        PropertyAnimation{
            id: upAnimation
            target: subWindow
            properties:"y"
            duration: 300
        }

        Window{
            flags: Qt.FramelessWindowHint
            color: "#ffffff"
            id: subWindow
            visible: false
            height: 200
            width: 300
            Text {
                id: info
                color: "#6C6C6C"
                font.family: "Arial"
                font.pixelSize: 20
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                height: 200
                width: 300
            }
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    overTimer.stop();
                }
                onExited: {
                    overTimer.start();
                }
            }
        }
}
