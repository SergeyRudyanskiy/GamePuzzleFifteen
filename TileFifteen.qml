import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

Item {
    id: root
    anchors.fill: parent

    property string display_text: ""
    property int size: Math.min(root.width,root.height)

    function func_scale_font() {
        var min_size = Math.min(root.width,root.height);

        if (min_size === root.width) {
            if(root.width < root.size) {
                return root.size / 16 // we need 20pt and appWndW 320
            }
            return root.width / 16
        }
    }

    Button {
        id: _root_button

        property string display_text: ""
        property color backgroundDefaultColor: "#2B99B9"
        property color backgroundPressedColor: Qt.darker(backgroundDefaultColor, 1.2)
        property color contentItemTextColor: "white"

        anchors.fill: parent
        text: "Button"

        contentItem: Text {
            text: root.display_text
            color:  _root_button.contentItemTextColor

            font.pixelSize: 8 * func_scale_font()
            font.family: "Segoe UI Light"
            font.weight: Font.Thin

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            implicitWidth: 40
            implicitHeight: 40

            color: _root_button.down ? _root_button.backgroundPressedColor : _root_button.backgroundDefaultColor
            radius: 8

            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                color: "black"
                samples: 16
            }
        }
    }
}
