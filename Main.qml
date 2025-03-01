import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    ListView {
        anchors.fill: parent
        clip: true
    }
    RoundButton {
        anchors {
            bottomMargin: 10
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        text: "+"
    }
}
