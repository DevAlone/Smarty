import QtQuick 2.9
import QtQuick.Controls 2.2
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
        onClicked: Qt.quit()
    }

    MainWidget {
        x: parent.width / 4
        y: isOnTheTop() ? parent.height / 4 : parent.height / 2 - getHeight()
        width: parent.width / 2
        height: Math.min(parent.height / 2, getHeight())
        spacing: 5

        Behavior on y {
            NumberAnimation {
                duration: 500
                //                easing.type: Easing.OutExpo
                easing.type: Easing.OutBack
            }
        }

        property bool _isOnTheTop: false

        function isOnTheTop() {
            var result = hasItems()
            if (result)
                _isOnTheTop = true

            return _isOnTheTop || result
        }
    }

    Button {
        x: parent.width - width
        y: 0
        z: 3
        width: 50
        height: 50
        text: "X"
        onClicked: app.close() // Qt.quit();
    }

    onActiveChanged: {
        if (!debug && !active)
            //            Qt.quit();
            app.close()
    }
}
