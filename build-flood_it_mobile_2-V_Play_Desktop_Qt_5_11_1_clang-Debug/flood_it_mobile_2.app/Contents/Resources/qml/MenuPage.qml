import QtQuick.Controls 2.1
import VPlay 2.0
import QtQuick 2.0

StackView {
    id: stack
    initialItem: view

    Component {
        id: view

        MouseArea {
            Text {
                text: stack.depth
                anchors.centerIn: parent
            }
            onClicked: stack.push(view)
        }
    }
}
