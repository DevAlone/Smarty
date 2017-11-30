import QtQuick 2.0
import QtQuick.Layouts 1.3
import smarty.models 1.0
import "constants.js" as Constants

Item {
    width: parent.width
    height: childrenRect.height

    Rectangle {
        property int padding: 25
        width: parent.width
        height: itemViewContainer.height + border.width + padding
        border.color: Constants.itemBorderColor
        border.width: Constants.itemBorderWidth
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
            x: parent.border.width + parent.padding / 2
            y: parent.border.width + parent.padding / 2
            width: parent.width - parent.border.width * 2 - parent.padding
            height: childrenRect.height
            z: 1
        }


        Component.onCompleted: {
            var path = "item_renderer/" + model.modelData.renderer + ".qml";
            var component = Qt.createComponent(path);

            if (component.status !== Component.Ready) {
                if (component.status === Component.Error)
                    console.error("Error during loading Item's renderer: " +
                                  component.errorString());

                return;
            }

            var obj = component.createObject(itemViewContainer);
        }
    }
}
