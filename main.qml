import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: root
    visible: true

    width: 320
    height: 580

    title: qsTr("GamePuzzleFifteen")

    background: BackgroundAnimatedGradient {
        anchors.fill: parent
    }

    //header:{}

    contentData: GameBoard {
        anchors.centerIn: parent

        width:  size - (size * 0.05)
        height:  size - (size * 0.05)
    }

    //footer: {}
}
