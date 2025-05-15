import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

Item {
    ListView {
        id: noteListView

        property int pullThreshold: 60
        property bool refreshing: false

        anchors.fill: parent
        anchors.margins: 25
        anchors.bottomMargin: 10
        clip: true
        model:  _noteModel
        delegate: RowLayout {
            id: noteDelgate
            width: noteListView.width
            Label {
                text: model._note
            }
            Item {
                Layout.fillWidth: true
            }
            Label {
                text: model._date
                Layout.rightMargin: 10
            }
            Button {
                text: "Erase"
                onClicked: {
                    confirmDialog.itemIndex = index;
                    confirmDialog.open();
                }
            }
            TapHandler {
                onTapped: stackView.push("EditNote.qml", {"index": index, "note": model._fullNote})
            }
        }
        onContentYChanged: {
            if (contentY < -pullThreshold && !refreshing && dragging) {
                refreshing = true
            } else if (!contentY && refreshing) {
                refreshing = false
                _noteModel.refresh()
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
    Dialog {
        property int itemIndex: -1
        id: confirmDialog
        title: "Confirm Deletion"
        anchors.centerIn: parent
        modal: true
        standardButtons: Dialog.Yes | Dialog.No
        onAccepted: _noteModel.erase(itemIndex)
        contentItem: Text {
            text: "Are you sure you want to delete this note?"
            color: "white"
            wrapMode: Text.Wrap
        }
    }
}
