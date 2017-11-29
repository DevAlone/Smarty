import QtQuick 2.0
import QtQuick.Layouts 1.3
import smarty.models 1.0
import "constants.js" as Constants

Rectangle {
    height: Constants.itemHeight
    //                border.color: index == itemsView.currentIndex ? Constants.itemBorderColorActive : Constants.itemBorderColor
    border.color: Constants.itemBorderColor
    border.width: Constants.itemBorderWidth
    width: parent.width
    z: 5
    color: Constants.itemColor

    MouseArea {
        anchors.fill: parent
        onClicked: itemsView.currentIndex = index
    }


    Text {
        text: model.modelData.moduleName
        x: Constants.itemBorderWidth + 2
        y: Constants.itemBorderWidth + 1
        font.pointSize: Constants.itemModuleNameFontSize
        color: "#777"
        z: 2
    }

    Rectangle {
        id: itemViewContainer
        x: parent.border.width
        y: parent.border.width
        width: parent.width - 2 * parent.border.width
        height: parent.height - 2 * parent.border.width
        z: 1
    }



    Component.onCompleted: {
        var component;

        switch(model.modelData.type) {
        case ItemModel.TEXT_ITEM:
            component = Qt.createComponent("TextItemView.qml");
            break;
        default:
            component = Qt.createComponent("ItemView.qml");
            break;
        }

        var obj = component.createObject(itemViewContainer);
    }
}
