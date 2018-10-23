import VPlay 2.0
import QtQuick 2.0
import QtQuick.Controls 2.1

import boardType 1.0

GameWindow {
    id: gameWindow

    property int boardSize

    // You get free licenseKeys from https://v-play.net/licenseKey
    // With a licenseKey you can:
    //  * Publish your games & apps for the app stores
    //  * Remove the V-Play Splash Screen or set a custom one (available with the Pro Licenses)
    //  * Add plugins to monetize, analyze & improve your apps (available with the Pro Licenses)
    //licenseKey: "<generate one from https://v-play.net/licenseKey>"

    // the size of the Window can be changed at runtime by pressing Ctrl (or Cmd on Mac) + the number keys 1-8
    // the content of the logical scene size (480x320 for landscape mode by default) gets scaled to the window size based on the scaleMode
    // you can set this size to any resolution you would like your project to start with, most of the times the one of your main target device
    // this resolution is for iPhone 4 & iPhone 4S
    screenWidth: 960
    screenHeight: 640


    Scene {
        id: scene

        // the "logical size" - the scene content is auto-scaled to match the GameWindow size
        width: 480
        height: 320

       Rectangle{
           id : backGround
           anchors.fill: parent
           color: "red"
       }
        // background rectangle matching the logical scene size (= safe zone available on all devices)
        // see here for more details on content scaling and safe zone: https://v-play.net/doc/vplay-different-screen-sizes/
        Text {
            id: initialText
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Select Board Size"
        }

        Grid {
            id : sizeSelectionGrid
            spacing: 2
            columns: 1

            anchors.centerIn: parent
            Rectangle { color: "orange"; width: 100; height: 40
                Text {
                    id: size6
                    anchors.centerIn: parent
                    text: qsTr("6 X 6")
                }
                MouseArea{
                    anchors.fill: parent
                            onClicked: { //generate 6x6 matrix
                                           scene.beginGame(6)
                                       }
                }
            }

            Rectangle { color: "green"; width: 100; height: 40
                Text {
                    id: size8
                    anchors.centerIn: parent
                    text: qsTr("8 X 8")
                }
                MouseArea{
                    anchors.fill: parent
                            onClicked: { //generate 8x8 matrix
                                           scene.beginGame(8)
                                       }
                }
            }

            Rectangle { color: "blue"; width: 100; height: 40
                Text {
                    id: size14
                    anchors.centerIn: parent
                    text: qsTr("14 X 14")
                }
                MouseArea{
                    anchors.fill: parent
                            onClicked: { //generate 14x14 matrix
                                            scene.beginGame(14)
                                       }
                }
            }
        }

        GridView {
            id : viewBoard
            anchors.centerIn: parent

            width: 20 * gameWindow.boardSize
            height: 20 * gameWindow.boardSize
            cellHeight: 20
            cellWidth: 20
            model: board.display
            delegate: Rectangle {
                height: 20
                width: 20
                color: modelData
                border.color: "white"
                border.width: 0.5

                MouseArea{
                    id: colorPicked
                    anchors.fill: parent
                    onClicked: board.flood = modelData
                }
            }
        }

        Board {
            id : board
            onGameFinished: {
                initialText.visible = true;
                initialText.text = "Congratulations! You did it in " + board.finished + " moves"
                sizeSelectionGrid.visible = true;
                viewBoard.visible = false;
            }
        }



        function beginGame(boardSize)
        {
            gameWindow.boardSize = boardSize;
            board.boardProperty = boardSize;
            initialText.text = "Color your way up";
            sizeSelectionGrid.visible = false;
            viewBoard.visible = true;
        }
    }
}
