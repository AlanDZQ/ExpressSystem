import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0

Item {
    ToolBar {
        width: window.width
        Material.background: "#20B2AA"
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTr("‹")
                font.pointSize: 20
                font.bold: true
                onClicked: stackView.pop()
            }
            Label {
                text: "Export Management"
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                text: qsTr("⋮")
                font.pointSize: 20
                font.bold: true
                onClicked: menu.open()
            }
        }
    }
}
