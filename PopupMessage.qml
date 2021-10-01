import QtQuick 2.0
import QtQuick.Controls 2.12
import GamePuzzleFifteen 1.0

Item {
    id: window
    width: 400
    height: 400
    visible: true
    anchors.centerIn: parent

    Button {
        text: "Open"
        onClicked: popup.open()
    }
    Button {
        text: "Shufle"
        onClicked: model.shuffle()
    }

    Popup {
        id: popup
        anchors.centerIn: parent
        width: 200
        height: 300
        modal: true
        focus: true

        Text {
            id: name
            text: qsTr("Hello")
        }

        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    }
}
