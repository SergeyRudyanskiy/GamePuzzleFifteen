import QtQuick 2.12
import GamePuzzleFifteen 1.0

GridView {
    id: root
    interactive: false

    property int size: Math.min(parent.width, parent.height)

    width: size
    height: size

    cellWidth: width / root.model.board_dimension
    cellHeight: height / root.model.board_dimension

    model: GameBordModel {}

    PopupMessage {}

    delegate: Item {
        id: _delegate_tile_placeholder
        visible: display !== root.model.hidden_element_value

        width: root.cellWidth
        height: root.cellHeight

        TileFifteen {
            display_text: display
            anchors.margins: 2

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    //index is attached property
                    root.model.move_tile(index);
                }
            }
        }
    }
}
