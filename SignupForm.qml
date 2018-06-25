import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0

Item {
    height: 500
    Button {
        id: backButton
        x: 8
        y: 8
        text: qsTr("< Back")
        font.bold: false
        font.family: "Arial"
        spacing: 0
        onClicked:stackView.pop()
    }

    TextField {
        id: nameField
        x: window.width/2 - 125
        y: window.height/2 - 100
        width: 250
        height: 50
        Material.accent: "#20B2AA"
        text: qsTr("")
        placeholderText: "Enter your name"
    }

    TextField {
        id: passwordField
        x: window.width/2 - 125
        y: window.height/2 - 25
        width: 250
        height: 50
        Material.accent: "#20B2AA"
        text: qsTr("")
        placeholderText: "Enter your password"
    }

    TextField {
        id: repasswordField
        x: window.width/2 - 125
        y: window.height/2 + 25
        width: 250
        height: 50
        Material.accent: "#20B2AA"
        text: qsTr("")
        placeholderText: "Confirm your password"
    }

    ToolBar {
        id: signupBar
        x: 0
        y: window.height - 50
        width: window.width
        height: 50
        Material.background: "#20B2AA"
        ToolButton {
            id: signupButton
            x: 0
            y: 0
            width: window.width
            height: 48
            text: qsTr("Signup")
            onClicked: {
                overTimer.stop();
                if (subWindow.visible === true) return;
                info.text= "Sign up successfully!"
                info.horizontalAlignment= Text.AlignHCenter
                subWindow.opacity = 0.0;
                subWindow.visible = true;
                downAnimation.start();
                showAnimation.start();
                overTimer.start();
                stackView.push("LoginForm.qml")
            }
        }
    }
}
