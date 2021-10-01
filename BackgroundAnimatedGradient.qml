import QtQuick 2.12

Rectangle {
    id: _back_ground_gradient
    anchors.fill: parent

    gradient: Gradient {
        GradientStop {
            position: 0.0
            SequentialAnimation on color {
                loops: Animation.Infinite
                ColorAnimation { from: "steelblue"; to: "lightgreen"; duration: 3000 }
                ColorAnimation { from: "lightgreen"; to: "steelblue"; duration: 3000 }
            }
        }
        GradientStop {
            position: 1.0
            SequentialAnimation on color {
                loops: Animation.Infinite
                ColorAnimation { from: "lightgreen"; to: "darksalmon"; duration: 3000 }
                ColorAnimation { from: "darksalmon"; to: "lightgreen"; duration: 3000 }
            }
        }
    }
}
