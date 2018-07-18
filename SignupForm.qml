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
        Material.background: "#20B2AA"
        Material.foreground: "#FFFFFF"
        onClicked:stackView.pop()
    }

//    TextField {
//        id: nameField
//        x: window.width/2 - 125
//        y: window.height/2 - 100
//        width: 250
//        height: 50
//        Material.accent: "#20B2AA"
//        text: qsTr("")
//        placeholderText: "Enter your name"
//    }

//    TextField {
//        id: passwordField
//        x: window.width/2 - 125
//        y: window.height/2 - 25
//        width: 250
//        height: 50
//        Material.accent: "#20B2AA"
//        text: qsTr("")
//        placeholderText: "Enter your password"
//    }

//    TextField {
//        id: repasswordField
//        x: window.width/2 - 125
//        y: window.height/2 + 25
//        width: 250
//        height: 50
//        Material.accent: "#20B2AA"
//        text: qsTr("")
//        placeholderText: "Confirm your password"
//    }
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


    Image {
        id: photo
        x: parent.width/6 - parent.width/8
        y: 100
        width: parent.width/4
        height: (parent.height-100)*3/5
        source: "default.png"
    }

    Label {
        x: parent.width/6 - 100
        y: 100 + photo.height
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "Name"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }


    TextField {
        id: field2
        x: parent.width/6-100
        y: 100 + photo.height + (parent.height-100)/10
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: name
    }

    Label {
        x: parent.width/2 - 100
        y: 100
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "password"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }

    TextField {
        id: field1
        x: parent.width/2-100
        y: 100+(parent.height-100)/10
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: password
    }

    Label {
        x: parent.width/2 - 100
        y: 100+(parent.height-100)/5
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "Gender"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }

    TextField {
        id: field3
        x: parent.width/2-100
        y: 100+(parent.height-100)*3/10
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: gender
    }

    Label {
        x: parent.width/2 - 100
        y: 100+(parent.height-100)*2/5
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "Age"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }

    TextField {
        id: field4
        x: parent.width/2-100
        y: 100+(parent.height-100)/2
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: age
    }

    Label {
        x: parent.width/2 - 100
        y: 100+(parent.height-100)*3/5
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "Privliege"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }

    TextField {
        id: field5
        x: parent.width/2-100
        y: 100+(parent.height-100)*7/10
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: privliege
    }

    Label {
        x: parent.width*5/6 - 100
        y: 100
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "Salary"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }

    TextField {
        id: field6
        x: parent.width*5/6-100
        y: 100 + (parent.height-100)/10
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: salary
    }

    Label {
        x: parent.width*5/6 - 100
        y: 100+(parent.height-100)/5
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "Email"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }

    TextField {
        id: field7
        x: parent.width*5/6-100
        y: 100 + (parent.height-100)*3/10
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: email
    }

    Label {
        x: parent.width*5/6 - 100
        y: 100+(parent.height-100)*2/5
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "Phone"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }

    TextField {
        id: field8
        x: parent.width*5/6-100
        y: 100 + (parent.height-100)/2
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: phone
    }

    Label {
        x: parent.width*5/6 - 100
        y: 100+(parent.height-100)*3/5
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        color: "#20B2AA"
        text: "WagecardID"
        font.bold: true
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignHCenter
    }

    TextField {
        id: field9
        x: parent.width*5/6-100
        y: 100+(parent.height-100)*7/10
        width: 200
        height: (parent.height-100)/10
        Material.accent: "#20B2AA"
        clip: true
        selectByMouse: true
        text: wagecardID
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
