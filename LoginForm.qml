import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Material 2.0

Item {
    ToolBar {
        id: loginToolBar
        x: 0
        y: window.height - 50
        width: window.width
        height: 50
        position: ToolBar.Footer
        font.family: "Arial"
        Material.background: "#20B2AA"

        ToolButton {
            id: loginButton
            x: 0
            y: 0
            width: window.width/2
            height: 50
            text: qsTr("Login")
            onClicked: {
                if(dbconnection.checkLogin(nameField.text, passwordField.text)){
                    stackView.push("HomeForm.qml")
                    overTimer.stop();
                    if (subWindow.visible === true) return;
                    info.text= "Welcome back " + nameField.text
                    subWindow.opacity = 0.0;
                    subWindow.visible = true;
                    downAnimation.start();
                    showAnimation.start();
                    overTimer.start();
                }else{
                    overTimer.stop();
                    if (subWindow.visible === true) return;
                    info.text= "wrong password!"
                    subWindow.opacity = 0.0;
                    subWindow.visible = true;
                    downAnimation.start();
                    showAnimation.start();
                    overTimer.start();
                }

            }
        }

        ToolButton {
            id: signupButton
            x: window.width/2
            y: 0
            width: window.width/2
            height: 50
            text: qsTr("Signup");
            onClicked: {
                stackView.push("SignupForm.qml")
            }
        }
    }

    Label {
        id: logo
        x: window.width/2 - 65
        y: window.height/2 - 180
        text: qsTr("Logistics")
        color: "#20B2AA"
        font.strikeout: true
        font.underline: true
        font.italic: true
        font.bold: true
        font.weight: Font.Bold
        font.pointSize: 31
    }

    TextField {
        id: nameField
        x: window.width/2 - 125
        y: window.height/2 - 25
        width: 250
        height: 50
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        placeholderText: "Enter your name"
    }

    TextField {
        id: passwordField
        x: window.width/2 - 125
        y: window.height/2+25
        width: 250
        height: 50
        Material.accent: "#20B2AA"
        clip: true
        placeholderText: "Enter your password"
        echoMode: TextInput.Password
    }
}
