import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    ListView {
        id: noteListView
        anchors.fill: parent
        anchors.margins: 25
        anchors.bottomMargin: 10
        clip: true
        model:  _noteModel
        delegate: RowLayout {
            id: noteDelgate
            width: noteListView.width
            Label {
                // required property string title
                text: model._note
            }
            Label {
                // required property string entryDate
                text: model._date
            }
            Item {
                Layout.fillWidth: true

            }
            Button {
                text: "Erase"
                onClicked: _noteModel.erase(index)
            }
            TapHandler {
                onTapped: stackView.push("EditNote.qml", {"index": index, "note": model._note})
            }
        }
        RoundButton {
            anchors {
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }
            text: "+"
            onClicked: stackView.push("EditNote.qml")
        }
    }
}
