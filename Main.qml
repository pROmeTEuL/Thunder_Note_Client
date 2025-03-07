import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Thunder Note")
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: NoteListView { }

    }
}
