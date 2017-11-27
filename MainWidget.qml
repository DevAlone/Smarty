import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls.Styles 1.4
import smarty.input 1.0
import smarty.models 1.0
import "constants.js" as Constants

Item {
    ColumnLayout {
        // anchors.fill: parent
        y: itemsView.count > 0 ? parent.height / 4 : parent.height / 2
        width: parent.width
        height: parent.height / 2

        spacing: 5

        Behavior on y {
            NumberAnimation {
                duration: 500
                //                easing.type: Easing.OutExpo
                easing.type: Easing.OutBack
            }
        }

        Rectangle {
            z: 5
            height: Constants.itemHeight
            color: Constants.itemColor
            border.color: Constants.itemBorderColor
            border.width: Constants.itemBorderWidth
            Layout.fillWidth: true

            TextField {
                id: mainInput
                x: parent.border.width
                y: parent.border.width
                width: parent.width - 2 * parent.border.width
                height: parent.height - 2 * parent.border.width
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                //                font.pointSize: Constants.textItemDataFontSize
                selectByMouse: true
                focus: true
                onFocusChanged: focus = true;

                Keys.onPressed: {
                    if (event.key === Qt.Key_Down)
                        itemsView.сurrentIndexAdd(1);
                    else if (event.key === Qt.Key_Up)
                        itemsView.currentIndexDeduct(1);
                    else if (event.key === Qt.Key_PageDown)
                        itemsView.сurrentIndexAdd(10);
                    else if (event.key === Qt.Key_PageUp)
                        itemsView.currentIndexDeduct(10);
                    else if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return) {
                        itemsView.doCurrentItemAction();
                    }
                    else if (inputProcessor.processKey(event.key))
                        event.accepted = true;
                }
                onTextChanged: inputProcessor.processInput(text);

                background: Rectangle {
                    color: Constants.itemColor
                }
            }
        }

        Item {
            z: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                anchors.fill: parent
                id: itemsView
                visible: false

                spacing: 5
                highlightMoveDuration: 300
                highlightMoveVelocity: 500
                flickableDirection: Flickable.VerticalFlick
                //                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar {}


                delegate: ItemViewDelegate { }

                highlight: Rectangle {
                    color: "transparent"
                    border.color: Constants.itemBorderColorActive
                    border.width: Constants.itemBorderWidth
                    z: 10
                }

                function сurrentIndexAdd(value) {
                    currentIndex += value;
                    if (currentIndex >= count)
                        currentIndex = count - 1;
                }
                function currentIndexDeduct(value) {
                    currentIndex -= value;
                    if (currentIndex < 0)
                        currentIndex = 0;
                }
                function doCurrentItemAction() {
                    if (visible && count > 0) {
                        var currentItem = model[currentIndex];
                        currentItem.action();
                        if (currentItem.smartyShouldBeClosed)
                            Qt.quit();
                    }
                }
            }
        }
    }

    InputProcessor {
        id: inputProcessor;
        onProcessingStarted: {
            itemsView.visible = false;
        }
        onProcessingFinished: function (items) {
            itemsView.model = items;
            itemsView.visible = items.length > 0;
        }
    }

    Component.onCompleted: {

    }
}
