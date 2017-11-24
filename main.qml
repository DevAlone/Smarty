import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import smarty.input 1.0
import "constants.js" as Constants

ApplicationWindow {
    id: root
    visible: true
    visibility: Window.FullScreen
    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground

    color: "#7f000000"

    MouseArea {
        anchors.fill: parent
        onClicked: Qt.quit();
//        propagateComposedEvents: false
    }

    MainWidget {
        x: parent.width / 4
        y: parent.height / 2 - Constants.itemHeight / 2
        width: parent.width / 2
        height: parent.height / 2  // - Constants.itemHeight / 2
    }

    Button {
        x: parent.width - width
        y: 0
        z: 3
        width: 50
        height: 50
        text: "X"
        onClicked: Qt.quit();
    }


}

