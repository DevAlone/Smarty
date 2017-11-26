import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls.Styles 1.4
import smarty.input 1.0
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
                font.pointSize: Constants.itemFontSize
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
                highlightMoveDuration: 1000
                highlightMoveVelocity: 500
                flickableDirection: Flickable.VerticalFlick
                //                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar {}


                delegate: Rectangle {
                    height: Constants.itemHeight
                    //                border.color: index == itemsView.currentIndex ? Constants.itemBorderColorActive : Constants.itemBorderColor
                    border.color: Constants.itemBorderColor
                    border.width: Constants.itemBorderWidth
                    width: parent.width
                    z: 5
                    color: Constants.itemColor

                    Text {
                        anchors.centerIn: parent
                        font.pointSize: Constants.itemFontSize
                        text: model.modelData.moduleName + ": " + model.modelData.data
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: itemsView.currentIndex = index
                    }
                }

                highlight: Rectangle {
                    color: "transparent"
                    border.color: Constants.itemBorderColorActive
                    border.width: Constants.itemBorderWidth
                    z: 10
                }

                function сurrentIndexAdd() {
                    if (currentIndex < count - 1)
                        ++currentIndex;
                }
                function currentIndexDeduct() {
                    if (currentIndex > 0)
                        --currentIndex;
                }
                function doCurrentItemAction() {
//                    console.log(JSON.stringify(model[currentIndex]));  // .modelData
                    if (visible && count > 0) {
                        var currentItem = model[currentIndex];
                        currentItem.action();
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
            console.log(items);
            console.log(items[0]);
            console.log(items[0].moduleName);

            itemsView.visible = true;
        }
    }

    Component.onCompleted: {

    }
}
