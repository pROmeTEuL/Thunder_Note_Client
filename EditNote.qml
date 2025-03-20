import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Frame {
    id: root
    property int index: -1
    property string note
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        RowLayout {
            Layout.fillWidth: true
            RoundButton {
                text: "←"
                font.pixelSize: 16
                onClicked: {
                    stackView.pop()
                    console.log("Back")
                }
            }
            Item {
                Layout.fillWidth: true
            }
            RoundButton {
                text: "✓"
                font.pixelSize: 16
                onClicked: {
                    if (index === -1) {
                        _noteModel.add(textArea.text)
                    } else {
                        _noteModel.edit(index, textArea.text)
                    }
                    stackView.pop()
                    console.log("Save")
                }
            }
        }
        TextArea {
            id: textArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            placeholderText: "Your note goes here"
            text: root.note
        }
    }
}
