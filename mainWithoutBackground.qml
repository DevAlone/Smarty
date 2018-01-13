import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import smarty.input 1.0
import "constants.js" as Constants

ApplicationWindow {
    id: root
    visible: true
    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground
    x: Screen.width / 4
    y: isOnTheTop() ? Screen.height / 4 : Screen.height / 2
    width: mainWidget.width + closeButton.width
    height: Math.min(Screen.height / 2, mainWidget.getHeight())
    color: "#eee"

    // color: "#00000000"
    MainWidget {
        id: mainWidget
        // anchors.fill: parent
        width: Screen.width / 2
        height: parent.height
        spacing: 5
    }

    Button {
        x: mainWidget.x + mainWidget.width
        y: mainWidget.y
        width: Constants.itemHeight
        height: Constants.itemHeight

        id: closeButton
        text: "X"

        onClicked: app.close()
    }

    Behavior on y {
        NumberAnimation {
            duration: 500
            easing.type: Easing.OutBack
        }
    }

    onActiveChanged: {
        if (!active)
            app.close()
    }

    property bool _isOnTheTop: false

    function isOnTheTop() {
        var result = mainWidget.hasItems()
        if (result)
            _isOnTheTop = true

        return _isOnTheTop || result
    }
}
